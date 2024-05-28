-- re2hs $INPUT -o $OUTPUT -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS

/*!include:re2c "definitions.hs" */

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _mar :: Int,
    _accept :: Int
} deriving (Show)

/*!re2c
    re2c:define:YYFN        = ["lexer;Number", "State{..};State"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index _str _cur";
    re2c:define:YYSKIP      = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYBACKUP    = "let _mar = _cur in";
    re2c:define:YYRESTORE   = "let _cur = _mar in";
    re2c:define:YYGETACCEPT = "_accept";
    re2c:define:YYSETACCEPT = "let _accept = @@{val} in";
    re2c:yyfill:enable      = 0;

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
