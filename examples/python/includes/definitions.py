from enum import Enum

class Num(Enum):
    INT = 1
    FLOAT = 2
    NAN = 3

/*!re2c
    number = [1-9][0-9]*;
*/
