//go:generate re2go $INPUT -o $OUTPUT -ir
package main

import "fmt"
import "reflect"

type mtagElem struct {
	tag, pred int
}

type mtagTrie = []mtagElem

func createPool(capacity int) mtagTrie {
	return make([]mtagElem, 0, capacity)
}

func mtag(mt *mtagTrie, tag int, val int) int {
	*mt = append(*mt, mtagElem{val, tag})
	return len(*mt) - 1
}

const mtagRoot int = -1

/*!rules:re2c
	re2c:flags:tags = 1;
	re2c:yyfill:enable = 0;
	re2c:define:YYCTYPE = byte;
	re2c:define:YYPEEK = "str[cursor]";
	re2c:define:YYSKIP = "cursor += 1";
	re2c:define:YYBACKUP  = "marker = cursor";
	re2c:define:YYRESTORE = "cursor = marker";
	re2c:define:YYSTAGP = "@@ = cursor";
	re2c:define:YYSTAGN = "@@ = -1";

	end = [\x00];

	#a [a]+ #b [b] @c [c]+ end        { return }
	(#a [a]+ | #b [b]+ | @c [c]+) end { return }
	(#a [a] (#b [b])? @c [c])* end    { return }
*/

func LexSlices(str string) (a []int, b []int, c int) {
	var cursor, marker int

	/*!stags:re2c
	format = "var @@ int";
	separator = "\n\t";
	*/

	/*!mtags:re2c
	format = "var @@ []int";
	separator = "\n\t";
	*/

	/*!use:re2c
	re2c:define:YYMTAGP = "@@ = append(@@, cursor)";
	re2c:define:YYMTAGN = "@@ = append(@@, -1)";

	* {return nil, nil, -2 }
	*/
}

func LexTrie(str string) (mt mtagTrie, a int, b int, c int) {
	var cursor, marker int
	mt = createPool(256)

	/*!stags:re2c
	format = "var @@ int";
	separator = "\n\t";
	*/

	/*!mtags:re2c
	format = "@@ := mtagRoot";
	separator = "\n\t";
	*/

	/*!use:re2c
	re2c:define:YYMTAGP = "@@ = mtag(&mt, @@, cursor)";
	re2c:define:YYMTAGN = "@@ = mtag(&mt, @@, -1)";

	* { return mt, -2, -2, -2 }
	*/
}

func cmp(str string, a, aref []int, b, bref []int, c, cref int) {
	if !(reflect.DeepEqual(a, aref) && reflect.DeepEqual(b, bref) && c == cref) {
		panic(fmt.Sprintf("failed %s: expected a=%v, b=%v, c=%v, got a=%v, b=%v, c=%v",
			str, aref, bref, cref, a, b, c))
	}
}

func testSlices(str string, aref []int, bref []int, cref int) {
	a, b, c := LexSlices(str)
	cmp(str, a, aref, b, bref, c, cref)
}

func testTrie(str string, aref []int, bref []int, cref int) {
	mt, a, b, c := LexTrie(str)
	cmp(str, unwind(mt, a), aref, unwind(mt, b), bref, c, cref)
}

func unwind(mt mtagTrie, tag int) []int {
	if tag == mtagRoot {
		return []int{}
	} else if tag > mtagRoot && tag < len(mt) {
		e := mt[tag]
		return append(unwind(mt, e.pred), e.tag)
	} else {
		return nil
	}
}

func test(str string, aref []int, bref []int, cref int) {
	testSlices(str, aref, bref, cref)
	testTrie(str, aref, bref, cref)
}

func main() {
	test("aabcc\000", []int{0}, []int{2}, 3)
	test("aaa\000", []int{0}, []int{-1}, -1)
	test("acabc\000", []int{0, 2}, []int{-1, 3}, 4)
	test("abcac\000", []int{0, 3}, []int{1, -1}, 4)
	test("ab\000", nil, nil, -2)
}
