-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import qualified Data.ByteString as BS
import Data.Word

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _mar :: Int,
    _lim :: Int,
    _cnt :: Int
}

-- expect a null-terminated string
/*!re2c
    re2c:define:YYFN = ["lexer;Int", "State{..};State"];
    re2c:define:YYCTYPE = "Word8";
    re2c:define:YYPEEK = "BS.index";
    re2c:eof = 0;
    re2c:yyfill:enable = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { (-1) }
    $    { _cnt }
    str  { lexer State{_cnt = _cnt + 1, ..} }
    [ ]+ { lexer State{..} }
*/

main :: IO ()
main = do
    let test s n = do
            let st = State {
                    _str = s,
                    _cur = 0, 
                    _mar = 0,
                    _lim = BS.length s - 1, -- terminating null not included
                    _cnt = 0}

            when (lexer st /= n) $ error "failed"

    test "\0" 0
    test "'qu\0tes' 'are' 'fine: \\'' \0" 3
    test "'unterminated\\'\0" (-1)
