-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    str :: !BS.ByteString,
    cur :: !Int,
    mar :: !Int
} deriving (Show)

peek_digit :: BS.ByteString -> Int -> Int -> Int
peek_digit str idx offs = fromIntegral (BS.index str (idx - 1)) - offs

/*!re2c
    re2c:define:YYCTYPE   = "Word8";
    re2c:define:YYPEEK    = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP    = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP  = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYSHIFT   = "let _t = _s{cur = _s.cur + (@@)} in let _s = _t in";
    re2c:yyfill:enable    = 0;
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_bin;Int", "_s;State", "num;Int"];
    [01] { parse_bin _s $ num * 2 + (peek_digit _s.str _s.cur 48) }
    *    { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_oct;Int", "_s;State", "num;Int"];
    [0-7] { parse_oct _s $ num * 8 + (peek_digit _s.str _s.cur 48) }
    *     { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_dec;Int", "_s;State", "num;Int"];
    [0-9] { parse_dec _s $ num * 10 + (peek_digit _s.str _s.cur 48) }
    *     { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse_hex;Int", "_s;State", "num;Int"];
    [0-9] { parse_hex _s $ num * 16 + (peek_digit _s.str _s.cur 48) }
    [a-f] { parse_hex _s $ num * 16 + (peek_digit _s.str _s.cur 87) }
    [A-F] { parse_hex _s $ num * 16 + (peek_digit _s.str _s.cur 55) }
    *     { num }
*/

/*!local:re2c
    re2c:define:YYFN = ["parse;Maybe Int", "_s;State"];
    '0b' / [01]        { Just $ parse_bin _s 0 }
    "0"                { Just $ parse_oct _s 0 }
    "" / [1-9]         { Just $ parse_dec _s 0 }
    '0x' / [0-9a-fA-F] { Just $ parse_hex _s 0 }
    *                  { Nothing }
*/

test :: BS.ByteString -> Maybe Int -> IO ()
test str expect = do
    let s = State {str = str, cur = 0, mar = 0}
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "\0" Nothing
    test "1234567890\0" (Just 1234567890)
    test "0b1101\0" (Just 13)
    test "0x7Fe\0" (Just 2046)
    test "0644\0" (Just 420)
    test "9223372036854775807\0" (Just 9223372036854775807)
