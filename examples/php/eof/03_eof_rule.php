<?php
// re2php $INPUT -o $OUTPUT

// expects a null-terminated string
function lex($yyinput) {
    $yycursor = 0;
    $yylimit = strlen($yyinput) - 1; // terminating null not included
    $count = 0;

    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case ' ':
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    case '\'':
                        $yycursor += 1;
                        $yystate = 5;
                        break 2;
                    default:
                        if ($yylimit <= $yycursor) {
                            $yystate = 10;
                            break 2;
                        }
                        $yycursor += 1;
                        $yystate = 1;
                        break 2;
                }
            case 1:
                $yystate = 2;
                break 2;
            case 2:
                return -1;
            case 3:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case ' ':
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 4;
                        break 2;
                }
            case 4:
                break 2;
            case 5:
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                if ($yych >= 0x01) {
                    $yystate = 7;
                    break 2;
                }
                if ($yylimit <= $yycursor) {
                    $yystate = 2;
                    break 2;
                }
                $yycursor += 1;
                $yystate = 6;
                break 2;
            case 6:
                $yych = $yyinput[$yycursor];
                $yystate = 7;
                break 2;
            case 7:
                switch ($yych) {
                    case '\'':
                        $yycursor += 1;
                        $yystate = 8;
                        break 2;
                    case '\\':
                        $yycursor += 1;
                        $yystate = 9;
                        break 2;
                    default:
                        if ($yylimit <= $yycursor) {
                            $yystate = 11;
                            break 2;
                        }
                        $yycursor += 1;
                        $yystate = 6;
                        break 2;
                }
            case 8:
                $count += 1; break 2;
            case 9:
                $yych = $yyinput[$yycursor];
                if ($yych <= 0x00) {
                    if ($yylimit <= $yycursor) {
                        $yystate = 11;
                        break 2;
                    }
                    $yycursor += 1;
                    $yystate = 6;
                    break 2;
                }
                $yycursor += 1;
                $yystate = 6;
                break 2;
            case 10:
                return $count;
            case 11:
                $yycursor = $yymarker;
                $yystate = 2;
                break 2;
            default:
                throw new \Exception("internal lexer error");
        }
    }

    }
}

function test($s, $n) {
    if (lex($s) != $n) {
        throw new \Exception("error!");
    }
}

test("\0", 0);
test("'qu\0tes' 'are' 'fine: \\'' \0", 3);
test("'unterminated\\'\0", -1);
