-- re2hs $INPUT -o $OUTPUT -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

/*!include:re2c "definitions.hs" */

data State = State {
    _str :: ByteString,
    _cur :: Int,
    _mar :: Int,
    _accept :: Int
}

/*!re2c
    re2c:define:YYFN = ["lexer;Number", "State{..};State"];
    re2c:yyfill:enable = 0;

    *      { NNaN }
    number { INum }
    !include "extra_rules.re.inc";
*/

main :: IO ()
main = do
    let test s n = do
            let st = State {_str = s, _cur = 0, _mar = 0, _accept = 0}
            when (lexer st /= n) $ error "failed"

    test "123\0" INum
    test "123.4567\0" FNum
