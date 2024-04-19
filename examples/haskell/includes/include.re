-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS

/*!include:re2c "definitions.hs" */

data State = State {
    str :: BS.ByteString,
    cur :: Int,
    mar :: Int,
    accept :: Int
} deriving (Show)

/*!re2c
    re2c:define:YYFN        = ["lexer;Number", "_s;State"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP      = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP    = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE   = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYGETACCEPT = "_s.accept";
    re2c:define:YYSETACCEPT = "let _t = _s{accept = @@{val}} in let _s = _t in";
    re2c:yyfill:enable      = 0;

    *      { NNaN }
    number { INum }
    !include "extra_rules.re.inc";
*/

main :: IO ()
main = do
    let test s n = do
            let st = State {str = s, cur = 0, mar = 0, accept = 0}
            when (lexer st /= n) $ error "failed"

    test "123\0" INum
    test "123.4567\0" FNum
