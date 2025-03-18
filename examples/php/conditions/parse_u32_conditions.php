<?php
// re2php $INPUT -o $OUTPUT -c

const YYC_INIT = 0;
const YYC_BIN = 10;
const YYC_OCT = 13;
const YYC_DEC = 16;
const YYC_HEX = 19;


function parse_u32($yyinput) {
    $yycursor = 0;
    $yycond = YYC_INIT;
    $n = 0;

    while (true) {
    
        $yych = 0;
        $yystate = $yycond;
        while (true) {
            switch ($yystate) {
                case 0:
                    $yych = $yyinput[$yycursor];
                    $yycursor += 1;
                    switch ($yych) {
                        case '0':
                            $yystate = 2;
                            break 2;
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                        case '8':
                        case '9':
                            $yystate = 4;
                            break 2;
                        default:
                            $yystate = 1;
                            break 2;
                    }
                case 1:
                    return null;
                case 2:
                    $yymarker = $yycursor;
                    $yych = $yyinput[$yycursor];
                    switch ($yych) {
                        case 'B':
                        case 'b':
                            $yycursor += 1;
                            $yystate = 5;
                            break 2;
                        case 'X':
                        case 'x':
                            $yycursor += 1;
                            $yystate = 7;
                            break 2;
                        default:
                            $yystate = 3;
                            break 2;
                    }
                case 3:
                    $yycond = YYC_OCT;
                    $yystate = YYC_OCT;
                    break 2;
                case 4:
                    $yycursor -= 1;
                    $yycond = YYC_DEC;
                    $yystate = YYC_DEC;
                    break 2;
                case 5:
                    $yych = $yyinput[$yycursor];
                    switch ($yych) {
                        case '0':
                        case '1':
                            $yycursor += 1;
                            $yystate = 8;
                            break 2;
                        default:
                            $yystate = 6;
                            break 2;
                    }
                case 6:
                    $yycursor = $yymarker;
                    $yystate = 3;
                    break 2;
                case 7:
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
                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D':
                        case 'E':
                        case 'F':
                        case 'a':
                        case 'b':
                        case 'c':
                        case 'd':
                        case 'e':
                        case 'f':
                            $yycursor += 1;
                            $yystate = 9;
                            break 2;
                        default:
                            $yystate = 6;
                            break 2;
                    }
                case 8:
                    $yycursor -= 1;
                    $yycond = YYC_BIN;
                    $yystate = YYC_BIN;
                    break 2;
                case 9:
                    $yycursor -= 1;
                    $yycond = YYC_HEX;
                    $yystate = YYC_HEX;
                    break 2;
                case 10:
                    $yych = $yyinput[$yycursor];
                    $yycursor += 1;
                    switch ($yych) {
                        case '0':
                        case '1':
                            $yystate = 12;
                            break 2;
                        default:
                            $yystate = 11;
                            break 2;
                    }
                case 11:
                    return $n;
                case 12:
                    $n = $n * 2 + (ord($yyinput[$yycursor - 1]) - 48); break 2;
                case 13:
                    $yych = $yyinput[$yycursor];
                    $yycursor += 1;
                    switch ($yych) {
                        case '0':
                        case '1':
                        case '2':
                        case '3':
                        case '4':
                        case '5':
                        case '6':
                        case '7':
                            $yystate = 15;
                            break 2;
                        default:
                            $yystate = 14;
                            break 2;
                    }
                case 14:
                    return $n;
                case 15:
                    $n = $n * 8 + (ord($yyinput[$yycursor - 1]) - 48); break 2;
                case 16:
                    $yych = $yyinput[$yycursor];
                    $yycursor += 1;
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
                            $yystate = 18;
                            break 2;
                        default:
                            $yystate = 17;
                            break 2;
                    }
                case 17:
                    return $n;
                case 18:
                    $n = $n * 10 + (ord($yyinput[$yycursor - 1]) - 48); break 2;
                case 19:
                    $yych = $yyinput[$yycursor];
                    $yycursor += 1;
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
                            $yystate = 21;
                            break 2;
                        case 'A':
                        case 'B':
                        case 'C':
                        case 'D':
                        case 'E':
                        case 'F':
                            $yystate = 22;
                            break 2;
                        case 'a':
                        case 'b':
                        case 'c':
                        case 'd':
                        case 'e':
                        case 'f':
                            $yystate = 23;
                            break 2;
                        default:
                            $yystate = 20;
                            break 2;
                    }
                case 20:
                    return $n;
                case 21:
                    $n = $n * 16 + (ord($yyinput[$yycursor - 1]) - 48); break 2;
                case 22:
                    $n = $n * 16 + (ord($yyinput[$yycursor - 1]) - 55); break 2;
                case 23:
                    $n = $n * 16 + (ord($yyinput[$yycursor - 1]) - 87); break 2;
                default:
                    throw new \Exception("internal lexer error");
            }
        }

    }
}

function test($s, $n) {
    if (parse_u32($s) != $n) {
        throw new \Exception("error!");
    }
}

test("\0", null);
test("1234567890\0", 1234567890);
test("0b1101\0", 13);
test("0x7Fe\0", 2046);
test("0644\0", 420);
test("9999999999\0", 9999999999);
