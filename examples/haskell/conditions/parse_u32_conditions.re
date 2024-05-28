-- re2hs $INPUT -o $OUTPUT -ci
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS

/*!conditions:re2c*/

data State = State {
    _str :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    _cond :: !YYCONDTYPE
} deriving (Show)

peek_digit :: BS.ByteString -> Int -> Int -> Int
peek_digit str idx offs = fromIntegral (BS.index str (idx - 1)) - offs

/*!re2c
    re2c:define:YYFN      = ["parse;Maybe Int", "State{..};State", "_n;Int"];
    re2c:define:YYCTYPE   = "Word8";
    re2c:define:YYPEEK    = "BS.index _str _cur";
    re2c:define:YYSKIP    = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYSHIFT   = "let cur = _cur + (@@) in let _cur = cur in";
    re2c:define:YYBACKUP  = "let _mar = _cur in";
    re2c:define:YYRESTORE = "let _cur = _mar in";
    re2c:define:YYGETCOND = "_cond";
    re2c:define:YYSETCOND = "let _cond = @@ in";
    re2c:yyfill:enable    = 0;

    <init> '0b' / [01]        :=> bin
    <init> "0"                :=> oct
    <init> "" / [1-9]         :=> dec
    <init> '0x' / [0-9a-fA-F] :=> hex
    <init> * { Nothing }

    <bin> [01]  { yyfnbin State{..} $ _n * 2 + (peek_digit _str _cur 48) }
    <oct> [0-7] { yyfnoct State{..} $ _n * 8 + (peek_digit _str _cur 48) }
    <dec> [0-9] { yyfndec State{..} $ _n * 10 + (peek_digit _str _cur 48) }
    <hex> [0-9] { yyfnhex State{..} $ _n * 16 + (peek_digit _str _cur 48) }
    <hex> [a-f] { yyfnhex State{..} $ _n * 16 + (peek_digit _str _cur 87) }
    <hex> [A-F] { yyfnhex State{..} $ _n * 16 + (peek_digit _str _cur 55) }

    <bin, oct, dec, hex> * { Just _n }
*/

test :: BS.ByteString -> Maybe Int -> IO ()
test str expect = do
    let s = State {_str = str, _cur = 0, _mar = 0, _cond = YYC_init}
    when (parse s 0 /= expect) $ error "failed!"

main :: IO ()
main = do
    test "\0" Nothing
    test "1234567890\0" (Just 1234567890)
    test "0b1101\0" (Just 13)
    test "0x7Fe\0" (Just 2046)
    test "0644\0" (Just 420)
    test "9223372036854775807\0" (Just 9223372036854775807)
