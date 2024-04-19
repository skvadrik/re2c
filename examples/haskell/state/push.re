-- re2hs $INPUT -o $OUTPUT -fi
{-# LANGUAGE OverloadedRecordDot #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Concurrent.Chan
import Control.Monad
import Data.ByteString as BS
import Text.Printf

debug :: PrintfType r => String -> r
debug format = printf format

data State = State {
    pipe :: !(Chan BS.ByteString),
    buf :: !BS.ByteString,
    cur :: !Int,
    mar :: !Int,
    lim :: !Int,
    tok :: !Int,
    eof :: !Bool,
    state :: !Int,
    recv :: !Int
}

data Status = End | Ready | Waiting | BadPacket deriving (Eq)

/*!re2c
    re2c:define:YYFN       = ["lexer;IO (State, Status)", "_st;State;!"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "return $ BS.index _st.buf _st.cur";
    re2c:define:YYSKIP     = "_st <- return _st{cur = _st.cur + 1}";
    re2c:define:YYBACKUP   = "_st <- return _st{mar = _st.cur}";
    re2c:define:YYRESTORE  = "_st <- return _st{cur = _st.mar}";
    re2c:define:YYGETSTATE = "_st.state";
    re2c:define:YYSETSTATE = "_st <- return _st{state = @@}";
    re2c:define:YYLESSTHAN = "_st.cur >= _st.lim";
    re2c:define:YYFILL     = "return (_st, Waiting)";
    re2c:eof = 0;
    re2c:monadic = 1;

    packet = [a-z]+[;];

    *      { return (_st, BadPacket) }
    $      { return (_st, End) }
    packet { lexer _st{tok = _st.cur, recv = _st.recv + 1} }
*/

fill :: State -> IO (State, Status)
fill st = do
    case st.eof of
        True -> return (st, End)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- readChan st.pipe
            let st' = st{
                buf = BS.concat [(BS.init . BS.drop st.tok) st.buf, chunk, "\0"],
                cur = st.cur - st.tok,
                mar = st.mar - st.tok,
                lim = st.lim - st.tok + BS.length chunk, -- exclude terminating null
                tok = 0,
                eof = BS.null chunk -- end of file?
            }
            return (st', Ready)

loop :: State -> [BS.ByteString] -> IO Status
loop st packets = do
    (st', status) <- lexer st
    case status of
        End -> do
            debug "done: got %d packets\n" st'.recv
            return End
        Waiting -> do
            debug "waiting...\n"
            packets' <- case packets of
                [] -> do
                    writeChan st'.pipe BS.empty
                    return []
                p:ps -> do
                    debug "sent packet '%s'\n" (show p)
                    writeChan st'.pipe p
                    return ps
            (st'', status') <- fill st'
            case status' of
                Ready -> loop st'' packets'
                _ -> error "unexpected status after fill"
        BadPacket -> do
            debug "error: ill-formed packet\n"
            return BadPacket
        _ -> error "unexpected status"

test :: [BS.ByteString] -> Status -> IO ()
test packets expect = do
    pipe <- newChan -- emulate pipe using a chan of bytestrings
    let st = State {
        pipe = pipe,
        buf = BS.singleton 0, -- null sentinel triggers YYFILL
        cur = 0,
        mar = 0,
        tok = 0,
        lim = 0,
        eof = False,
        state = -1,
        recv = 0
    }
    status <- loop st packets
    when (status /= expect) $ error "failed"
    return ()

main :: IO ()
main = do
    test [] End
    test ["ze", "ro;o", "ne", ";t", "wo;thr", "e", "e", ";", "four;"] End
    test ["zer0;"] BadPacket
