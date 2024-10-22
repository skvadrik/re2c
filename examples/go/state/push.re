//go:generate re2go -f $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"os"
)

// Use a small buffer to cover the case when a lexeme doesn't fit.
// In real world use a larger buffer.
const BUFSIZE int = 10

type State struct {
	file     *os.File
	yyinput  []byte
	yycursor int
	yymarker int
	yylimit  int
	token    int
	yystate  int
}

const (
	lexEnd = iota
	lexReady
	lexWaitingForInput
	lexPacketBroken
	lexPacketTooBig
)

func fill(st *State) int {
	shift := st.token
	used := st.yylimit - st.token
	free := BUFSIZE - used

	// Error: no space. In real life can reallocate a larger buffer.
	if free < 1 { return lexPacketTooBig }

	// Shift buffer contents (discard already processed data).
	copy(st.yyinput[0:], st.yyinput[shift:shift+used])
	st.yycursor -= shift
	st.yymarker -= shift
	st.yylimit -= shift
	st.token -= shift

	// Fill free space at the end of buffer with new data.
	n, _ := st.file.Read(st.yyinput[st.yylimit:BUFSIZE])
	st.yylimit += n
	st.yyinput[st.yylimit] = 0 // append sentinel symbol

	return lexReady
}

func lex(yyrecord *State, recv *int) int {
	var yych byte
	/*!getstate:re2c*/
loop:
	yyrecord.token = yyrecord.yycursor
	/*!re2c
		re2c:api = record;
		re2c:eof = 0;
		re2c:YYFILL = "return lexWaitingForInput";

		packet = [a-z]+[;];

		*      { return lexPacketBroken }
		$      { return lexEnd }
		packet { *recv = *recv + 1; goto loop }
	*/
}

func test(expect int, packets []string) {
	// Create a pipe (open the same file for reading and writing).
	fname := "pipe"
	fw, _ := os.Create(fname)
	fr, _ := os.Open(fname)

	// Initialize lexer state: `state` value is -1, all offsets are at the end
	// of buffer.
	st := &State{
		file:     fr,
		// Sentinel at `yylimit` offset is set to zero, which triggers YYFILL.
		yyinput:  make([]byte, BUFSIZE+1),
		yycursor: BUFSIZE,
		yymarker: BUFSIZE,
		yylimit:  BUFSIZE,
		token:    BUFSIZE,
		yystate:  -1,
	}

	// Main loop. The buffer contains incomplete data which appears packet by
	// packet. When the lexer needs more input it saves its internal state and
	// returns to the caller which should provide more input and resume lexing.
	var status int
	send := 0
	recv := 0
	for {
		status = lex(st, &recv)
		if status == lexEnd {
			break
		} else if status == lexWaitingForInput {
			if send < len(packets) {
				fw.WriteString(packets[send])
				send += 1
			}
			status = fill(st)
			if status != lexReady {
				break
			}
		} else if status == lexPacketBroken {
			break
		}
	}

	// Check results.
	if status != expect || (status == lexEnd && recv != send) {
		panic(fmt.Sprintf("got %d, want %d", status, expect))
	}

	// Cleanup: remove input file.
	fr.Close()
	fw.Close()
	os.Remove(fname)
}

func main() {
	test(lexEnd, []string{})
	test(lexEnd, []string{"zero;", "one;", "two;", "three;", "four;"})
	test(lexPacketBroken, []string{"??;"})
	test(lexPacketTooBig, []string{"looooooooooooong;"})
}
