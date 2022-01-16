#[derive(Debug, PartialEq)]
enum Num { Int, Float, NaN }

/*!re2c
    number = [1-9][0-9]*;
*/
