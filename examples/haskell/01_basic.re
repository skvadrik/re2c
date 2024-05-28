-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}

import Data.ByteString as BS

/*!re2c
    re2c:define:YYFN    = ["lexer;Bool", "_str;BS.ByteString", "_cur;Int"];
    re2c:define:YYCTYPE = "Word8";
    re2c:define:YYPEEK  = "BS.index _str _cur";
    re2c:define:YYSKIP  = "let cur = _cur + 1 in let _cur = cur in";
    re2c:yyfill:enable  = 0;

    number = [1-9][0-9]*;

    number { True }
    *      { False }
*/

main :: IO ()
main = case lexer "1234\0" 0 of
    True -> return ()
    False -> error "lexer failed!"
