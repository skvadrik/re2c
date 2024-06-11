-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

data State = State {
    _str :: ByteString,
    _cur :: Int,
    _cnt :: Int
}

-- expect a null-terminated string
/*!re2c
    re2c:define:YYFN = ["lexer;Int", "State{..};State"];
    re2c:yyfill:enable = 0;

    *      { (-1) }
    [\x00] { _cnt }
    [a-z]+ { lexer State{_cnt = _cnt + 1, ..} }
    [ ]+   { lexer State{..} }
*/

main :: IO ()
main = do
    let test s n = when (lexer State{_str = s, _cur = 0, _cnt = 0} /= n) $ error "failed"
    test "\0" 0
    test "one two three\0" 3
    test "f0ur\0" (-1)
