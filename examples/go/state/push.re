//go:generate re2go -f $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"os"
)

// Intentionally small to trigger buffer refill.
const BUFSIZE int = 10

type State struct {
	file   *os.File
	data   []byte
	cursor int
	marker int
	token  int
	limit  int
	state  int
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
	used := st.limit - st.token
	free := BUFSIZE - used

	// Error: no space. In real life can reallocate a larger buffer.
	if free < 1 { return lexPacketTooBig }

	// Shift buffer contents (discard already processed data).
	copy(st.data[0:], st.data[shift:shift+used])
	st.cursor -= shift
	st.marker -= shift
	st.limit -= shift
	st.token -= shift

	// Fill free space at the end of buffer with new data.
	n, _ := st.file.Read(st.data[st.limit:BUFSIZE])
	st.limit += n
	st.data[st.limit] = 0 // append sentinel symbol

	return lexReady
}

func lex(st *State, recv *int) int {
	var yych byte
	/*!getstate:re2c*/
loop:
	st.token = st.cursor
	/*!re2c
		re2c:eof = 0;
		re2c:define:YYPEEK     = "st.data[st.cursor]";
		re2c:define:YYSKIP     = "st.cursor += 1";
		re2c:define:YYBACKUP   = "st.marker = st.cursor";
		re2c:define:YYRESTORE  = "st.cursor = st.marker";
		re2c:define:YYLESSTHAN = "st.limit <= st.cursor";
		re2c:define:YYFILL     = "return lexWaitingForInput";
		re2c:define:YYGETSTATE = "st.state";
		re2c:define:YYSETSTATE = "st.state = @@{state}";

		packet = [a-z]+[;];

		*      { return lexPacketBroken }
		$      { return lexEnd }
		packet { *recv = *recv + 1; goto loop }
	*/
}

func test(expect int, packets []string) {
	// Create a "socket" (open the same file for reading and writing).
	fname := "pipe"
	fw, _ := os.Create(fname)
	fr, _ := os.Open(fname)

	// Initialize lexer state: `state` value is -1, all offsets are at the end
	// of buffer, the character at `lim` offset is the sentinel (null).
	st := &State{
		file:   fr,
		data:   make([]byte, BUFSIZE+1),
		cursor: BUFSIZE,
		marker: BUFSIZE,
		token:  BUFSIZE,
		limit:  BUFSIZE,
		state:  -1,
	}
	// data is zero-initialized, no need to write sentinel

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
