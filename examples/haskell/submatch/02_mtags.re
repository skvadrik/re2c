-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import qualified Data.ByteString as BS

data State = State {
    _str :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    _1 :: !Int,
    _2 :: !Int,
    /*!mtags:re2c format = '\n@@{tag} :: ![Int],'; */
    _3 :: ![Int],
    _4 :: ![Int]
} deriving (Show)

none :: Int
none = -1

s2n :: BS.ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (BS.index s k) - 48))

/*!re2c
    re2c:define:YYFN       = ["parse;Maybe [Int]", "State{..};State"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "BS.index _str _cur";
    re2c:define:YYSKIP     = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYBACKUP   = "let _mar = _cur in";
    re2c:define:YYRESTORE  = "let _cur = _mar in";
    re2c:define:YYSTAGP    = "let @@{tag} = _cur in";
    re2c:define:YYSTAGN    = "let @@{tag} = none in";
    re2c:define:YYMTAGP    = "let tag = _cur : @@{tag} in let @@{tag} = tag in";
    re2c:define:YYMTAGN    = ""; // alternatively could add `none` to the list
    re2c:define:YYCOPYSTAG = "let @@{lhs} = @@{rhs} in";
    re2c:define:YYCOPYMTAG = "let @@{lhs} = @@{rhs} in";
    re2c:tags = 1;
    re2c:tags:prefix = _t;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @_1 num @_2 ("." #_3 num #_4)* [\x00] {
        Just $ (s2n _str _1 _2) : (reverse $ zipWith (\i j -> s2n _str i j) _3 _4)
    }
    * { Nothing }
*/

test :: BS.ByteString -> Maybe [Int] -> IO ()
test str expect = do
    let st = State {
        _str = str,
        _cur = 0,
        _mar = 0,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        _1 = none,
        _2 = none,
        /*!mtags:re2c format = '\n@@{tag} = [],'; */
        _3 = [],
        _4 = []
    }
    when (parse st /= expect) $ error "failed!"

main :: IO ()
main = do
    test "1\0" (Just [1])
    test "1.2.3.4.5.6.7\0" (Just [1, 2, 3, 4, 5, 6, 7])
    test "1.2.\0" Nothing
