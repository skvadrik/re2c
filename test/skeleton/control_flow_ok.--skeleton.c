/* Generated by re2c */

#include <stddef.h> /* size_t */
#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */

static void *read_file
    ( const char *fname
    , size_t unit
    , size_t padding
    , size_t *pfsize
    )
{
    void *buffer = NULL;
    size_t fsize = 0;

    /* open file */
    FILE *f = fopen(fname, "rb");
    if (f == NULL) {
        goto error;
    }

    /* get file size */
    fseek(f, 0, SEEK_END);
    fsize = (size_t) ftell(f) / unit;
    fseek(f, 0, SEEK_SET);

    /* allocate memory for file and padding */
    buffer = malloc(unit * (fsize + padding));
    if (buffer == NULL) {
        goto error;
    }

    /* read the whole file in memory */
    if (fread(buffer, unit, fsize, f) != fsize) {
        goto error;
    }

    fclose(f);
    *pfsize = fsize;
    return buffer;

error:
    fprintf(stderr, "error: cannot read file '%s'\n", fname);
    free(buffer);
    if (f != NULL) {
        fclose(f);
    }
    return NULL;
}

#define YYCTYPE unsigned char
#define YYKEYTYPE unsigned char
#define YYPEEK() *cursor
#define YYSKIP() ++cursor
#define YYLESSTHAN(n) (limit - cursor) < n
#define YYFILL(n) { break; }

static int action_line6
    ( unsigned *pkix
    , const YYKEYTYPE *keys
    , const YYCTYPE *start
    , const YYCTYPE *token
    , const YYCTYPE **cursor
    , YYKEYTYPE rule_act
    )
{
    const unsigned kix = *pkix;
    const long pos = token - start;
    const long len_act = *cursor - token;
    const long len_exp = (long) keys[kix + 1];
    const YYKEYTYPE rule_exp = keys[kix + 2];
    *pkix = kix + 3;
    if (rule_exp == 255) {
        fprintf
            ( stderr
            , "warning: lex_line6: control flow is undefined"
                " for input at position %ld, rerun re2c with '-W'\n"
            , pos
            );
    }
    if (len_act == len_exp && rule_act == rule_exp) {
        const YYKEYTYPE offset = keys[kix];
        *cursor = token + offset;
        return 0;
    } else {
        fprintf
            ( stderr
            , "error: lex_line6: at position %ld (key %u):\n"
                "\texpected: match length %ld, rule %u\n"
                "\tactual:   match length %ld, rule %u\n"
            , pos
            , kix
            , len_exp
            , rule_exp
            , len_act
            , rule_act
            );
        return 1;
    }
}

static int check_key_count_line6(unsigned have, unsigned used, unsigned need)
{
    if (used + need <= have) return 0;
    fprintf(stderr, "error: lex_line6: not enough keys\n");
    return 1;
}

int lex_line6()
{
    const size_t padding = 3; /* YYMAXFILL */
    int status = 0;
    size_t input_len = 0;
    size_t keys_count = 0;
    YYCTYPE *input = NULL;
    YYKEYTYPE *keys = NULL;
    const YYCTYPE *cursor = NULL;
    const YYCTYPE *limit = NULL;
    const YYCTYPE *token = NULL;
    const YYCTYPE *eof = NULL;
    unsigned int i = 0;

    input = (YYCTYPE *) read_file
        ( "skeleton/control_flow_ok.--skeleton.c.line6.input"
        , sizeof (YYCTYPE)
        , padding
        , &input_len
        );
    if (input == NULL) {
        status = 1;
        goto end;
    }

    keys = (YYKEYTYPE *) read_file
        ( "skeleton/control_flow_ok.--skeleton.c.line6.keys"
        , sizeof (YYKEYTYPE)
        , 0
        , &keys_count
        );
    if (keys == NULL) {
        status = 1;
        goto end;
    }

    cursor = input;
    limit = input + input_len + padding;
    eof = input + input_len;

    for (i = 0; status == 0 && cursor < eof && i < keys_count;) {
        token = cursor;
        YYCTYPE yych;

        if (YYLESSTHAN (3)) YYFILL(3);
        yych = YYPEEK ();
        YYSKIP ();
        yych = YYPEEK ();
        YYSKIP ();
        yych = YYPEEK ();
        switch (yych) {
        case 'a':    goto yy5;
        default:    goto yy4;
        }
yy4:
        status = check_key_count_line6(keys_count, i, 3)
             || action_line6(&i, keys, input, token, &cursor, 1);
        continue;
yy5:
        YYSKIP ();
        status = check_key_count_line6(keys_count, i, 3)
             || action_line6(&i, keys, input, token, &cursor, 0);
        continue;

    }
    if (status == 0) {
        if (cursor != eof) {
            status = 1;
            const long pos = token - input;
            fprintf(stderr, "error: lex_line6: unused input strings left at position %ld\n", pos);
        }
        if (i != keys_count) {
            status = 1;
            fprintf(stderr, "error: lex_line6: unused keys left after %u keys\n", i);
        }
    }

end:
    free(input);
    free(keys);

    return status;
}

#undef YYCTYPE
#undef YYKEYTYPE
#undef YYPEEK
#undef YYSKIP
#undef YYLESSTHAN
#undef YYFILL

int main()
{
    if (lex_line6() != 0) {
        return 1;
    }
    return 0;
}
  aaaaaaaaa		a

aaaaaaaaaaaaaaaaaaaaaa  a!!a""a##a$$a%%a&&a''a((a))a**a++a,,a--a..a//a00a11a22a33a44a55a66a77a88a99a::a;;a<<a==a>>a??a@@aAAaBBaCCaDDaEEaFFaGGaHHaIIaJJaKKaLLaMMaNNaOOaPPaQQaRRaSSaTTaUUaVVaWWaXXaYYaZZa[[a\\a]]a^^a__a``aaaabbaccaddaeeaffaggahhaiiajjakkallammannaooappaqqarrassattauuavvawwaxxayyazza{{a||a}}a~~aa��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a��a   			


   !!!"""###$$$%%%&&&'''((()))***+++,,,---...///000111222333444555666777888999:::;;;<<<===>>>???@@@AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVWWWXXXYYYZZZ[[[\\\]]]^^^___```aabbbcccdddeeefffggghhhiiijjjkkklllmmmnnnooopppqqqrrrssstttuuuvvvwwwxxxyyyzzz{{{|||}}}~~~������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������                                                                                                                                                                                                                                                                 