-- re2hs $INPUT -o $OUTPUT -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Exception
import Control.Monad (when)
import qualified Data.ByteString as BS

data State = State {
    _yyinput :: BS.ByteString,
    _yycursor :: Int,
    _yymarker :: Int,
    _yylimit :: Int,
    _yyend :: Int
}

make_state :: BS.ByteString -> Int -> Int -> State
make_state s n m = State {
    _yyinput = s,
    _yycursor = 0,
    _yymarker = 0,
    _yylimit = n,
    _yyend = m}

%{rules:x
    re2c:YYPEEK = "BS.index";
    re2c:monadic = 1;

    $           { return 0 }
    *           { return 1 }
    [a] $       { return 2 }
    [a]         { return 3 }
    [b] $ | [b] { return 4 }
    [c]+ $      { return 5 }
%}

%{use:x
    re2c:YYFN = ["lex_simple;IO Int", "State{..};State"];
    re2c:yyfill:enable = 0;
%}

%{use:x
    re2c:YYFN = ["lex_eof;IO Int", "State{..};State"];
    re2c:YYFILL = "let yyfill = False";
    re2c:YYEND = "_yycursor == _yylimit";
    re2c:eof = 0;
%}

data FillException = UnexpectedFill deriving (Show)
instance Exception FillException

yymaxfill :: Int
%{max%}

%{use:x
    re2c:YYFN  = ["lex_scc;IO Int", "State{..};State"];
    re2c:YYFILL = "throw UnexpectedFill";
    re2c:YYEND = "_yycursor == _yyend";
%}

main :: IO ()
main = do
    let test_simple s n = do
            m <- lex_simple $ make_state s (BS.length s - 1) 0
            when (m /= n) $ error "failed simple"

        test_eof s n = do
            m <- lex_eof $ make_state s (BS.length s - 1) 0
            when (m /= n) $ error "failed eof"

        test_scc s n = do
            let buf = BS.concat [s, BS.replicate yymaxfill 0]
            let st = make_state buf (BS.length buf) (BS.length s - 1)
            m <- catch (lex_scc st) (\(_ :: FillException) -> return (-1))
            when (m /= n) $ error "failed scc"

        test s n = do
            test_simple s n
            test_eof s n
            test_scc s n

    test "\0"  0
    test "a\0"  2
    test "ax\0"  3
    test "b\0"  4
    test "bx\0"  4
    test "ccc\0"  5
