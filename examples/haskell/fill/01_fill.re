-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedRecordDot #-}
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
    file :: !Handle,
    buf :: !BS.ByteString,
    cur :: !Int,
    mar :: !Int,
    lim :: !Int,
    tok :: !Int,
    eof :: !Bool
} deriving (Show)

/*!re2c
    re2c:define:YYFN       = ["lexer;IO Int", "_st;State;!_st", "_count;Int;!_count"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "return $ BS.index _st.buf _st.cur";
    re2c:define:YYSKIP     = "_st <- return _st{cur = _st.cur + 1}";
    re2c:define:YYBACKUP   = "_st <- return _st{mar = _st.cur}";
    re2c:define:YYRESTORE  = "_st <- return _st{cur = _st.mar}";
    re2c:define:YYLESSTHAN = "_st.cur >= _st.lim";
    re2c:define:YYFILL     = "(_st, yyfill) <- fill _st";
    re2c:eof = 0;
    re2c:monadic = 1;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { return (-1) }
    $    { return _count }
    str  { lexer _st{tok = _st.cur} (_count + 1) }
    [ ]+ { lexer _st{tok = _st.cur} _count }
*/

fill :: State -> IO (State, Bool)
fill st = do
    case st.eof of
        True -> return (st, False)
        False -> do
            -- Discard everything up to the current token, cut off terminating null,
            -- read new chunk from file and reappend terminating null at the end.
            chunk <- BS.hGet st.file chunk_size
            let st' = st{
                buf = BS.concat [(BS.init . BS.drop st.tok) st.buf, chunk, "\0"],
                cur = st.cur - st.tok,
                mar = st.mar - st.tok,
                lim = st.lim - st.tok + BS.length chunk, -- exclude terminating null
                tok = 0,
                eof = BS.null chunk -- end of file?
            }
            return (st', True)

main :: IO ()
main = do
    let fname = "input"

    -- Prepare input file.
    BS.writeFile fname $ BS.concat ["'qu\0tes' 'are' 'fine: \\'' " | _ <- [1..chunk_size]]
    let expect = 3 * chunk_size -- the total number of strings in file

    -- Run lexer on the prepared file.
    fh <- openFile fname ReadMode
    let st = State {
        file = fh,
        buf = BS.singleton 0,
        cur = 0,
        mar = 0,
        tok = 0,
        lim = 0,
        eof = False
    }
    result <- lexer st 0
    hClose fh

    -- Cleanup.
    removeFile fname

    -- Check result.
    when (result /= expect) $ error $ "expected " ++ show expect ++ ", got " ++ show result
    return ()
