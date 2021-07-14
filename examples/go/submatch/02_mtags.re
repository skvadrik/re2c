//go:generate re2go $INPUT -o $OUTPUT
package main

import (
	"reflect"
	"testing"
)

const (
	mtagRoot int = -1
	mtagNil int = -2
)

type mtagElem struct {
	val  int
	pred int
}

type mtagTrie = []mtagElem

func createTrie(capacity int) mtagTrie {
	return make([]mtagElem, 0, capacity)
}

func mtag(trie *mtagTrie, tag int, val int) int {
	*trie = append(*trie, mtagElem{val, tag})
	return len(*trie) - 1
}

// Recursively unwind both tag histories and consruct submatches.
func unwind(trie mtagTrie, x int, y int, str string) []string {
	if x == mtagRoot && y == mtagRoot {
		return []string{}
	} else if x == mtagRoot || y == mtagRoot {
		panic("tag histories have different length")
	} else {
		xval := trie[x].val
		yval := trie[y].val
		ss := unwind(trie, trie[x].pred, trie[y].pred, str)

		// Either both tags should be nil, or none of them.
		if xval == mtagNil && yval == mtagNil {
			return ss
		} else if xval == mtagNil || yval == mtagNil {
			panic("tag histories positive/negative tag mismatch")
		} else {
			s := str[xval:yval]
			return append(ss, s)
		}
	}
}

func lex(str string) []string {
	var cursor, marker int
	trie := createTrie(256)
	x := mtagRoot
	y := mtagRoot
	/*!mtags:re2c format = "\t@@ := mtagRoot\n"; */

	/*!re2c
	re2c:flags:tags = 1;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cursor]";
	re2c:define:YYSKIP    = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";
	re2c:define:YYMTAGP   = "@@{tag} = mtag(&trie, @@{tag}, cursor)";
	re2c:define:YYMTAGN   = "@@{tag} = mtag(&trie, @@{tag}, mtagNil)";

	end = [\x00];

	(#x [a-z]+ #y [;])* end { return unwind(trie, x, y, str) }
	*                       { return nil }
	*/
}

func TestLex(t *testing.T) {
	var tests = []struct {
		str string
		res []string
	}{
		{"\000", []string{}},
		{"one;two;three;\000", []string{"one", "two", "three"}},
		{"one;two\000", nil},
	}

	for _, x := range tests {
		t.Run(x.str, func(t *testing.T) {
			res := lex(x.str)
			if !reflect.DeepEqual(res, x.res) {
				t.Errorf("got %v, want %v", res, x.res)
			}
		})
	}
}
