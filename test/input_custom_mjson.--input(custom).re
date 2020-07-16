// re2c $INPUT -o $OUTPUT  --input custom
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

/** 
 * mjson - modified json parser
 * syntax changes:
 *   - no {} needed around the whole file
 *   - "=" is allowed instead of ":"
 *   - quotes around the key are optional
 *   - commas after values are optional 
 *   - and c-style comments allowed
 *
 * intermediate storage is based on ideas from BJSON specification: http://bjson.org
 *
 * some code ideas are borrowed from another json parser: https://github.com/megous/sjson
 */

#ifndef __MJSON_H_INCLUDED__
#define __MJSON_H_INCLUDED__

#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct _mjson_entry_t;

typedef const struct _mjson_entry_t* mjson_element_t;

enum mjson_element_id_t
{
    MJSON_ID_NULL           =  0,
    MJSON_ID_FALSE          =  1,
    MJSON_ID_EMPTY_STRING   =  2,
    MJSON_ID_TRUE           =  3,

    MJSON_ID_UINT32         =  4,
    MJSON_ID_UINT64         =  5,

    MJSON_ID_SINT32         =  6,
    MJSON_ID_SINT64         =  7,

    MJSON_ID_FLOAT32        =  8,
    MJSON_ID_FLOAT64        =  9,

    MJSON_ID_UTF8_KEY32     = 10,
    MJSON_ID_UTF8_KEY64     = 11,

    MJSON_ID_UTF8_STRING32  = 12,
    MJSON_ID_UTF8_STRING64  = 13,

    MJSON_ID_BINARY32       = 14,
    MJSON_ID_BINARY64       = 15,

    MJSON_ID_ARRAY32        = 16,
    MJSON_ID_ARRAY64        = 17,

    MJSON_ID_DICT32         = 18,
    MJSON_ID_DICT64         = 19
};

int mjson_parse(const char *json_data, size_t json_data_size, void* storage_buf, size_t storage_buf_size, mjson_element_t* top_element);

mjson_element_t   mjson_get_top_element(void* storage_buf, size_t storage_buf_size);

mjson_element_t   mjson_get_element_first(mjson_element_t array);
mjson_element_t   mjson_get_element_next (mjson_element_t array, mjson_element_t current_value);
mjson_element_t   mjson_get_element      (mjson_element_t array, int index);

mjson_element_t   mjson_get_member_first(mjson_element_t dictionary, mjson_element_t* value);
mjson_element_t   mjson_get_member_next (mjson_element_t dictionary, mjson_element_t current_key, mjson_element_t* next_value);
mjson_element_t   mjson_get_member      (mjson_element_t dictionary, const char* name);

int mjson_get_type(mjson_element_t element);

const char* mjson_get_string(mjson_element_t element, const char* fallback);
int32_t     mjson_get_int   (mjson_element_t element, int32_t     fallback);
float       mjson_get_float (mjson_element_t element, float       fallback);
int         mjson_get_bool  (mjson_element_t element, int         fallback);
int         mjson_is_null   (mjson_element_t element);

#ifdef __cplusplus
}
#endif

#endif

enum mjson_token_t
{
    TOK_NONE,
    TOK_IDENTIFIER,
    TOK_NOESC_STRING,
    TOK_STRING,
    TOK_OCT_NUMBER,
    TOK_HEX_NUMBER,
    TOK_DEC_NUMBER,
    TOK_FLOAT_NUMBER,
    TOK_COMMA,
    TOK_COLON,
    TOK_EQUAL,
    TOK_LEFT_BRACKET,
    TOK_RIGHT_BRACKET,
    TOK_LEFT_CURLY_BRACKET,
    TOK_RIGHT_CURLY_BRACKET,
    TOK_FALSE,
    TOK_TRUE,
    TOK_NULL,
    TOK_WHITESPACE,
    TOK_INVALID,
    TOK_COUNT
};

struct _mjson_parser_t
{
    int token;
    uint8_t* start;
    uint8_t* next;
    uint8_t* end;
    uint8_t* bjson;
    uint8_t* bjson_limit;
};

struct _mjson_entry_t
{
    uint32_t  id;
    union
    {
        uint32_t val_u32;
        int32_t  val_s32;
        float    val_f32;
    };
};

#define RETURN_VAL_IF_FAIL(cond, val) if (!(cond)) return (val)
#define RETURN_IF_FAIL(cond) if (!(cond)) return
#define MAX_UTF8_CHAR_LEN 6
#define TRUE  1
#define FALSE 0

