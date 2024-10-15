-- Generated by re2hs
{-# LANGUAGE RecordWildCards #-}
#1 "haskell/reuse/reuse.re"
-- re2hs $INPUT -o $OUTPUT --input-encoding utf8
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

-- This example supports multiple input encodings: UTF-8 and UTF-32.
-- Both lexers are generated from the same rules block, and the use
-- blocks add only encoding-specific configurations.

import Control.Monad (when)
import Data.Array
import Data.Word

data State a = State {
    _yyinput :: a,
    _yycursor :: Int,
    _yymarker :: Int
}

#25 "haskell/reuse/reuse.re"



#27 "haskell/reuse/reuse.hs"
yy0 :: State (Array Int Word8) -> Maybe Int
yy0 State{..} =
    let yych = (!) _yyinput _yycursor in
    let __ = _yycursor + 1 in let _yycursor = __ in
    case yych of
        _c | 0xE2 == _c ->
            yy3 State{..}
        _c | True ->
            yy1 State{..}

yy1 :: State (Array Int Word8) -> Maybe Int
yy1 State{..} =
    yy2 State{..}

yy2 :: State (Array Int Word8) -> Maybe Int
yy2 State{..} =
#24 "haskell/reuse/reuse.re"
    Nothing
#46 "haskell/reuse/reuse.hs"

yy3 :: State (Array Int Word8) -> Maybe Int
yy3 State{..} =
    let _yymarker = _yycursor in
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x88 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy4 State{..}
        _c | True ->
            yy2 State{..}

yy4 :: State (Array Int Word8) -> Maybe Int
yy4 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x80 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy6 State{..}
        _c | True ->
            yy5 State{..}

yy5 :: State (Array Int Word8) -> Maybe Int
yy5 State{..} =
    let _yycursor = _yymarker in
    yy2 State{..}

yy6 :: State (Array Int Word8) -> Maybe Int
yy6 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x78 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy7 State{..}
        _c | True ->
            yy5 State{..}

yy7 :: State (Array Int Word8) -> Maybe Int
yy7 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x20 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy8 State{..}
        _c | True ->
            yy5 State{..}

yy8 :: State (Array Int Word8) -> Maybe Int
yy8 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0xE2 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy9 State{..}
        _c | True ->
            yy5 State{..}

yy9 :: State (Array Int Word8) -> Maybe Int
yy9 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x88 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy10 State{..}
        _c | True ->
            yy5 State{..}

yy10 :: State (Array Int Word8) -> Maybe Int
yy10 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x83 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy11 State{..}
        _c | True ->
            yy5 State{..}

yy11 :: State (Array Int Word8) -> Maybe Int
yy11 State{..} =
    let yych = (!) _yyinput _yycursor in
    case yych of
        _c | 0x79 == _c ->
            let __ = _yycursor + 1 in let _yycursor = __ in
            yy12 State{..}
        _c | True ->
            yy5 State{..}

yy12 :: State (Array Int Word8) -> Maybe Int
yy12 State{..} =
#23 "haskell/reuse/reuse.re"
    Just _yycursor
#138 "haskell/reuse/reuse.hs"

lex8 :: State (Array Int Word8) -> Maybe Int
lex8 State{..} =
    yy0 State{..}

#31 "haskell/reuse/reuse.re"



#148 "haskell/reuse/reuse.hs"
yy13 :: State (Array Int Int) -> Maybe Int
yy13 State{..} =
    let yych = (!) _yyinput _yycursor in
    let __ = _yycursor + 1 in let _yycursor = __ in
    if yych == 0x00002200 then yy16 State{..}
    else yy14 State{..}

yy14 :: State (Array Int Int) -> Maybe Int
yy14 State{..} =
    yy15 State{..}

yy15 :: State (Array Int Int) -> Maybe Int
yy15 State{..} =
#24 "haskell/reuse/reuse.re"
    Nothing
#164 "haskell/reuse/reuse.hs"

yy16 :: State (Array Int Int) -> Maybe Int
yy16 State{..} =
    let _yymarker = _yycursor in
    let yych = (!) _yyinput _yycursor in
    if yych == 0x00000078 then
        let __ = _yycursor + 1 in let _yycursor = __ in
        yy17 State{..}
    else
        yy15 State{..}

yy17 :: State (Array Int Int) -> Maybe Int
yy17 State{..} =
    let yych = (!) _yyinput _yycursor in
    if yych == 0x00000020 then
        let __ = _yycursor + 1 in let _yycursor = __ in
        yy19 State{..}
    else
        yy18 State{..}

yy18 :: State (Array Int Int) -> Maybe Int
yy18 State{..} =
    let _yycursor = _yymarker in
    yy15 State{..}

yy19 :: State (Array Int Int) -> Maybe Int
yy19 State{..} =
    let yych = (!) _yyinput _yycursor in
    if yych == 0x00002203 then
        let __ = _yycursor + 1 in let _yycursor = __ in
        yy20 State{..}
    else
        yy18 State{..}

yy20 :: State (Array Int Int) -> Maybe Int
yy20 State{..} =
    let yych = (!) _yyinput _yycursor in
    if yych == 0x00000079 then
        let __ = _yycursor + 1 in let _yycursor = __ in
        yy21 State{..}
    else
        yy18 State{..}

yy21 :: State (Array Int Int) -> Maybe Int
yy21 State{..} =
#23 "haskell/reuse/reuse.re"
    Just _yycursor
#212 "haskell/reuse/reuse.hs"

lex32 :: State (Array Int Int) -> Maybe Int
lex32 State{..} =
    yy13 State{..}

#37 "haskell/reuse/reuse.re"


main :: IO ()
main = do
    let make_st l = State {
            _yyinput = listArray (0, length l - 1) l,
            _yycursor = 0,
            _yymarker = 0}

    let s8 = [0xe2, 0x88, 0x80, 0x78, 0x20, 0xe2, 0x88, 0x83, 0x79]
    when (lex8 (make_st s8) /= Just (length s8)) $ error "lex8 failed"

    let s32 = [0x2200, 0x78, 0x20, 0x2203, 0x79]
    when (lex32 (make_st s32) /= Just (length s32)) $ error "lex32 failed"
