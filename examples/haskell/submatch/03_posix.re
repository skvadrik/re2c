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
    %{stags format = "\n@@{tag} :: !Int,"; %}
    -- use record fields instead of canonical POSIX `yypmatch` array,
    -- as mutable arrays are non-idiomatic in Haskell
    _yytl0 :: !Int,
    _yytr0 :: !Int,
    _yytl1 :: !Int,
    _yytr1 :: !Int,
    _yytl2 :: !Int,
    _yytr2 :: !Int,
    _yytl3 :: !Int,
    _yytr3 :: !Int
}

data SemVer = SemVer {
    major :: !Int,
    minor :: !Int,
    patch :: !Int
} deriving (Eq)

s2n :: ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (index s k) - 48))

%{
    re2c:define:YYFN = ["parse;Maybe SemVer", "State{..};State"];
    re2c:define:YYCTYPE = "Word8";
    re2c:posix-captvars = 1;
    re2c:variable:yypmatch = _;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    (num) "." (num) ("." num)? [\x00] {
        -- Even `yypmatch` values are for opening parentheses, odd values
        -- are for closing parentheses, the first group is the whole match.
        Just SemVer {
            major = s2n _yyinput _yytl1 _yytr1,
            minor = s2n _yyinput _yytl2 _yytr2,
            patch = if _yytl3 == none then 0 else s2n _yyinput (_yytl3 + 1) _yytr3
        }
    }
    * { Nothing }
%}

test :: ByteString -> Maybe SemVer -> IO ()
test str expect = do
    let s = State {
        _yyinput = str,
        _yycursor = 0,
        _yymarker = 0,
        %{stags format = "\n@@{tag} = none,"; %}
        _yytl0 = none,
        _yytr0 = none,
        _yytl1 = none,
        _yytr1 = none,
        _yytl2 = none,
        _yytr2 = none,
        _yytl3 = none,
        _yytr3 = none
    }
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "23.34\0" (Just SemVer {major = 23, minor = 34, patch = 0})
    test "1.2.99999\0" (Just SemVer {major = 1, minor = 2, patch = 99999})
    test "1.a\0" Nothing
