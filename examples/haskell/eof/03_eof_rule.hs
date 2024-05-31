-- Generated by re2c
#1 "haskell/eof/03_eof_rule.re"
-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad (when)
import Data.ByteString as BS
import Data.Word

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _mar :: Int,
    _lim :: Int
} deriving (Show)

-- expect a null-terminated string

#22 "haskell/eof/03_eof_rule.hs"
yy0 :: State -> Int -> Int
yy0 State{..} _cnt =
    let yych = BS.index _str _cur in
    case yych of
        _c | 0x20 == _c ->
            let cur = _cur + 1 in let _cur = cur in
            yy3 State{..} _cnt
        _c | 0x27 == _c ->
            let cur = _cur + 1 in let _cur = cur in
            yy5 State{..} _cnt
        _c | True ->
            if _cur >= _lim then
                yy10 State{..} _cnt
            else
                let cur = _cur + 1 in let _cur = cur in
                yy1 State{..} _cnt

yy1 :: State -> Int -> Int
yy1 State{..} _cnt =
    yy2 State{..} _cnt

yy2 :: State -> Int -> Int
yy2 State{..} _cnt =
#31 "haskell/eof/03_eof_rule.re"
    (-1)
#48 "haskell/eof/03_eof_rule.hs"

yy3 :: State -> Int -> Int
yy3 State{..} _cnt =
    let yych = BS.index _str _cur in
    case yych of
        _c | 0x20 == _c ->
            let cur = _cur + 1 in let _cur = cur in
            yy3 State{..} _cnt
        _c | True ->
            yy4 State{..} _cnt

yy4 :: State -> Int -> Int
yy4 State{..} _cnt =
#34 "haskell/eof/03_eof_rule.re"
    lexer State{..} _cnt
#64 "haskell/eof/03_eof_rule.hs"

yy5 :: State -> Int -> Int
yy5 State{..} _cnt =
    let _mar = _cur in
    let yych = BS.index _str _cur in
    if yych <= 0x00 then
        if _cur >= _lim then
            yy2 State{..} _cnt
        else
            let cur = _cur + 1 in let _cur = cur in
            yy6 State{..} _cnt
    else
        yy7 State{..} _cnt yych

yy6 :: State -> Int -> Int
yy6 State{..} _cnt =
    let yych = BS.index _str _cur in
    yy7 State{..} _cnt yych

yy7 :: State -> Int -> Word8 -> Int
yy7 State{..} _cnt yych =
    case yych of
        _c | 0x27 == _c ->
            let cur = _cur + 1 in let _cur = cur in
            yy8 State{..} _cnt
        _c | 0x5C == _c ->
            let cur = _cur + 1 in let _cur = cur in
            yy9 State{..} _cnt
        _c | True ->
            if _cur >= _lim then
                yy11 State{..} _cnt
            else
                let cur = _cur + 1 in let _cur = cur in
                yy6 State{..} _cnt

yy8 :: State -> Int -> Int
yy8 State{..} _cnt =
#33 "haskell/eof/03_eof_rule.re"
    lexer State{..} (_cnt + 1)
#104 "haskell/eof/03_eof_rule.hs"

yy9 :: State -> Int -> Int
yy9 State{..} _cnt =
    let yych = BS.index _str _cur in
    if yych <= 0x00 then
        if _cur >= _lim then
            yy11 State{..} _cnt
        else
            let cur = _cur + 1 in let _cur = cur in
            yy6 State{..} _cnt
    else
        let cur = _cur + 1 in let _cur = cur in
        yy6 State{..} _cnt

yy10 :: State -> Int -> Int
yy10 State{..} _cnt =
#32 "haskell/eof/03_eof_rule.re"
    _cnt
#123 "haskell/eof/03_eof_rule.hs"

yy11 :: State -> Int -> Int
yy11 State{..} _cnt =
    let _cur = _mar in
    yy2 State{..} _cnt

lexer :: State -> Int -> Int
lexer State{..} _cnt =
    yy0 State{..} _cnt

#35 "haskell/eof/03_eof_rule.re"


main :: IO ()
main = do
    let test s n = do
            let st = State {
                    _str = s,
                    _cur = 0, 
                    _mar = 0,
                    _lim = BS.length s - 1} -- terminating null not included

            when (lexer st 0 /= n) $ error "failed"

    test "\0" 0
    test "'qu\0tes' 'are' 'fine: \\'' \0" 3
    test "'unterminated\\'\0" (-1)