typedef struct _mjson_parser_t  mjson_parser_t;
typedef struct _mjson_entry_t   mjson_entry_t;

static void* parsectx_allocate_output(mjson_parser_t* ctx, ptrdiff_t size);

static void parsectx_next_token    (mjson_parser_t* context);

static int parse_value_list    (mjson_parser_t *context);
static int parse_key_value_pair(mjson_parser_t *context, int stop_token);

static mjson_element_t next_element(mjson_element_t element);

int mjson_parse(const char *json_data, size_t json_data_size, void* storage_buf, size_t storage_buf_size, const mjson_entry_t** top_element)
{
    uint32_t* fourcc;
    mjson_parser_t c = {
        TOK_NONE, 0,
        (uint8_t*)json_data,   (uint8_t*)json_data + json_data_size,
        (uint8_t*)storage_buf, (uint8_t*)storage_buf + storage_buf_size
    };
    int stop_token = TOK_NONE;

    *top_element = 0;

    fourcc = (uint32_t*)parsectx_allocate_output(&c, (ptrdiff_t)sizeof(uint32_t));

    if (!fourcc) return 0;

    *fourcc = '23JB';

    parsectx_next_token(&c);

    if (c.token == TOK_LEFT_BRACKET)
    {
        parsectx_next_token(&c);
        if (!parse_value_list(&c))
            return 0;
    }
    else
    {
        if (c.token == TOK_LEFT_CURLY_BRACKET)
        {
            stop_token = TOK_RIGHT_CURLY_BRACKET;
            parsectx_next_token(&c);
        }

        if (!parse_key_value_pair(&c, stop_token))
            return 0;
    }

    if (c.token != TOK_NONE)
        return 0;

    *top_element = (mjson_entry_t*)(fourcc + 1);

    return 1;
}

mjson_element_t mjson_get_top_element(void* storage_buf, size_t storage_buf_size)
{
    mjson_element_t top = (mjson_element_t)storage_buf;
    
    RETURN_VAL_IF_FAIL(top, NULL);
    RETURN_VAL_IF_FAIL(top->id == MJSON_ID_DICT32 || top->id == MJSON_ID_ARRAY32, NULL);
    RETURN_VAL_IF_FAIL(top->val_u32 <= storage_buf_size, NULL);
    
    return top;
}

mjson_element_t mjson_get_element_first(mjson_element_t array)
{
    RETURN_VAL_IF_FAIL(array, NULL);
    RETURN_VAL_IF_FAIL(array->id == MJSON_ID_ARRAY32, NULL);
    
    return array + 1;
}

mjson_element_t mjson_get_element_next(mjson_element_t array, mjson_element_t current_value)
{
    mjson_element_t next = NULL;

    RETURN_VAL_IF_FAIL(array, NULL);
    RETURN_VAL_IF_FAIL(current_value, NULL);
    RETURN_VAL_IF_FAIL(array->id == MJSON_ID_ARRAY32, NULL);
    RETURN_VAL_IF_FAIL((uint8_t*)array + array->val_u32 > (uint8_t*)current_value, NULL);
    
    next = next_element(current_value);
    
    RETURN_VAL_IF_FAIL((uint8_t*)array + array->val_u32 > (uint8_t*)next, NULL);
    
    return next;
}

mjson_element_t mjson_get_element(mjson_element_t array, int index)
{
    mjson_element_t result;
    
    result = mjson_get_element_first(array);
    while (result && index--)
        result = mjson_get_element_next(array, result);
    
    return result;
}

mjson_element_t mjson_get_member_first(mjson_element_t dictionary, mjson_element_t* value)
{
    RETURN_VAL_IF_FAIL(dictionary, NULL);
    RETURN_VAL_IF_FAIL(dictionary->id == MJSON_ID_DICT32, NULL);
    RETURN_VAL_IF_FAIL((dictionary+1)->id == MJSON_ID_UTF8_KEY32, NULL);
    
    *value = next_element(dictionary+1);
    
    return dictionary + 1;
}

