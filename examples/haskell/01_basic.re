-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}

import Data.ByteString (ByteString, index)

data State = State {
    _yyinput :: ByteString,
    _yycursor :: Int
}

%{
    re2c:YYFN = ["lexer;Bool", "State{..};State"];
    re2c:yyfill:enable = 0;

    [1-9][0-9]* { True }
    *           { False }
%}

main :: IO ()
main = case lexer State{_yyinput = "1234\0", _yycursor = 0} of
    True -> return ()
    False -> error "lexer failed!"
