-- re2hs $INPUT -o $OUTPUT --input-encoding utf8
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

-- This example supports multiple input encodings: UTF-8 and UTF-32.
-- Both lexers are generated from the same rules block, and the use
-- blocks add only encoding-specific configurations.

import Control.Monad (when)
import Data.Array as A
import Data.Word

data State a = State {
    str :: a,
    cur :: Int,
    mar :: Int
} deriving (Show)

/*!rules:re2c
    re2c:define:YYSKIP    = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP  = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:yyfill:enable    = 0;

    "∀x ∃y" { Just _s.cur }
    *       { Nothing }
*/

/*!use:re2c
    re2c:define:YYFN = ["lex8;Maybe Int", "_s;State (A.Array Int Word8)"];
    re2c:encoding:utf8 = 1;
    re2c:define:YYCTYPE = Word8;
    re2c:define:YYPEEK = "_s.str ! _s.cur";
*/

/*!use:re2c
    re2c:define:YYFN = ["lex32;Maybe Int", "_s;State (A.Array Int Int)"];
    re2c:encoding:utf32 = 1;
    re2c:define:YYCTYPE = Int;
    re2c:define:YYPEEK = "_s.str ! _s.cur";
*/

main :: IO ()
main = do
    let str8 = [0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79]
    let st8 = State {str = listArray (0, length str8 - 1) str8, cur = 0, mar = 0}
    when (lex8 st8 /= Just (length str8)) $ error "lex8 failed"

    let str32 = [0x2200, 0x78, 0x20, 0x2203, 0x79]
    let st32 = State {str = listArray (0, length str32 - 1) str32, cur = 0, mar = 0}
    when (lex32 st32 /= Just (length str32)) $ error "lex32 failed"
