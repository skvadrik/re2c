-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}

import Data.ByteString (ByteString, index)

data State = State {
    _str :: ByteString,
    _cur :: Int
}

/*!re2c
    re2c:define:YYFN = ["lexer;Bool", "State{..};State"];
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;

    number { True }
    *      { False }
*/

main :: IO ()
main = case lexer State{_str = "1234\0", _cur = 0} of
    True -> return ()
    False -> error "lexer failed!"
