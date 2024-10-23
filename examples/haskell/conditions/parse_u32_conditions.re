-- re2hs $INPUT -o $OUTPUT -ci
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

%{conditions %}

data State = State {
    _yyinput :: !ByteString,
    _yycursor :: !Int,
    _yymarker :: !Int,
    _yycond :: !YYCONDTYPE
}

peek_digit :: ByteString -> Int -> Int -> Int
peek_digit str idx offs = fromIntegral (index str (idx - 1)) - offs

%{
    re2c:YYFN = ["parse;Maybe Int", "State{..};State", "_num;Int"];
    re2c:yyfill:enable = 0;

    <init> '0b' / [01]        :=> bin
    <init> "0"                :=> oct
    <init> "" / [1-9]         :=> dec
    <init> '0x' / [0-9a-fA-F] :=> hex
    <init> * { Nothing }

    <bin> [01]  { yyfnbin State{..} $ _num * 2 + (peek_digit _yyinput _yycursor 48) }
    <oct> [0-7] { yyfnoct State{..} $ _num * 8 + (peek_digit _yyinput _yycursor 48) }
    <dec> [0-9] { yyfndec State{..} $ _num * 10 + (peek_digit _yyinput _yycursor 48) }
    <hex> [0-9] { yyfnhex State{..} $ _num * 16 + (peek_digit _yyinput _yycursor 48) }
    <hex> [a-f] { yyfnhex State{..} $ _num * 16 + (peek_digit _yyinput _yycursor 87) }
    <hex> [A-F] { yyfnhex State{..} $ _num * 16 + (peek_digit _yyinput _yycursor 55) }

    <bin, oct, dec, hex> * { Just _num }
%}

test :: ByteString -> Maybe Int -> IO ()
test str expect = do
    let s = State {
            _yyinput = str,
            _yycursor = 0,
            _yymarker = 0,
            _yycond = YYC_init}
    when (parse s 0 /= expect) $ error "failed!"

main :: IO ()
main = do
    test "\0" Nothing
    test "1234567890\0" (Just 1234567890)
    test "0b1101\0" (Just 13)
    test "0x7Fe\0" (Just 2046)
    test "0644\0" (Just 420)
    test "9223372036854775807\0" (Just 9223372036854775807)
