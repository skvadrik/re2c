-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE RecordWildCards #-}

import Control.Exception
import Control.Monad (when)
import Data.ByteString as BS

data State = State {
    _buf :: BS.ByteString,
    _cur :: Int,
    _lim :: Int
} deriving (Show)

data FillException = UnexpectedFill deriving (Show)
instance Exception FillException

yymaxfill :: Int
/*!max:re2c*/

/*!re2c
    re2c:define:YYFN       = ["lexer;IO Int", "State{..};State", "_cnt;Int"];
    re2c:define:YYCTYPE    = "Word8";
    re2c:define:YYPEEK     = "return $ BS.index _buf _cur";
    re2c:define:YYSKIP     = "_cur <- return $ _cur + 1";
    re2c:define:YYLESSTHAN = "_lim - _cur < @@";
    re2c:define:YYFILL     = "throw UnexpectedFill";
    re2c:monadic = 1; // YYFILL requires monadic do-notation for `when` conditions

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        -- check that it is the sentinel, not some unexpected null
        return $ if _cur == BS.length _buf - yymaxfill + 1 then _cnt else (-1)
    }
    str  { lexer State{..} (_cnt + 1) }
    [ ]+ { lexer State{..} _cnt }
    *    { return (-1) }
*/

main :: IO ()
main = do
    let test s n = do
            let buf = BS.concat [s, BS.replicate yymaxfill 0]
            let st = State {_buf = buf, _cur = 0, _lim = BS.length buf}
            m <- catch (lexer st 0) (\(_ :: FillException) -> return (-2))
            when (m /= n) $ error "failed"

    test "" 0
    test "'unterminated\\'" (-2)
    test "'qu\0tes' 'are' 'fine: \\'' " 3
    test "'unexpected' \0 'null'" (-1)
