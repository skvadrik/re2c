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
    /*!mtags:re2c format = '\n@@{tag} :: ![Int],'; */
    t3 :: ![Int],
    t4 :: ![Int]
} deriving (Show)

none :: Int
none = -1

s2n :: BS.ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (BS.index s k) - 48))

/*!re2c
    re2c:define:YYFN       = ["parse;Maybe [Int]", "_s;State;!"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "BS.index _s.str _s.cur";
    re2c:define:YYSKIP     = "let _t = _s{cur = _s.cur + 1} in let _s = _t in";
    re2c:define:YYBACKUP   = "let _t = _s{mar = _s.cur} in let _s = _t in";
    re2c:define:YYRESTORE  = "let _t = _s{cur = _s.mar} in let _s = _t in";
    re2c:define:YYSTAGP    = "let _t = _s{@@{tag} = _s.cur} in let _s = _t in";
    re2c:define:YYSTAGN    = "let _t = _s{@@{tag} = none} in let _s = _t in";
    re2c:define:YYMTAGP    = "let _t = _s{@@{tag} = _s.cur : _s.@@{tag}} in let _s = _t in";
    re2c:define:YYMTAGN    = ""; // alternatively could add `none` to the list
    re2c:define:YYCOPYSTAG = "let _t = _s{@@{lhs} = _s.@@{rhs}} in let _s = _t in";
    re2c:define:YYCOPYMTAG = "let _t = _s{@@{lhs} = _s.@@{rhs}} in let _s = _t in";
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @t1 num @t2 ("." #t3 num #t4)* [\x00] {
        let x = s2n _s.str _s.t1 _s.t2
            xs = Prelude.reverse $ Prelude.zipWith (\i j -> s2n _s.str i j) _s.t3 _s.t4
        in Just (x : xs)
    }
    * { Nothing }
*/

test :: BS.ByteString -> Maybe [Int] -> IO ()
test str expect = do
    let s = State {
        str = str,
        cur = 0,
        mar = 0,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        t1 = none,
        t2 = none,
        /*!mtags:re2c format = '\n@@{tag} = [],'; */
        t3 = [],
        t4 = []
    }
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "1\0" (Just [1])
    test "1.2.3.4.5.6.7\0" (Just [1, 2, 3, 4, 5, 6, 7])
    test "1.2.\0" Nothing
