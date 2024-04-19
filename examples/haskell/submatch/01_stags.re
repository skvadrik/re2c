-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    str :: !BS.ByteString,
    cur :: !Int,
    mar :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    t1 :: !Int,
    t2 :: !Int,
    t3 :: !Int,
    t4 :: !Int,
    t5 :: !Int
} deriving (Show)

data SemVer = SemVer {
    major :: !Int,
    minor :: !Int,
    patch :: !Int
} deriving (Show, Eq)

none :: Int
none = -1

s2n :: BS.ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (BS.index s k) - 48))

/*!re2c
    re2c:define:YYFN        = ["parse;Maybe SemVer", "_s;State;!"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP      = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP    = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE   = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYSTAGP     = "let _t = _s{@@{tag} = _s.cur} in let _s = _t in";
    re2c:define:YYSTAGN     = "let _t = _s{@@{tag} = none} in let _s = _t in";
    re2c:define:YYCOPYSTAG  = "let _t = _s{@@{lhs} = _s.@@{rhs}} in let _s = _t in";
    re2c:define:YYSHIFTSTAG = "let _t = if _s.@@{tag} == none then _s else _s{@@{tag} = _s.@@{tag} + (@@{shift})} in let _s = _t in";
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\x00] {
        Just SemVer {
            major = s2n _s.str _s.t1 _s.t2,
            minor = s2n _s.str _s.t3 _s.t4,
            patch = if _s.t5 == none then 0 else s2n _s.str _s.t5 (_s.cur - 1)
        }
    }
    * { Nothing }
*/

test :: BS.ByteString -> Maybe SemVer -> IO ()
test str expect = do
    let s = State {
        str = str,
        cur = 0,
        mar = 0,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        t1 = none,
        t2 = none,
        t3 = none,
        t4 = none,
        t5 = none
    }
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "23.34\0" (Just SemVer {major = 23, minor = 34, patch = 0})
    test "1.2.99999\0" (Just SemVer {major = 1, minor = 2, patch = 99999})
    test "1.a\0" Nothing
