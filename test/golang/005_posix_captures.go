// Code generated by re2c, DO NOT EDIT.
//line "golang/005_posix_captures.re":1
//go:generate re2go $INPUT -o $OUTPUT 
package main

import "reflect"

//line "golang/005_posix_captures.go":9
const YYMAXNMATCH = 5
//line "golang/005_posix_captures.re":6


func Lex(str string) (int, []int) {
	var cursor, marker, yynmatch int
	yypmatch := make([]int, YYMAXNMATCH*2)

	
//line "golang/005_posix_captures.go":19
	var yyt1 int
	var yyt2 int
	var yyt3 int
	var yyt4 int
	var yyt5 int
	var yyt6 int
	var yyt7 int
//line "golang/005_posix_captures.re":12


	
//line "golang/005_posix_captures.go":31
{
	var yych byte
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt1 = cursor
		yyt2 = -1
		yyt3 = -1
		yyt4 = -1
		goto yy1
	case 'a':
		yyt1 = cursor
		yyt3 = cursor
		goto yy4
	case 'b':
		yyt1 = cursor
		yyt3 = -1
		yyt4 = -1
		yyt5 = cursor
		goto yy5
	case 'c':
		yyt1 = cursor
		yyt3 = -1
		yyt4 = -1
		yyt5 = -1
		yyt6 = -1
		yyt7 = cursor
		goto yy6
	default:
		goto yy2
	}
yy1:
	cursor += 1
	yynmatch = 5
	yypmatch[0] = yyt1
	yypmatch[3] = yyt2
	yypmatch[5] = yyt3
	yypmatch[7] = yyt4
	yypmatch[1] = cursor
	yypmatch[2] = yyt3
	yypmatch[4] = yyt3
	yypmatch[6] = yyt4
	yypmatch[8] = yyt2
	yypmatch[9] = yyt2
	/* materialize no-match value */
	yyt3 = -1
	if (yypmatch[2] != yyt3) {
		yypmatch[2] += -1
	}
	if (yypmatch[4] != yyt3) {
		yypmatch[4] += -1
	}
	if (yypmatch[6] != yyt3) {
		yypmatch[6] += -1
	}
	if (yypmatch[8] != yyt3) {
		yypmatch[8] += -1
	}
//line "golang/005_posix_captures.re":40
	{
		return yynmatch, yypmatch
	}
//line "golang/005_posix_captures.go":94
yy2:
	cursor += 1
yy3:
//line "golang/005_posix_captures.re":28
	{
		return -1, nil
	}
//line "golang/005_posix_captures.go":102
yy4:
	cursor += 1
	marker = cursor
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = -1
		yyt4 = cursor
		yyt5 = -1
		yyt6 = -1
		yyt7 = -1
		goto yy7
	case 'a':
		goto yy8
	case 'b':
		goto yy10
	case 'c':
		yyt3 = cursor
		yyt4 = -1
		goto yy11
	default:
		goto yy3
	}
yy5:
	cursor += 1
	marker = cursor
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = -1
		yyt6 = cursor
		yyt7 = -1
		goto yy7
	case 'b':
		goto yy12
	default:
		goto yy3
	}
yy6:
	cursor += 1
	marker = cursor
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = cursor
		goto yy7
	case 'c':
		goto yy13
	default:
		goto yy3
	}
yy7:
	cursor += 1
	yynmatch = 5
	yypmatch[2] = yyt1
	yypmatch[4] = yyt3
	yypmatch[5] = yyt4
	yypmatch[6] = yyt5
	yypmatch[7] = yyt6
	yypmatch[8] = yyt7
	yypmatch[9] = yyt2
	yypmatch[0] = yyt1
	yypmatch[1] = cursor
	yypmatch[3] = cursor
	yypmatch[3] += -1
//line "golang/005_posix_captures.re":36
	{
		return yynmatch, yypmatch
	}
//line "golang/005_posix_captures.go":172
yy8:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = -1
		yyt4 = cursor
		yyt5 = -1
		yyt6 = -1
		yyt7 = -1
		goto yy7
	case 'a':
		goto yy8
	case 'b':
		goto yy14
	default:
		goto yy9
	}
yy9:
	cursor = marker
	goto yy3
yy10:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 'c':
		yyt2 = cursor
		goto yy15
	default:
		goto yy9
	}
yy11:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = cursor
		goto yy1
	case 'a':
		goto yy16
	default:
		goto yy9
	}
yy12:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = -1
		yyt6 = cursor
		yyt7 = -1
		goto yy7
	case 'b':
		goto yy12
	default:
		goto yy9
	}
yy13:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 0x00:
		yyt2 = cursor
		goto yy7
	case 'c':
		goto yy13
	default:
		goto yy9
	}
yy14:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 'c':
		yyt2 = cursor
		goto yy17
	default:
		goto yy9
	}
yy15:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 'a':
		goto yy16
	default:
		goto yy18
	}
yy16:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 'b':
		yyt3 = cursor
		goto yy20
	case 'c':
		yyt3 = cursor
		yyt4 = -1
		goto yy11
	default:
		goto yy9
	}
yy17:
	cursor += 1
	yych = str[cursor]
yy18:
	switch (yych) {
	case 0x00:
		goto yy19
	case 'c':
		goto yy17
	default:
		goto yy9
	}
yy19:
	cursor += 1
	yynmatch = 4
	yypmatch[2] = yyt1
	yypmatch[6] = yyt2
	yypmatch[0] = yyt1
	yypmatch[1] = cursor
	yypmatch[3] = yyt2
	yypmatch[3] += -1
	yypmatch[4] = yyt2
	yypmatch[4] += -1
	yypmatch[5] = yyt2
	yypmatch[7] = cursor
	yypmatch[7] += -1
//line "golang/005_posix_captures.re":32
	{
		return yynmatch, yypmatch
	}
//line "golang/005_posix_captures.go":305
yy20:
	cursor += 1
	yych = str[cursor]
	switch (yych) {
	case 'c':
		yyt4 = cursor
		goto yy11
	default:
		goto yy9
	}
}
//line "golang/005_posix_captures.re":43

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
