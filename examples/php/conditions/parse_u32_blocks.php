<?php
// re2php $INPUT -o $OUTPUT



function parse_u32($str) {
    $st = new \stdClass();
    $st->yyinput = $str;
    $st->yycursor = 0;
    $st->yymarker = 0;

    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $st->yyinput[$st->yycursor];
                $st->yycursor += 1;
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
                $st->yymarker = $st->yycursor;
                $yych = $st->yyinput[$st->yycursor];
                switch ($yych) {
                    case 'B':
                    case 'b':
                        $st->yycursor += 1;
                        $yystate = 5;
                        break 2;
                    case 'X':
                    case 'x':
                        $st->yycursor += 1;
                        $yystate = 7;
                        break 2;
                    default:
                        $yystate = 3;
                        break 2;
                }
            case 3:
                return parse_oct($st);
            case 4:
                $st->yycursor -= 1;
                return parse_dec($st);
            case 5:
                $yych = $st->yyinput[$st->yycursor];
                switch ($yych) {
                    case '0':
                    case '1':
                        $st->yycursor += 1;
                        $yystate = 8;
                        break 2;
                    default:
                        $yystate = 6;
                        break 2;
                }
            case 6:
                $st->yycursor = $st->yymarker;
                $yystate = 3;
                break 2;
            case 7:
                $yych = $st->yyinput[$st->yycursor];
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
                        $st->yycursor += 1;
                        $yystate = 9;
                        break 2;
                    default:
                        $yystate = 6;
                        break 2;
                }
            case 8:
                $st->yycursor -= 1;
                return parse_bin($st);
            case 9:
                $st->yycursor -= 1;
                return parse_hex($st);
            default:
                throw new \Exception("internal lexer error");
        }
    }

}

function parse_bin($st): int {
    $n = 0;
    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $st->yyinput[$st->yycursor];
                $st->yycursor += 1;
                switch ($yych) {
                    case '0':
                    case '1':
                        $yystate = 2;
                        break 2;
                    default:
                        $yystate = 1;
                        break 2;
                }
            case 1:
                return $n;
            case 2:
                $n = $n * 2 + (ord($st->yyinput[$st->yycursor - 1]) - 48); break 2;
            default:
                throw new \Exception("internal lexer error");
        }
    }

    }
}

function parse_oct($st): int {
    $n = 0;
    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $st->yyinput[$st->yycursor];
                $st->yycursor += 1;
                switch ($yych) {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                        $yystate = 2;
                        break 2;
                    default:
                        $yystate = 1;
                        break 2;
                }
            case 1:
                return $n;
            case 2:
                $n = $n * 8 + (ord($st->yyinput[$st->yycursor - 1]) - 48); break 2;
            default:
                throw new \Exception("internal lexer error");
        }
    }

    }
}

function parse_dec($st): int {
    $n = 0;
    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $st->yyinput[$st->yycursor];
                $st->yycursor += 1;
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
                        $yystate = 2;
                        break 2;
                    default:
                        $yystate = 1;
                        break 2;
                }
            case 1:
                return $n;
            case 2:
                
            $n = $n * 10 + (ord($st->yyinput[$st->yycursor - 1]) - 48);
            break 2;

            default:
                throw new \Exception("internal lexer error");
        }
    }

    }
}

function parse_hex($st): int {
    $n = 0;
    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $st->yyinput[$st->yycursor];
                $st->yycursor += 1;
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
                        $yystate = 2;
                        break 2;
                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                        $yystate = 3;
                        break 2;
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                        $yystate = 4;
                        break 2;
                    default:
                        $yystate = 1;
                        break 2;
                }
            case 1:
                return $n;
            case 2:
                $n = $n * 16 + (ord($st->yyinput[$st->yycursor - 1]) - 48); break 2;
            case 3:
                $n = $n * 16 + (ord($st->yyinput[$st->yycursor - 1]) - 55); break 2;
            case 4:
                $n = $n * 16 + (ord($st->yyinput[$st->yycursor - 1]) - 87); break 2;
            default:
                throw new \Exception("internal lexer error");
        }
    }

    }
}

function test($s, $n): void {
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
