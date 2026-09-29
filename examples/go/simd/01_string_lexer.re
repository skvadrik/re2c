//go:generate re2go $INPUT -o $OUTPUT -i --api simple --vectorize-loops
//go:build goexperiment.simd && (amd64 || arm64)

package main

import (
	"fmt"
	"simd/archsimd"
)

// LexString scanne une tranche d'octets délimitée par des guillemets avec Fast-Forward SIMD.
// Accepte []byte (standard zéro-allocation Go) et retourne la longueur du contenu extrait ou -1.
func LexString(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)

	if yycursor >= yylimit || yyinput[yycursor] != '"' {
		return -1
	}
	yycursor++
	start := yycursor

	for {
		/*!re2c
		re2c:vectorize:loops = 1;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "return -1";
		re2c:YYFILL:naked = 1;

		*               { return -1 }
		"\""            { return yycursor - start - 1 }
		"\\"            {
			if yycursor >= yylimit { return -1 }
			esc := yyinput[yycursor]
			if esc == '\\' || esc == '"' || esc == '/' || esc == 'b' || esc == 'f' || esc == 'n' || esc == 'r' || esc == 't' {
				yycursor++
				continue
			}
			return -1
		}
		[^"\\\x00\n\r]+ { continue }
		*/
	}
}

// LexStringScalar scanne une tranche d'octets de manière scalaire pour servir de baseline.
func LexStringScalar(yyinput []byte) int {
	var yycursor int
	yylimit := len(yyinput)

	if yycursor >= yylimit || yyinput[yycursor] != '"' {
		return -1
	}
	yycursor++
	start := yycursor

	for {
		/*!re2c
		re2c:vectorize:loops = 0;
		re2c:YYCTYPE = byte;
		re2c:YYFILL = "return -1";
		re2c:YYFILL:naked = 1;

		*               { return -1 }
		"\""            { return yycursor - start - 1 }
		"\\"            {
			if yycursor >= yylimit { return -1 }
			esc := yyinput[yycursor]
			if esc == '\\' || esc == '"' || esc == '/' || esc == 'b' || esc == 'f' || esc == 'n' || esc == 'r' || esc == 't' {
				yycursor++
				continue
			}
			return -1
		}
		[^"\\\x00\n\r]+ { continue }
		*/
	}
}

func main() {
	sample := []byte("\"Identifiant_Systeme_Tres_Long_Sans_Echappement_Pour_Prouver_Le_Debit_SIMD\"\x00")
	length := LexString(sample)
	fmt.Printf("Longueur extraite : %d\n", length)
}
