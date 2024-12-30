<?php
// re2php $INPUT -o $OUTPUT

const YYMAXFILL = 1;


function lex($yyinput) {
    $yycursor = 0;
    $yylimit = strlen($yyinput);
    $count = 0;

    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                if ($yylimit <= $yycursor) {
                    return -1;
                }
                $yych = $yyinput[$yycursor];
                $yycursor += 1;
                switch ($yych) {
                    case "\0":
                        $yystate = 1;
                        break 2;
                    case ' ':
                        $yystate = 3;
                        break 2;
                    case '\'':
                        $yystate = 5;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 1:
                
            // check that it is the sentinel, not some unexpected null
            return ($yycursor == $yylimit - YYMAXFILL + 1) ? $count : -1;

            case 2:
                return -1;
            case 3:
                if ($yylimit <= $yycursor) {
                    return -1;
                }
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
                if ($yylimit <= $yycursor) {
                    return -1;
                }
                $yych = $yyinput[$yycursor];
                $yycursor += 1;
                switch ($yych) {
                    case '\'':
                        $yystate = 6;
                        break 2;
                    case '\\':
                        $yystate = 7;
                        break 2;
                    default:
                        $yystate = 5;
                        break 2;
                }
            case 6:
                $count += 1; break 2;
            case 7:
                if ($yylimit <= $yycursor) {
                    return -1;
                }
                $yycursor += 1;
                $yystate = 5;
                break 2;
            default:
                throw new \Exception("internal lexer error");
        }
    }

    }
}

function test($s, $n) {
    $padded_s = $s . str_repeat("\0", YYMAXFILL);
    if (lex($padded_s) != $n) {
        throw new \Exception("error!");
    }
}

test("", 0);
test("'unterminated\\'", -1);
test("'qu\0tes' 'are' 'fine: \\'' ", 3);
test("'unexpected \0 null", -1);
