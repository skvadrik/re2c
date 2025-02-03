-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

data State = State {
    _yyinput :: ByteString,
    _yycursor :: Int,
    _count :: Int
}

-- expect a null-terminated string
%{
    re2c:YYFN = ["lexer;Int", "State{..};State"];
    re2c:yyfill:enable = 0;

    *      { (-1) }
    [\x00] { _count }
    [a-z]+ { lexer State{_count = _count + 1, ..} }
    [ ]+   { lexer State{..} }
%}

main :: IO ()
main = do
    let test s n = when (lexer st  /= n) $ error "failed"
                   where st = State{_yyinput = s, _yycursor = 0, _count = 0}
    test "\0" 0
    test "one two three\0" 3
    test "f0ur\0" (-1)
