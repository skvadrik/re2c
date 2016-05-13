// Be careful with substitution of tag names:
// if one tag's name is a prefix of another tag's name,
// tag with longer name must be substituted first.

/*!re2c
    "a"+ @p12 "b"+ @p123 "c"+ @p "d"+ @p1 "e"+ { @p @p1 @p12 @p123 }
    * {}
*/
