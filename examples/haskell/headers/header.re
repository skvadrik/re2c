-- re2hs $INPUT -o $OUTPUT --header lexer/State.hs -i
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Data.ByteString as BS
import Control.Monad (when)
import State

/*!header:re2c:on*/
module State where

import Data.ByteString as BS

data State = State {
    str :: !BS.ByteString,
    cur :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    tag :: !Int
} deriving (Show)
/*!header:re2c:off*/

/*!re2c
    re2c:define:YYFN       = ["lexer;Int", "_s;State"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP     = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYSTAGP    = "let _t = _s{@@{tag} = _s.cur} in let _s = _t in";
    re2c:define:YYCOPYSTAG = "let _t = _s{@@{lhs} = _s.@@{rhs}} in let _s = _t in";
    re2c:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:header = "lexer/State.hs";

    [a]* @tag [b]* { _s.tag }
*/

main :: IO ()
main = do
    let s = State {
        str = "ab\0",
        cur = 0,
        /*!stags:re2c format = '\n@@{tag} = -1,'; */
        tag = 0
    }
    when (lexer s /= 1) $ error "failed!"
