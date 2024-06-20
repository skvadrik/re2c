-- re2hs $INPUT -o $OUTPUT --header lexer/State.hs -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (index)
import State

/*!header:re2c:on*/
module State where

import Data.ByteString (ByteString)

data State = State {
    _str :: !ByteString,
    _yycursor :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    _tag :: !Int
}
/*!header:re2c:off*/

/*!re2c
    re2c:define:YYFN = ["lexer;Int", "State{..};State"];
    re2c:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:header = "lexer/State.hs";

    [a]* @_tag [b]* { _tag }
*/

main :: IO ()
main = do
    let s = State {
        _str = "ab\0",
        _yycursor = 0,
        /*!stags:re2c format = '\n@@{tag} = -1,'; */
        _tag = 0}

    when (lexer s /= 1) $ error "failed!"
