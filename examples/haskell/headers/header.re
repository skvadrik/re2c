-- re2hs $INPUT -o $OUTPUT --header lexer/State.hs -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Data.ByteString as BS
import Control.Monad (when)
import State

/*!header:re2c:on*/
module State where

import Data.ByteString as BS

data State = State {
    _str :: !BS.ByteString,
    _cur :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    _tag :: !Int
} deriving (Show)
/*!header:re2c:off*/

/*!re2c
    re2c:define:YYFN       = ["lexer;Int", "State{..};State"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "BS.index _str _cur";
    re2c:define:YYSKIP     = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYSTAGP    = "let @@{tag} = _cur in";
    re2c:define:YYCOPYSTAG = "let @@{lhs} = @@{rhs} in";
    re2c:tags = 1;
    re2c:tags:prefix = _t;
    re2c:yyfill:enable = 0;
    re2c:header = "lexer/State.hs";

    [a]* @_tag [b]* { _tag }
*/

main :: IO ()
main = do
    let s = State {
        _str = "ab\0",
        _cur = 0,
        /*!stags:re2c format = '\n@@{tag} = -1,'; */
        _tag = 0}

    when (lexer s /= 1) $ error "failed!"
