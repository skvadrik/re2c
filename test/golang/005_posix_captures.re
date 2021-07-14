//go:generate re2go $INPUT -o $OUTPUT 
package main

import "reflect"

/*!maxnmatch:re2c*/

func Lex(str string) (int, []int) {
	var cursor, marker, yynmatch int
	yypmatch := make([]int, YYMAXNMATCH*2)

	/*!stags:re2c format = "\tvar @@ int\n"; */

	/*!re2c
	re2c:flags:posix-captures = 1;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";
	re2c:define:YYSTAGP = "@@{tag} = cursor";
	re2c:define:YYSTAGN = "@@{tag} = -1";
	re2c:define:YYSHIFTSTAG = "@@{tag} += @@{shift}";

	end = [\x00];

	* {
		return -1, nil
	}

	([a]+) ([b]) ([c]+) end {
		return yynmatch, yypmatch
	}

	(([a]+) | ([b]+) | ([c]+)) end {
		return yynmatch, yypmatch
	}

	(([a]) ([b])? ([c]))* end {
		return yynmatch, yypmatch
	}
	*/
}

func main() {
	var n int
	var m []int

	n, m = Lex("aabcc\000")
	if !(n == 4 && reflect.DeepEqual(m[0:2*n], []int{0, 6, 0, 2, 2, 3, 3, 5})) {
		panic("failed on aabcc")
	}
	n, m = Lex("aaa\000")
	if !(n == 5 && reflect.DeepEqual(m[0:2*n], []int{0, 4, 0, 3, 0, 3, -1, -1, -1, -1})) {
		panic("failed on aaa")
	}
	n, m = Lex("acabc\000")
	if !(n == 5 && reflect.DeepEqual(m[0:2*n], []int{0, 6, 2, 5, 2, 3, 3, 4, 4, 5})) {
		panic("failed on acabc")
	}
	n, m = Lex("abcac\000")
	if !(n == 5 && reflect.DeepEqual(m[0:2*n], []int{0, 6, 3, 5, 3, 4, -1, -1, 4, 5})) {
		panic("failed on abcac")
	}
	n, m = Lex("ab\000")
	if !(n == -1 && m == nil) {
		panic("failed on ab")
	}
}
