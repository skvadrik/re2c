-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS
import Data.Word

none :: Int
none = -1

data State = State {
    _str :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    -- use record fields instead of canonical POSIX `yypmatch` array,
    -- as mutable arrays are non-idiomatic in Haskell
    _0 :: !Int,
    _1 :: !Int,
    _2 :: !Int,
    _3 :: !Int,
    _4 :: !Int,
    _5 :: !Int,
    _6 :: !Int,
    _7 :: !Int
} deriving (Show)

data SemVer = SemVer {
    major :: !Int,
    minor :: !Int,
    patch :: !Int
} deriving (Show, Eq)

s2n :: BS.ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (BS.index s k) - 48))

/*!re2c
    re2c:define:YYFN        = ["parse;Maybe SemVer", "State{..};State"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "BS.index _str _cur";
    re2c:define:YYSKIP      = "let cur = _cur + 1 in let _cur = cur in";
    re2c:define:YYBACKUP    = "let _mar = _cur in";
    re2c:define:YYRESTORE   = "let _cur = _mar in";
    re2c:define:YYSTAGP     = "let @@{tag} = _cur in";
    re2c:define:YYSTAGN     = "let @@{tag} = none in";
    re2c:define:YYCOPYSTAG  = "let @@{lhs} = @@{rhs} in";
    re2c:define:YYSHIFTSTAG = "let tag = if @@{tag} == none then none else @@{tag} + (@@{shift}) "
                              "in let @@{tag} = tag in";
    re2c:posix-captures = 1;
    re2c:tags:prefix = _t;
    re2c:variable:yypmatch = _;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    (num) "." (num) ("." num)? [\x00] {
        -- Even `yypmatch` values are for opening parentheses, odd values
        -- are for closing parentheses, the first group is the whole match.
        Just SemVer {
            major = s2n _str _2 _3,
            minor = s2n _str _4 _5,
            patch = if _6 == none then 0 else s2n _str (_6 + 1) _7
        }
    }
    * { Nothing }
*/

test :: BS.ByteString -> Maybe SemVer -> IO ()
test str expect = do
    let s = State {
        _str = str,
        _cur = 0,
        _mar = 0,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        _0 = none,
        _1 = none,
        _2 = none,
        _3 = none,
        _4 = none,
        _5 = none,
        _6 = none,
        _7 = none
    }
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "23.34\0" (Just SemVer {major = 23, minor = 34, patch = 0})
    test "1.2.99999\0" (Just SemVer {major = 1, minor = 2, patch = 99999})
    test "1.a\0" Nothing
