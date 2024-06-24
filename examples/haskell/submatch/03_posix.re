-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)
import Data.Word (Word8)

none :: Int
none = -1

data State = State {
    _yyinput :: !ByteString,
    _yycursor :: !Int,
    _yymarker :: !Int,
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
}

data SemVer = SemVer {
    major :: !Int,
    minor :: !Int,
    patch :: !Int
} deriving (Eq)

s2n :: ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (index s k) - 48))

/*!re2c
    re2c:define:YYFN = ["parse;Maybe SemVer", "State{..};State"];
    re2c:define:YYCTYPE = "Word8";
    re2c:posix-captures = 1;
    re2c:variable:yypmatch = _;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    (num) "." (num) ("." num)? [\x00] {
        -- Even `yypmatch` values are for opening parentheses, odd values
        -- are for closing parentheses, the first group is the whole match.
        Just SemVer {
            major = s2n _yyinput _2 _3,
            minor = s2n _yyinput _4 _5,
            patch = if _6 == none then 0 else s2n _yyinput (_6 + 1) _7
        }
    }
    * { Nothing }
*/

test :: ByteString -> Maybe SemVer -> IO ()
test str expect = do
    let s = State {
        _yyinput = str,
        _yycursor = 0,
        _yymarker = 0,
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
