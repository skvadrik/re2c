-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import qualified Data.ByteString as BS

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _lim :: Int,
    _cnt :: Int
}

-- Expect a string without terminating null.
%{
    re2c:api = generic;
    re2c:YYFN = ["lexer;Int", "State{..};State"];
    re2c:YYPEEK = "if _cur < _lim then BS.index _str _cur else 0";
    re2c:YYSKIP = "let cur = _cur + 1 in let _cur = cur in";
    re2c:yyfill:enable = 0;

    *      { (-1) }
    [\x00] { _cnt }
    [a-z]+ { lexer State{_cnt = _cnt + 1, ..} }
    [ ]+   { lexer State{..} }
%}

main :: IO ()
main = do
    let test s n =
            let st = State {_str = s, _cur = 0, _lim = BS.length s, _cnt = 0}
            in when (lexer st /= n) $ error "failed"

    test "" 0
    test "one two three " 3
    test "f0ur" (-1)
