//go:generate re2go $INPUT -o $OUTPUT -i --api simple --vectorize-linear
package main

import (
	"encoding/binary"
	"fmt"
)

var curInput string

func YYPEEKN(cur int, n int) uint64 {
	if cur+n > len(curInput) {
		return 0
	}
	var buf [8]byte
	copy(buf[:], curInput[cur:cur+n])
	return binary.LittleEndian.Uint64(buf[:])
}

const (
	TokUnknown = 0
	TokSelect  = 1
	TokInsert  = 2
	TokUpdate  = 3
	TokDelete  = 4
	TokFrom    = 5
	TokWhere   = 6
)

// LexKeyword reconnaît un mot-clé avec le fast-path broadword vectorisé.
func LexKeyword(yyinput string) int {
	curInput = yyinput
	var yycursor int
	var yymarker int

	/*!re2c
	re2c:YYCTYPE = byte;
	re2c:yyfill:enable = 0;
	re2c:vectorize:linear = 1;

	*              { return TokUnknown }
	"SELECT\x00"   { return TokSelect }
	"INSERT\x00"   { return TokInsert }
	"UPDATE\x00"   { return TokUpdate }
	"DELETE\x00"   { return TokDelete }
	"FROM\x00"     { return TokFrom }
	"WHERE\x00"    { return TokWhere }
	*/
}

// LexKeywordScalar reconnaît le même mot-clé avec l'automate scalaire conventionnel.
func LexKeywordScalar(yyinput string) int {
	var yycursor int
	var yymarker int

	/*!re2c
	re2c:YYCTYPE = byte;
	re2c:yyfill:enable = 0;
	re2c:vectorize:linear = 0;

	*              { return TokUnknown }
	"SELECT\x00"   { return TokSelect }
	"INSERT\x00"   { return TokInsert }
	"UPDATE\x00"   { return TokUpdate }
	"DELETE\x00"   { return TokDelete }
	"FROM\x00"     { return TokFrom }
	"WHERE\x00"    { return TokWhere }
	*/
}

func main() {
	fmt.Printf("Vectorized SELECT -> %d\n", LexKeyword("SELECT\x00"))
	fmt.Printf("Scalar     SELECT -> %d\n", LexKeywordScalar("SELECT\x00"))
	fmt.Printf("Vectorized FROM   -> %d\n", LexKeyword("FROM\x00"))
	fmt.Printf("Scalar     FROM   -> %d\n", LexKeywordScalar("FROM\x00"))
}
