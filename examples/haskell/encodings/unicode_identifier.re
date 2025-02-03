-- re2hs $INPUT -o $OUTPUT --utf8 -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

%{include "unicode_categories.re" %}

data State = State {
    _yyinput :: ByteString,
    _yycursor :: Int,
    _yymarker :: Int,
    _yyaccept :: Int
}

%{
    re2c:YYFN = ["lexer;Bool", "State{..};State"];
    re2c:yyfill:enable = 0;

    // Simplified "Unicode Identifier and Pattern Syntax"
    // (see https://unicode.org/reports/tr31)
    id_start    = L | Nl | [$_];
    id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
    identifier  = id_start id_continue*;

    identifier { True }
    *          { False }
%}

main :: IO ()
main = do
    let st = State {
            _yyinput = "_Ыдентификатор\x00",
            _yycursor = 0,
            _yymarker = 0,
            _yyaccept = 0}

    when (not $ lexer st) $ error "failed"
