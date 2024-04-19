-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

-- This example shows how to combine reusable re2c blocks: two blocks
-- ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
-- in both blocks; the 'fish' block takes priority because it is used
-- earlier. Default rule * occurs in all three blocks; the local (not
-- inherited) definition takes priority.

import Control.Monad (when)
import Data.ByteString as BS

data Answer = Color | Fish | Dunno deriving (Eq)

data State = State {
    str :: BS.ByteString,
    cur :: Int,
    mar :: Int
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
    re2c:define:YYFN      = ["lexer;Answer", "_s;State"];
    re2c:define:YYCTYPE   = "Word8";
    re2c:define:YYPEEK    = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP    = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP  = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:yyfill:enable    = 0;

    !use:fish;
    !use:colors;
    * { Dunno } // overrides inherited '*' rules
*/

main :: IO ()
main = do
    let test str ans = do
            let st = State {str = str, cur = 0, mar = 0}
            when (lexer st /= ans) $ error "failed"

    test "salmon" Fish
    test "what?" Dunno
