-- re2hs $INPUT -o $OUTPUT -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

%{include "definitions.hs" %}

data State = State {
    _yyinput :: ByteString,
    _yycursor :: Int,
    _yymarker :: Int,
    _yyaccept :: Int
}

%{
    re2c:YYFN = ["lexer;Number", "State{..};State"];
    re2c:yyfill:enable = 0;

    *      { NNaN }
    number { INum }
    !include "extra_rules.re.inc";
%}

main :: IO ()
main = do
    let test s n = do
            let st = State {
                    _yyinput = s,
                    _yycursor = 0,
                    _yymarker = 0,
                    _yyaccept = 0}

            when (lexer st /= n) $ error "failed"

    test "123\0" INum
    test "123.4567\0" FNum
