// Code generated by re2go, DO NOT EDIT.
//line "go/reuse/usedir.re":1
//go:generate re2go $INPUT -o $OUTPUT --api simple
package main

// This example shows how to combine reusable re2c blocks: two blocks
// ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
// in both blocks; the 'fish' block takes priority because it is used
// earlier. Default rule * occurs in all three blocks; the local (not
// inherited) definition takes priority.

const (
	Color = iota
	Fish
	Dunno
)

//line "go/reuse/usedir.re":19


//line "go/reuse/usedir.re":24


func lex(yyinput string) int {
	var yycursor, yymarker int
	
//line "go/reuse/usedir.go":28
{
	var yych byte
	yych = yyinput[yycursor]
	switch (yych) {
	case 'e':
		goto yy3
	case 'h':
		goto yy4
	case 'm':
		goto yy5
	case 'r':
		goto yy6
	case 's':
		goto yy7
	default:
		goto yy1
	}
yy1:
	yycursor += 1
yy2:
//line "go/reuse/usedir.re":34
	{ return Dunno }
//line "go/reuse/usedir.go":51
yy3:
	yycursor += 1
	yymarker = yycursor
	yych = yyinput[yycursor]
	switch (yych) {
	case 'e':
		goto yy8
	default:
		goto yy2
	}
yy4:
	yycursor += 1
	yymarker = yycursor
	yych = yyinput[yycursor]
	switch (yych) {
	case 'a':
		goto yy10
	default:
		goto yy2
	}
yy5:
	yycursor += 1
	yymarker = yycursor
	yych = yyinput[yycursor]
	switch (yych) {
	case 'a':
		goto yy11
	default:
		goto yy2
	}
yy6:
	yycursor += 1
	yymarker = yycursor
	yych = yyinput[yycursor]
	switch (yych) {
	case 'e':
		goto yy12
	default:
		goto yy2
	}
yy7:
	yycursor += 1
	yymarker = yycursor
	yych = yyinput[yycursor]
	switch (yych) {
	case 'a':
		goto yy13
	default:
		goto yy2
	}
yy8:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'l':
		goto yy14
	default:
		goto yy9
	}
yy9:
	yycursor = yymarker
	goto yy2
yy10:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'd':
		goto yy15
	default:
		goto yy9
	}
yy11:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'g':
		goto yy16
	default:
		goto yy9
	}
yy12:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'd':
		goto yy17
	default:
		goto yy9
	}
yy13:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'l':
		goto yy18
	default:
		goto yy9
	}
yy14:
	yycursor += 1
//line "go/reuse/usedir.re":23
	{ return Fish }
//line "go/reuse/usedir.go":154
yy15:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'd':
		goto yy19
	default:
		goto yy9
	}
yy16:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'e':
		goto yy20
	default:
		goto yy9
	}
yy17:
	yycursor += 1
//line "go/reuse/usedir.re":18
	{ return Color }
//line "go/reuse/usedir.go":177
yy18:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'm':
		goto yy21
	default:
		goto yy9
	}
yy19:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'o':
		goto yy22
	default:
		goto yy9
	}
yy20:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'n':
		goto yy23
	default:
		goto yy9
	}
yy21:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'o':
		goto yy24
	default:
		goto yy9
	}
yy22:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'c':
		goto yy25
	default:
		goto yy9
	}
yy23:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 't':
		goto yy26
	default:
		goto yy9
	}
yy24:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'n':
		goto yy14
	default:
		goto yy9
	}
yy25:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'k':
		goto yy14
	default:
		goto yy9
	}
yy26:
	yycursor += 1
	yych = yyinput[yycursor]
	switch (yych) {
	case 'a':
		goto yy17
	default:
		goto yy9
	}
}
//line "go/reuse/usedir.re":35

}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(lex("salmon"), Fish);
	assert_eq(lex("what?"), Dunno);
}