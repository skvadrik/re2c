<?php
// re2php $INPUT -o $OUTPUT

// expects a string without terminating null
function lex($str) {
    $cur = 0;
    $lim = strlen($str);
    $count = 0;

    while (true) {
    
    $yych = 0;
    $yystate = 0;
    while (true) {
        switch ($yystate) {
            case 0:
                $yych = $cur < $lim ? ord($cur) : 0;
                $cur += 1;
                switch ($yych) {
                    case 0x00:
                        $yystate = 1;
                        break 2;
                    case ' ':
                        $yystate = 3;
                        break 2;
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
                        $yystate = 5;
                        break 2;
                    default:
                        $yystate = 2;
                        break 2;
                }
            case 1:
                return $count;
            case 2:
                return -1;
            case 3:
                $yych = $cur < $lim ? ord($cur) : 0;
                switch ($yych) {
                    case ' ':
                        $cur += 1;
                        $yystate = 3;
                        break 2;
                    default:
                        $yystate = 4;
                        break 2;
                }
            case 4:
                break 2;
            case 5:
                $yych = $cur < $lim ? ord($cur) : 0;
                switch ($yych) {
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
                        $cur += 1;
                        $yystate = 5;
                        break 2;
                    default:
                        $yystate = 6;
                        break 2;
                }
            case 6:
                $count += 1; break 2;
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

test("", 0);
test("one two three", 3);
test("f0ur", -1);