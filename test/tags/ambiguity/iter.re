// re2c $INPUT -o $OUTPUT -i --tags
/*!re2c
    ((@a "a")*)* { @a }
    (("d" @d)*)* { @d }

    (@b "b"*)* { @b }
    ("e"* @e)* { @e }

    (@c "c"+)* { @c }
    ("f"+ @f)* { @f }
*/
