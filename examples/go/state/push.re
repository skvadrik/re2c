//go:generate re2go -f $INPUT -o $OUTPUT
package main

import (
	"fmt"
	"os"
	"testing"
)

// Intentionally small to trigger buffer refill.
const SIZE int = 16

type Input struct {
	file     *os.File
	data     []byte
	cursor   int
	marker   int
	token    int
	limit    int
	state    int
	yyaccept int
}

const (
	lexEnd = iota
	lexReady
	lexWaitingForInput
	lexPacketBroken
	lexPacketTooBig
	lexCountMismatch
)

func fill(in *Input) int {
	if in.token == 0 {
		// Error: no space can be freed.
		// In real life can reallocate a larger buffer.
		return lexPacketTooBig
	}

	// Discard everything up to the start of the current lexeme,
	// shift buffer contents and adjust offsets.
	copy(in.data[0:], in.data[in.token:in.limit])
	in.cursor -= in.token
	in.marker -= in.token
	in.limit -= in.token
	in.token = 0

	// Read new data (as much as possible to fill the buffer).
	n, _ := in.file.Read(in.data[in.limit:SIZE])
	in.limit += n
	in.data[in.limit] = 0 // append sentinel symbol

	return lexReady
}

func lex(in *Input, recv *int) int {
	var yych byte
	/*!getstate:re2c*/
loop:
	in.token = in.cursor
	/*!re2c
	re2c:eof = 0;
	re2c:define:YYPEEK     = "in.data[in.cursor]";
	re2c:define:YYSKIP     = "in.cursor += 1";
	re2c:define:YYBACKUP   = "in.marker = in.cursor";
	re2c:define:YYRESTORE  = "in.cursor = in.marker";
	re2c:define:YYLESSTHAN = "in.limit <= in.cursor";
	re2c:define:YYFILL     = "return lexWaitingForInput";
	re2c:define:YYGETSTATE = "in.state";
	re2c:define:YYSETSTATE = "in.state = @@{state}";

	packet = [a-z]+[;];

	*      { return lexPacketBroken }
	$      { return lexEnd }
	packet { *recv = *recv + 1; goto loop }
	*/
}

func test(packets []string) int {
	fname := "pipe"
	fw, _ := os.Create(fname);
	fr, _ := os.Open(fname);

	in := &Input{
		file:   fr,
		data:   make([]byte, SIZE+1),
		cursor: SIZE,
		marker: SIZE,
		token:  SIZE,
		limit:  SIZE,
		state:  -1,
	}
	// data is zero-initialized, no need to write sentinel

	var status int
	send := 0
	recv := 0
loop:
	for {
		status = lex(in, &recv)
		if status == lexEnd {
			if send != recv {
				status = lexCountMismatch
			}
			break loop
		} else if status == lexWaitingForInput {
			if send < len(packets) {
				fw.WriteString(packets[send])
				send += 1
			}
			status = fill(in)
			if status != lexReady {
				break loop
			}
		} else if status == lexPacketBroken {
			break loop
		} else {
			panic("unexpected status")
		}
	}

	fr.Close()
	fw.Close()
	os.Remove(fname)

	return status
}

func TestLex(t *testing.T) {
	var tests = []struct {
		status  int
		packets []string
	}{
		{lexEnd, []string{}},
		{lexEnd, []string{"zero;", "one;", "two;", "three;", "four;"}},
		{lexPacketBroken, []string{"??;"}},
		{lexPacketTooBig, []string{"looooooooooooong;"}},
	}

	for i, x := range tests {
		t.Run(fmt.Sprintf("%d", i), func(t *testing.T) {
			status := test(x.packets)
			if status != x.status {
				t.Errorf("got %d, want %d", status, x.status)
			}
		})
	}
}
