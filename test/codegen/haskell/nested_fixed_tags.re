-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Monad (when)
import Data.ByteString as BS

none :: Int
none = -1

data State = State {
    str :: !BS.ByteString,
    cur :: !Int,
    mar :: !Int,
    /*!stags:re2c:b1:b2 format = '\n@@{tag} :: !Int,'; */
    x :: !Int,
    y :: !Int,
    yypmatch0 :: !Int,
    yypmatch1 :: !Int,
    yypmatch2 :: !Int,
    yypmatch3 :: !Int,
    yypmatch4 :: !Int,
    yypmatch5 :: !Int
} deriving (Show)

/*!re2c
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP      = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP    = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE   = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYSTAGP     = "let _t = _s{@@{tag} = _s.cur} in let _s = _t in";
    re2c:define:YYSTAGN     = "let _t = _s{@@{tag} = none} in let _s = _t in";
    re2c:define:YYCOPYSTAG  = "let _t = _s{@@{lhs} = _s.@@{rhs}} in let _s = _t in";
    re2c:define:YYSHIFTSTAG = "let _t = if _s.@@{tag} == none "
                                  "then _s "
                                  "else _s{@@{tag} = _s.@@{tag} + (@@{shift})} "
                              "in let _s = _t in";
    re2c:yyfill:enable = 0;
*/

/*!re2c:b1
    re2c:define:YYFN = ["lex_tags;Int", "_s;State"];
    re2c:tags = 1;

    ([b] @x [a] @y)? { if _s.x == none then none else _s.y - _s.x }
*/

/*!re2c:b2
    re2c:define:YYFN = ["lex_captures;Int", "_s;State"];
    re2c:posix-captures = 1;

    (([a]))? { _s.yypmatch4 }
*/

make_state :: BS.ByteString -> State
make_state str =
    State {
        str = str,
        cur = 0,
        mar = 0,
        /*!stags:re2c:b1:b2 format = '\n@@{tag} = none,'; */
        x = none,
        y = none,
        yypmatch0 = none,
        yypmatch1 = none,
        yypmatch2 = none,
        yypmatch3 = none,
        yypmatch4 = none,
        yypmatch5 = none
    }

main :: IO ()
main = do
    let test fn str expect =
            when (fn (make_state str) /= expect) $ error "failed"

    test lex_tags "\0" none
    test lex_tags "ba\0" 1
    test lex_captures "\0" none
    test lex_captures "a\0" 0
