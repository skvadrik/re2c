-- re2hs $INPUT -o $OUTPUT --input-encoding utf8
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

-- This example supports multiple input encodings: UTF-8 and UTF-32.
-- Both lexers are generated from the same rules block, and the use
-- blocks add only encoding-specific configurations.

import Control.Monad (when)
import Data.Array as A
import Data.Word

data State a = State {
    _str :: a,
    _cur :: Int,
    _mar :: Int
} deriving (Show)

/*!rules:re2c
    re2c:define:YYSKIP    = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYBACKUP  = "let _mar = _cur in";
    re2c:define:YYRESTORE = "let _cur = _mar in";
    re2c:yyfill:enable    = 0;

    "∀x ∃y" { Just _cur }
    *       { Nothing }
*/

/*!use:re2c
    re2c:define:YYFN = ["lex8;Maybe Int", "State{..};State (A.Array Int Word8)"];
    re2c:encoding:utf8 = 1;
    re2c:define:YYCTYPE = Word8;
    re2c:define:YYPEEK = "_str ! _cur";
*/

/*!use:re2c
    re2c:define:YYFN = ["lex32;Maybe Int", "State{..};State (A.Array Int Int)"];
    re2c:encoding:utf32 = 1;
    re2c:define:YYCTYPE = Int;
    re2c:define:YYPEEK = "_str ! _cur";
*/

main :: IO ()
main = do
    let make_st l = State {_str = listArray (0, length l - 1) l, _cur = 0, _mar = 0}

    let s8 = [0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79]
    when (lex8 (make_st s8) /= Just (length s8)) $ error "lex8 failed"

    let s32 = [0x2200, 0x78, 0x20, 0x2203, 0x79]
    when (lex32 (make_st s32) /= Just (length s32)) $ error "lex32 failed"
