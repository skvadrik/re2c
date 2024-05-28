-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Monad
import Data.ByteString as BS
import Data.Word
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
    _eof :: !Bool
} deriving (Show)

/*!re2c
    re2c:define:YYFN       = ["lexer;IO Int", "State{..};State;!State{..}", "_count;Int;!_count"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "return $ BS.index _buf _cur";
    re2c:define:YYSKIP     = "_cur <- return $ _cur + 1";
    re2c:define:YYBACKUP   = "let _mar = _cur";
    re2c:define:YYRESTORE  = "let _cur = _mar";
    re2c:define:YYLESSTHAN = "_cur >= _lim";
    re2c:define:YYFILL     = "(State{..}, yyfill) <- fill State{..}";
    re2c:eof = 0;
    re2c:monadic = 1;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return (-1) }
    $    { return _count }
    str  { lexer State{_tok = _cur, ..} (_count + 1) }
    [ ]+ { lexer State{_tok = _cur, ..} _count }
*/

fill :: State -> IO (State, Bool)
fill State{..} = do
    case _eof of
        True -> return (State{..}, False)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- BS.hGet _file chunk_size
            return (State {
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
    BS.writeFile fname $ BS.concat ["'qu\0tes' 'are' 'fine: \\'' " | _ <- [1..chunk_size]]
    let expect = 3 * chunk_size -- the total number of strings in file

    -- Run lexer on the prepared file.
    fh <- openFile fname ReadMode
    let st = State {
        _file = fh,
        _buf = BS.singleton 0,
        _cur = 0,
        _mar = 0,
        _tok = 0,
        _lim = 0,
        _eof = False
    }
    result <- lexer st 0
    hClose fh

    -- Cleanup.
    removeFile fname

    -- Check result.
    when (result /= expect) $ error $ "expected " ++ show expect ++ ", got " ++ show result
    return ()