mjson_element_t mjson_get_member_next(mjson_element_t dictionary, mjson_element_t current_key, mjson_element_t* next_value)
{
    mjson_element_t next_key = NULL;

    RETURN_VAL_IF_FAIL(dictionary, NULL);
    RETURN_VAL_IF_FAIL(dictionary->id == MJSON_ID_DICT32, NULL);
    RETURN_VAL_IF_FAIL(current_key, NULL);
    RETURN_VAL_IF_FAIL((uint8_t*)dictionary + dictionary->val_u32 > (uint8_t*)current_key, NULL);
    RETURN_VAL_IF_FAIL(current_key->id == MJSON_ID_UTF8_KEY32, NULL);
    
    next_key = next_element(current_key);
    next_key = next_element(next_key);
    
    RETURN_VAL_IF_FAIL(next_key, NULL);
    RETURN_VAL_IF_FAIL((uint8_t*)dictionary + dictionary->val_u32 > (uint8_t*)next_key, NULL);
    RETURN_VAL_IF_FAIL(next_key->id == MJSON_ID_UTF8_KEY32, NULL);

    *next_value = next_element(next_key);
   
    return next_key;    
}

mjson_element_t mjson_get_member(mjson_element_t dictionary, const char* name)
{
    mjson_element_t key, result;
    
    key = mjson_get_member_first(dictionary, &result);
    while (key && strncmp(name, (char*)(key+1), key->val_u32) != 0)
        result = mjson_get_member_next(dictionary, key, &result);
    
    return result;
}

int mjson_get_type(mjson_element_t element)
{
    RETURN_VAL_IF_FAIL(element, MJSON_ID_NULL);
    
    return element->id;
}

const char* mjson_get_string(mjson_element_t element, const char* fallback)
{
    RETURN_VAL_IF_FAIL(element, fallback);
    RETURN_VAL_IF_FAIL(element->id == MJSON_ID_UTF8_STRING32 ||
                       element->id == MJSON_ID_UTF8_KEY32,
                       fallback);
    
    return (const char*)(element+1);
}

int32_t mjson_get_int(mjson_element_t element, int32_t fallback)
{
    RETURN_VAL_IF_FAIL(element, fallback);
    RETURN_VAL_IF_FAIL(element->id == MJSON_ID_SINT32, fallback);
    
    return element->val_s32;
}

float mjson_get_float(mjson_element_t element, float fallback)
{
    RETURN_VAL_IF_FAIL(element, fallback);
    RETURN_VAL_IF_FAIL(element->id == MJSON_ID_FLOAT32, fallback);
    
    return element->val_f32;
}

int mjson_get_bool(mjson_element_t element, int fallback)
{
    RETURN_VAL_IF_FAIL(element, fallback);
    RETURN_VAL_IF_FAIL(element->id == MJSON_ID_TRUE || element->id == MJSON_ID_FALSE, fallback);
    
    return element->id == MJSON_ID_TRUE;
}

int mjson_is_null(mjson_element_t element)
{
    RETURN_VAL_IF_FAIL(element, TRUE);

    return element->id == MJSON_ID_NULL;
}

/////////////////////////////////////////////////////////////////////////////
// API helpers
/////////////////////////////////////////////////////////////////////////////

static size_t element_size(mjson_element_t element)
{
    RETURN_VAL_IF_FAIL(element, 0);

    switch(element->id)
    {
        case MJSON_ID_NULL:
        case MJSON_ID_FALSE:
        case MJSON_ID_EMPTY_STRING:
        case MJSON_ID_TRUE:
            return sizeof(uint32_t);

        case MJSON_ID_UINT32:
        case MJSON_ID_SINT32:
        case MJSON_ID_FLOAT32:
            return sizeof(mjson_entry_t);

        case MJSON_ID_UTF8_KEY32:
        case MJSON_ID_UTF8_STRING32:
            return sizeof(mjson_entry_t) + ((element->val_u32 + 1 + 3) & (~3));

        case MJSON_ID_BINARY32:
        case MJSON_ID_ARRAY32:
        case MJSON_ID_DICT32:
            return sizeof(mjson_entry_t) + ((element->val_u32 + 3) & (~3));
    };

    return 0;
}

static mjson_element_t next_element(mjson_element_t element)
{
    size_t size;
    
    RETURN_VAL_IF_FAIL(element, 0);

    size = element_size(element);
    assert(size>0);
    
    return (mjson_element_t)((uint8_t*)element + size);
}

static void* parsectx_reserve_output(mjson_parser_t* ctx, ptrdiff_t size)
{
    return (ctx->bjson_limit - ctx->bjson < size) ? 0 : ctx->bjson;
}

static void parsectx_advance_output(mjson_parser_t* ctx, ptrdiff_t size)
{
    ctx->bjson += size;
}

static void* parsectx_allocate_output(mjson_parser_t* ctx, ptrdiff_t size)
{
    void* ptr;

    if (ctx->bjson_limit - ctx->bjson < size)
        return 0;

    ptr = ctx->bjson;
    ctx->bjson += size;

    return ptr;
}

