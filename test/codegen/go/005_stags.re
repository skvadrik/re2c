//go:generate re2go $INPUT -o $OUTPUT 
package main

func Lex(str string) (a int, b int, c int) {
	var cursor, marker int
	/*!stags:re2c format = "\tvar @@ int\n"; */

	/*!re2c
	re2c:flags:tags = 1;
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
		return -2, -2, -2
	}

	@a [a]+ @b [b] @c [c]+ end {
		return a, b, c
	}

	(@a [a]+ | @b [b]+ | @c [c]+) end {
		return a, b, c
	}

	(@a [a] (@b [b])? @c [c])* end {
		return a, b, c
	}
	*/
}

func main() {
	if a, b, c := Lex("aabcc\000"); !(a == 0 && b == 2 && c == 3) {
		panic("expected 0,2,3")
	}
	if a, b, c := Lex("aaa\000"); !(a == 0 && b == -1 && c == -1) {
		panic("expected 0,-1,-1")
	}
	if a, b, c := Lex("acabc\000"); !(a == 2 && b == 3 && c == 4) {
		panic("expected 2,3,4")
	}
	if a, b, c := Lex("abcac\000"); !(a == 3 && b == -1 && c == 4) {
		panic("expected 3,-1,4")
	}
	if a, b, c := Lex("ab\000"); !(a == -2 && b == -2 && c == -2) {
		panic("expected -2,-2,-2")
	}
}
