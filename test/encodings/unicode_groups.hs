{-

Compile: ghc -O2 -W -Wall unicode_groups.hs

This program is a test generator for re2c's support of Unicode encodings.
It generates two kinds of tests:

1) Multiple tests for Unicode categories (like uppercase letters, space
   modifiers, etc.). We cannot test all categories in one file because they
   overlap.

2) Single test for Unicode blocks (like Basic Latin, Hangul, Arabian, etc.).
   These blocks do not overlap, so we can generate one test for all of them.

All tests have the same structure: re2c block for Unicode range is tested on
encoded bytestring, which contains all Unicode runes from this range and ends
with another Unicode rune.

In case of success, generated program runs silently, otherwise it outputs error
to stdout in form "test 'XXX' failed".

-}

import           Data.Char                           (ord, isAlpha)
import qualified Data.CharSet                  as CS (fromCharSet, toAscList, union, empty, complement)
import           Data.CharSet                  as CS (CharSet)
import           Data.CharSet.Unicode.Category       (Category(..), categories)
import           Data.CharSet.Unicode.Block          (Block(..), blocks)
import qualified Data.IntSet                   as IS (foldl')
import qualified Data.List                     as L  (foldl', intercalate)
import           Text.Printf                         (printf)


show_int :: Int -> String
show_int c = case c of
    _ | c < 0xFF   -> printf "\\x%02x" c
    _ | c < 0xFFFF -> printf "\\u%04x" c
    _              -> printf "\\U%08x" c


show_range_re2c :: (Int, Int) -> String
show_range_re2c (l, h) = concat
    [ show_int l
    , "-"
    , show_int h
    ]


show_range_c :: (Int, Int) -> String
show_range_c (l, h) = printf "0x%x,0x%x" l h


take_range :: [(Int, Int)] -> Int -> [(Int, Int)]
take_range [] c = [(c, c)]
take_range ((l, h) : xs) c =
    if c == h + 1
        then (l, c) : xs
        else (c, c) : (l, h) : xs


group_charset :: CharSet -> [(Int, Int)]
group_charset cs =
    ( reverse
    . IS.foldl' take_range []
    . snd
    . CS.fromCharSet
    ) cs


show_charset :: CharSet -> (String, String)
show_charset cs =
    let groups = group_charset cs
        last_char = ord $ outer cs
        groups' = groups ++ [(last_char, last_char)]
        s_re2c = "[" ++ concatMap show_range_re2c groups ++ "]"
        s_c = "{" ++ L.intercalate ",  " (map show_range_c groups') ++ "}"
    in  (s_re2c, s_c)


prettify :: String -> String
prettify = map (\ c -> if isAlpha c then c else '_')


outer :: CharSet -> Char
outer cs = head $ CS.toAscList $ CS.complement cs


encode_function_utf8 :: (String, String)
encode_function_utf8 = ("encode_utf8", unlines
    [ "static unsigned int encode_utf8 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)"
    , "{"
    , "\tunsigned int * const s_start = s;"
    , "\tfor (unsigned int i = 0; i < ranges_count - 2; i += 2)"
    , "\t\tfor (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)"
    , "\t\t\ts += re2c::utf8::rune_to_bytes (s, j);"
    , "\tre2c::utf8::rune_to_bytes (s, ranges[ranges_count - 1]);"
    , "\treturn s - s_start + 1;"
    , "}"
    ])


encode_function_utf16 :: (String, String)
encode_function_utf16 = ("encode_utf16", unlines
    [ "static unsigned int encode_utf16 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)"
    , "{"
    , "\tunsigned int * const s_start = s;"
    , "\tfor (unsigned int i = 0; i < ranges_count; i += 2)"
    , "\t\tfor (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)"
    , "\t\t{"
    , "\t\t\tif (j <= re2c::utf16::MAX_1WORD_RUNE)"
    , "\t\t\t\t*s++ = j;"
    , "\t\t\telse"
    , "\t\t\t{"
    , "\t\t\t\t*s++ = re2c::utf16::lead_surr(j);"
    , "\t\t\t\t*s++ = re2c::utf16::trail_surr(j);"
    , "\t\t\t}"
    , "\t\t}"
    , "\treturn s - s_start;"
    , "}"
    ])


encode_function_utf32 :: (String, String)
encode_function_utf32 = ("encode_utf32", unlines
    [ "static unsigned int encode_utf32 (const unsigned int * ranges, unsigned int ranges_count, unsigned int * s)"
    , "{"
    , "\tunsigned int * const s_start = s;"
    , "\tfor (unsigned int i = 0; i < ranges_count; i += 2)"
    , "\t\tfor (unsigned int j = ranges[i]; j <= ranges[i + 1]; ++j)"
    , "\t\t\t*s++ = j;"
    , "\treturn s - s_start;"
    , "}"
    ])


gen_categories :: [Category] -> IO ()
gen_categories cats =
    let f :: Category -> String
        f (Category _ name charset _) =
            let name' = prettify name
                (charset', _) = show_charset charset
            in name' ++ " = " ++ charset' ++ ";"

        content = unlines $ ["/*!re2c"] ++ (map f cats) ++ ["*/"]

    in  writeFile "unicode_categories.re.inc" content


gen_test_category :: Category -> IO ()
gen_test_category (Category _ name cs _) =
    let catname = prettify name

        file8_ignore      = "unicode_group_" ++ catname ++ "_8_encoding_policy_ignore.re"
        file8_substitute  = "unicode_group_" ++ catname ++ "_8_encoding_policy_substitute.re"
        file8_fail        = "unicode_group_" ++ catname ++ "_8_encoding_policy_fail.re"
        file16_ignore     = "unicode_group_" ++ catname ++ "_x_encoding_policy_ignore.re"
        file16_substitute = "unicode_group_" ++ catname ++ "_x_encoding_policy_substitute.re"
        file16_fail       = "unicode_group_" ++ catname ++ "_x_encoding_policy_fail.re"
        file32_ignore     = "unicode_group_" ++ catname ++ "_u_encoding_policy_ignore.re"
        file32_substitute = "unicode_group_" ++ catname ++ "_u_encoding_policy_substitute.re"
        file32_fail       = "unicode_group_" ++ catname ++ "_u_encoding_policy_fail.re"

        opt8_ignore      = "// re2c $INPUT -o $OUTPUT -8 --encoding-policy ignore"
        opt8_substitute  = "// re2c $INPUT -o $OUTPUT -8 --encoding-policy substitute"
        opt8_fail        = "// re2c $INPUT -o $OUTPUT -8 --encoding-policy fail"
        opt16_ignore     = "// re2c $INPUT -o $OUTPUT -x --encoding-policy ignore"
        opt16_substitute = "// re2c $INPUT -o $OUTPUT -x --encoding-policy substitute"
        opt16_fail       = "// re2c $INPUT -o $OUTPUT -x --encoding-policy fail"
        opt32_ignore     = "// re2c $INPUT -o $OUTPUT -u --encoding-policy ignore"
        opt32_substitute = "// re2c $INPUT -o $OUTPUT -u --encoding-policy substitute"
        opt32_fail       = "// re2c $INPUT -o $OUTPUT -u --encoding-policy fail"

        include_utf8  = "#include \"utf8.h\""
        include_utf16 = "#include \"utf16.h\""
        include_utf32 = ""

        (charset_re2c, charset_c) = show_charset cs
        charset_size = (length $ CS.toAscList cs) + 1 -- +1 for outer symbol
        charset_size_utf8  = show $ charset_size * 4
        charset_size_utf16 = show $ charset_size * 2
        charset_size_utf32 = show $ charset_size
        charset_c_name = "chars_" ++ catname
        buffer = "buffer_" ++ catname

        content ctype opt include sz_charset (ef_name, ef_body) = unlines
            [ opt
            , "#include <stdio.h>"
            , include
            , "#define YYCTYPE " ++ ctype
            , "bool scan(const YYCTYPE * start, const YYCTYPE * const limit)"
            , "{"
            , "\t__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used"
            , "#\tdefine YYCURSOR start"
            , catname ++ ":"
            , "\t/*!re2c"
            , "\t\tre2c:yyfill:enable = 0;"
            , "\t\t" ++ catname ++ " = " ++ charset_re2c ++ ";"
            , "\t\t" ++ catname ++ " { goto " ++ catname ++ "; }"
            , "\t\t* { return YYCURSOR == limit; }"
            , "\t*/"
            , "}"
            , "static const unsigned int " ++ charset_c_name ++ " [] = " ++ charset_c ++ ";"
            , ef_body
            , "int main ()"
            , "{"
            , "\tunsigned int * " ++ buffer ++ " = new unsigned int [" ++ sz_charset ++ "];"
            , "\tYYCTYPE * s = (YYCTYPE *) " ++ buffer ++ ";"
            , "\tunsigned int buffer_len = " ++ ef_name ++ " ("
                ++ charset_c_name ++ ", "
                ++ "sizeof (" ++ charset_c_name ++ ") / sizeof (unsigned int)" ++ ", "
                ++ buffer ++ ");"
            , "\t/* convert 32-bit code units to YYCTYPE; reuse the same buffer */"
            , "\tfor (unsigned int i = 0; i < buffer_len; ++i) s[i] = " ++ buffer ++ "[i];"
            , "\tif (!scan (s, s + buffer_len))"
            , "\t\tprintf(\"test '" ++ catname ++ "' failed\\n\");"
            , "\tdelete [] " ++ buffer ++ ";"
            , "\treturn 0;"
            , "}"
            ]

    in  writeFile file8_ignore      (content "unsigned char"  opt8_ignore      include_utf8  charset_size_utf8  encode_function_utf8) >>
        writeFile file8_substitute  (content "unsigned char"  opt8_substitute  include_utf8  charset_size_utf8  encode_function_utf8) >>
        writeFile file8_fail        (content "unsigned char"  opt8_fail        include_utf8  charset_size_utf8  encode_function_utf8) >>

        writeFile file16_ignore     (content "unsigned short" opt16_ignore     include_utf16 charset_size_utf16 encode_function_utf16) >>
        writeFile file16_substitute (content "unsigned short" opt16_substitute include_utf16 charset_size_utf16 encode_function_utf16) >>
        writeFile file16_fail       (content "unsigned short" opt16_fail       include_utf16 charset_size_utf16 encode_function_utf16) >>

        writeFile file32_ignore     (content "unsigned int"   opt32_ignore     include_utf32 charset_size_utf32 encode_function_utf32) >>
        writeFile file32_substitute (content "unsigned int"   opt32_substitute include_utf32 charset_size_utf32 encode_function_utf32) >>
        writeFile file32_fail       (content "unsigned int"   opt32_fail       include_utf32 charset_size_utf32 encode_function_utf32)


gen_test_blocks :: IO ()
gen_test_blocks =
    let (blocknames, charsets) = unzip $ map (\ (Block name cs) -> (prettify name, cs)) blocks
        blocknames' = blocknames ++ ["All"]
        charsets' = charsets ++ [L.foldl' CS.union CS.empty charsets]
        (charsets_re2c, charsets_c) = unzip $ map show_charset charsets'
        charsets_sizes = map ((+ 1) . length . CS.toAscList) charsets' -- +1 for outer symbol
        charsets_sizes_utf8  = map (show . (* 4)) charsets_sizes
        charsets_sizes_utf16 = map (show . (* 2)) charsets_sizes
        charsets_sizes_utf32 = map show charsets_sizes

        include_utf8  = "#include \"utf8.h\""
        include_utf16 = "#include \"utf16.h\""
        include_utf32 = ""

        file8_ignore      = "unicode_blocks_8_encoding_policy_ignore.re"
        file8_substitute  = "unicode_blocks_8_encoding_policy_substitute.re"
        file8_fail        = "unicode_blocks_8_encoding_policy_fail.re"
        file16_ignore     = "unicode_blocks_x_encoding_policy_ignore.re"
        file16_substitute = "unicode_blocks_x_encoding_policy_substitute.re"
        file16_fail       = "unicode_blocks_x_encoding_policy_fail.re"
        file32_ignore     = "unicode_blocks_u_encoding_policy_ignore.re"
        file32_substitute = "unicode_blocks_u_encoding_policy_substitute.re"
        file32_fail       = "unicode_blocks_u_encoding_policy_fail.re"

        opt8_ignore      = "// re2c $INPUT -o $OUTPUT -8 --encoding-policy ignore"
        opt8_substitute  = "// re2c $INPUT -o $OUTPUT -8 --encoding-policy substitute"
        opt8_fail        = "// re2c $INPUT -o $OUTPUT -8 --encoding-policy fail"
        opt16_ignore     = "// re2c $INPUT -o $OUTPUT -x --encoding-policy ignore"
        opt16_substitute = "// re2c $INPUT -o $OUTPUT -x --encoding-policy substitute"
        opt16_fail       = "// re2c $INPUT -o $OUTPUT -x --encoding-policy fail"
        opt32_ignore     = "// re2c $INPUT -o $OUTPUT -u --encoding-policy ignore"
        opt32_substitute = "// re2c $INPUT -o $OUTPUT -u --encoding-policy substitute"
        opt32_fail       = "// re2c $INPUT -o $OUTPUT -u --encoding-policy fail"

        content ctype opt include sz_charsets (ef_name, ef_body) = unlines
            [ opt
            , "#include <stdio.h>"
            , include
            , "#define YYCTYPE " ++ ctype
            , "enum Block"
            , "{"
            , unlines $ map (\ s -> "\t" ++ s ++ ",") blocknames'
            , "\tError"
            , "};"
            , "Block scan(const YYCTYPE * start, const YYCTYPE * const limit, Block blk)"
            , "{"
            , "\t__attribute__((unused)) const YYCTYPE * YYMARKER; // silence compiler warnings when YYMARKER is not used"
            , "#\tdefine YYCURSOR start"
            , "\tswitch (blk)"
            , "\t{"
            , unlines $ map (\ s -> "\t\tcase " ++ s ++ ": goto " ++ s ++ " ;") blocknames'
            , "\t\tdefault: return Error;"
            , "\t}"
            , "\t/*!re2c"
            , unlines $ map (\ (b, s) -> "\t\t" ++ b ++ " = " ++ s ++ ";") $ zip blocknames' charsets_re2c
            , "\t*/"
            , unlines $ map
                (\ s -> unlines
                    [ s ++ ":"
                    , "\t/*!re2c"
                    , "\t\tre2c:yyfill:enable = 0;"
                    , "\t\t" ++ s ++ " { goto " ++ s ++ "; }"
                    , "\t\t* { if (YYCURSOR == limit) return " ++ s ++ "; else return Error; }"
                    , "\t*/"
                    ]
                ) blocknames'
            , "}"
            , unlines $ map
                (\ (s, cs) -> "static const unsigned int chars_" ++ s ++ " [] = " ++ cs ++ ";"
                ) $ zip blocknames' charsets_c
            , ef_body
            , "int main()"
            , "{"
            , unlines $ map
                (\ (s, sz) ->
                    let buffer = "buffer_" ++ s
                        buffer_len = buffer ++ "_len"
                        str = "s_" ++ s
                        charset_c_name = "chars_" ++ s
                    in  unlines
                        [ "\tunsigned int * " ++ buffer ++ " = new unsigned int [" ++ sz ++ "];"
                        , "\tYYCTYPE * " ++ str ++ " = (YYCTYPE *) " ++ buffer ++ ";"
                        , "\tunsigned int " ++ buffer_len ++ " = " ++ ef_name ++ " ("
                            ++ charset_c_name ++ ", "
                            ++ "sizeof (" ++ charset_c_name ++ ") / sizeof (unsigned int)" ++ ", "
                            ++ buffer ++ ");"
                        , "\t/* convert 32-bit code units to YYCTYPE; reuse the same buffer */"
                        , "\tfor (unsigned int i = 0; i < " ++ buffer_len ++ "; ++i) " ++ str ++ "[i] = " ++ buffer ++ "[i];"
                        , "\tif (scan (" ++ str ++ ", " ++ str ++ " + " ++ buffer_len ++ ", " ++ s ++ ") != " ++ s ++ ")"
                        , "\t\tprintf (\"test '" ++ s ++ "' failed\\n\");"
                        , "\tdelete [] " ++ buffer ++ ";"
                        ]
                ) $ zip blocknames' sz_charsets
            , "\treturn 0;"
            , "}"
            ]

    in  writeFile file8_ignore      (content "unsigned char"  opt8_ignore      include_utf8  charsets_sizes_utf8  encode_function_utf8) >>
        writeFile file8_substitute  (content "unsigned char"  opt8_substitute  include_utf8  charsets_sizes_utf8  encode_function_utf8) >>
        writeFile file8_fail        (content "unsigned char"  opt8_fail        include_utf8  charsets_sizes_utf8  encode_function_utf8) >>

        writeFile file16_ignore     (content "unsigned short" opt16_ignore     include_utf16 charsets_sizes_utf16 encode_function_utf16) >>
        writeFile file16_substitute (content "unsigned short" opt16_substitute include_utf16 charsets_sizes_utf16 encode_function_utf16) >>
        writeFile file16_fail       (content "unsigned short" opt16_fail       include_utf16 charsets_sizes_utf16 encode_function_utf16) >>

        writeFile file32_ignore     (content "unsigned int"   opt32_ignore     include_utf32 charsets_sizes_utf32 encode_function_utf32) >>
        writeFile file32_substitute (content "unsigned int"   opt32_substitute include_utf32 charsets_sizes_utf32 encode_function_utf32) >>
        writeFile file32_fail       (content "unsigned int"   opt32_fail       include_utf32 charsets_sizes_utf32 encode_function_utf32)


main :: IO ()
main = do
    gen_categories categories
    mapM_ gen_test_category categories
    gen_test_blocks
