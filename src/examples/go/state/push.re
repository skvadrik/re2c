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
	file  *os.File
	buf   []byte
	cur   int
	mar   int
	tok   int
	lim   int
	state int
}

const (
	lexEnd = iota
	lexReady
	lexWaitingForInput
	lexPacketBroken
	lexPacketTooBig
)

func fill(st *State) int {
	shift := st.tok
	used := st.lim - st.tok
	free := BUFSIZE - used

	// Error: no space. In real life can reallocate a larger buffer.
	if free < 1 { return lexPacketTooBig }

	// Shift buffer contents (discard already processed data).
	copy(st.buf[0:], st.buf[shift:shift+used])
	st.cur -= shift
	st.mar -= shift
	st.lim -= shift
	st.tok -= shift

	// Fill free space at the end of buffer with new data.
	n, _ := st.file.Read(st.buf[st.lim:BUFSIZE])
	st.lim += n
	st.buf[st.lim] = 0 // append sentinel symbol

	return lexReady
}

func lex(st *State, recv *int) int {
	var yych byte
	/*!getstate:re2c*/
loop:
	st.tok = st.cur
	/*!re2c
		re2c:eof = 0;
		re2c:define:YYPEEK     = "st.buf[st.cur]";
		re2c:define:YYSKIP     = "st.cur += 1";
		re2c:define:YYBACKUP   = "st.mar = st.cur";
		re2c:define:YYRESTORE  = "st.cur = st.mar";
		re2c:define:YYLESSTHAN = "st.lim <= st.cur";
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
	// of buffer.
	st := &State{
		file:  fr,
		// Sentinel at `lim` offset is set to zero, which triggers YYFILL.
		buf:   make([]byte, BUFSIZE+1),
		cur:   BUFSIZE,
		mar:   BUFSIZE,
		tok:   BUFSIZE,
		lim:   BUFSIZE,
		state: -1,
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
