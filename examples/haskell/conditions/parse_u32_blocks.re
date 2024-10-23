-- re2hs $INPUT -o $OUTPUT -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (ByteString, index)

data State = State {
    _yyinput :: !ByteString,
    _yycursor :: !Int,
    _yymarker :: !Int
}

peek_digit :: ByteString -> Int -> Int -> Int
peek_digit str idx offs = fromIntegral (index str (idx - 1)) - offs

%{
    re2c:yyfill:enable = 0;
%}

%{local
    re2c:YYFN = ["parse_bin;Int", "State{..};State", "num;Int"];
    [01] { parse_bin State{..} $ num * 2 + (peek_digit _yyinput _yycursor 48) }
    *    { num }
%}

%{local
    re2c:YYFN = ["parse_oct;Int", "State{..};State", "num;Int"];
    [0-7] { parse_oct State{..} $ num * 8 + (peek_digit _yyinput _yycursor 48) }
    *     { num }
%}

%{local
    re2c:YYFN = ["parse_dec;Int", "State{..};State", "num;Int"];
    [0-9] { parse_dec State{..} $ num * 10 + (peek_digit _yyinput _yycursor 48) }
    *     { num }
%}

%{local
    re2c:YYFN = ["parse_hex;Int", "State{..};State", "num;Int"];
    [0-9] { parse_hex State{..} $ num * 16 + (peek_digit _yyinput _yycursor 48) }
    [a-f] { parse_hex State{..} $ num * 16 + (peek_digit _yyinput _yycursor 87) }
    [A-F] { parse_hex State{..} $ num * 16 + (peek_digit _yyinput _yycursor 55) }
    *     { num }
%}

%{local
    re2c:YYFN = ["parse;Maybe Int", "State{..};State"];
    '0b' / [01]        { Just $ parse_bin State{..} 0 }
    "0"                { Just $ parse_oct State{..} 0 }
    "" / [1-9]         { Just $ parse_dec State{..} 0 }
    '0x' / [0-9a-fA-F] { Just $ parse_hex State{..} 0 }
    *                  { Nothing }
%}

test :: ByteString -> Maybe Int -> IO ()
test str expect = do
    let s = State {_yyinput = str, _yycursor = 0, _yymarker = 0}
    when (parse s /= expect) $ error "failed!"

main :: IO ()
main = do
    test "\0" Nothing
    test "1234567890\0" (Just 1234567890)
    test "0b1101\0" (Just 13)
    test "0x7Fe\0" (Just 2046)
    test "0644\0" (Just 420)
    test "9223372036854775807\0" (Just 9223372036854775807)
