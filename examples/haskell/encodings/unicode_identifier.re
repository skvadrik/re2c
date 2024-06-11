-- re2hs $INPUT -o $OUTPUT --utf8 -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

/*!include:re2c "unicode_categories.re" */

data State = State {
    _str :: ByteString,
    _cur :: Int,
    _mar :: Int,
    _accept :: Int
}

/*!re2c
    re2c:define:YYFN = ["lexer;Bool", "State{..};State"];
    re2c:yyfill:enable = 0;

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
            _str = "_Ыдентификатор\x00",
            _cur = 0,
            _mar = 0,
            _accept = 0}

    when (not $ lexer st) $ error "failed"
