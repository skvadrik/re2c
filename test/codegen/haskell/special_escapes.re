-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}

import Data.ByteString (ByteString, index)

data State = State {
    _yyinput :: ByteString,
    _yycursor :: Int,
    _yymarker :: Int
}

%{
    re2c:YYFN = ["lexer;Bool", "State{..};State"];
    re2c:yyfill:enable = 0;

    "\a\b\f\n\r\t\v\\'\"" { True }
    * {
        let _ = ['\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '\'', '\"'] in
        False
    }
%}

main :: IO ()
main = do
    let st = State{
            _yyinput = "\x07\x08\x0c\x0a\x0d\x09\x0b\\'\"\0",
            _yycursor = 0,
            _yymarker = 0}
    case lexer st of
        True -> return ()
        False -> error "lexer failed!"
