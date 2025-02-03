-- re2hs $INPUT -o $OUTPUT --header lexer/state.hs -i
{-# OPTIONS_GHC -Wno-unused-record-wildcards #-}
{-# LANGUAGE OverloadedStrings #-}

import Control.Monad (when)
import Data.ByteString (index)
import State

%{header:on %}
module State where

import Data.ByteString (ByteString)

data State = State {
    _yyinput :: !ByteString,
    _yycursor :: !Int,
    %{stags format = "\n@@{tag} :: !Int,"; %}
    _tag :: !Int
}
%{header:off %}

%{
    re2c:YYFN = ["lexer;Int", "State{..};State"];
    re2c:tags = 1;
    re2c:yyfill:enable = 0;
    re2c:header = "lexer/state.hs";

    [a]* @_tag [b]* { _tag }
%}

main :: IO ()
main = do
    let s = State {
        _yyinput = "ab\0",
        _yycursor = 0,
        %{stags format = "\n@@{tag} = -1,"; %}
        _tag = 0}

    when (lexer s /= 1) $ error "failed!"
