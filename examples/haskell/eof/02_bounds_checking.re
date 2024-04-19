-- re2hs $INPUT -o $OUTPUT
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE OverloadedRecordDot #-}

import Control.Exception
import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    buf :: BS.ByteString,
    cur :: Int,
    lim :: Int
} deriving (Show)

data FillException = UnexpectedFill deriving (Show)
instance Exception FillException

yymaxfill :: Int
/*!max:re2c*/

/*!re2c
    re2c:define:YYFN       = ["lexer;IO Int", "_s;State", "_cnt;Int"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "return $ BS.index _s.buf _s.cur";
    re2c:define:YYSKIP     = "_s <- return _s{cur = _s.cur + 1}";
    re2c:define:YYLESSTHAN = "_s.lim - _s.cur < @@";
    re2c:define:YYFILL     = "throw UnexpectedFill";
    re2c:monadic = 1; // YYFILL requires monadic do-notation for `when` conditions

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        -- check that it is the sentinel, not some unexpected null
        return $ if _s.cur == BS.length _s.buf - yymaxfill + 1 then _cnt else (-1)
    }
    str  { lexer _s (_cnt + 1) }
    [ ]+ { lexer _s _cnt }
    *    { return (-1) }
*/

main :: IO ()
main = do
    let test s n = do
            let buf = BS.concat [s, BS.replicate yymaxfill 0]
            let st = State {buf = buf, cur = 0, lim = BS.length buf}
            m <- catch (lexer st 0) (\(_ :: FillException) -> return (-2))
            when (m /= n) $ error "failed"

    test "" 0
    test "'unterminated\\'" (-2)
    test "'qu\0tes' 'are' 'fine: \\'' " 3
    test "'unexpected' \0 'null'" (-1)
