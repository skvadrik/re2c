-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    str :: BS.ByteString,
    cur :: Int,
    lim :: Int
} deriving (Show)

-- Expect a string without terminating null.
/*!re2c
    re2c:define:YYFN    = ["lexer;Int", "_s;State", "_cnt;Int"];
    re2c:define:YYCTYPE = "Word8";
    re2c:define:YYPEEK  = "if _s.cur < _s.lim then BS.index _s.str _s.cur else 0";
    re2c:define:YYSKIP  = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:yyfill:enable  = 0;

    *      { (-1) }
    [\x00] { _cnt }
    [a-z]+ { lexer _s (_cnt + 1) }
    [ ]+   { lexer _s _cnt }
*/

main :: IO ()
main = do
    let test s n =
            let st = State {str = s, cur = 0, lim = BS.length s}
            in when (lexer st 0 /= n) $ error "failed"

    test "" 0
    test "one two three " 3
    test "f0ur" (-1)
