-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

-- This example shows how to combine reusable re2c blocks: two blocks
-- ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
-- in both blocks; the 'fish' block takes priority because it is used
-- earlier. Default rule * occurs in all three blocks; the local (not
-- inherited) definition takes priority.

import Control.Monad (when)
import Data.ByteString as BS

data Answer = Color | Fish | Dunno deriving (Eq)

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _mar :: Int
} deriving (Show)

/*!rules:re2c:colors
    *                            { error "ah" }
    "red" | "salmon" | "magenta" { Color }
*/

/*!rules:re2c:fish
    *                            { error "oh" }
    "haddock" | "salmon" | "eel" { Fish }
*/

/*!re2c
    re2c:define:YYFN      = ["lexer;Answer", "State{..};State"];
    re2c:define:YYCTYPE   = "Word8";
    re2c:define:YYPEEK    = "BS.index _str _cur";
    re2c:define:YYSKIP    = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYBACKUP  = "let _mar = _cur in";
    re2c:define:YYRESTORE = "let _cur = _mar in";
    re2c:yyfill:enable    = 0;

    !use:fish;
    !use:colors;
    * { Dunno } // overrides inherited '*' rules
*/

main :: IO ()
main = do
    let test str ans = do
            let st = State {_str = str, _cur = 0, _mar = 0}
            when (lexer st /= ans) $ error "failed"

    test "salmon" Fish
    test "what?" Dunno
