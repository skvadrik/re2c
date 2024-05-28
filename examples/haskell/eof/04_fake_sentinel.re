-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _lim :: Int
} deriving (Show)

-- Expect a string without terminating null.
/*!re2c
    re2c:define:YYFN    = ["lexer;Int", "State{..};State", "_cnt;Int"];
    re2c:define:YYCTYPE = "Word8";
    re2c:define:YYPEEK  = "if _cur < _lim then BS.index _str _cur else 0";
    re2c:define:YYSKIP  = "let cur = _cur + 1 in let _cur = cur in";
    re2c:yyfill:enable  = 0;

    *      { (-1) }
    [\x00] { _cnt }
    [a-z]+ { lexer State{..} (_cnt + 1) }
    [ ]+   { lexer State{..} _cnt }
*/

main :: IO ()
main = do
    let test s n =
            let st = State {_str = s, _cur = 0, _lim = BS.length s}
            in when (lexer st 0 /= n) $ error "failed"

    test "" 0
    test "one two three " 3
    test "f0ur" (-1)
