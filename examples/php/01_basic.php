<?php
// re2php $INPUT -o $OUTPUT

function lex($yyinput) {
    $yycursor = 0;

    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $yyinput[$yycursor];
                $yycursor += 1;
                switch ($yych) {
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        $yystate = 2;
                        break 2;
                    default:
                        $yystate = 1;
                        break 2;
                }
            case 1:
                return false;
            case 2:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        $yycursor += 1;
                        $yystate = 2;
                        break 2;
                    default:
                        $yystate = 3;
                        break 2;
                }
            case 3:
                return true;
            default:
                throw new \Exception("internal lexer error");
        }
    }

}

if (!lex("1234\0")) {
    throw new \Exception("error!");
}