//TODO: what about 64 bit code????
static void parsectx_align4_output(mjson_parser_t* ctx)
{
    ctx->bjson = (uint8_t*)(((ptrdiff_t)ctx->bjson + 3) & (~3));
}

static void unicode_cp_to_utf8(uint32_t uni_cp, uint8_t* utf8char/*[6]*/, size_t* charlen)
{
    uint32_t first, i;
    
    if (uni_cp < 0x80)
    {
        first   = 0;
        *charlen = 1;
    }
    else if (uni_cp < 0x800)
    {
        first   = 0xc0;
        *charlen = 2;
    }
    else if (uni_cp < 0x10000)
    {
        first   = 0xe0;
        *charlen = 3;
    }
    else if (uni_cp < 0x200000)
    {
        first   = 0xf0;
        *charlen = 4;
    }
    else if (uni_cp < 0x4000000)
    {
        first   = 0xf8;
        *charlen = 5;
    }
    else
    {
        first   = 0xfc;
        *charlen = 6;
    }

    for (i = *charlen - 1; i > 0; --i)
    {
        utf8char[i] = (uni_cp & 0x3f) | 0x80;
        uni_cp >>= 6;
    }
    utf8char[0] = uni_cp | first;
}

/////////////////////////////////////////////////////////////////////////////
// Lexer+Parser code
/////////////////////////////////////////////////////////////////////////////

/*!re2c
    re2c:yyfill:enable      = 0;
    re2c:indent:top         = 2;
    re2c:indent:string      = "    ";

    WS = [ \t\n\r]+;

    S = [+-];
    O = [0-7];
    D = [0-9];
    H = [a-fA-F0-9];
    L = [a-zA-Z_];
    E = [Ee] [+-]? D+;

    HEX_NUMBER = ("0" [xX] H+);
    OCT_NUMBER = ("0" O+);
    DEC_NUMBER = (S? ("0"|([1-9]D*)));

    FLOAT_NUMBER = (S? D+ E) | (S? D* "." D+ E?) | (S? D+ "." D* E?);

    CHAR               = [^\\"\000];
    CTL                = "\\" ["\\/bfnrt];
    UNICODE            = "\\u" H{4};
    STRING             = "\"" (CHAR|CTL|UNICODE)* "\"";
    NOESC_STRING       = "\"" (CHAR)* "\"";
    IDENTIFIER         = L (L|D)*;
    SINGLELINE_COMMENT = "//" [^\n\000]* "\n";
    MULTILINE_COMMENT  = "\/*" [^*\000]* [*]+ ( [^\/\000] [^*\000]* [*]+ )* "\/";
*/

static void parsectx_next_token(mjson_parser_t* context)
{
#define YYCTYPE        uint8_t
#define YYPEEK()       (c>=e?0:*c)
#define YYSKIP()       ++c
#define YYBACKUP()     m = c
#define YYRESTORE()    c = m

    uint8_t* c = context->next;
    uint8_t* e = context->end;
    uint8_t* m = NULL;
    uint8_t* s;
    int token = TOK_NONE;

    assert(context);
    RETURN_IF_FAIL(context->next != NULL);

    while (TRUE)
    {
        s = c;

/*!re2c
            WS {
                continue; 
            }
            
            SINGLELINE_COMMENT {
                continue; 
            }
            
            MULTILINE_COMMENT {
                continue; 
            }
            
            "{" {
                token = TOK_LEFT_CURLY_BRACKET;
                goto done;
            }
    
            "}" {
                token = TOK_RIGHT_CURLY_BRACKET;
                goto done;
            }
    
            "[" {
                token = TOK_LEFT_BRACKET;
                goto done;
            }
    
            "]" {
                token = TOK_RIGHT_BRACKET;
                goto done;
            }
    
            ":" {
                token = TOK_COLON;
                goto done;
            }
    
            "=" {
                token = TOK_EQUAL;
                goto done;
            }

            "," {
                token = TOK_COMMA;
                goto done;
            }
    
            OCT_NUMBER {
                token = TOK_OCT_NUMBER;
                goto done;
            }
    
            HEX_NUMBER {
                token = TOK_HEX_NUMBER;
                goto done;
            }
    
            DEC_NUMBER {
                token = TOK_DEC_NUMBER;
                goto done;
            }
    
            FLOAT_NUMBER {
                token = TOK_FLOAT_NUMBER;
                goto done;
            }
    
            "true" {
                token = TOK_TRUE;
                goto done;
            }
    
            "false" {
                token = TOK_FALSE;
                goto done;
            }
    
            "null" {
                token = TOK_NULL;
                goto done;
            }
    
            IDENTIFIER {
                token = TOK_IDENTIFIER;
                goto done;
            }

            NOESC_STRING {
                token = TOK_NOESC_STRING;
                goto done;
            }
    
            STRING {
                token = TOK_STRING;
                goto done;
            }
    
            [\000] { 
                context->token = TOK_NONE;
                return;
            }
    
            (L|D)+ {
                context->token = TOK_INVALID;
                return;
            }

            . | "\n" {
                context->token = TOK_INVALID;
                return;
            }
*/
    }

done:
    context->token = token;
    context->start = s;
    context->next  = c;

#undef YYREADINPUT
#undef YYCTYPE           
#undef YYCURSOR          
#undef YYMARKER          
}

