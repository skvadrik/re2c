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
    _yyinput :: !BS.ByteString,
    _yycursor :: !Int,
    _yymarker :: !Int,
    _yylimit :: !Int,
    _token :: !Int,
    _eof :: !Bool,
    _count :: !Int
}

%{
    re2c:YYFN = ["lexer;IO Int", "State{..};State;!State{..}"];
    re2c:YYCTYPE = "Word8";
    re2c:YYPEEK = "BS.index";
    re2c:YYFILL = "(State{..}, yyfill) <- fill State{..}";
    re2c:eof = 0;
    re2c:monadic = 1;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return (-1) }
    $    { return _count }
    str  { lexer State{_token = _yycursor, _count = _count + 1, ..} }
    [ ]+ { lexer State{_token = _yycursor, ..} }
%}

fill :: State -> IO (State, Bool)
fill State{..} = do
    case _eof of
        True -> return (State{..}, False)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- BS.hGet _file chunk_size
            return (State {
                _yyinput = BS.concat [(BS.init . BS.drop _token) _yyinput, chunk, "\0"],
                _yycursor = _yycursor - _token,
                _yymarker = _yymarker - _token,
                _yylimit = _yylimit - _token + BS.length chunk, -- exclude terminating null
                _token = 0,
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
        _yyinput = BS.singleton 0,
        _yycursor = 0,
        _yymarker = 0,
        _token = 0,
        _yylimit = 0,
        _eof = False,
        _count = 0
    }
    result <- lexer st
    hClose fh

    -- Cleanup.
    removeFile fname

    -- Check result.
    when (result /= expect) $ error $ "expected " ++ show expect ++ ", got " ++ show result
    return ()
