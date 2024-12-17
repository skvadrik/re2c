<?php
// re2php $INPUT -o $OUTPUT

function lex($yyinput) {
    $yycursor = 0;

    {
        $yych = 0;
        $yystate = 0;
        while (true) {
            switch ($yystate) {
                case 0:
                    $yych = $yyinput[$yycursor];
                    $yycursor += 1;
                    switch ($yych) {
                        case 0x31:
                        case 0x32:
                        case 0x33:
                        case 0x34:
                        case 0x35:
                        case 0x36:
                        case 0x37:
                        case 0x38:
                        case 0x39:
                            $yystate = 2;
                            break;
                        default:
                            $yystate = 1;
                            break;
                    }
                case 1:
                { return false; }
                case 2:
                    $yych = $yyinput[$yycursor];
                    switch ($yych) {
                        case 0x30:
                        case 0x31:
                        case 0x32:
                        case 0x33:
                        case 0x34:
                        case 0x35:
                        case 0x36:
                        case 0x37:
                        case 0x38:
                        case 0x39:
                            $yycursor += 1;
                            $yystate = 2;
                            break;
                        default:
                            $yystate = 3;
                            break;
                    }
                case 3:
                { return true; }
                default:
                    throw new \Exception("internal lexer error");
            }
        }
    }

}

if (!lex("1234\0")) {
    throw new \Exception("error!");
}
