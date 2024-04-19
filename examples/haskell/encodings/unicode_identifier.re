-- re2hs $INPUT -o $OUTPUT --utf8 -i
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS

/*!include:re2c "unicode_categories.re" */

data State = State {
    str :: BS.ByteString,
    cur :: Int,
    mar :: Int,
    accept :: Int
} deriving (Show)

/*!re2c
    re2c:define:YYFN        = ["lexer;Bool", "_s;State"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP      = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP    = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE   = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYGETACCEPT = "_s.accept";
    re2c:define:YYSETACCEPT = "let _t = _s{accept = @@{val}} in let _s = _t in";
    re2c:yyfill:enable      = 0;

    // Simplified "Unicode Identifier and Pattern Syntax"
    // (see https://unicode.org/reports/tr31)
    id_start    = L | Nl | [$_];
    id_continue = id_start | Mn | Mc | Nd | Pc | [\u200D\u05F3];
    identifier  = id_start id_continue*;

    identifier { True }
    *          { False }
*/

main :: IO ()
main = do
    let st = State {
            str = "_Ыдентификатор\x00",
            cur = 0,
            mar = 0,
            accept = 0
        }
    when (not $ lexer st) $ error "failed"
