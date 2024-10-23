-- re2hs $INPUT -o $OUTPUT -fi
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Concurrent.Chan
import Control.Monad
import Data.ByteString as BS
import Text.Printf

debug :: IO () -> IO ()
debug = when False

data State = State {
    _pipe :: !(Chan BS.ByteString),
    _yyinput :: !BS.ByteString,
    _yycursor :: !Int,
    _yymarker :: !Int,
    _yylimit :: !Int,
    _token :: !Int,
    _eof :: !Bool,
    _yystate :: !Int,
    _recv :: !Int
}

data Status = End | Ready | Waiting | BadPacket deriving (Eq)

%{
    re2c:YYFN = ["lexer;IO (State, Status)", "State{..};State;!State{..}"];
    re2c:YYPEEK = "BS.index";
    re2c:YYFILL = "return (State{..}, Waiting)";
    re2c:eof = 0;
    re2c:monadic = 1;

    packet = [a-z]+[;];

    *      { return (State{..}, BadPacket) }
    $      { return (State{..}, End) }
    packet { lexer State{_token = _yycursor, _recv = _recv + 1, ..} }
%}

fill :: State -> IO (State, Status)
fill st@State{..} = do
    case _eof of
        True -> return (st, End)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- readChan _pipe
            return (State {
                _yyinput = BS.concat [(BS.init . BS.drop _token) _yyinput, chunk, "\0"],
                _yycursor = _yycursor - _token,
                _yymarker = _yymarker - _token,
                _yylimit = _yylimit - _token + BS.length chunk, -- exclude terminating null
                _token = 0,
                _eof = BS.null chunk, -- end of file?
                ..}, Ready)

loop :: State -> [BS.ByteString] -> IO Status
loop State{..} packets = do
    (State{..}, status) <- lexer State{..}
    case status of
        End -> do
            debug $ printf "done: got %d packets\n" _recv
            return End
        Waiting -> do
            debug $ printf "waiting...\n"
            packets' <- case packets of
                [] -> do
                    writeChan _pipe BS.empty
                    return []
                p:ps -> do
                    debug $ printf "sent packet '%s'\n" (show p)
                    writeChan _pipe p
                    return ps
            (State{..}, status') <- fill State{..}
            case status' of
                Ready -> loop State{..} packets'
                _ -> error "unexpected status after fill"
        BadPacket -> do
            debug $ printf "error: ill-formed packet\n"
            return BadPacket
        _ -> error "unexpected status"

test :: [BS.ByteString] -> Status -> IO ()
test packets expect = do
    pipe <- newChan -- emulate pipe using a chan of bytestrings
    let st = State {
        _pipe = pipe,
        _yyinput = BS.singleton 0, -- null sentinel triggers YYFILL
        _yycursor = 0,
        _yymarker = 0,
        _token = 0,
        _yylimit = 0,
        _eof = False,
        _yystate = -1,
        _recv = 0
    }
    status <- loop st packets
    when (status /= expect) $ error "failed"
    return ()

main :: IO ()
main = do
    test [] End
    test ["ze", "ro;o", "ne", ";t", "wo;thr", "e", "e", ";", "four;"] End
    test ["zer0;"] BadPacket
