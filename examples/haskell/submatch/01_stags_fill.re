-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedRecordDot #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad
import Data.ByteString as BS
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
    eof :: !Bool,
    /*!stags:re2c format = '\n@@{tag} :: !Int,'; */
    t1 :: !Int,
    t2 :: !Int,
    t3 :: !Int,
    t4 :: !Int,
    t5 :: !Int
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
    re2c:define:YYFN        = ["lexer;IO [SemVer]", "_st;State;!_st", "_vs;[SemVer];!_vs"];
    re2c:define:YYCTYPE     = "Word8";
    re2c:define:YYPEEK      = "return $ BS.index _st.buf _st.cur";
    re2c:define:YYSKIP      = "_st <- return _st{cur = _st.cur + 1}";
    re2c:define:YYBACKUP    = "_st <- return _st{mar = _st.cur}";
    re2c:define:YYRESTORE   = "_st <- return _st{cur = _st.mar}";
    re2c:define:YYSTAGP     = "_st <- return _st{@@{tag} = _st.cur}";
    re2c:define:YYSTAGN     = "_st <- return _st{@@{tag} = none}";
    re2c:define:YYCOPYSTAG  = "_st <- return _st{@@{lhs} = _st.@@{rhs}}";
    re2c:define:YYSHIFTSTAG = "_st <- return $ if _st.@@{tag} == none "
                                  "then _st "
                                  "else _st{@@{tag} = _st.@@{tag} + (@@{shift})}";
    re2c:define:YYLESSTHAN  = "_st.cur >= _st.lim";
    re2c:define:YYFILL      = "(_st, yyfill) <- fill _st";
    re2c:eof = 0;
    re2c:monadic = 1;
    re2c:tags = 1;

    num = [0-9]+;

    @t1 num @t2 "." @t3 num @t4 ("." @t5 num)? [\n] {
        let v = SemVer {
            major = s2n _st.buf _st.t1 _st.t2,
            minor = s2n _st.buf _st.t3 _st.t4,
            patch = if _st.t5 == none then 0 else s2n _st.buf _st.t5 (_st.cur - 1)
        }
        lexer _st (v: _vs)
    }
    $ { return _vs }
    * { error "lexer failed" }
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
    BS.writeFile fname $ BS.concat ["1.22.333\n" | _ <- [1..chunk_size]]
    let expect = [SemVer {major = 1, minor = 22, patch = 333} | _ <- [1..chunk_size]]

    -- Run lexer on the prepared file.
    fh <- openFile fname ReadMode
    let st = State {
        file = fh,
        buf = BS.singleton 0,
        cur = 0,
        mar = 0,
        tok = 0,
        lim = 0,
        eof = False,
        /*!stags:re2c format = '\n@@{tag} = none,'; */
        t1 = none,
        t2 = none,
        t3 = none,
        t4 = none,
        t5 = none
    }
    result <- lexer st []
    hClose fh

    -- Cleanup.
    removeFile fname

    -- Check result.
    when (result /= expect) $ error $ "expected " ++ show expect ++ ", got " ++ show result
    return ()
