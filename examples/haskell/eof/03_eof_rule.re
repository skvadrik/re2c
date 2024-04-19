-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS
import Data.Word

data State = State {
    str :: BS.ByteString,
    cur :: Int,
    mar :: Int,
    lim :: Int
} deriving (Show)

-- expect a null-terminated string
/*!re2c
    re2c:define:YYFN       = ["lexer;Int", "_s;State", "_cnt;Int"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP     = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP   = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE  = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYLESSTHAN = "_s.cur >= _s.lim";
    re2c:eof = 0;
    re2c:yyfill:enable = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { (-1) }
    $    { _cnt }
    str  { lexer _s (_cnt + 1) }
    [ ]+ { lexer _s _cnt }
*/

main :: IO ()
main = do
    let test s n = do
            let st = State {
                    str = s,
                    cur = 0, 
                    mar = 0,
                    lim = BS.length s - 1 -- terminating null not included
                }
            when (lexer st 0 /= n) $ error "failed"

    test "\0" 0
    test "'qu\0tes' 'are' 'fine: \\'' \0" 3
    test "'unterminated\\'\0" (-1)
