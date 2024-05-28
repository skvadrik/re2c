-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad
import Data.ByteString as BS
import GHC.IO.Handle
import System.Directory
import System.IO

chunk_size :: Int
chunk_size = 4096

data State = State {
    _file :: !Handle,
    _buf :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    _lim :: !Int,
    _tok :: !Int,
    _eof :: !Bool,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    _1 :: !Int,
    _2 :: !Int,
    _3 :: !Int,
    _4 :: !Int,
    _5 :: !Int
} deriving (Show)

data SemVer = SemVer {
    major :: !Int,
    minor :: !Int,
    patch :: !Int
} deriving (Show, Eq)

none :: Int
none = -1

s2n :: BS.ByteString -> Int -> Int -> Int
s2n s i j = f i 0 where
    f k n = if k >= j then n else f (k + 1) (n * 10 + (fromIntegral (BS.index s k) - 48))

/*!re2c
    re2c:define:YYFN        = ["lexer;IO [SemVer]", "State{..};State", "_vers;[SemVer]"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "return $ BS.index _buf _cur";
    re2c:define:YYSKIP      = "_cur <- return $ _cur + 1";
    re2c:define:YYBACKUP    = "let _mar = _cur";
    re2c:define:YYRESTORE   = "let _cur = _mar";
    re2c:define:YYSTAGP     = "let @@{tag} = _cur";
    re2c:define:YYSTAGN     = "let @@{tag} = none";
    re2c:define:YYCOPYSTAG  = "let @@{lhs} = @@{rhs}";
    re2c:define:YYSHIFTSTAG = "@@{tag} <- return $ "
                                  "if @@{tag} == none then none else @@{tag} + (@@{shift})";
    re2c:define:YYLESSTHAN  = "_cur >= _lim";
    re2c:define:YYFILL      = "(State{..}, yyfill) <- fill State{..}";
    re2c:eof = 0;
    re2c:monadic = 1;
    re2c:tags = 1;
    re2c:tags:prefix = _t;

    num = [0-9]+;

    @_1 num @_2 "." @_3 num @_4 ("." @_5 num)? [\n] {
        let ver = SemVer {
            major = s2n _buf _1 _2,
            minor = s2n _buf _3 _4,
            patch = if _5 == none then 0 else s2n _buf _5 (_cur - 1)
        }
        lexer State{..} (ver: _vers)
    }
    $ { return _vers }
    * { error "lexer failed" }
*/

fill :: State -> IO (State, Bool)
fill State{..} = do
    case _eof of
        True -> return (State{..}, False)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- BS.hGet _file chunk_size
            return (State{
                _buf = BS.concat [(BS.init . BS.drop _tok) _buf, chunk, "\0"],
                _cur = _cur - _tok,
                _mar = _mar - _tok,
                _lim = _lim - _tok + BS.length chunk, -- exclude terminating null
                _tok = 0,
                _eof = BS.null chunk, -- end of file?
                ..}, True)

main :: IO ()
main = do
    let fname = "input"

    -- Prepare input file.
    BS.writeFile fname $ BS.concat ["1.22.333\n" | _ <- [1..chunk_size]]
    let expect = [SemVer {major = 1, minor = 22, patch = 333} | _ <- [1..chunk_size]]

    -- Run lexer on the prepared file.
    fh <- openFile fname ReadMode
    let st = State {
        _file = fh,
        _buf = BS.singleton 0,
        _cur = 0,
        _mar = 0,
        _tok = 0,
        _lim = 0,
        _eof = False,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        _1 = none,
        _2 = none,
        _3 = none,
        _4 = none,
        _5 = none
    }
    result <- lexer st []
    hClose fh

    -- Cleanup.
    removeFile fname

    -- Check result.
    when (result /= expect) $ error $ "expected " ++ show expect ++ ", got " ++ show result
    return ()
