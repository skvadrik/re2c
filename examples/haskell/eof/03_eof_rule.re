-- re2hs $INPUT -o $OUTPUT
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import qualified Data.ByteString as BS
import Data.Word

data State = State {
    _yyinput :: BS.ByteString,
    _yycursor :: Int,
    _yymarker :: Int,
    _yylimit :: Int,
    _count :: Int
}

-- expect a null-terminated string
%{
    re2c:YYFN = ["lexer;Int", "State{..};State"];
    re2c:YYCTYPE = "Word8";
    re2c:YYPEEK = "BS.index";
    re2c:eof = 0;
    re2c:yyfill:enable = 0;

    str = ['] ([^'\\] | [\\][^])* ['];

    *    { (-1) }
    $    { _count }
    str  { lexer State{_count = _count + 1, ..} }
    [ ]+ { lexer State{..} }
%}

main :: IO ()
main = do
    let test s n = do
            let st = State {
                    _yyinput = s,
                    _yycursor = 0, 
                    _yymarker = 0,
                    _yylimit = BS.length s - 1, -- terminating null not included
                    _count = 0}

            when (lexer st /= n) $ error "failed"

    test "\0" 0
    test "'qu\0tes' 'are' 'fine: \\'' \0" 3
    test "'unterminated\\'\0" (-1)
