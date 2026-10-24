//go:generate re2go $INPUT -o $OUTPUT -i
// Packed reads must apply the same byte conversion as scalar reads.
package main

import "fmt"

/*!rules:re2c:wide
	re2c:api = simple;
	re2c:YYCTYPE = byte;
	re2c:yych:conversion = 1;
	re2c:yyfill:enable = 0;
	"abcdefgh" { return 1, yycursor }
	*          { return 0, yycursor }
	[\x00]     { return -1, yycursor }
*/

func wideScalar(yyinput []uint16) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:wide re2c:vectorize:linear = 0; */
}

func wideVector(yyinput []uint16) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:wide re2c:vectorize:linear = 1; */
}

/*!rules:re2c:signed
	re2c:api = simple;
	re2c:YYCTYPE = uint8;
	re2c:yych:conversion = 1;
	re2c:yyfill:enable = 0;
	"a" "\x80\xff\xff\xff\xff\xff\xff\xff" "z" { return 1, yycursor }
	*          { return 0, yycursor }
	[\x00]     { return -1, yycursor }
*/

func signedScalar(yyinput []int8) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:signed re2c:vectorize:linear = 0; */
}

func signedVector(yyinput []int8) (int, int) {
	yycursor, yymarker := 0, 0
	_ = yymarker
	/*!use:re2c:signed re2c:vectorize:linear = 1; */
}

func main() {
	failures := 0
	check := func(name string, r0, c0, r1, c1, rule, cursor int) {
		if r0 != rule || c0 != cursor || r1 != rule || c1 != cursor {
			fmt.Printf("%s: scalar=(%d,%d) vector=(%d,%d) want=(%d,%d)\n",
				name, r0, c0, r1, c1, rule, cursor)
			failures++
		}
	}
	for _, tc := range []struct {
		name string
		input []uint16
		rule, cursor int
	}{
		{"wide probe", []uint16{'a', 0x6362, 0, 'd', 'e', 'f', 'g', 'h', 0}, 0, 1},
		{"wide exact", []uint16{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 0}, 1, 8},
		{"wide truncated", []uint16{0x161, 0x262, 0x363, 0x464, 0x565, 0x666, 0x767, 0x868, 0}, 1, 8},
		{"wide near miss", []uint16{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'i', 0}, 0, 1},
		{"wide sentinel", []uint16{0x100}, -1, 1},
	} {
		r0, c0 := wideScalar(tc.input)
		r1, c1 := wideVector(tc.input)
		check(tc.name, r0, c0, r1, c1, tc.rule, tc.cursor)
	}
	for _, tc := range []struct {
		name string
		input []int8
		rule, cursor int
	}{
		{"signed probe", []int8{'a', -128, 0, 0, 0, 0, 0, 0, 0, 'z', 0}, 0, 1},
		{"signed exact", []int8{'a', -128, -1, -1, -1, -1, -1, -1, -1, 'z', 0}, 1, 10},
		{"signed near miss", []int8{'a', -128, -1, -1, -1, -1, -1, -1, -1, 'y', 0}, 0, 1},
		{"signed sentinel", []int8{0}, -1, 1},
	} {
		r0, c0 := signedScalar(tc.input)
		r1, c1 := signedVector(tc.input)
		check(tc.name, r0, c0, r1, c1, tc.rule, tc.cursor)
	}
	if failures != 0 {
		panic(fmt.Sprintf("%d conversion checks failed", failures))
	}
}
