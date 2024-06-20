-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

data State = State {
    _str :: !ByteString,
    _yycursor :: !Int,
    _yymarker :: !Int,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    _1 :: !Int,
    _2 :: !Int,
    _3 :: !Int,
    _4 :: !Int,
    _5 :: !Int
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
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @_1 num @_2 "." @_3 num @_4 ("." @_5 num)? [\x00] {
        Just SemVer {
            major = s2n _str _1 _2,
            minor = s2n _str _3 _4,
            patch = if _5 == (-1) then 0 else s2n _str _5 (_yycursor - 1)
        }
    }
    * { Nothing }
*/

test :: ByteString -> Maybe SemVer -> IO ()
test str expect = do
    let s = State {
        _str = str,
        _yycursor = 0,
        _yymarker = 0,
        /*!stags:re2c format = '\n@@{tag} = (-1),'; */
        _1 = (-1),
        _2 = (-1),
        _3 = (-1),
        _4 = (-1),
        _5 = (-1)
    }
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "23.34\0" (Just SemVer {major = 23, minor = 34, patch = 0})
    test "1.2.99999\0" (Just SemVer {major = 1, minor = 2, patch = 99999})
    test "1.a\0" Nothing
