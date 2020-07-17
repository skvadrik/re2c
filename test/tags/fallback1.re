// re2c $INPUT -o $OUTPUT -i --tags
// This test demonstrates that fallback tags should be forward-propagated
// from final states, and that merging all possible fallback tags and
// backward-propagating them from default transitions is too crude,
// inhibits tag interference where there is none and gets in the way
// of tag deduplication.

// Three overlapping rules (constructed so that they trigger 'yyaccept'
// generation), 2nd and 3rd rules have variable-length tail so that their
// tags are not fixed. When 2nd rule is matched, 3rd rule's tag can be
// forgotten: we will never fall back to 3rd rule after matching another
// rule.

/*!re2c

    "ababa"          { 1 }
    "ab" @p "a" "c"? { 2 p }
    @p "a"?          { 3 p }

*/
