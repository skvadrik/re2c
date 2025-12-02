-- re2hs $INPUT -o $OUTPUT -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.Array
import Data.Int
import Data.Word

data State a = State {
    _yyinput :: a,
    _yycursor :: Int
}

%{rules
    re2c:yyfill:enable = 0;
    re2c:YYPEEK = "(!)";

    "\xff" { True }
    *      { False }
%}

%{use
    re2c:YYFN = ["lex_unsigned;Bool", "State{..};State (Array Int Word8)"];
    re2c:YYCTYPE = Word8;
%}

%{use
    re2c:YYFN = ["lex_signed;Bool", "State{..};State (Array Int Int8)"];
    re2c:YYCTYPE = Int8; // should be unsigned!
%}

main :: IO ()
main = do
    let make_st l = State {
            _yyinput = listArray (0, length l - 1) l,
            _yycursor = 0}

    let u8 = [0x60] -- ok, 'a' should not match
    when (lex_unsigned (make_st u8) /= False) $ error "lex_unsigned"

    let s8 = [0x60] -- error, 'a' does match
    when (lex_signed (make_st s8) /= True) $ error "lex_signed"
