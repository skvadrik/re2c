-- re2hs $INPUT -o $OUTPUT -i
{-# LANGUAGE OverloadedStrings #-}
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}

import Data.ByteString (ByteString, index)

data S't''a'''t'e' = S't''a'''t'e' {
    _yyinput :: ByteString,
    _yycursor :: Int
}

%{
    re2c:define:YYFN = ["l'''e'x''''e'r';Bool", "S't''a'''t'e'{..};S't''a'''t'e'"];
    re2c:yyfill:enable = 0;

    number = [1-9][0-9]*;

    number { let _x' = '}' in let _x'' = '}' in let x'0'' = True in x'0'' }
    *      { let _y' = '\n' in let _x'' = '\'' in let y' = False in y' }
%}

main :: IO ()
main = case l'''e'x''''e'r' S't''a'''t'e'{_yyinput = "1234\0", _yycursor = 0} of
    True -> return ()
    False -> error "lexer failed!"