static int parse_number(mjson_parser_t *context)
{
    int            num_parsed;
    uint8_t        bjson_id;
    const char*    format;
    mjson_entry_t* bdata;

    switch(context->token)
    {
        case TOK_OCT_NUMBER:
            bjson_id = MJSON_ID_SINT32;
            format   = "%o";
            break;
        case TOK_HEX_NUMBER:
            bjson_id = MJSON_ID_SINT32;
            format   = "%x";
            break;
        case TOK_DEC_NUMBER:
            bjson_id = MJSON_ID_SINT32;
            format   = "%d";
            break;
        case TOK_FLOAT_NUMBER:
            bjson_id = MJSON_ID_FLOAT32;
            format   = "%f";
            break;
        default:
            assert(!"unknown token");
    }

    bdata = (mjson_entry_t*)parsectx_allocate_output(context, (ptrdiff_t)sizeof(mjson_entry_t));

    if (!bdata) return 0;

    bdata->id = bjson_id;
    num_parsed = sscanf((char*)context->start, format, &bdata->val_u32);
    assert(num_parsed == 1);

    parsectx_next_token(context);
    return 1;
}

static int parse_string(mjson_parser_t *context, uint32_t id)
{
#define YYREADINPUT(c) (c>=e?0:*c)
#define YYCTYPE        uint8_t
#define YYCURSOR       c
#define YYMARKER       m

    uint8_t* c = context->start+1;
    uint8_t* e = context->next;
    uint8_t* m = NULL;
    uint8_t* s;

    mjson_entry_t* bdata;
    uint32_t       ch = 0;
    uint8_t*       str_dst;
    const uint8_t* str_src;
    ptrdiff_t      str_len;
    size_t         len;
    int            num_parsed;

    assert(
        context->token == TOK_STRING       ||
        context->token == TOK_NOESC_STRING ||
        context->token == TOK_IDENTIFIER
    );
    
    bdata = (mjson_entry_t*)parsectx_allocate_output(context, (ptrdiff_t)sizeof(mjson_entry_t));
    
    if (!bdata) return 0;
    
    bdata->id = id;

    if (context->token != TOK_STRING)
    {
        str_src = context->start;
        str_len = context->next - context->start;

        if (context->token==TOK_NOESC_STRING)
        {
            str_src += 1;
            str_len -= 2;
        }
        
        bdata->val_u32 = str_len;

        str_dst = (uint8_t*)parsectx_allocate_output(context, str_len + 1);

        if (!str_dst) return 0;

        memcpy(str_dst, str_src, str_len);
        str_dst[str_len] = 0;

        parsectx_align4_output(context);

        parsectx_next_token(context);

        return 1;
    }

    while (TRUE)
    {
        s = c;

/*!re2c
            CHAR+ {
                str_dst = (uint8_t*)parsectx_allocate_output(context, c - s);
                
                if (!str_dst) return 0;
                
                memcpy(str_dst, s, c - s);

                continue;
            }
            
            
            CTL {
                char decoded = s[1];
                
                switch (s[1])
                {
                    case 'b':
                        decoded = '\b';
                        break;
                    case 'n':
                        decoded = '\n';
                        break;
                    case 'r':
                        decoded = '\r';
                        break;
                    case 't':
                        decoded = '\t';
                        break;
                    case 'f':
                        decoded = '\f';
                        break;
                }
                
                str_dst = (uint8_t*)parsectx_allocate_output(context, 1);
                
                if (!str_dst) return 0;
                
                *str_dst = decoded;
                
                continue;
            }

            UNICODE {
                str_dst = (uint8_t*)parsectx_reserve_output(context, 6);

                if (!str_dst) return 0;

                num_parsed = sscanf((char*)(s + 2), "%4x", &ch);
                assert(num_parsed == 1);
                unicode_cp_to_utf8(ch, str_dst, &len);

                parsectx_advance_output(context, len);

                continue;
            }

            "\"" {
                bdata->val_u32 = context->bjson - (uint8_t*)(bdata + 1);
                *context->bjson++ = 0;
                parsectx_align4_output(context);
                parsectx_next_token(context);

                return 1;
            }

            . | "\n" | [\000] { 
                assert(!"reachable");
            }
*/
    }

#undef YYREADINPUT
#undef YYCTYPE           
#undef YYCURSOR          
#undef YYMARKER 

    assert(!"reachable");
    return 0;
}

