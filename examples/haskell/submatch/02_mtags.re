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
    /*!mtags:re2c format = '\n@@{tag} :: ![Int],'; */
    _3 :: ![Int],
    _4 :: ![Int]
}

s2n :: ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (index s k) - 48))

/*!re2c
    re2c:define:YYFN = ["parse;Maybe [Int]", "State{..};State"];
    re2c:define:YYMTAGP = "let tag = _yycursor : @@{tag} in let @@{tag} = tag in";
    re2c:define:YYMTAGN = ""; // alternatively could add -1 to the list
    re2c:tags = 1;
    re2c:yyfill:enable = 0;

    num = [0-9]+;

    @_1 num @_2 ("." #_3 num #_4)* [\x00] {
        Just $ (s2n _str _1 _2) : (reverse $ zipWith (\i j -> s2n _str i j) _3 _4)
    }
    * { Nothing }
*/

test :: ByteString -> Maybe [Int] -> IO ()
test str expect = do
    let st = State {
        _str = str,
        _yycursor = 0,
        _yymarker = 0,
        /*!stags:re2c format = '\n@@{tag} = (-1),'; */
        _1 = (-1),
        _2 = (-1),
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
