//go:generate re2go $INPUT -o $OUTPUT --recursive-functions -i
package main

import "errors"

const u32Limit uint64 = 1<<32
var (
	eSyntax   = errors.New("syntax error")
	eOverflow = errors.New("overflow error")
)

func adddgt(base uint64, digit byte, result uint64) uint64 {
	result = result * base + uint64(digit)
	if result >= u32Limit {
		result = u32Limit
	}
	return result
}

/*!re2c
	re2c:yyfill:enable = 0;
	re2c:define:YYFN = [
		"lex;(uint64, error)", "str;string", "cur;int", "mar;int", "result;uint64"];
	re2c:define:YYCTYPE   = byte;
	re2c:define:YYPEEK    = "str[cur]";
	re2c:define:YYSKIP    = "cur += 1";
	re2c:define:YYSHIFT   = "cur += @@{shift}";
	re2c:define:YYBACKUP  = "mar = cur";
	re2c:define:YYRESTORE = "cur = mar";

	end = "\x00";

	'0b' / [01]        { return lex_bin(str, cur, mar, result) }
	"0"                { return lex_oct(str, cur, mar, result) }
	""   / [1-9]       { return lex_dec(str, cur, mar, result) }
	'0x' / [0-9a-fA-F] { return lex_hex(str, cur, mar, result) }
	*                  { return 0, eSyntax }
*/

/*!re2c
	re2c:define:YYFN = [
		"lex_bin;(uint64, error)", "str;string", "cur;int", "mar;int", "result;uint64"];
	end   { return result, nil }
	[01]  { result = adddgt(2, str[cur-1]-'0', result); return lex_bin(str, cur, mar, result) }
	*     { return 0, eSyntax }
*/

/*!re2c
	re2c:define:YYFN = [
		"lex_oct;(uint64, error)", "str;string", "cur;int", "mar;int", "result;uint64"];
	end   { return result, nil }
	[0-7] { result = adddgt(8, str[cur-1]-'0', result); return lex_oct(str, cur, mar, result) }
	*     { return 0, eSyntax }
*/

/*!re2c
	re2c:define:YYFN = [
		"lex_dec;(uint64, error)", "str;string", "cur;int", "mar;int", "result;uint64"];
	end   { return result, nil }
	[0-9] { result = adddgt(10, str[cur-1]-'0', result); return lex_dec(str, cur, mar, result) }
	*     { return 0, eSyntax }
*/

/*!re2c
	re2c:define:YYFN = [
		"lex_hex;(uint64, error)", "str;string", "cur;int", "mar;int", "result;uint64"];
	end   { return result, nil }
	[0-9] { result = adddgt(16, str[cur-1]-'0', result);    return lex_hex(str, cur, mar, result) }
	[a-f] { result = adddgt(16, str[cur-1]-'a'+10, result); return lex_hex(str, cur, mar, result) }
	[A-F] { result = adddgt(16, str[cur-1]-'A'+10, result); return lex_hex(str, cur, mar, result) }
	*     { return 0, eSyntax }
*/

func parse_u32(str string) (uint32, error) {
	result, err := lex(str, 0, 0, uint64(0))
	if err != nil {
		return 0, err
	} else if result < u32Limit {
		return uint32(result), nil
	} else {
		return 0, eOverflow
	}
}

func main() {
	test := func(num uint32, str string, err error) {
		if n, e := parse_u32(str); !(n == num && e == err) {
			panic("error")
		}
	}
	test(1234567890, "1234567890\000", nil)
	test(13, "0b1101\000", nil)
	test(0x7fe, "0x007Fe\000", nil)
	test(0644, "0644\000", nil)
	test(0, "9999999999\000", eOverflow)
	test(0, "123??\000", eSyntax)
}