static int parse_simple(mjson_parser_t *context)
{
    uint32_t* id;

    assert(
        context->token == TOK_NULL  ||
        context->token == TOK_FALSE ||
        context->token == TOK_TRUE
    );

    id = (uint32_t*)parsectx_allocate_output(context, sizeof(uint32_t));
    if (!id) return 0;

    switch (context->token)
    {
        case TOK_NULL:
            *id = MJSON_ID_NULL;
            break;
        case TOK_FALSE:
            *id = MJSON_ID_FALSE;
            break;
        case TOK_TRUE:
            *id = MJSON_ID_TRUE;
            break;
    }

    parsectx_next_token(context);
    return 1;
}

static int parse_value(mjson_parser_t *context)
{
    assert(context);
 
    switch (context->token)
    {
        case TOK_NULL:
        case TOK_FALSE:
        case TOK_TRUE:
            return parse_simple(context);

        case TOK_OCT_NUMBER:
        case TOK_HEX_NUMBER:
        case TOK_DEC_NUMBER:
        case TOK_FLOAT_NUMBER:
            return parse_number(context);

        case TOK_NOESC_STRING:
        case TOK_STRING:
            return parse_string(context, MJSON_ID_UTF8_STRING32);

        case TOK_LEFT_CURLY_BRACKET:
            parsectx_next_token(context);
            return parse_key_value_pair(context, TOK_RIGHT_CURLY_BRACKET);

        case TOK_LEFT_BRACKET:
            parsectx_next_token(context);
            return parse_value_list(context);
    }

    return 0;
}

static int parse_value_list(mjson_parser_t *context)
{
    mjson_entry_t* array;
    uint8_t*       data_start;
    int            expect_separator;

    assert(context);

    array = (mjson_entry_t*)parsectx_allocate_output(context, sizeof(mjson_entry_t));

    if (!array) return 0;
    
    array->id  = MJSON_ID_ARRAY32;
    data_start = context->bjson;

    expect_separator = FALSE;

    while (context->token != TOK_RIGHT_BRACKET)
    {
        if (expect_separator && context->token == TOK_COMMA)
            parsectx_next_token(context);
        else
            expect_separator = TRUE;

        if (!parse_value(context))
            return 0;
    }

    array->val_u32 = context->bjson - data_start;

    assert((array->val_u32 & 3) == 0);

    parsectx_next_token(context);

    return 1;
}

static int parse_key_value_pair(mjson_parser_t* context, int stop_token)
{
    mjson_entry_t* dictionary;
    uint8_t*       data_start;
    int            expect_separator;
 
    assert(context);

    dictionary = (mjson_entry_t*)parsectx_allocate_output(context, sizeof(mjson_entry_t));
    
    if (!dictionary) return 0;
    
    dictionary->id = MJSON_ID_DICT32;
    data_start     = context->bjson;
    
    expect_separator = FALSE;
    while (context->token != stop_token)
    {
        if (expect_separator && context->token == TOK_COMMA)
            parsectx_next_token(context);
        else
            expect_separator = TRUE;

        switch (context->token)
        {
            case TOK_IDENTIFIER:
            case TOK_NOESC_STRING:
                if (!parse_string(context, MJSON_ID_UTF8_KEY32))
                    return 0;
                break;        
            default:
                return 0;
        }

        if (context->token != TOK_COLON && context->token != TOK_EQUAL)
            return 0;

        parsectx_next_token(context);

        if (!parse_value(context))
            return 0;
    }

    dictionary->val_u32 = context->bjson - data_start;
    
    assert((dictionary->val_u32 & 3) == 0);
    
    parsectx_next_token(context);

    return 1;
}
