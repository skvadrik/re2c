// This example shows that fallback copy of tag, if needed, should be
// created on all non-accepting paths from fallback state, even if they
// don't overwrite the tag. The reason is that overwriting and
// non-overwriting paths may join later along the way and they should
// have the same tag version and at the join point.

/*!re2c

    (("a" @p | "d") "bc")* { p } // join point is "c"

*/
