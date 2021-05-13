#include <jni.h>
#include <assert.h>
#include "re2c_RE2C.h"
#include "regex.h"


JNIEXPORT jlong JNICALL Java_re2c_RE2C_regcomp(JNIEnv *env, jclass, jstring pattern,
    jboolean nfa, jboolean regless, jboolean subhist, jboolean tstring, jboolean autotags)
{
    const char *c_pattern = env->GetStringUTFChars(pattern, NULL);
    if (c_pattern == NULL) return 1;

    const int flags = (nfa ? REG_NFA : 0)
        | (regless ? REG_REGLESS : 0)
        | (subhist ? REG_SUBHIST : 0)
        | (tstring ? REG_TSTRING : 0)
        | (autotags ? REG_AUTOTAGS : 0);

    regex_t *re = new regex_t;
    int e = regcomp(re, c_pattern, flags);
    if (e != 0) {
        re = NULL;
        goto end;
    }

    if (re->flags & REG_TSTRING) {
        // allocated by the library
    } else if (re->flags & REG_SUBHIST) {
        // allocated by the library
    } else {
        // allocated by the user (pointer stored in regex_t)
        re->pmatch = new regmatch_t[re->re_nsub];
    }

end:
    env->ReleaseStringUTFChars(pattern, c_pattern);
    return (jlong)re;
}

JNIEXPORT jint JNICALL Java_re2c_RE2C_regexec(JNIEnv *env, jclass,
    jlong reg, jstring str)
{
    const char *c_str = env->GetStringUTFChars(str, NULL);
    if (NULL == c_str) return 1;

    regex_t *re = (regex_t*)reg;
    int e;
    if (re->flags & REG_TSTRING) {
        const tstring_t *s = regtstring(re, c_str);
        e = s ? 0 : 1;
    } else if (re->flags & REG_SUBHIST) {
        re->psubhist = regparse(re, c_str, re->re_nsub);
        e = re->psubhist ? 0 : 1;
    } else {
        e = regexec(re, c_str, re->re_nsub, re->pmatch, 0);
    }

    env->ReleaseStringUTFChars(str, c_str);

    return e;
}

JNIEXPORT void JNICALL Java_re2c_RE2C_regfree(JNIEnv *, jclass, jlong reg)
{
    regex_t *re = (regex_t*)reg;
    if (re->flags & REG_TSTRING) {
        // freed by the library in regfree()
    } else if (re->flags & REG_SUBHIST) {
        // freed by the library in regfreesub()
    } else {
        // freed by the user (pointer stored in regex_t)
        delete[] re->pmatch;
    }
    regfree(re);
    delete re;
}

JNIEXPORT void JNICALL Java_re2c_RE2C_regfreesub(JNIEnv *, jclass, jlong reg)
{
    regex_t *re = (regex_t*)reg;
    if (re->flags & REG_TSTRING) {
        // freed by the library in regfree()
    } else if (re->flags & REG_SUBHIST) {
        // freed by the library in regfreesub()
        regfreesub(re->psubhist);
    } else {
        // freed by the user (pointer stored in regex_t)
    }
}

JNIEXPORT jint JNICALL Java_re2c_RE2C_getNtags(JNIEnv *, jclass, jlong reg)
{
    regex_t *re = (regex_t*)reg;
    return static_cast<jint>(re->re_ntag);
}

JNIEXPORT jint JNICALL Java_re2c_RE2C_getNmatch(JNIEnv *, jclass, jlong reg)
{
    regex_t *re = (regex_t*)reg;
    return static_cast<jint>(re->re_nsub);
}

JNIEXPORT jlong JNICALL Java_re2c_RE2C_getStartOffset(JNIEnv *, jclass,
    jlong reg, jint index)
{
    regex_t *re = (regex_t*)reg;
    return static_cast<jlong>(re->pmatch[index].rm_so);
}

JNIEXPORT jlong JNICALL Java_re2c_RE2C_getEndOffset(JNIEnv *, jclass,
    jlong reg, jint index)
{
    regex_t *re = (regex_t*)reg;
    return static_cast<jlong>(re->pmatch[index].rm_eo);
}

JNIEXPORT jcharArray JNICALL Java_re2c_RE2C_getTstring(JNIEnv *env, jclass, jlong reg)
{
    regex_t *re = (regex_t*)reg;
    const tstring_t &s = re->tstring;
    const jsize length = static_cast<jsize>(s.length);

    jcharArray result = env->NewCharArray(length);

    // C++ t-string character is also 16 bits.
    env->SetCharArrayRegion(result, 0, length, s.string);

    return result;
}
