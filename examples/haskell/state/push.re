-- re2hs $INPUT -o $OUTPUT -fi
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Concurrent.Chan
import Control.Monad
import Data.ByteString as BS
import Text.Printf

debug :: PrintfType r => String -> r
debug format = printf format -- not sure how to make it conditional

data State = State {
    _pipe :: !(Chan BS.ByteString),
    _buf :: !BS.ByteString,
    _cur :: !Int,
    _mar :: !Int,
    _lim :: !Int,
    _tok :: !Int,
    _eof :: !Bool,
    _state :: !Int,
    _recv :: !Int
}

data Status = End | Ready | Waiting | BadPacket deriving (Eq)

/*!re2c
    re2c:define:YYFN       = ["lexer;IO (State, Status)", "State{..};State;!State{..}"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "return $ BS.index _buf _cur";
    re2c:define:YYSKIP     = "_cur <- return $ _cur + 1";
    re2c:define:YYBACKUP   = "let _mar = _cur";
    re2c:define:YYRESTORE  = "let _cur = _mar";
    re2c:define:YYGETSTATE = "_state";
    re2c:define:YYSETSTATE = "let _state = @@";
    re2c:define:YYLESSTHAN = "_cur >= _lim";
    re2c:define:YYFILL     = "return (State{..}, Waiting)";
    re2c:eof = 0;
    re2c:monadic = 1;

    packet = [a-z]+[;];

    *      { return (State{..}, BadPacket) }
    $      { return (State{..}, End) }
    packet { lexer State{_tok = _cur, _recv = _recv + 1, ..} }
*/

fill :: State -> IO (State, Status)
fill st@State{..} = do
    case _eof of
        True -> return (st, End)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- readChan _pipe
            return (State {
                _buf = BS.concat [(BS.init . BS.drop _tok) _buf, chunk, "\0"],
                _cur = _cur - _tok,
                _mar = _mar - _tok,
                _lim = _lim - _tok + BS.length chunk, -- exclude terminating null
                _tok = 0,
                _eof = BS.null chunk, -- end of file?
                ..}, Ready)

loop :: State -> [BS.ByteString] -> IO Status
loop State{..} packets = do
    (State{..}, status) <- lexer State{..}
    case status of
        End -> do
            debug "done: got %d packets\n" _recv
            return End
        Waiting -> do
            debug "waiting...\n"
            packets' <- case packets of
                [] -> do
                    writeChan _pipe BS.empty
                    return []
                p:ps -> do
                    debug "sent packet '%s'\n" (show p)
                    writeChan _pipe p
                    return ps
            (State{..}, status') <- fill State{..}
            case status' of
                Ready -> loop State{..} packets'
                _ -> error "unexpected status after fill"
        BadPacket -> do
            debug "error: ill-formed packet\n"
            return BadPacket
        _ -> error "unexpected status"

test :: [BS.ByteString] -> Status -> IO ()
test packets expect = do
    pipe <- newChan -- emulate pipe using a chan of bytestrings
    let st = State {
        _pipe = pipe,
        _buf = BS.singleton 0, -- null sentinel triggers YYFILL
        _cur = 0,
        _mar = 0,
        _tok = 0,
        _lim = 0,
        _eof = False,
        _state = -1,
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
