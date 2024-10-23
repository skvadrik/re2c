-- re2hs $INPUT -o $OUTPUT --input-encoding utf8
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

-- This example supports multiple input encodings: UTF-8 and UTF-32.
-- Both lexers are generated from the same rules block, and the use
-- blocks add only encoding-specific configurations.

import Control.Monad (when)
import Data.Array
import Data.Word

data State a = State {
    _yyinput :: a,
    _yycursor :: Int,
    _yymarker :: Int
}

%{rules
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "(!)";

    "∀x ∃y" { Just _yycursor }
    *       { Nothing }
%}

%{use
    re2c:YYFN = ["lex8;Maybe Int", "State{..};State (Array Int Word8)"];
    re2c:encoding:utf8 = 1;
    re2c:YYCTYPE = Word8;
%}

%{use
    re2c:YYFN = ["lex32;Maybe Int", "State{..};State (Array Int Int)"];
    re2c:encoding:utf32 = 1;
    re2c:YYCTYPE = Int;
%}

main :: IO ()
main = do
    let make_st l = State {
            _yyinput = listArray (0, length l - 1) l,
            _yycursor = 0,
            _yymarker = 0}

    let s8 = [0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79]
    when (lex8 (make_st s8) /= Just (length s8)) $ error "lex8 failed"

    let s32 = [0x2200, 0x78, 0x20, 0x2203, 0x79]
    when (lex32 (make_st s32) /= Just (length s32)) $ error "lex32 failed"
