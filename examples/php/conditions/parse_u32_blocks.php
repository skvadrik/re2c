<?php
// re2js $INPUT -o $OUTPUT

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
                $yych = ord($st->yyinput[$st->yycursor]);
                $st->yycursor += 1;
                switch ($yych) {
                    case 0x30:
                        $yystate = 2;
                        break;
                    case 0x31:
                    case 0x32:
                    case 0x33:
                    case 0x34:
                    case 0x35:
                    case 0x36:
                    case 0x37:
                    case 0x38:
                    case 0x39:
                        $yystate = 4;
                        break;
                    default:
                        $yystate = 1;
                        break;
                }
            case 1:
                return null;
            case 2:
                $st->yymarker = $st->yycursor;
                $yych = ord($st->yyinput[$st->yycursor]);
                switch ($yych) {
                    case 0x42:
                    case 0x62:
                        $st->yycursor += 1;
                        $yystate = 5;
                        break;
                    case 0x58:
                    case 0x78:
                        $st->yycursor += 1;
                        $yystate = 7;
                        break;
                    default:
                        $yystate = 3;
                        break;
                }
            case 3:
                return parse_oct($st);
            case 4:
                $st->yycursor -= 1;
                return parse_dec($st);
            case 5:
                $yych = ord($st->yyinput[$st->yycursor]);
                switch ($yych) {
                    case 0x30:
                    case 0x31:
                        $st->yycursor += 1;
                        $yystate = 8;
                        break;
                    default:
                        $yystate = 6;
                        break;
                }
            case 6:
                $st->yycursor = $st->yymarker;
                $yystate = 3;
                break;
            case 7:
                $yych = ord($st->yyinput[$st->yycursor]);
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
                    case 0x41:
                    case 0x42:
                    case 0x43:
                    case 0x44:
                    case 0x45:
                    case 0x46:
                    case 0x61:
                    case 0x62:
                    case 0x63:
                    case 0x64:
                    case 0x65:
                    case 0x66:
                        $st->yycursor += 1;
                        $yystate = 9;
                        break;
                    default:
                        $yystate = 6;
                        break;
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

function parse_bin($st) {
    $n = 0;
    while (true) {

        $yych = 0;
        $yystate = 0;
        while (true) {
            switch ($yystate) {
                case 0:
                    $yych = ord($st->yyinput[$st->yycursor]);
                    $st->yycursor += 1;
                    switch ($yych) {
                        case 0x30:
                        case 0x31:
                            $yystate = 2;
                            break;
                        default:
                            $yystate = 1;
                            break;
                    }
                case 1:
                    return $n;
                case 2:
                    $n = $n * 2 + ($st->yyinput[$st->yycursor - 1] - 48); break;
                default:
                    throw new \Exception("internal lexer error");
            }
        }

    }
}

function parse_oct($st) {
    $n = 0;
    while (true) {

        $yych = 0;
        $yystate = 0;
        while (true) {
            switch ($yystate) {
                case 0:
                    $yych = ord($st->yyinput[$st->yycursor]);
                    $st->yycursor += 1;
                    switch ($yych) {
                        case 0x30:
                        case 0x31:
                        case 0x32:
                        case 0x33:
                        case 0x34:
                        case 0x35:
                        case 0x36:
                        case 0x37:
                            $yystate = 2;
                            break;
                        default:
                            $yystate = 1;
                            break;
                    }
                case 1:
                    return $n;
                case 2:
                    $n = $n * 8 + ($st->yyinput[$st->yycursor - 1] - 48); break;
                default:
                    throw new \Exception("internal lexer error");
            }
        }

    }
}

function parse_dec($st) {
    $n = 0;
    while (true) {

        $yych = 0;
        $yystate = 0;
        while (true) {
            switch ($yystate) {
                case 0:
                    $yych = ord($st->yyinput[$st->yycursor]);
                    $st->yycursor += 1;
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
                            $yystate = 2;
                            break;
                        default:
                            $yystate = 1;
                            break;
                    }
                case 1:
                    return $n;
                case 2:
                    $n = $n * 10 + ($st->yyinput[$st->yycursor - 1] - 48); break;
                default:
                    throw new \Exception("internal lexer error");
            }
        }

    }
}

function parse_hex($st) {
    $n = 0;
    while (true) {

        $yych = 0;
        $yystate = 0;
        while (true) {
            switch ($yystate) {
                case 0:
                    $yych = ord($st->yyinput[$st->yycursor]);
                    $st->yycursor += 1;
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
                            $yystate = 2;
                            break;
                        case 0x41:
                        case 0x42:
                        case 0x43:
                        case 0x44:
                        case 0x45:
                        case 0x46:
                            $yystate = 3;
                            break;
                        case 0x61:
                        case 0x62:
                        case 0x63:
                        case 0x64:
                        case 0x65:
                        case 0x66:
                            $yystate = 4;
                            break;
                        default:
                            $yystate = 1;
                            break;
                    }
                case 1:
                    return $n;
                case 2:
                    $n = $n * 16 + ($st->yyinput[$st->yycursor - 1] - 48); break;
                case 3:
                    $n = $n * 16 + ($st->yyinput[$st->yycursor - 1] - 55); break;
                case 4:
                    $n = $n * 16 + ($st->yyinput[$st->yycursor - 1] - 87); break;
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
