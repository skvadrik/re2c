-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

-- This example shows how to combine reusable re2c blocks: two blocks
-- ('colors' and 'fish') are merged into one. The 'salmon' rule occurs
-- in both blocks; the 'fish' block takes priority because it is used
-- earlier. Default rule * occurs in all three blocks; the local (not
-- inherited) definition takes priority.

import Control.Monad (when)
import Data.ByteString (ByteString, index)

data Answer = Color | Fish | Dunno deriving (Eq)

data State = State {
    _yyinput :: ByteString,
    _yycursor :: Int,
    _yymarker :: Int
}

%{rules:colors
    *                            { error "ah" }
    "red" | "salmon" | "magenta" { Color }
%}

%{rules:fish
    *                            { error "oh" }
    "haddock" | "salmon" | "eel" { Fish }
%}

%{
    re2c:YYFN = ["lexer;Answer", "State{..};State"];
    re2c:yyfill:enable = 0;

    !use:fish;
    !use:colors;
    * { Dunno } // overrides inherited '*' rules
%}

main :: IO ()
main = do
    let test str ans = do
            let st = State {_yyinput = str, _yycursor = 0, _yymarker = 0}
            when (lexer st /= ans) $ error "failed"

    test "salmon" Fish
    test "what?" Dunno
