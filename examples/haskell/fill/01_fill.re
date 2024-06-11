-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

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
    _str :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    _lim :: !Int,
    _tok :: !Int,
    _eof :: !Bool,
    _cnt :: !Int
}

/*!re2c
    re2c:define:YYFN = ["lexer;IO Int", "State{..};State;!State{..}"];
    re2c:define:YYCTYPE = "Word8";
    re2c:define:YYPEEK = "BS.index";
    re2c:define:YYFILL = "(State{..}, yyfill) <- fill State{..}";
    re2c:eof = 0;
    re2c:monadic = 1;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return (-1) }
    $    { return _cnt }
    str  { lexer State{_tok = _cur, _cnt = _cnt + 1, ..} }
    [ ]+ { lexer State{_tok = _cur, ..} }
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
                _str = BS.concat [(BS.init . BS.drop _tok) _str, chunk, "\0"],
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
        _str = BS.singleton 0,
        _cur = 0,
        _mar = 0,
        _tok = 0,
        _lim = 0,
        _eof = False,
        _cnt = 0
    }
    result <- lexer st
    hClose fh

    -- Cleanup.
    removeFile fname

    -- Check result.
    when (result /= expect) $ error $ "expected " ++ show expect ++ ", got " ++ show result
    return ()
