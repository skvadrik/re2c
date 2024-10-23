-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Exception
import Control.Monad (when)
import qualified Data.ByteString as BS

data State = State {
    _yyinput :: BS.ByteString,
    _yycursor :: Int,
    _yylimit :: Int,
    _count :: Int
}

data FillException = UnexpectedFill deriving (Show)
instance Exception FillException

yymaxfill :: Int
%{max %}

%{
    re2c:YYFN  = ["lexer;IO Int", "State{..};State"];
    re2c:YYPEEK = "BS.index";
    re2c:YYFILL = "throw UnexpectedFill";
    re2c:monadic = 1; // YYFILL requires monadic do-notation for `when` conditions

    str = ['] ([^'\\] | [\\][^])* ['];

    [\x00] {
        -- check that it is the sentinel, not some unexpected null
        return $ if _yycursor == BS.length _yyinput - yymaxfill + 1 then _count else (-1)
    }
    str  { lexer State{_count = _count + 1, ..} }
    [ ]+ { lexer State{..} }
    *    { return (-1) }
%}

main :: IO ()
main = do
    let test s n = do
            let buf = BS.concat [s, BS.replicate yymaxfill 0]
            let st = State {
                    _yyinput = buf,
                    _yycursor = 0,
                    _yylimit = BS.length buf,
                    _count = 0}
            m <- catch (lexer st) (\(_ :: FillException) -> return (-2))
            when (m /= n) $ error "failed"

    test "" 0
    test "'unterminated\\'" (-2)
    test "'qu\0tes' 'are' 'fine: \\'' " 3
    test "'unexpected' \0 'null'" (-1)
