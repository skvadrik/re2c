-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Exception
import Control.Monad (when)
import qualified Data.ByteString as BS

data State = State {
    _str :: BS.ByteString,
    _cur :: Int,
    _lim :: Int,
    _cnt :: Int
}

data FillException = UnexpectedFill deriving (Show)
instance Exception FillException

yymaxfill :: Int
/*!max:re2c*/

/*!re2c
    re2c:define:YYFN  = ["lexer;IO Int", "State{..};State"];
    re2c:define:YYPEEK = "BS.index";
    re2c:define:YYFILL = "throw UnexpectedFill";
    re2c:monadic = 1; // YYFILL requires monadic do-notation for `when` conditions

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        -- check that it is the sentinel, not some unexpected null
        return $ if _cur == BS.length _str - yymaxfill + 1 then _cnt else (-1)
    }
    str  { lexer State{_cnt = _cnt + 1, ..} }
    [ ]+ { lexer State{..} }
    *    { return (-1) }
*/

main :: IO ()
main = do
    let test s n = do
            let buf = BS.concat [s, BS.replicate yymaxfill 0]
            let st = State {_str = buf, _cur = 0, _lim = BS.length buf, _cnt = 0}
            m <- catch (lexer st) (\(_ :: FillException) -> return (-2))
            when (m /= n) $ error "failed"

    test "" 0
    test "'unterminated\\'" (-2)
    test "'qu\0tes' 'are' 'fine: \\'' " 3
    test "'unexpected' \0 'null'" (-1)
