// re2c $INPUT -o $OUTPUT -i --posix-captures --fixed-tags toplevel
// if two histories are both bottoms (default) for the given tag,
// they are uncomparable from this tag's point of view: decision
// should be relayed on less prioritized tags

/*!re2c
    ("a")? ("b" | "bb")* {}
*/
