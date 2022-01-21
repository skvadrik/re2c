// re2c $INPUT

// NFA has too many states
/*!re2c
    x = [a]{1,10};
    y = x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x|
        x|x|x|x|x|x|x|x|x|x;
    z = y{1,10};
    w = z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z|
        z|z|z|z|z|z|z|z|z|z;
    u = w{100};
    u {}
*/
