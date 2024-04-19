-- re2hs $INPUT -o $OUTPUT -ci
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS

/*!conditions:re2c*/

data State = State {
    str :: !BS.ByteString,
    cur :: !Int,
    mar :: !Int,
    cond :: !YYCONDTYPE
} deriving (Show)

peek_digit :: BS.ByteString -> Int -> Int -> Int
peek_digit str idx offs = fromIntegral (BS.index str (idx - 1)) - offs

/*!re2c
    re2c:define:YYFN      = ["parse;Maybe Int", "_s;State", "_n;Int"];
    re2c:define:YYCTYPE   = "Word8";
    re2c:define:YYPEEK    = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP    = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP  = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYSHIFT   = "let _t = _s{cur = _s.cur + (@@)} in let _s = _t in";
    re2c:define:YYGETCOND = "_s.cond";
    re2c:define:YYSETCOND = "let _t = _s{cond = @@} in let _s = _t in";
    re2c:yyfill:enable    = 0;

    <init> '0b' / [01]        :=> bin
    <init> "0"                :=> oct
    <init> "" / [1-9]         :=> dec
    <init> '0x' / [0-9a-fA-F] :=> hex
    <init> * { Nothing }

    <bin> [01]  { yyfnbin _s $ _n * 2 + (peek_digit _s.str _s.cur 48) }
    <oct> [0-7] { yyfnoct _s $ _n * 8 + (peek_digit _s.str _s.cur 48) }
    <dec> [0-9] { yyfndec _s $ _n * 10 + (peek_digit _s.str _s.cur 48) }
    <hex> [0-9] { yyfnhex _s $ _n * 16 + (peek_digit _s.str _s.cur 48) }
    <hex> [a-f] { yyfnhex _s $ _n * 16 + (peek_digit _s.str _s.cur 87) }
    <hex> [A-F] { yyfnhex _s $ _n * 16 + (peek_digit _s.str _s.cur 55) }

    <bin, oct, dec, hex> * { Just _n }
*/

test :: BS.ByteString -> Maybe Int -> IO ()
test str expect = do
    let s = State {str = str, cur = 0, mar = 0, cond = YYC_init}
    when (parse s 0 /= expect) $ error "failed!"

main :: IO ()
main = do
    test "\0" Nothing
    test "1234567890\0" (Just 1234567890)
    test "0b1101\0" (Just 13)
    test "0x7Fe\0" (Just 2046)
    test "0644\0" (Just 420)
    test "9223372036854775807\0" (Just 9223372036854775807)
