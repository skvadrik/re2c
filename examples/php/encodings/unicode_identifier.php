<?php
// re2php $INPUT -o $OUTPUT --utf8 -s




function lex($yyinput) {
    $yycursor = 0;
    
    $yych = 0;
    $yyaccept = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $yyinput[$yycursor];
                $yycursor += 1;
                switch ($yych) {
                    case '$':
                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                    case 'G':
                    case 'H':
                    case 'I':
                    case 'J':
                    case 'K':
                    case 'L':
                    case 'M':
                    case 'N':
                    case 'O':
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                    case 'T':
                    case 'U':
                    case 'V':
                    case 'W':
                    case 'X':
                    case 'Y':
                    case 'Z':
                    case '_':
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                    case 'g':
                    case 'h':
                    case 'i':
                    case 'j':
                    case 'k':
                    case 'l':
                    case 'm':
                    case 'n':
                    case 'o':
                    case 'p':
                    case 'q':
                    case 'r':
                    case 's':
                    case 't':
                    case 'u':
                    case 'v':
                    case 'w':
                    case 'x':
                    case 'y':
                    case 'z':
                        $yystate = 3;
                        break 2;
                    case 0xC2:
                        $yystate = 5;
                        break 2;
                    case 0xC3:
                        $yystate = 6;
                        break 2;
                    case 0xC4:
                    case 0xC5:
                    case 0xC6:
                    case 0xC7:
                    case 0xC8:
                    case 0xC9:
                    case 0xCA:
                    case 0xD0:
                    case 0xD1:
                    case 0xD3:
                    case 0xDA:
                        $yystate = 7;
                        break 2;
                    case 0xCB:
                        $yystate = 8;
                        break 2;
                    case 0xCD:
                        $yystate = 9;
                        break 2;
                    case 0xCE:
                        $yystate = 10;
                        break 2;
                    case 0xCF:
                        $yystate = 11;
                        break 2;
                    case 0xD2:
                        $yystate = 12;
                        break 2;
                    case 0xD4:
                        $yystate = 13;
                        break 2;
                    case 0xD5:
                        $yystate = 14;
                        break 2;
                    case 0xD6:
                        $yystate = 15;
                        break 2;
                    case 0xD7:
                        $yystate = 16;
                        break 2;
                    case 0xD8:
                        $yystate = 17;
                        break 2;
                    case 0xD9:
                        $yystate = 18;
                        break 2;
                    case 0xDB:
                        $yystate = 19;
                        break 2;
                    case 0xDC:
                        $yystate = 20;
                        break 2;
                    case 0xDD:
                        $yystate = 21;
                        break 2;
                    case 0xDE:
                        $yystate = 22;
                        break 2;
                    case 0xDF:
                        $yystate = 23;
                        break 2;
                    case 0xE0:
                        $yystate = 24;
                        break 2;
                    case 0xE1:
                        $yystate = 25;
                        break 2;
                    case 0xE2:
                        $yystate = 26;
                        break 2;
                    case 0xE3:
                        $yystate = 27;
                        break 2;
                    case 0xE4:
                        $yystate = 28;
                        break 2;
                    case 0xE5:
                    case 0xE6:
                    case 0xE7:
                    case 0xE8:
                    case 0xEB:
                    case 0xEC:
                        $yystate = 29;
                        break 2;
                    case 0xE9:
                        $yystate = 30;
                        break 2;
                    case 0xEA:
                        $yystate = 31;
                        break 2;
                    case 0xED:
                        $yystate = 32;
                        break 2;
                    case 0xEF:
                        $yystate = 33;
                        break 2;
                    case 0xF0:
                        $yystate = 34;
                        break 2;
                    default:
                        $yystate = 1;
                        break 2;
                }
            case 1:
                $yystate = 2;
                break 2;
            case 2:
                return false;
            case 3:
                $yyaccept = 0;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case '$':
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
                    case 'G':
                    case 'H':
                    case 'I':
                    case 'J':
                    case 'K':
                    case 'L':
                    case 'M':
                    case 'N':
                    case 'O':
                    case 'P':
                    case 'Q':
                    case 'R':
                    case 'S':
                    case 'T':
                    case 'U':
                    case 'V':
                    case 'W':
                    case 'X':
                    case 'Y':
                    case 'Z':
                    case '_':
                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                    case 'g':
                    case 'h':
                    case 'i':
                    case 'j':
                    case 'k':
                    case 'l':
                    case 'm':
                    case 'n':
                    case 'o':
                    case 'p':
                    case 'q':
                    case 'r':
                    case 's':
                    case 't':
                    case 'u':
                    case 'v':
                    case 'w':
                    case 'x':
                    case 'y':
                    case 'z':
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    case 0xC2:
                        $yycursor += 1;
                        $yystate = 35;
                        break 2;
                    case 0xC3:
                        $yycursor += 1;
                        $yystate = 37;
                        break 2;
                    case 0xC4:
                    case 0xC5:
                    case 0xC6:
                    case 0xC7:
                    case 0xC8:
                    case 0xC9:
                    case 0xCA:
                    case 0xCC:
                    case 0xD0:
                    case 0xD1:
                    case 0xD3:
                    case 0xDA:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xCB:
                        $yycursor += 1;
                        $yystate = 39;
                        break 2;
                    case 0xCD:
                        $yycursor += 1;
                        $yystate = 40;
                        break 2;
                    case 0xCE:
                        $yycursor += 1;
                        $yystate = 41;
                        break 2;
                    case 0xCF:
                        $yycursor += 1;
                        $yystate = 42;
                        break 2;
                    case 0xD2:
                        $yycursor += 1;
                        $yystate = 43;
                        break 2;
                    case 0xD4:
                        $yycursor += 1;
                        $yystate = 44;
                        break 2;
                    case 0xD5:
                        $yycursor += 1;
                        $yystate = 45;
                        break 2;
                    case 0xD6:
                        $yycursor += 1;
                        $yystate = 46;
                        break 2;
                    case 0xD7:
                        $yycursor += 1;
                        $yystate = 47;
                        break 2;
                    case 0xD8:
                        $yycursor += 1;
                        $yystate = 48;
                        break 2;
                    case 0xD9:
                        $yycursor += 1;
                        $yystate = 49;
                        break 2;
                    case 0xDB:
                        $yycursor += 1;
                        $yystate = 50;
                        break 2;
                    case 0xDC:
                        $yycursor += 1;
                        $yystate = 51;
                        break 2;
                    case 0xDD:
                        $yycursor += 1;
                        $yystate = 52;
                        break 2;
                    case 0xDE:
                        $yycursor += 1;
                        $yystate = 53;
                        break 2;
                    case 0xDF:
                        $yycursor += 1;
                        $yystate = 54;
                        break 2;
                    case 0xE0:
                        $yycursor += 1;
                        $yystate = 55;
                        break 2;
                    case 0xE1:
                        $yycursor += 1;
                        $yystate = 56;
                        break 2;
                    case 0xE2:
                        $yycursor += 1;
                        $yystate = 57;
                        break 2;
                    case 0xE3:
                        $yycursor += 1;
                        $yystate = 58;
                        break 2;
                    case 0xE4:
                        $yycursor += 1;
                        $yystate = 59;
                        break 2;
                    case 0xE5:
                    case 0xE6:
                    case 0xE7:
                    case 0xE8:
                    case 0xEB:
                    case 0xEC:
                        $yycursor += 1;
                        $yystate = 60;
                        break 2;
                    case 0xE9:
                        $yycursor += 1;
                        $yystate = 61;
                        break 2;
                    case 0xEA:
                        $yycursor += 1;
                        $yystate = 62;
                        break 2;
                    case 0xED:
                        $yycursor += 1;
                        $yystate = 63;
                        break 2;
                    case 0xEF:
                        $yycursor += 1;
                        $yystate = 64;
                        break 2;
                    case 0xF0:
                        $yycursor += 1;
                        $yystate = 65;
                        break 2;
                    case 0xF3:
                        $yycursor += 1;
                        $yystate = 66;
                        break 2;
                    default:
                        $yystate = 4;
                        break 2;
                }
            case 4:
                return true;
            case 5:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xAA:
                    case 0xB5:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 6:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 7:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 8:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xAC:
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 9:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 10:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 11:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 12:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 13:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 14:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 15:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 16:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 17:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 18:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 19:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x95:
                    case 0xA5:
                    case 0xA6:
                    case 0xAE:
                    case 0xAF:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 20:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 21:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 22:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 23:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xB4:
                    case 0xB5:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 24:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 67;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 68;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 69;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 70;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 71;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 72;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 73;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 74;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 75;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 76;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 77;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 78;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 79;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 80;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 81;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 82;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 83;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 84;
                        break 2;
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 85;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 86;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 87;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 88;
                        break 2;
                    case 0xB7:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 89;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 90;
                        break 2;
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 91;
                        break 2;
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 92;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 93;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 94;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 95;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 25:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 96;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 97;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 98;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 99;
                        break 2;
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x89:
                        $yycursor += 1;
                        $yystate = 100;
                        break 2;
                    case 0x8A:
                        $yycursor += 1;
                        $yystate = 101;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 102;
                        break 2;
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 103;
                        break 2;
                    case 0x8D:
                        $yycursor += 1;
                        $yystate = 104;
                        break 2;
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 105;
                        break 2;
                    case 0x8F:
                        $yycursor += 1;
                        $yystate = 106;
                        break 2;
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 107;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 108;
                        break 2;
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 109;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 110;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 111;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 112;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 113;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 114;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 115;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 116;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 117;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 118;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 120;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 121;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 122;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 123;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 124;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 125;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 126;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 127;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 128;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 129;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 130;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 131;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 132;
                        break 2;
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 133;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 134;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 135;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 136;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 137;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 26:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 138;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 139;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 140;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 141;
                        break 2;
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 142;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 143;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 144;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 145;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 146;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 147;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 148;
                        break 2;
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 149;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 150;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 27:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 151;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 107;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 152;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 153;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 154;
                        break 2;
                    case 0x85:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 155;
                        break 2;
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 156;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 28:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 118;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 29:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 30:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 157;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 31:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9D:
                    case 0xAE:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 158;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 159;
                        break 2;
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 160;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 161;
                        break 2;
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 162;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 157;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 163;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 164;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 165;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 166;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 113;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 167;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 168;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 169;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 170;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 171;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 172;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 173;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 174;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 175;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 176;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 177;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 178;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 179;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 32:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 180;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 181;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 33:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 182;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 183;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 184;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 185;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 53;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 186;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 187;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 51;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 188;
                        break 2;
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 189;
                        break 2;
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 190;
                        break 2;
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 191;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 192;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 193;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 194;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 195;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 34:
                $yyaccept = 1;
                $yymarker = $yycursor;
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 196;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 197;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 198;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 199;
                        break 2;
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 200;
                        break 2;
                    case 0x96:
                        $yycursor += 1;
                        $yystate = 201;
                        break 2;
                    case 0x97:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 60;
                        break 2;
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 202;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 203;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 204;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 205;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 206;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 207;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 208;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 209;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 210;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 35:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xAA:
                    case 0xB5:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 36:
                $yycursor = $yymarker;
                if ($yyaccept === 0) {
                    $yystate = 4;
                    break 2;
                } else {
                    $yystate = 2;
                    break 2;
                }
            case 37:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 38:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 39:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xAC:
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 40:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 41:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 42:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 43:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 44:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 45:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 46:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 47:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x84:
                    case 0x85:
                    case 0x87:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 48:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 49:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 50:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 51:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 52:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 53:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 54:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xBA:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 55:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 211;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 212;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 69;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 213;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 214;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 215;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 216;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 217;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 218;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 219;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 220;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 221;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 222;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 223;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 224;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 225;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 226;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 227;
                        break 2;
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 228;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 229;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 230;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 231;
                        break 2;
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 232;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 233;
                        break 2;
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 234;
                        break 2;
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 235;
                        break 2;
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 236;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 237;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 238;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 239;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 240;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 56:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x9E:
                    case 0xAC:
                    case 0xAE:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 241;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 162;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 99;
                        break 2;
                    case 0x89:
                        $yycursor += 1;
                        $yystate = 100;
                        break 2;
                    case 0x8A:
                        $yycursor += 1;
                        $yystate = 101;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 102;
                        break 2;
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 103;
                        break 2;
                    case 0x8D:
                        $yycursor += 1;
                        $yystate = 242;
                        break 2;
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 105;
                        break 2;
                    case 0x8F:
                        $yycursor += 1;
                        $yystate = 106;
                        break 2;
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 107;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 108;
                        break 2;
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 109;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 110;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 243;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 244;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 245;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 246;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 116;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 247;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 118;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 248;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 249;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 121;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 250;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 251;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 252;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 253;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 254;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 113;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 255;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 256;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 132;
                        break 2;
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 257;
                        break 2;
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 258;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 134;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 135;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 136;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 137;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 57:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 259;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 260;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 139;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 261;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 140;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 141;
                        break 2;
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 142;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 143;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 144;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 262;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 146;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 263;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 148;
                        break 2;
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 264;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 150;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 58:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 265;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 107;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 266;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 153;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 154;
                        break 2;
                    case 0x85:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 155;
                        break 2;
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 156;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 59:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 118;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 60:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 61:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 157;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 62:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9A:
                    case 0x9D:
                    case 0xA2:
                    case 0xA6:
                    case 0xAA:
                    case 0xAE:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 158;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 159;
                        break 2;
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 267;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 268;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 53;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 163;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 164;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 165;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 269;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 113;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 270;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 182;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 271;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 272;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 273;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 274;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 275;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 177;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 178;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 276;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 63:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 180;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 181;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 64:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 182;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 183;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 277;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 185;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 53;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 186;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 187;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 51;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 188;
                        break 2;
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 189;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 278;
                        break 2;
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 279;
                        break 2;
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 191;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 280;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 193;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 194;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 195;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 65:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 281;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 282;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 198;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 199;
                        break 2;
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 200;
                        break 2;
                    case 0x96:
                        $yycursor += 1;
                        $yystate = 283;
                        break 2;
                    case 0x97:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 60;
                        break 2;
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 202;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 284;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 285;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 286;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 206;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 207;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 208;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 209;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 210;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 66:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 287;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 67:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x9A:
                    case 0xA4:
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 68:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 69:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 70:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 71:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 72:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 73:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8E:
                    case 0x9C:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xB0:
                    case 0xB1:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 74:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 75:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9E:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 76:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 77:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0xA0:
                    case 0xA1:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 78:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 79:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x9C:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 80:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x99:
                    case 0x9A:
                    case 0x9C:
                    case 0x9E:
                    case 0x9F:
                    case 0xA3:
                    case 0xA4:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 81:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 82:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 83:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0xA0:
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 84:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 85:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 86:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 87:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8E:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 88:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 89:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 90:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 91:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA5:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 92:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 93:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 94:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 95:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 96:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 97:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA1:
                    case 0xA5:
                    case 0xA6:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 98:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x8E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 99:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x87:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 100:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 101:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 102:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 103:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 104:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 105:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 106:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 107:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 108:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 109:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 110:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 111:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 112:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 113:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 114:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x97:
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 115:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 116:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 117:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 118:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 119:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 120:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 121:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 122:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 123:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 124:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 125:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 126:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 127:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 128:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xAE:
                    case 0xAF:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 129:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 130:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 131:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 132:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 133:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 134:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 135:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x99:
                    case 0x9B:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 136:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 137:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 138:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xB1:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 139:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 140:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x87:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x95:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA4:
                    case 0xA6:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 141:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 142:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 143:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 144:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 145:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 146:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA7:
                    case 0xAD:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 147:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 148:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 149:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 150:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 151:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 152:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 153:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 154:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 155:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 156:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 157:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 158:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 159:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 160:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xAA:
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 161:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 162:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 163:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 164:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 165:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 166:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 167:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 168:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xBB:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 169:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 170:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 171:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 172:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 173:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 174:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xBA:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 175:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB5:
                    case 0xB6:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 176:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x82:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 177:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 178:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 179:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 180:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 181:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 182:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 183:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 184:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 185:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 186:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 187:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 188:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 189:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 190:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 191:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 192:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 193:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 194:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 195:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 196:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 288;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 289;
                        break 2;
                    case 0x82:
                    case 0x90:
                    case 0x91:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 290;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 291;
                        break 2;
                    case 0x8A:
                        $yycursor += 1;
                        $yystate = 292;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 293;
                        break 2;
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 294;
                        break 2;
                    case 0x8D:
                        $yycursor += 1;
                        $yystate = 295;
                        break 2;
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 162;
                        break 2;
                    case 0x8F:
                        $yycursor += 1;
                        $yystate = 296;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 297;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 298;
                        break 2;
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 299;
                        break 2;
                    case 0x95:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 130;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 273;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 300;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 301;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 302;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 303;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 304;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 305;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 306;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 307;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 308;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 309;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 118;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 310;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 311;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 142;
                        break 2;
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 312;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 313;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 314;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 315;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 197:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 316;
                        break 2;
                    case 0x82:
                        $yycursor += 1;
                        $yystate = 317;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 318;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 319;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 320;
                        break 2;
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 321;
                        break 2;
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 322;
                        break 2;
                    case 0x88:
                        $yycursor += 1;
                        $yystate = 323;
                        break 2;
                    case 0x8A:
                        $yycursor += 1;
                        $yystate = 324;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 78;
                        break 2;
                    case 0x8D:
                        $yycursor += 1;
                        $yystate = 325;
                        break 2;
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 291;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 326;
                        break 2;
                    case 0x92:
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 157;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 327;
                        break 2;
                    case 0x96:
                        $yycursor += 1;
                        $yystate = 328;
                        break 2;
                    case 0x97:
                        $yycursor += 1;
                        $yystate = 329;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 330;
                        break 2;
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 331;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 104;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 332;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 115;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 333;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 334;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 335;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 336;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 337;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 338;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 116;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 339;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 340;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 341;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 342;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 343;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 344;
                        break 2;
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 345;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 198:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 183;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 328;
                        break 2;
                    case 0x95:
                        $yycursor += 1;
                        $yystate = 346;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 199:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 328;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 200:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 89;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 201:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xB9:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 116;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 347;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 157;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 348;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 341;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 349;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 350;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 351;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 202:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 255;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 312;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 203:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 352;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 353;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 354;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 355;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 204:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 356;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 357;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 358;
                        break 2;
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 359;
                        break 2;
                    case 0x95:
                        $yycursor += 1;
                        $yystate = 360;
                        break 2;
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 361;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 362;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 363;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 364;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 365;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 366;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 205:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 367;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 368;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 332;
                        break 2;
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 369;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 370;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 371;
                        break 2;
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 372;
                        break 2;
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 373;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 206:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 374;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 207:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 291;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 162;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 208:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 375;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 209:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 376;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 210:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 377;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 211:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 212:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 213:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 214:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 215:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 216:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x87:
                    case 0x88:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x97:
                    case 0x9C:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xBC:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 217:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBC:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 218:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x87:
                    case 0x88:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x91:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9E:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 219:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 220:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 221:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 222:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x87:
                    case 0x88:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x96:
                    case 0x97:
                    case 0x9C:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 223:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x99:
                    case 0x9A:
                    case 0x9C:
                    case 0x9E:
                    case 0x9F:
                    case 0xA3:
                    case 0xA4:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 224:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x97:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 225:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 226:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 227:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 228:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x95:
                    case 0x96:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 229:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 230:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 231:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 232:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x8A:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 233:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 234:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 235:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA5:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 236:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 237:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x98:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xB5:
                    case 0xB7:
                    case 0xB9:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 238:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 239:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 240:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 241:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 242:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 243:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 244:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 245:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x97:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 246:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 247:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 248:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 249:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 250:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 251:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 252:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 253:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA7:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 254:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 255:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 256:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 257:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 258:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 259:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8D:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 260:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x94:
                    case 0xB1:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 261:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0xA1:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 262:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 263:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xAF:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 264:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 265:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 266:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x99:
                    case 0x9A:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 267:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 268:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 269:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 270:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xBB:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 271:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 272:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 273:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 274:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 275:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 276:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAC:
                    case 0xAD:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 277:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 278:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 279:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 280:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 281:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 288;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 289;
                        break 2;
                    case 0x82:
                    case 0x90:
                    case 0x91:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 290;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 291;
                        break 2;
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 378;
                        break 2;
                    case 0x8A:
                        $yycursor += 1;
                        $yystate = 292;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 379;
                        break 2;
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 294;
                        break 2;
                    case 0x8D:
                        $yycursor += 1;
                        $yystate = 380;
                        break 2;
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 162;
                        break 2;
                    case 0x8F:
                        $yycursor += 1;
                        $yystate = 296;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 381;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 298;
                        break 2;
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 299;
                        break 2;
                    case 0x95:
                        $yycursor += 1;
                        $yystate = 130;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 273;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 300;
                        break 2;
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 301;
                        break 2;
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 302;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 303;
                        break 2;
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 304;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 305;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 382;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 307;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 308;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 383;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 118;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 310;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 311;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 142;
                        break 2;
                    case 0xB2:
                    case 0xB3:
                        $yycursor += 1;
                        $yystate = 312;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 384;
                        break 2;
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 313;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 293;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 315;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 282:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x86:
                    case 0x90:
                    case 0x92:
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x81:
                        $yycursor += 1;
                        $yystate = 385;
                        break 2;
                    case 0x82:
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 290;
                        break 2;
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 386;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 387;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 388;
                        break 2;
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 389;
                        break 2;
                    case 0x88:
                        $yycursor += 1;
                        $yystate = 390;
                        break 2;
                    case 0x8A:
                        $yycursor += 1;
                        $yystate = 324;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 391;
                        break 2;
                    case 0x8C:
                        $yycursor += 1;
                        $yystate = 392;
                        break 2;
                    case 0x8D:
                        $yycursor += 1;
                        $yystate = 393;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 394;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 395;
                        break 2;
                    case 0x96:
                        $yycursor += 1;
                        $yystate = 396;
                        break 2;
                    case 0x97:
                        $yycursor += 1;
                        $yystate = 397;
                        break 2;
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 398;
                        break 2;
                    case 0x9A:
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 116;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 122;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 399;
                        break 2;
                    case 0xA2:
                        $yycursor += 1;
                        $yystate = 115;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 400;
                        break 2;
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 334;
                        break 2;
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 401;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 194;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 402;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 403;
                        break 2;
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 404;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 405;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 406;
                        break 2;
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 407;
                        break 2;
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 408;
                        break 2;
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 409;
                        break 2;
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 315;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 283:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xB9:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 116;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 410;
                        break 2;
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 120;
                        break 2;
                    case 0xAC:
                        $yycursor += 1;
                        $yystate = 273;
                        break 2;
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 411;
                        break 2;
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 341;
                        break 2;
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 412;
                        break 2;
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 413;
                        break 2;
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 351;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 284:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 119;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 352;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 353;
                        break 2;
                    case 0xB1:
                        $yycursor += 1;
                        $yystate = 354;
                        break 2;
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 414;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 285:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 415;
                        break 2;
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 416;
                        break 2;
                    case 0x89:
                        $yycursor += 1;
                        $yystate = 417;
                        break 2;
                    case 0x90:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 356;
                        break 2;
                    case 0x92:
                        $yycursor += 1;
                        $yystate = 357;
                        break 2;
                    case 0x93:
                        $yycursor += 1;
                        $yystate = 358;
                        break 2;
                    case 0x94:
                        $yycursor += 1;
                        $yystate = 359;
                        break 2;
                    case 0x95:
                        $yycursor += 1;
                        $yystate = 360;
                        break 2;
                    case 0x9A:
                        $yycursor += 1;
                        $yystate = 361;
                        break 2;
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 362;
                        break 2;
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 363;
                        break 2;
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 364;
                        break 2;
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 365;
                        break 2;
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 418;
                        break 2;
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 419;
                        break 2;
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 420;
                        break 2;
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 421;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 286:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                        $yycursor += 1;
                        $yystate = 422;
                        break 2;
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 423;
                        break 2;
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 424;
                        break 2;
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 425;
                        break 2;
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 426;
                        break 2;
                    case 0xA5:
                        $yycursor += 1;
                        $yystate = 427;
                        break 2;
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 371;
                        break 2;
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 372;
                        break 2;
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 373;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 287:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x85:
                    case 0x86:
                        $yycursor += 1;
                        $yystate = 38;
                        break 2;
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 157;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 288:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBC:
                    case 0xBD:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 289:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 290:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 291:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 292:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 293:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 294:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 295:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 296:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 297:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 298:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 299:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 300:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 301:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB7:
                    case 0xB8:
                    case 0xBC:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 302:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 303:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB4:
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 304:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 305:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 306:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 307:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 308:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 309:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 310:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 311:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 312:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 313:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0xA7:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 314:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 315:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 316:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 317:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 318:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 319:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 320:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 321:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 322:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x9A:
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 323:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 324:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 325:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 326:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 327:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x85:
                    case 0x87:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 328:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 329:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 330:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 331:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xB8:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 332:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 333:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 334:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 335:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0xA1:
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 336:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 337:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 338:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 339:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 340:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 341:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 342:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 343:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x86:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 344:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x98:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 345:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 346:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 347:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 348:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 349:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x90:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 350:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 351:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA0:
                    case 0xA1:
                    case 0xA3:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 352:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 353:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 354:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 355:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 356:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 357:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9E:
                    case 0x9F:
                    case 0xA2:
                    case 0xA5:
                    case 0xA6:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBB:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 358:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 359:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 360:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x86:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 361:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 362:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 363:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 364:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 365:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 366:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 367:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 368:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 369:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 370:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x8B:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 371:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA1:
                    case 0xA2:
                    case 0xA4:
                    case 0xA7:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB9:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 372:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x87:
                    case 0x89:
                    case 0x8B:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x91:
                    case 0x92:
                    case 0x94:
                    case 0x97:
                    case 0x99:
                    case 0x9B:
                    case 0x9D:
                    case 0x9F:
                    case 0xA1:
                    case 0xA2:
                    case 0xA4:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 373:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 374:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 375:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 376:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 377:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 378:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 379:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0xA0:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 380:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 381:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 382:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 383:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 384:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 385:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 386:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 387:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 388:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 389:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9C:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 390:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xBE:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 391:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 392:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8F:
                    case 0x90:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB2:
                    case 0xB3:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 393:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x87:
                    case 0x88:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x90:
                    case 0x97:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 394:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9E:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 395:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x87:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 396:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 397:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 398:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x84:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 399:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 400:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 401:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA3:
                    case 0xA4:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 402:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x87:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 403:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9D:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 404:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 405:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 406:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 407:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xBA:
                    case 0xBC:
                    case 0xBD:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 408:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA7:
                    case 0xA8:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 409:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x90:
                    case 0x91:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 410:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 411:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 412:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 413:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 414:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9D:
                    case 0x9E:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 415:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 416:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 417:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x82:
                    case 0x83:
                    case 0x84:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 418:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 419:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                    case 0xBE:
                    case 0xBF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 420:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xB5:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 421:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x84:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 422:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA3:
                    case 0xA4:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 423:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                    case 0xBA:
                    case 0xBB:
                    case 0xBC:
                    case 0xBD:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 424:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8E:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 425:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x8C:
                    case 0x8D:
                    case 0x8E:
                    case 0x8F:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                    case 0x9A:
                    case 0x9B:
                    case 0x9C:
                    case 0x9D:
                    case 0x9E:
                    case 0x9F:
                    case 0xA0:
                    case 0xA1:
                    case 0xA2:
                    case 0xA3:
                    case 0xA4:
                    case 0xA5:
                    case 0xA6:
                    case 0xA7:
                    case 0xA8:
                    case 0xA9:
                    case 0xAA:
                    case 0xAB:
                    case 0xAC:
                    case 0xAD:
                    case 0xAE:
                    case 0xAF:
                    case 0xB0:
                    case 0xB1:
                    case 0xB2:
                    case 0xB3:
                    case 0xB4:
                    case 0xB5:
                    case 0xB6:
                    case 0xB7:
                    case 0xB8:
                    case 0xB9:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 426:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            case 427:
                $yych = $yyinput[$yycursor];
                switch ($yych) {
                    case 0x80:
                    case 0x81:
                    case 0x82:
                    case 0x83:
                    case 0x84:
                    case 0x85:
                    case 0x86:
                    case 0x87:
                    case 0x88:
                    case 0x89:
                    case 0x8A:
                    case 0x8B:
                    case 0x90:
                    case 0x91:
                    case 0x92:
                    case 0x93:
                    case 0x94:
                    case 0x95:
                    case 0x96:
                    case 0x97:
                    case 0x98:
                    case 0x99:
                        $yycursor += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 36;
                        break 2;
                }
            default:
                throw new \Exception("internal lexer error");
        }
    }

}

if (!lex("_Ыдентификатор\0")) {
    throw new \Exception("error!");
}
