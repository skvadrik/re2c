-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    str :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    _1 :: !Int,
    _2 :: !Int,
    _3 :: !Int,
    _4 :: !Int,
    _5 :: !Int
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
    re2c:define:YYFN        = ["parse;Maybe SemVer", "State{..};State"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index str _cur";
    re2c:define:YYSKIP      = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYBACKUP    = "let _mar = _cur in";
    re2c:define:YYRESTORE   = "let _cur = _mar in";
    re2c:define:YYSTAGP     = "let @@{tag} = _cur in";
    re2c:define:YYSTAGN     = "let @@{tag} = none in";
    re2c:define:YYCOPYSTAG  = "let @@{lhs} = @@{rhs} in";
    re2c:define:YYSHIFTSTAG = "let tag = @@{tag} + if @@{tag} == none then 0 else (@@{shift}) "
                              "in let @@{tag} = tag in";
    re2c:tags = 1;
    re2c:tags:prefix = _t;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @_1 num @_2 "." @_3 num @_4 ("." @_5 num)? [\x00] {
        Just SemVer {
            major = s2n str _1 _2,
            minor = s2n str _3 _4,
            patch = if _5 == none then 0 else s2n str _5 (_cur - 1)
        }
    }
    * { Nothing }
*/

test :: BS.ByteString -> Maybe SemVer -> IO ()
test str expect = do
    let s = State {
        str = str,
        _cur = 0,
        _mar = 0,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        _1 = none,
        _2 = none,
        _3 = none,
        _4 = none,
        _5 = none
    }
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "23.34\0" (Just SemVer {major = 23, minor = 34, patch = 0})
    test "1.2.99999\0" (Just SemVer {major = 1, minor = 2, patch = 99999})
    test "1.a\0" Nothing
