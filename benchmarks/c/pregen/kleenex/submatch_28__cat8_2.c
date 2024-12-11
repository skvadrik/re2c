
#define NUM_PHASES 1
#define BUFFER_UNIT_T uint8_t
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>
#include <getopt.h>
#include <unistd.h>
#include <sys/time.h>
#ifdef __APPLE__
#   include <mach-o/dyld.h>
#endif

#define RETC_PRINT_USAGE     1
#define RETC_PRINT_INFO      2

#define OUTBUFFER_SIZE       (16*1024)
#define INBUFFER_SIZE        (16*1024)
#define INITIAL_BUFFER_SIZE  (4096*8)
#define OUTBUFFER_STACK_SIZE (1024)

#ifdef FLAG_NOINLINE
#define INLINE static
#endif
#ifndef INLINE
#define INLINE static inline
#endif

#ifndef BUFFER_UNIT_T
#warning "BUFFER_UNIT_T not defined. Falling back to default 'uint8_t'"
#define BUFFER_UNIT_T uint8_t
#endif

#ifndef NUM_PHASES
#error "NUM_PHASES not defined."
#endif

#ifndef OUTSTREAM
#define OUTSTREAM stdout
#endif

// Order of descriptors provided by pipe()
#define  READ_FD 0
#define WRITE_FD 1

typedef BUFFER_UNIT_T buffer_unit_t;
typedef struct {
  buffer_unit_t *data;
  size_t size;         /* size in bytes */
  size_t bitpos;       /* bit offset from data  */
} buffer_t;

#define BUFFER_UNIT_SIZE (sizeof(buffer_unit_t))
#define BUFFER_UNIT_BITS (BUFFER_UNIT_SIZE * 8)

unsigned char *next;
buffer_t outbuf;
buffer_t *outbuf_ptr;
size_t count = 0;

unsigned char inbuf[INBUFFER_SIZE*2];
size_t in_size = 0;
int in_cursor = 0;
#define avail (in_size - in_cursor)

// Output buffer stack

typedef struct {
  buffer_t **data;
  size_t capacity;
  size_t size;
} buf_stack;

buf_stack outbuf_stack;

void pushoutbuf(buffer_t *buf) {
  if (outbuf_stack.size == outbuf_stack.capacity) {
    outbuf_stack.capacity *= 2;
    outbuf_stack.data = realloc(outbuf_stack.data, outbuf_stack.capacity*sizeof(buffer_t *));
  }
  outbuf_stack.data[outbuf_stack.size++] = outbuf_ptr;
  outbuf_ptr = buf;
}

void popoutbuf() {
  if (outbuf_stack.size <= 0) {
    fprintf(stderr, "Error: Tried popping an empty buffer stack");
    exit(1);
  }
  outbuf_ptr = outbuf_stack.data[--outbuf_stack.size];
}

void init_outbuf_stack()
{
  outbuf_ptr = &outbuf;
  outbuf_stack.size = 0;
  outbuf_stack.capacity = OUTBUFFER_STACK_SIZE;
  outbuf_stack.data = malloc(OUTBUFFER_STACK_SIZE*sizeof(buffer_t *));
}

// Program interface

void printCompilationInfo();
void init();
void match(int phase);

void buf_flush(buffer_t *buf)
{
  size_t word_index = buf->bitpos / BUFFER_UNIT_BITS;
  // If we do not have a single complete word to flush, return.
  // Not just an optimization! The zeroing logic below assumes word_index > 0.
  if (word_index == 0)
  {
    return;
  }
  if (fwrite(buf->data, BUFFER_UNIT_SIZE, word_index, OUTSTREAM) == -1)
  {
    fprintf(stderr, "Error writing to output stream.\n");
    exit(1);
  }
  // Since partially written words are not flushed, they need to be moved to the
  // beginning of the buffer.
  if (buf->bitpos % BUFFER_UNIT_BITS != 0)
  {
    buf->data[0] = buf->data[word_index];
  }
  else
  {
    // If we flushed everything, re-establish the invariant that the word at the
    // cursor is garbage-free by simply zeroing it.
    buf->data[0] = 0;
  }

  // Rewind cursor
  buf->bitpos = buf->bitpos - word_index * BUFFER_UNIT_BITS;
}

// Write first 'bits' of 'w' to 'buf', starting from the MOST significant bit.
// Precondition: Remaining bits of 'w' must be zero.
INLINE
bool buf_writeconst(buffer_t *buf, buffer_unit_t w, size_t bits)
{
  size_t word_index = buf->bitpos / BUFFER_UNIT_BITS;
  size_t offset = buf->bitpos % BUFFER_UNIT_BITS;
  size_t bits_available = BUFFER_UNIT_BITS - offset;

#ifdef FLAG_WORDALIGNED
  buf->data[word_index] = w;
#else
  buf->data[word_index] |= w >> offset;
  // test for offset > 0 important; shifting by the word size is undefined behaviour.
  buf->data[word_index+1] = (offset == 0) ? 0 : (w << bits_available);
#endif

  buf->bitpos += bits;

  // Is cursor in last word?
  return (buf->bitpos >= buf->size * 8 - BUFFER_UNIT_BITS);
}

void buf_resize(buffer_t *buf, size_t shift)
{
  size_t new_size = buf->size << shift;
  buffer_unit_t *data2 = calloc(new_size, 1);
  memcpy(data2, buf->data, buf->size);
  free(buf->data);
  buf->data = data2;
  buf->size = new_size;
}

INLINE
void buf_writearray(buffer_t *dst, const buffer_unit_t *arr, size_t bits)
{
  if (dst->bitpos % BUFFER_UNIT_BITS == 0)
  {
    int count = (bits / BUFFER_UNIT_BITS) + (bits % BUFFER_UNIT_BITS ? 1 : 0);
    memcpy(&dst->data[dst->bitpos / BUFFER_UNIT_BITS], arr, count * BUFFER_UNIT_SIZE);
    dst->bitpos += bits;
    dst->data[dst->bitpos / BUFFER_UNIT_BITS] = 0;
  } else
  {
    int word_index = 0;
    for (word_index = 0; word_index < bits / BUFFER_UNIT_BITS; word_index++)
    {
      buf_writeconst(dst, arr[word_index], BUFFER_UNIT_BITS);
    }

    if (bits % BUFFER_UNIT_BITS != 0)
    {
      buf_writeconst(dst, arr[word_index], bits % BUFFER_UNIT_BITS);
    }
  }
}

INLINE
void reset(buffer_t *buf)
{
  buf->data[0] = 0;
  buf->bitpos = 0;
}

void init_buffer(buffer_t *buf)
{
  buf->data = malloc(INITIAL_BUFFER_SIZE);
  buf->size = INITIAL_BUFFER_SIZE;
  buf->bitpos = 0;
  buf->data[0] = 0;
}

void destroy_buffer(buffer_t *buf)
{
  if (buf->data != NULL)
    free(buf->data);
  buf->data = NULL;
}

INLINE
void outputconst(buffer_unit_t w, size_t bits)
{
  if (buf_writeconst(outbuf_ptr, w, bits))
  {
    if (outbuf_stack.size == 0)
    {
      buf_flush(outbuf_ptr);
    }
  }
}

INLINE
void appendarray(buffer_t *dst, const buffer_unit_t *arr, size_t bits)
{
  size_t total_bits = dst->bitpos + bits;
  if (total_bits >= (dst->size - 1) * BUFFER_UNIT_BITS * BUFFER_UNIT_SIZE)
  {
    size_t shift = 1;
    while (total_bits >= ((dst->size << shift) - 1) * BUFFER_UNIT_BITS * BUFFER_UNIT_SIZE)
    {
      shift++;
    }
    buf_resize(dst, shift);
  }

  buf_writearray(dst, arr, bits);
}

INLINE
void append(buffer_t *buf, buffer_unit_t w, size_t bits)
{
  if (buf_writeconst(buf, w, bits))
  {
    buf_resize(buf, 1);
  }
}

INLINE
void concat(buffer_t *dst, buffer_t *src)
{
  appendarray(dst, src->data, src->bitpos);
}

INLINE
void outputarray(const buffer_unit_t *arr, size_t bits)
{
  int word_count = bits / BUFFER_UNIT_BITS;
  // Write completed words
  size_t word_index = 0;
  for (word_index = 0; word_index < word_count; word_index++)
  {
    outputconst(arr[word_index], BUFFER_UNIT_BITS);
  }

  int remaining = bits % BUFFER_UNIT_BITS;
  if (remaining != 0)
  {
    outputconst(arr[bits / BUFFER_UNIT_BITS], remaining);
  }
}

INLINE
void output(buffer_t *buf)
{
  outputarray(buf->data, buf->bitpos);
}

INLINE
void consume(int c)
{
  count     += c;
  in_cursor += c;
  next      += c;
}

INLINE
int readnext(int minCount, int maxCount)
{
  // We can always take epsilon transitions
  if (minCount == 0) return 1;

  if (avail < maxCount)
  {
    int remaining = avail;
    memmove(&inbuf[INBUFFER_SIZE - remaining], &inbuf[INBUFFER_SIZE+in_cursor], remaining);
    in_cursor = -remaining;
    in_size = fread(&inbuf[INBUFFER_SIZE], 1, INBUFFER_SIZE, stdin);
  }
  if (avail < minCount)
  {
    return 0;
  }
  next = &inbuf[INBUFFER_SIZE+in_cursor];
  return 1;
}

INLINE
int cmp(unsigned char *str1, unsigned char *str2, int l)
{
  int i = 0;
  for (i = 0; i < l; i++)
  {
    if (str1[i] != str2[i])
      return 0;
  }
  return 1;
}

void printUsage(char *name)
{
  fprintf(stdout, "Normal usage: %s < infile > outfile\n", name);
  fprintf(stdout, "- \"%s\": reads from stdin and writes to stdout.\n", name);
  fprintf(stdout, "- \"%s -i\": prints compilation info.\n", name);
  fprintf(stdout, "- \"%s -t\": runs normally, but prints timing to stderr.\n", name);
}

void flush_outbuf()
{
  if (outbuf.bitpos % BUFFER_UNIT_BITS != 0)
  {
    outputconst(0, BUFFER_UNIT_BITS);
  }
  if (outbuf_stack.size > 0)
  {
    fprintf(stderr, "Error: buffer stack ended non-empty\n");
    exit(1);
  }
  buf_flush(&outbuf);
}

void init_outbuf()
{
  outbuf.size = OUTBUFFER_SIZE + BUFFER_UNIT_SIZE;
  outbuf.data = malloc(outbuf.size);
  reset(&outbuf);
  init_outbuf_stack();
}

void run(int phase)
{
  init_outbuf();
  init();

  match(phase);

  flush_outbuf();
}

#ifndef FLAG_NOMAIN
static struct option long_options[] = {
    { "phase", required_argument, 0, 'p' },
    { 0, 0, 0, 0 }
};

int main(int argc, char *argv[])
{
  bool do_timing = false;
  int c;
  int option_index = 0;
  int phase;
  bool do_phase = false;

  while ((c = getopt_long (argc, argv, "ihtp:", long_options, &option_index)) != -1)
  {
    switch (c)
    {
      case 'i':
        printCompilationInfo();
        return RETC_PRINT_INFO;
      case 't':
        do_timing = true;
        break;
      case 'p':
        phase = atoi(optarg);
        do_phase = true;
        break;
      case 'h':
      default:
        printUsage(argv[0]);
        return RETC_PRINT_USAGE;
    }
  }

  struct timeval time_before, time_after, time_result;
  long int millis;
  if(do_timing)
  {
    gettimeofday(&time_before, NULL);
  }

  if (do_phase)
  {
    run(phase);
  }
  else
  {
    // set up a pipeline
    // stdin -> prog --phase 1 -> prog --phase 2 -> ... -> prog --phase n -> stdout

    int orig_stdout = dup(STDOUT_FILENO);
    int pipes[NUM_PHASES-1][2];

    int i;
    for (i = 1; i < NUM_PHASES; i++)
    {
      if (i != 1) close(pipes[i-2][WRITE_FD]);

      if (pipe(pipes[i-1]) != 0)
      {
        fprintf(stderr, "Error creating pipe %d.", i);
        return 1;
      }
      dup2(pipes[i-1][WRITE_FD], STDOUT_FILENO);

      if (! fork())
      {
        close(orig_stdout);
        close(pipes[i-1][READ_FD]);

        // Should use snprintf, but I assume something else will break before we hit 10^19 phases.
        char phase[20] = {0};
        sprintf(phase, "%d", i);
        char *args[] = { argv[0], "--phase", phase, 0 };
        return main(3, args);
      }

      close(STDIN_FILENO);
      dup2(pipes[i-1][READ_FD], STDIN_FILENO);
    }

    #if NUM_PHASES>1
    close(pipes[NUM_PHASES-2][WRITE_FD]);
    dup2(orig_stdout, STDOUT_FILENO);
    #endif

    // Run last phase in-process
    run(NUM_PHASES);
  }

  if (do_timing)
  {
    gettimeofday(&time_after, NULL);
    timersub(&time_after, &time_before, &time_result);
    // A timeval contains seconds and microseconds.
    millis = time_result.tv_sec * 1000 + time_result.tv_usec / 1000;
    fprintf(stderr, "time (ms): %ld\n", millis);
  }

  return 0;
}
#endif

/* no tables */
buffer_t buf_0;
buffer_t buf_1;
buffer_t buf_2;
buffer_t buf_3;
buffer_t buf_4;
buffer_t buf_5;
buffer_t buf_6;
buffer_t buf_7;
buffer_t buf_8;
buffer_t buf_9;
buffer_t buf_10;
buffer_t buf_11;
buffer_t buf_12;
buffer_t buf_13;
buffer_t buf_14;
// \xa
const buffer_unit_t const_1_0[1] = {0xa};
// .
const buffer_unit_t const_1_1[1] = {0x2e};
// .a
const buffer_unit_t const_1_2[2] = {0x2e,0x61};
// .aa\xa
const buffer_unit_t const_1_3[4] = {0x2e,0x61,0x61,0xa};
// .aa.
const buffer_unit_t const_1_4[4] = {0x2e,0x61,0x61,0x2e};
// .aa..aa
const buffer_unit_t const_1_5[7] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa\xa
const buffer_unit_t const_1_6[8] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa
const buffer_unit_t const_1_7[11] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa..aa\xa
const buffer_unit_t const_1_8[12] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa..aa
const buffer_unit_t const_1_9[15] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa..aa..aa\xa
const buffer_unit_t const_1_10[16] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa..aa..aa
const buffer_unit_t const_1_11[19] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa..aa..aa..aa\xa
const buffer_unit_t const_1_12[20] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa..aa..aa..aa
const buffer_unit_t const_1_13[23] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa..aa..aa..aa..aa\xa
const buffer_unit_t const_1_14[24] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa..aa..aa..aa..aa
const buffer_unit_t const_1_15[27] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa..aa..aa..aa..aa..aa\xa
const buffer_unit_t const_1_16[28] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa..aa..aa..aa..aa..aa
const buffer_unit_t const_1_17[31] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aa..aa..aa..aa..aa..aa..aa..aa\xa
const buffer_unit_t const_1_18[32] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0xa};
// .aa..aa..aa..aa..aa..aa..aa..aab
const buffer_unit_t const_1_19[32] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa..aa..aa..aa..aa..aa..aab
const buffer_unit_t const_1_20[28] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa..aa..aa..aa..aa..aab
const buffer_unit_t const_1_21[24] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa..aa..aa..aa..aab
const buffer_unit_t const_1_22[20] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa..aa..aa..aab
const buffer_unit_t const_1_23[16] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa..aa..aab
const buffer_unit_t const_1_24[12] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa..aab
const buffer_unit_t const_1_25[8] = {0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x62};
// .aa.a
const buffer_unit_t const_1_26[5] = {0x2e,0x61,0x61,0x2e,0x61};
// .aab
const buffer_unit_t const_1_27[4] = {0x2e,0x61,0x61,0x62};
// a
const buffer_unit_t const_1_28[1] = {0x61};
// a.aa
const buffer_unit_t const_1_29[4] = {0x61,0x2e,0x61,0x61};
// a.aa..aa
const buffer_unit_t const_1_30[8] = {0x61,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aa..aa..aa
const buffer_unit_t const_1_31[12] = {0x61,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aa..aa..aa..aa
const buffer_unit_t const_1_32[16] = {0x61,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aa..aa..aa..aa..aa
const buffer_unit_t const_1_33[20] = {0x61,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aa..aa..aa..aa..aa..aa
const buffer_unit_t const_1_34[24] = {0x61,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aa..aa..aa..aa..aa..aa..aa
const buffer_unit_t const_1_35[28] = {0x61,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61,0x2e,0x2e,0x61,0x61};
// aa
const buffer_unit_t const_1_36[2] = {0x61,0x61};
// aa.aab
const buffer_unit_t const_1_37[6] = {0x61,0x61,0x2e,0x61,0x61,0x62};
// aaa
const buffer_unit_t const_1_38[3] = {0x61,0x61,0x61};
// b
const buffer_unit_t const_1_39[1] = {0x62};
void printCompilationInfo()
{
  fprintf(stdout, "No object file generated!\nOptions:\nSST optimization level:  3\nWord size:               UInt8T\nIdentity tables removed: False\n\nSource file: ../../../benchmarks/submatch_dfa_aot/src/kleenex/28__cat8_2.kex\nSource md5:  6898388b6920f2bd628e4ef4fc8e e4b\nSST states:  230\n");
}

void init()
{
init_buffer(&buf_1);
init_buffer(&buf_2);
init_buffer(&buf_3);
init_buffer(&buf_4);
init_buffer(&buf_5);
init_buffer(&buf_6);
init_buffer(&buf_7);
init_buffer(&buf_8);
init_buffer(&buf_9);
init_buffer(&buf_10);
init_buffer(&buf_11);
init_buffer(&buf_12);
init_buffer(&buf_13);
init_buffer(&buf_14);
}
void match1()
{
  int i = 0;
goto l1_0;
l1_0: if (!readnext(1, 2))
      {
         goto accept1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_40;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_1;
      }
      goto fail1;
l1_1: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_40;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_1;
      }
      goto fail1;
l1_2: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_43;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_2;
      }
      goto fail1;
l1_3: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_46;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_3;
      }
      goto fail1;
l1_4: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_49;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_4;
      }
      goto fail1;
l1_5: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_52;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_5;
      }
      goto fail1;
l1_6: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_55;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_6;
      }
      goto fail1;
l1_7: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_58;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_7;
      }
      goto fail1;
l1_8: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            consume(2);
            goto l1_60;
         }
         outputarray(const_1_28,8);
         consume(1);
         goto l1_8;
      }
      goto fail1;
l1_9: if (!readnext(1, 2))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 2) && ((next[1] == 'a') && 1)))
         {
            outputarray(const_1_1,8);
            consume(2);
            goto l1_43;
         }
         outputarray(const_1_2,16);
         consume(1);
         goto l1_2;
      }
      if (((avail >= 1) && ((next[0] == 'b') && 1)))
      {
         outputarray(const_1_39,8);
         consume(1);
         goto l1_9;
      }
      goto fail1;
l1_10: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_1,8);
             consume(2);
             goto l1_46;
          }
          outputarray(const_1_2,16);
          consume(1);
          goto l1_3;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_10;
       }
       goto fail1;
l1_11: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_1,8);
             consume(2);
             goto l1_49;
          }
          outputarray(const_1_2,16);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_11;
       }
       goto fail1;
l1_12: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_1,8);
             consume(2);
             goto l1_52;
          }
          outputarray(const_1_2,16);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_12;
       }
       goto fail1;
l1_13: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_1,8);
             consume(2);
             goto l1_55;
          }
          outputarray(const_1_2,16);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_13;
       }
       goto fail1;
l1_14: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_1,8);
             consume(2);
             goto l1_58;
          }
          outputarray(const_1_2,16);
          consume(1);
          goto l1_7;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_14;
       }
       goto fail1;
l1_15: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_1,8);
             consume(2);
             goto l1_60;
          }
          outputarray(const_1_2,16);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_15;
       }
       goto fail1;
l1_16: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_0,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_39,8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_17: if (!readnext(1, 2))
       {
          goto accept1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_40;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_1;
       }
       goto fail1;
l1_18: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_67;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_19: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_67;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_18;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_9;
       }
       goto fail1;
l1_20: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_70;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_20;
       }
       goto fail1;
l1_21: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_70;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_10;
       }
       goto fail1;
l1_22: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_73;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_22;
       }
       goto fail1;
l1_23: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_73;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_11;
       }
       goto fail1;
l1_24: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_76;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_24;
       }
       goto fail1;
l1_25: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_76;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_12;
       }
       goto fail1;
l1_26: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_79;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_27: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_79;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_26;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_13;
       }
       goto fail1;
l1_28: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_82;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_28;
       }
       goto fail1;
l1_29: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_82;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_28;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_14;
       }
       goto fail1;
l1_30: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_84;
          }
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_30;
       }
       goto fail1;
l1_31: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_84;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_15;
       }
       goto fail1;
l1_32: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_3,32);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_36,16);
             consume(2);
             goto l1_60;
          }
          outputarray(const_1_38,24);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_33: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_70;
          }
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_33;
       }
       goto fail1;
l1_34: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_73;
          }
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_34;
       }
       goto fail1;
l1_35: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_76;
          }
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_36: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_79;
          }
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_26;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_36;
       }
       goto fail1;
l1_37: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_82;
          }
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_28;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_37;
       }
       goto fail1;
l1_38: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_84;
          }
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_39: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_8);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             output(&buf_1);
             outputarray(const_1_1,8);
             consume(2);
             goto l1_60;
          }
          output(&buf_1);
          outputarray(const_1_2,16);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_39,8);
          consume(1);
          goto l1_39;
       }
       goto fail1;
l1_40: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_90;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_19;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_9;
       }
       goto fail1;
l1_41: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_91;
          }
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_41;
       }
       goto fail1;
l1_42: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_91;
          }
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_41;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_33;
       }
       goto fail1;
l1_43: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_94;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_10;
       }
       goto fail1;
l1_44: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_95;
          }
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_44;
       }
       goto fail1;
l1_45: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_95;
          }
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_44;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_34;
       }
       goto fail1;
l1_46: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_98;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_23;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_11;
       }
       goto fail1;
l1_47: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_99;
          }
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_47;
       }
       goto fail1;
l1_48: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_99;
          }
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_49: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_102;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_25;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_12;
       }
       goto fail1;
l1_50: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_103;
          }
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_50;
       }
       goto fail1;
l1_51: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_103;
          }
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_50;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_36;
       }
       goto fail1;
l1_52: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_106;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_27;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_13;
       }
       goto fail1;
l1_53: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_107;
          }
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_53;
       }
       goto fail1;
l1_54: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_107;
          }
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_53;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_37;
       }
       goto fail1;
l1_55: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_109;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_14;
       }
       goto fail1;
l1_56: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_110;
          }
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_56;
       }
       goto fail1;
l1_57: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_110;
          }
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_56;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_58: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_111;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_31;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_15;
       }
       goto fail1;
l1_59: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_8);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             appendarray(&buf_8,const_1_4,32);
             output(&buf_1);
             reset(&buf_1);
             appendarray(&buf_1,const_1_36,16);
             consume(2);
             goto l1_84;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_26,40);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_39;
       }
       goto fail1;
l1_60: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_3,32);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             outputarray(const_1_36,16);
             consume(2);
             goto l1_60;
          }
          outputarray(const_1_28,8);
          consume(1);
          goto l1_32;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_27,32);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_61: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_2,const_1_1,8);
             consume(2);
             goto l1_95;
          }
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_44;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_39,8);
          consume(1);
          goto l1_61;
       }
       goto fail1;
l1_62: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_2,const_1_1,8);
             consume(2);
             goto l1_99;
          }
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_39,8);
          consume(1);
          goto l1_62;
       }
       goto fail1;
l1_63: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_2,const_1_1,8);
             consume(2);
             goto l1_103;
          }
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_50;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_39,8);
          consume(1);
          goto l1_63;
       }
       goto fail1;
l1_64: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_2,const_1_1,8);
             consume(2);
             goto l1_107;
          }
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_53;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_39,8);
          consume(1);
          goto l1_64;
       }
       goto fail1;
l1_65: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_2,const_1_1,8);
             consume(2);
             goto l1_110;
          }
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_56;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_39,8);
          consume(1);
          goto l1_65;
       }
       goto fail1;
l1_66: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_8);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             concat(&buf_8,&buf_9);
             appendarray(&buf_8,const_1_1,8);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             appendarray(&buf_1,const_1_1,8);
             consume(2);
             goto l1_84;
          }
          reset(&buf_8);
          concat(&buf_8,&buf_9);
          appendarray(&buf_8,const_1_2,16);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_39,8);
          consume(1);
          goto l1_66;
       }
       goto fail1;
l1_67: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_116;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_42;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_33;
       }
       goto fail1;
l1_68: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_117;
          }
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_3,const_1_28,8);
          consume(1);
          goto l1_68;
       }
       goto fail1;
l1_69: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_10);
             appendarray(&buf_10,const_1_4,32);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_3);
             appendarray(&buf_3,const_1_36,16);
             consume(2);
             goto l1_117;
          }
          reset(&buf_10);
          appendarray(&buf_10,const_1_26,40);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_38,24);
          consume(1);
          goto l1_68;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_61;
       }
       goto fail1;
l1_70: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_120;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_45;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_34;
       }
       goto fail1;
l1_71: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_121;
          }
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_3,const_1_28,8);
          consume(1);
          goto l1_71;
       }
       goto fail1;
l1_72: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_10);
             appendarray(&buf_10,const_1_4,32);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_3);
             appendarray(&buf_3,const_1_36,16);
             consume(2);
             goto l1_121;
          }
          reset(&buf_10);
          appendarray(&buf_10,const_1_26,40);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_38,24);
          consume(1);
          goto l1_71;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_62;
       }
       goto fail1;
l1_73: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_124;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_48;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_74: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_125;
          }
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_3,const_1_28,8);
          consume(1);
          goto l1_74;
       }
       goto fail1;
l1_75: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_10);
             appendarray(&buf_10,const_1_4,32);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_3);
             appendarray(&buf_3,const_1_36,16);
             consume(2);
             goto l1_125;
          }
          reset(&buf_10);
          appendarray(&buf_10,const_1_26,40);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_38,24);
          consume(1);
          goto l1_74;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_63;
       }
       goto fail1;
l1_76: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_128;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_51;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_36;
       }
       goto fail1;
l1_77: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_129;
          }
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_3,const_1_28,8);
          consume(1);
          goto l1_77;
       }
       goto fail1;
l1_78: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_10);
             appendarray(&buf_10,const_1_4,32);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_3);
             appendarray(&buf_3,const_1_36,16);
             consume(2);
             goto l1_129;
          }
          reset(&buf_10);
          appendarray(&buf_10,const_1_26,40);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_38,24);
          consume(1);
          goto l1_77;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_64;
       }
       goto fail1;
l1_79: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_131;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_54;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_37;
       }
       goto fail1;
l1_80: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_132;
          }
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_3,const_1_28,8);
          consume(1);
          goto l1_80;
       }
       goto fail1;
l1_81: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_10);
             appendarray(&buf_10,const_1_4,32);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_3);
             appendarray(&buf_3,const_1_36,16);
             consume(2);
             goto l1_132;
          }
          reset(&buf_10);
          appendarray(&buf_10,const_1_26,40);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_38,24);
          consume(1);
          goto l1_80;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_65;
       }
       goto fail1;
l1_82: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_133;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_57;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_83: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_8);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             concat(&buf_8,&buf_9);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_9);
             appendarray(&buf_9,const_1_4,32);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             appendarray(&buf_2,const_1_36,16);
             consume(2);
             goto l1_110;
          }
          reset(&buf_8);
          concat(&buf_8,&buf_9);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_9);
          appendarray(&buf_9,const_1_26,40);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_38,24);
          consume(1);
          goto l1_56;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_66;
       }
       goto fail1;
l1_84: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_8);
          outputarray(const_1_3,32);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             output(&buf_1);
             consume(2);
             goto l1_111;
          }
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_1,const_1_28,8);
          consume(1);
          goto l1_59;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_1,const_1_27,32);
          consume(1);
          goto l1_39;
       }
       goto fail1;
l1_85: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_10,const_1_1,8);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_3,const_1_1,8);
             consume(2);
             goto l1_121;
          }
          appendarray(&buf_10,const_1_2,16);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_3,const_1_2,16);
          consume(1);
          goto l1_71;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_39,8);
          consume(1);
          goto l1_85;
       }
       goto fail1;
l1_86: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_10,const_1_1,8);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_3,const_1_1,8);
             consume(2);
             goto l1_125;
          }
          appendarray(&buf_10,const_1_2,16);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_3,const_1_2,16);
          consume(1);
          goto l1_74;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_39,8);
          consume(1);
          goto l1_86;
       }
       goto fail1;
l1_87: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_10,const_1_1,8);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_3,const_1_1,8);
             consume(2);
             goto l1_129;
          }
          appendarray(&buf_10,const_1_2,16);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_3,const_1_2,16);
          consume(1);
          goto l1_77;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_39,8);
          consume(1);
          goto l1_87;
       }
       goto fail1;
l1_88: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             appendarray(&buf_10,const_1_1,8);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             appendarray(&buf_3,const_1_1,8);
             consume(2);
             goto l1_132;
          }
          appendarray(&buf_10,const_1_2,16);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          appendarray(&buf_3,const_1_2,16);
          consume(1);
          goto l1_80;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_39,8);
          consume(1);
          goto l1_88;
       }
       goto fail1;
l1_89: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_8);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_8);
             concat(&buf_8,&buf_9);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_9);
             concat(&buf_9,&buf_10);
             appendarray(&buf_9,const_1_1,8);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             concat(&buf_2,&buf_3);
             appendarray(&buf_2,const_1_1,8);
             consume(2);
             goto l1_110;
          }
          reset(&buf_8);
          concat(&buf_8,&buf_9);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_9);
          concat(&buf_9,&buf_10);
          appendarray(&buf_9,const_1_2,16);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_56;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_39,8);
          consume(1);
          goto l1_89;
       }
       goto fail1;
l1_90: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_137;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_5,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_36,16);
          outputarray(const_1_28,8);
          consume(1);
          goto l1_42;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_25,64);
          reset(&buf_1);
          appendarray(&buf_1,const_1_37,48);
          consume(1);
          goto l1_33;
       }
       goto fail1;
l1_91: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_138;
          }
          appendarray(&buf_9,const_1_29,32);
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_69;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_27,32);
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_61;
       }
       goto fail1;
l1_92: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_139;
          }
          appendarray(&buf_11,const_1_28,8);
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_4,const_1_28,8);
          consume(1);
          goto l1_92;
       }
       goto fail1;
l1_93: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_11);
             appendarray(&buf_11,const_1_4,32);
             appendarray(&buf_10,const_1_1,8);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_4);
             appendarray(&buf_4,const_1_36,16);
             consume(2);
             goto l1_139;
          }
          reset(&buf_11);
          appendarray(&buf_11,const_1_26,40);
          appendarray(&buf_10,const_1_2,16);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_4);
          appendarray(&buf_4,const_1_38,24);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_27,32);
          consume(1);
          goto l1_85;
       }
       goto fail1;
l1_94: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_142;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_5,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_36,16);
          outputarray(const_1_28,8);
          consume(1);
          goto l1_45;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_25,64);
          reset(&buf_1);
          appendarray(&buf_1,const_1_37,48);
          consume(1);
          goto l1_34;
       }
       goto fail1;
l1_95: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_143;
          }
          appendarray(&buf_9,const_1_29,32);
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_72;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_27,32);
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_62;
       }
       goto fail1;
l1_96: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_144;
          }
          appendarray(&buf_11,const_1_28,8);
          appendarray(&buf_10,const_1_28,8);
          appendarray(&buf_9,const_1_28,8);
          appendarray(&buf_8,const_1_28,8);
          appendarray(&buf_4,const_1_28,8);
          consume(1);
          goto l1_96;
       }
       goto fail1;
l1_97: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             reset(&buf_11);
             appendarray(&buf_11,const_1_4,32);
             appendarray(&buf_10,const_1_1,8);
             appendarray(&buf_9,const_1_1,8);
             appendarray(&buf_8,const_1_1,8);
             reset(&buf_4);
             appendarray(&buf_4,const_1_36,16);
             consume(2);
             goto l1_144;
          }
          reset(&buf_11);
          appendarray(&buf_11,const_1_26,40);
          appendarray(&buf_10,const_1_2,16);
          appendarray(&buf_9,const_1_2,16);
          appendarray(&buf_8,const_1_2,16);
          reset(&buf_4);
          appendarray(&buf_4,const_1_38,24);
          consume(1);
          goto l1_96;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_10,const_1_39,8);
          appendarray(&buf_9,const_1_39,8);
          appendarray(&buf_8,const_1_39,8);
          appendarray(&buf_3,const_1_27,32);
          consume(1);
          goto l1_86;
       }
       goto fail1;
l1_98: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_147;
          }
          reset(&buf_8);
          appendarray(&buf_8,const_1_5,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_36,16);
          outputarray(const_1_28,8);
          consume(1);
          goto l1_48;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_25,64);
          reset(&buf_1);
          appendarray(&buf_1,const_1_37,48);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_99: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             consume(2);
             goto l1_148;
          }
          appendarray(&buf_9,const_1_29,32);
          appendarray(&buf_8,const_1_29,32);
          appendarray(&buf_2,const_1_28,8);
          consume(1);
          goto l1_75;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_9,const_1_27,32);
          appendarray(&buf_8,const_1_27,32);
          appendarray(&buf_2,const_1_27,32);
          consume(1);
          goto l1_63;
       }
       goto fail1;
l1_100: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_149;
           }
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_100;
        }
        goto fail1;
l1_101: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_11);
              appendarray(&buf_11,const_1_4,32);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_36,16);
              consume(2);
              goto l1_149;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_26,40);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_38,24);
           consume(1);
           goto l1_100;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_87;
        }
        goto fail1;
l1_102: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_151;
           }
           reset(&buf_8);
           appendarray(&buf_8,const_1_5,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_51;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_8);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_1);
           appendarray(&buf_1,const_1_37,48);
           consume(1);
           goto l1_36;
        }
        goto fail1;
l1_103: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_152;
           }
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_78;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_2,const_1_27,32);
           consume(1);
           goto l1_64;
        }
        goto fail1;
l1_104: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_153;
           }
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_104;
        }
        goto fail1;
l1_105: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_11);
              appendarray(&buf_11,const_1_4,32);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_36,16);
              consume(2);
              goto l1_153;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_26,40);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_38,24);
           consume(1);
           goto l1_104;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_88;
        }
        goto fail1;
l1_106: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_154;
           }
           reset(&buf_8);
           appendarray(&buf_8,const_1_5,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_54;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_8);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_1);
           appendarray(&buf_1,const_1_37,48);
           consume(1);
           goto l1_37;
        }
        goto fail1;
l1_107: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_155;
           }
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_81;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_2,const_1_27,32);
           consume(1);
           goto l1_65;
        }
        goto fail1;
l1_108: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              appendarray(&buf_10,const_1_4,32);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              appendarray(&buf_3,const_1_36,16);
              consume(2);
              goto l1_132;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           appendarray(&buf_10,const_1_26,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           appendarray(&buf_3,const_1_38,24);
           consume(1);
           goto l1_80;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_89;
        }
        goto fail1;
l1_109: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_156;
           }
           reset(&buf_8);
           appendarray(&buf_8,const_1_5,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_57;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_8);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_1);
           appendarray(&buf_1,const_1_37,48);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_110: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_3,32);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              consume(2);
              goto l1_133;
           }
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_83;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_2,const_1_27,32);
           consume(1);
           goto l1_66;
        }
        goto fail1;
l1_111: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_111;
           }
           reset(&buf_8);
           appendarray(&buf_8,const_1_5,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_59;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_8);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_1);
           appendarray(&buf_1,const_1_37,48);
           consume(1);
           goto l1_39;
        }
        goto fail1;
l1_112: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              appendarray(&buf_4,const_1_1,8);
              consume(2);
              goto l1_144;
           }
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           appendarray(&buf_4,const_1_2,16);
           consume(1);
           goto l1_96;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_39,8);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_113: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              appendarray(&buf_4,const_1_1,8);
              consume(2);
              goto l1_149;
           }
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           appendarray(&buf_4,const_1_2,16);
           consume(1);
           goto l1_100;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_39,8);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_114: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              appendarray(&buf_4,const_1_1,8);
              consume(2);
              goto l1_153;
           }
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           appendarray(&buf_4,const_1_2,16);
           consume(1);
           goto l1_104;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_39,8);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_115: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              appendarray(&buf_3,const_1_1,8);
              consume(2);
              goto l1_132;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           appendarray(&buf_3,const_1_2,16);
           consume(1);
           goto l1_80;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_39,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_116: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_159;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_69;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           consume(1);
           goto l1_61;
        }
        goto fail1;
l1_117: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_160;
           }
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_93;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_85;
        }
        goto fail1;
l1_118: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_161;
           }
           appendarray(&buf_12,const_1_28,8);
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_118;
        }
        goto fail1;
l1_119: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_12);
              appendarray(&buf_12,const_1_4,32);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_36,16);
              consume(2);
              goto l1_161;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,40);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_38,24);
           consume(1);
           goto l1_118;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_120: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_164;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_72;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           consume(1);
           goto l1_62;
        }
        goto fail1;
l1_121: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_165;
           }
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_97;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_86;
        }
        goto fail1;
l1_122: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_166;
           }
           appendarray(&buf_12,const_1_28,8);
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_122;
        }
        goto fail1;
l1_123: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_12);
              appendarray(&buf_12,const_1_4,32);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_36,16);
              consume(2);
              goto l1_166;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,40);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_38,24);
           consume(1);
           goto l1_122;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_124: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_168;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_75;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           consume(1);
           goto l1_63;
        }
        goto fail1;
l1_125: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_169;
           }
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_101;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_87;
        }
        goto fail1;
l1_126: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_170;
           }
           appendarray(&buf_12,const_1_28,8);
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_126;
        }
        goto fail1;
l1_127: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_12);
              appendarray(&buf_12,const_1_4,32);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_36,16);
              consume(2);
              goto l1_170;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,40);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_38,24);
           consume(1);
           goto l1_126;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_128: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_171;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_78;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           consume(1);
           goto l1_64;
        }
        goto fail1;
l1_129: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_172;
           }
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_105;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_88;
        }
        goto fail1;
l1_130: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              appendarray(&buf_11,const_1_4,32);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              appendarray(&buf_4,const_1_36,16);
              consume(2);
              goto l1_153;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           appendarray(&buf_11,const_1_26,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           appendarray(&buf_4,const_1_38,24);
           consume(1);
           goto l1_104;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_131: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_173;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_81;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           consume(1);
           goto l1_65;
        }
        goto fail1;
l1_132: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_3,32);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              consume(2);
              goto l1_155;
           }
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_108;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_3,const_1_27,32);
           consume(1);
           goto l1_89;
        }
        goto fail1;
l1_133: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              output(&buf_1);
              consume(2);
              goto l1_156;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_83;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           consume(1);
           goto l1_66;
        }
        goto fail1;
l1_134: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              appendarray(&buf_12,const_1_1,8);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              appendarray(&buf_5,const_1_1,8);
              consume(2);
              goto l1_166;
           }
           appendarray(&buf_12,const_1_2,16);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           appendarray(&buf_5,const_1_2,16);
           consume(1);
           goto l1_122;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_5,const_1_39,8);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_135: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              appendarray(&buf_12,const_1_1,8);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              appendarray(&buf_5,const_1_1,8);
              consume(2);
              goto l1_170;
           }
           appendarray(&buf_12,const_1_2,16);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           appendarray(&buf_5,const_1_2,16);
           consume(1);
           goto l1_126;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_5,const_1_39,8);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_136: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              appendarray(&buf_11,const_1_1,8);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              appendarray(&buf_4,const_1_1,8);
              consume(2);
              goto l1_153;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           concat(&buf_11,&buf_12);
           appendarray(&buf_11,const_1_2,16);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           concat(&buf_4,&buf_5);
           appendarray(&buf_4,const_1_2,16);
           consume(1);
           goto l1_104;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_5,const_1_39,8);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_137: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_175;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           reset(&buf_8);
           appendarray(&buf_8,const_1_7,88);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_69;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           reset(&buf_8);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_61;
        }
        goto fail1;
l1_138: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_176;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_93;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           consume(1);
           goto l1_85;
        }
        goto fail1;
l1_139: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_177;
           }
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_140: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_178;
           }
           appendarray(&buf_13,const_1_28,8);
           appendarray(&buf_12,const_1_28,8);
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_6,const_1_28,8);
           consume(1);
           goto l1_140;
        }
        goto fail1;
l1_141: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_13);
              appendarray(&buf_13,const_1_4,32);
              appendarray(&buf_12,const_1_1,8);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_6);
              appendarray(&buf_6,const_1_36,16);
              consume(2);
              goto l1_178;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,40);
           appendarray(&buf_12,const_1_2,16);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_38,24);
           consume(1);
           goto l1_140;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_5,const_1_27,32);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_142: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_180;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           reset(&buf_8);
           appendarray(&buf_8,const_1_7,88);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_72;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           reset(&buf_8);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_62;
        }
        goto fail1;
l1_143: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_181;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_97;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           consume(1);
           goto l1_86;
        }
        goto fail1;
l1_144: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_182;
           }
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_123;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_145: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_183;
           }
           appendarray(&buf_13,const_1_28,8);
           appendarray(&buf_12,const_1_28,8);
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_6,const_1_28,8);
           consume(1);
           goto l1_145;
        }
        goto fail1;
l1_146: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_13);
              appendarray(&buf_13,const_1_4,32);
              appendarray(&buf_12,const_1_1,8);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_6);
              appendarray(&buf_6,const_1_36,16);
              consume(2);
              goto l1_183;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,40);
           appendarray(&buf_12,const_1_2,16);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_38,24);
           consume(1);
           goto l1_145;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_5,const_1_27,32);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_147: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_184;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           reset(&buf_8);
           appendarray(&buf_8,const_1_7,88);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_75;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           reset(&buf_8);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_63;
        }
        goto fail1;
l1_148: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_185;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_101;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           consume(1);
           goto l1_87;
        }
        goto fail1;
l1_149: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_186;
           }
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_127;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_150: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              appendarray(&buf_11,const_1_1,8);
              reset(&buf_12);
              appendarray(&buf_12,const_1_4,32);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              appendarray(&buf_5,const_1_36,16);
              consume(2);
              goto l1_170;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           concat(&buf_11,&buf_12);
           appendarray(&buf_11,const_1_2,16);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           concat(&buf_4,&buf_5);
           reset(&buf_5);
           appendarray(&buf_5,const_1_38,24);
           consume(1);
           goto l1_126;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_5,const_1_27,32);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_151: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_187;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           reset(&buf_8);
           appendarray(&buf_8,const_1_7,88);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_78;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           reset(&buf_8);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_64;
        }
        goto fail1;
l1_152: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_188;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_105;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           consume(1);
           goto l1_88;
        }
        goto fail1;
l1_153: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_3,32);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              consume(2);
              goto l1_172;
           }
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_130;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_4,const_1_27,32);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_154: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_189;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           reset(&buf_8);
           appendarray(&buf_8,const_1_7,88);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_81;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           reset(&buf_8);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_65;
        }
        goto fail1;
l1_155: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              consume(2);
              goto l1_173;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_108;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           consume(1);
           goto l1_89;
        }
        goto fail1;
l1_156: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_8,96);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_156;
           }
           reset(&buf_9);
           appendarray(&buf_9,const_1_5,56);
           reset(&buf_8);
           appendarray(&buf_8,const_1_7,88);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_83;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_9);
           appendarray(&buf_9,const_1_25,64);
           reset(&buf_8);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_37,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_66;
        }
        goto fail1;
l1_157: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              appendarray(&buf_13,const_1_1,8);
              appendarray(&buf_12,const_1_1,8);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              appendarray(&buf_6,const_1_1,8);
              consume(2);
              goto l1_183;
           }
           appendarray(&buf_13,const_1_2,16);
           appendarray(&buf_12,const_1_2,16);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           appendarray(&buf_6,const_1_2,16);
           consume(1);
           goto l1_145;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_13,const_1_39,8);
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_6,const_1_39,8);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_158: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              appendarray(&buf_11,const_1_1,8);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_1,8);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              appendarray(&buf_5,const_1_1,8);
              consume(2);
              goto l1_170;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           concat(&buf_11,&buf_12);
           appendarray(&buf_11,const_1_2,16);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_2,16);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           concat(&buf_4,&buf_5);
           reset(&buf_5);
           concat(&buf_5,&buf_6);
           appendarray(&buf_5,const_1_2,16);
           consume(1);
           goto l1_126;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_13,const_1_39,8);
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_6,const_1_39,8);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_159: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_190;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_93;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_85;
        }
        goto fail1;
l1_160: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_191;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_161: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_192;
           }
           appendarray(&buf_12,const_1_29,32);
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_27,32);
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_5,const_1_27,32);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_162: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_193;
           }
           appendarray(&buf_14,const_1_28,8);
           appendarray(&buf_13,const_1_28,8);
           appendarray(&buf_12,const_1_28,8);
           appendarray(&buf_11,const_1_28,8);
           appendarray(&buf_10,const_1_28,8);
           appendarray(&buf_9,const_1_28,8);
           appendarray(&buf_8,const_1_28,8);
           appendarray(&buf_7,const_1_28,8);
           consume(1);
           goto l1_162;
        }
        goto fail1;
l1_163: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_14);
              appendarray(&buf_14,const_1_4,32);
              appendarray(&buf_13,const_1_1,8);
              appendarray(&buf_12,const_1_1,8);
              appendarray(&buf_11,const_1_1,8);
              appendarray(&buf_10,const_1_1,8);
              appendarray(&buf_9,const_1_1,8);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_7);
              appendarray(&buf_7,const_1_36,16);
              consume(2);
              goto l1_193;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_26,40);
           appendarray(&buf_13,const_1_2,16);
           appendarray(&buf_12,const_1_2,16);
           appendarray(&buf_11,const_1_2,16);
           appendarray(&buf_10,const_1_2,16);
           appendarray(&buf_9,const_1_2,16);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_7);
           appendarray(&buf_7,const_1_38,24);
           consume(1);
           goto l1_162;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_13,const_1_39,8);
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_6,const_1_27,32);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_164: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_194;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_97;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_86;
        }
        goto fail1;
l1_165: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_195;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_123;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_166: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_196;
           }
           appendarray(&buf_12,const_1_29,32);
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_27,32);
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_5,const_1_27,32);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_167: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              appendarray(&buf_11,const_1_1,8);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_1,8);
              reset(&buf_13);
              appendarray(&buf_13,const_1_4,32);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              reset(&buf_6);
              appendarray(&buf_6,const_1_36,16);
              consume(2);
              goto l1_183;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           concat(&buf_11,&buf_12);
           appendarray(&buf_11,const_1_2,16);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           concat(&buf_4,&buf_5);
           reset(&buf_5);
           concat(&buf_5,&buf_6);
           reset(&buf_6);
           appendarray(&buf_6,const_1_38,24);
           consume(1);
           goto l1_145;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_13,const_1_39,8);
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_6,const_1_27,32);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_168: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_197;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_101;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_87;
        }
        goto fail1;
l1_169: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_198;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_127;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_170: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_3,32);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              consume(2);
              goto l1_186;
           }
           appendarray(&buf_12,const_1_29,32);
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_150;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_12,const_1_27,32);
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_5,const_1_27,32);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_171: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_199;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_105;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_88;
        }
        goto fail1;
l1_172: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              consume(2);
              goto l1_188;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_130;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_173: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_8,96);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              output(&buf_1);
              consume(2);
              goto l1_189;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_108;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_89;
        }
        goto fail1;
l1_174: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              appendarray(&buf_11,const_1_1,8);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_1,8);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_1,8);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              reset(&buf_6);
              concat(&buf_6,&buf_7);
              appendarray(&buf_6,const_1_1,8);
              consume(2);
              goto l1_183;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           concat(&buf_11,&buf_12);
           appendarray(&buf_11,const_1_2,16);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_2,16);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           concat(&buf_4,&buf_5);
           reset(&buf_5);
           concat(&buf_5,&buf_6);
           reset(&buf_6);
           concat(&buf_6,&buf_7);
           appendarray(&buf_6,const_1_2,16);
           consume(1);
           goto l1_145;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_14,const_1_39,8);
           appendarray(&buf_13,const_1_39,8);
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_7,const_1_39,8);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_175: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_200;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           reset(&buf_8);
           appendarray(&buf_8,const_1_9,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_93;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           reset(&buf_8);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_85;
        }
        goto fail1;
l1_176: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_201;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_177: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_202;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           appendarray(&buf_11,const_1_30,64);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_178: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_203;
           }
           appendarray(&buf_13,const_1_29,32);
           appendarray(&buf_12,const_1_29,32);
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_6,const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_13,const_1_27,32);
           appendarray(&buf_12,const_1_27,32);
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_6,const_1_27,32);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_179: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              appendarray(&buf_8,const_1_1,8);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              appendarray(&buf_9,const_1_1,8);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              appendarray(&buf_10,const_1_1,8);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              appendarray(&buf_11,const_1_1,8);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_1,8);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_1,8);
              reset(&buf_14);
              appendarray(&buf_14,const_1_4,32);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              reset(&buf_6);
              concat(&buf_6,&buf_7);
              reset(&buf_7);
              appendarray(&buf_7,const_1_36,16);
              consume(2);
              goto l1_193;
           }
           reset(&buf_8);
           concat(&buf_8,&buf_9);
           appendarray(&buf_8,const_1_2,16);
           reset(&buf_9);
           concat(&buf_9,&buf_10);
           appendarray(&buf_9,const_1_2,16);
           reset(&buf_10);
           concat(&buf_10,&buf_11);
           appendarray(&buf_10,const_1_2,16);
           reset(&buf_11);
           concat(&buf_11,&buf_12);
           appendarray(&buf_11,const_1_2,16);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_2,16);
           reset(&buf_14);
           appendarray(&buf_14,const_1_26,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           reset(&buf_4);
           concat(&buf_4,&buf_5);
           reset(&buf_5);
           concat(&buf_5,&buf_6);
           reset(&buf_6);
           concat(&buf_6,&buf_7);
           reset(&buf_7);
           appendarray(&buf_7,const_1_38,24);
           consume(1);
           goto l1_162;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_14,const_1_39,8);
           appendarray(&buf_13,const_1_39,8);
           appendarray(&buf_12,const_1_39,8);
           appendarray(&buf_11,const_1_39,8);
           appendarray(&buf_10,const_1_39,8);
           appendarray(&buf_9,const_1_39,8);
           appendarray(&buf_8,const_1_39,8);
           appendarray(&buf_7,const_1_27,32);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_180: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_204;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           reset(&buf_8);
           appendarray(&buf_8,const_1_9,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_97;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           reset(&buf_8);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_86;
        }
        goto fail1;
l1_181: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_205;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_123;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_182: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_206;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           appendarray(&buf_11,const_1_30,64);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_183: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_3,32);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              consume(2);
              goto l1_196;
           }
           appendarray(&buf_13,const_1_29,32);
           appendarray(&buf_12,const_1_29,32);
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_6,const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_13,const_1_27,32);
           appendarray(&buf_12,const_1_27,32);
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_6,const_1_27,32);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_184: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_207;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           reset(&buf_8);
           appendarray(&buf_8,const_1_9,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_101;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           reset(&buf_8);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_87;
        }
        goto fail1;
l1_185: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_208;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_127;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_186: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              consume(2);
              goto l1_198;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           appendarray(&buf_11,const_1_30,64);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_150;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_187: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_209;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           reset(&buf_8);
           appendarray(&buf_8,const_1_9,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_105;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           reset(&buf_8);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_88;
        }
        goto fail1;
l1_188: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_8,96);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              consume(2);
              goto l1_199;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_130;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_189: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_10,128);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_189;
           }
           reset(&buf_10);
           appendarray(&buf_10,const_1_5,56);
           reset(&buf_9);
           appendarray(&buf_9,const_1_7,88);
           reset(&buf_8);
           appendarray(&buf_8,const_1_9,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_108;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_10);
           appendarray(&buf_10,const_1_25,64);
           reset(&buf_9);
           appendarray(&buf_9,const_1_24,96);
           reset(&buf_8);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_3);
           appendarray(&buf_3,const_1_37,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_89;
        }
        goto fail1;
l1_190: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_210;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_191: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_211;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           appendarray(&buf_10,const_1_31,96);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_192: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_212;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           appendarray(&buf_12,const_1_30,64);
           appendarray(&buf_11,const_1_30,64);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           appendarray(&buf_12,const_1_25,64);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_193: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_3,32);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              reset(&buf_6);
              concat(&buf_6,&buf_7);
              consume(2);
              goto l1_203;
           }
           appendarray(&buf_14,const_1_29,32);
           appendarray(&buf_13,const_1_29,32);
           appendarray(&buf_12,const_1_29,32);
           appendarray(&buf_11,const_1_29,32);
           appendarray(&buf_10,const_1_29,32);
           appendarray(&buf_9,const_1_29,32);
           appendarray(&buf_8,const_1_29,32);
           appendarray(&buf_7,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_14,const_1_27,32);
           appendarray(&buf_13,const_1_27,32);
           appendarray(&buf_12,const_1_27,32);
           appendarray(&buf_11,const_1_27,32);
           appendarray(&buf_10,const_1_27,32);
           appendarray(&buf_9,const_1_27,32);
           appendarray(&buf_8,const_1_27,32);
           appendarray(&buf_7,const_1_27,32);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_194: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_213;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_123;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_195: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_214;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           appendarray(&buf_10,const_1_31,96);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_196: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              consume(2);
              goto l1_206;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           appendarray(&buf_12,const_1_30,64);
           appendarray(&buf_11,const_1_30,64);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           appendarray(&buf_12,const_1_25,64);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_197: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_215;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_127;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_198: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_8,96);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              consume(2);
              goto l1_208;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           appendarray(&buf_10,const_1_31,96);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_150;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_199: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_10,128);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              output(&buf_1);
              consume(2);
              goto l1_209;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_130;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_200: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_216;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           reset(&buf_8);
           appendarray(&buf_8,const_1_11,152);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           reset(&buf_8);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_112;
        }
        goto fail1;
l1_201: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_217;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           appendarray(&buf_9,const_1_32,128);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_202: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_218;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           appendarray(&buf_11,const_1_31,96);
           appendarray(&buf_10,const_1_31,96);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           appendarray(&buf_11,const_1_24,96);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_203: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_6,64);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              consume(2);
              goto l1_212;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           appendarray(&buf_13,const_1_30,64);
           appendarray(&buf_12,const_1_30,64);
           appendarray(&buf_11,const_1_30,64);
           appendarray(&buf_10,const_1_30,64);
           appendarray(&buf_9,const_1_30,64);
           appendarray(&buf_8,const_1_30,64);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           appendarray(&buf_6,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           appendarray(&buf_13,const_1_25,64);
           appendarray(&buf_12,const_1_25,64);
           appendarray(&buf_11,const_1_25,64);
           appendarray(&buf_10,const_1_25,64);
           appendarray(&buf_9,const_1_25,64);
           appendarray(&buf_8,const_1_25,64);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_204: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_219;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           reset(&buf_8);
           appendarray(&buf_8,const_1_11,152);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_123;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           reset(&buf_8);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_205: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_220;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           appendarray(&buf_9,const_1_32,128);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_206: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_8,96);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              consume(2);
              goto l1_214;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           appendarray(&buf_11,const_1_31,96);
           appendarray(&buf_10,const_1_31,96);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           appendarray(&buf_11,const_1_24,96);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_207: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_221;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           reset(&buf_8);
           appendarray(&buf_8,const_1_11,152);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_127;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           reset(&buf_8);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_208: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_10,128);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              consume(2);
              goto l1_215;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           appendarray(&buf_9,const_1_32,128);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_150;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_209: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_12,160);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_209;
           }
           reset(&buf_11);
           appendarray(&buf_11,const_1_5,56);
           reset(&buf_10);
           appendarray(&buf_10,const_1_7,88);
           reset(&buf_9);
           appendarray(&buf_9,const_1_9,120);
           reset(&buf_8);
           appendarray(&buf_8,const_1_11,152);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_130;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_11);
           appendarray(&buf_11,const_1_25,64);
           reset(&buf_10);
           appendarray(&buf_10,const_1_24,96);
           reset(&buf_9);
           appendarray(&buf_9,const_1_23,128);
           reset(&buf_8);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_4);
           appendarray(&buf_4,const_1_37,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_210: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_222;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           reset(&buf_9);
           appendarray(&buf_9,const_1_11,152);
           appendarray(&buf_8,const_1_33,160);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           reset(&buf_9);
           appendarray(&buf_9,const_1_22,160);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_211: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_223;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           appendarray(&buf_10,const_1_32,128);
           appendarray(&buf_9,const_1_32,128);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           appendarray(&buf_10,const_1_23,128);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_212: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_8,96);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              reset(&buf_11);
              concat(&buf_11,&buf_12);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              consume(2);
              goto l1_218;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_7,88);
           appendarray(&buf_12,const_1_31,96);
           appendarray(&buf_11,const_1_31,96);
           appendarray(&buf_10,const_1_31,96);
           appendarray(&buf_9,const_1_31,96);
           appendarray(&buf_8,const_1_31,96);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           appendarray(&buf_5,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_24,96);
           appendarray(&buf_12,const_1_24,96);
           appendarray(&buf_11,const_1_24,96);
           appendarray(&buf_10,const_1_24,96);
           appendarray(&buf_9,const_1_24,96);
           appendarray(&buf_8,const_1_24,96);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_213: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_224;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           reset(&buf_9);
           appendarray(&buf_9,const_1_11,152);
           appendarray(&buf_8,const_1_33,160);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           reset(&buf_9);
           appendarray(&buf_9,const_1_22,160);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_214: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_10,128);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              consume(2);
              goto l1_220;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           appendarray(&buf_10,const_1_32,128);
           appendarray(&buf_9,const_1_32,128);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           appendarray(&buf_10,const_1_23,128);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_215: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_12,160);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              output(&buf_1);
              consume(2);
              goto l1_221;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           reset(&buf_9);
           appendarray(&buf_9,const_1_11,152);
           appendarray(&buf_8,const_1_33,160);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_150;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           reset(&buf_9);
           appendarray(&buf_9,const_1_22,160);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_216: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_225;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           reset(&buf_9);
           appendarray(&buf_9,const_1_11,152);
           reset(&buf_8);
           appendarray(&buf_8,const_1_13,184);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           reset(&buf_9);
           appendarray(&buf_9,const_1_22,160);
           reset(&buf_8);
           appendarray(&buf_8,const_1_21,192);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_134;
        }
        goto fail1;
l1_217: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_226;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           reset(&buf_10);
           appendarray(&buf_10,const_1_11,152);
           appendarray(&buf_9,const_1_33,160);
           appendarray(&buf_8,const_1_33,160);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           reset(&buf_10);
           appendarray(&buf_10,const_1_22,160);
           appendarray(&buf_9,const_1_22,160);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_218: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_10,128);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              reset(&buf_10);
              concat(&buf_10,&buf_11);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              consume(2);
              goto l1_223;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_7,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_9,120);
           appendarray(&buf_11,const_1_32,128);
           appendarray(&buf_10,const_1_32,128);
           appendarray(&buf_9,const_1_32,128);
           appendarray(&buf_8,const_1_32,128);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           appendarray(&buf_4,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_24,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,128);
           appendarray(&buf_11,const_1_23,128);
           appendarray(&buf_10,const_1_23,128);
           appendarray(&buf_9,const_1_23,128);
           appendarray(&buf_8,const_1_23,128);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_219: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_227;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           reset(&buf_9);
           appendarray(&buf_9,const_1_11,152);
           reset(&buf_8);
           appendarray(&buf_8,const_1_13,184);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           reset(&buf_9);
           appendarray(&buf_9,const_1_22,160);
           reset(&buf_8);
           appendarray(&buf_8,const_1_21,192);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_135;
        }
        goto fail1;
l1_220: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_12,160);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              consume(2);
              goto l1_224;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           reset(&buf_10);
           appendarray(&buf_10,const_1_11,152);
           appendarray(&buf_9,const_1_33,160);
           appendarray(&buf_8,const_1_33,160);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           reset(&buf_10);
           appendarray(&buf_10,const_1_22,160);
           appendarray(&buf_9,const_1_22,160);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_221: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_14,192);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_221;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_5,56);
           reset(&buf_11);
           appendarray(&buf_11,const_1_7,88);
           reset(&buf_10);
           appendarray(&buf_10,const_1_9,120);
           reset(&buf_9);
           appendarray(&buf_9,const_1_11,152);
           reset(&buf_8);
           appendarray(&buf_8,const_1_13,184);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_150;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_25,64);
           reset(&buf_11);
           appendarray(&buf_11,const_1_24,96);
           reset(&buf_10);
           appendarray(&buf_10,const_1_23,128);
           reset(&buf_9);
           appendarray(&buf_9,const_1_22,160);
           reset(&buf_8);
           appendarray(&buf_8,const_1_21,192);
           reset(&buf_5);
           appendarray(&buf_5,const_1_37,48);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_136;
        }
        goto fail1;
l1_222: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_228;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           reset(&buf_10);
           appendarray(&buf_10,const_1_11,152);
           reset(&buf_9);
           appendarray(&buf_9,const_1_13,184);
           appendarray(&buf_8,const_1_34,192);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           reset(&buf_10);
           appendarray(&buf_10,const_1_22,160);
           reset(&buf_9);
           appendarray(&buf_9,const_1_21,192);
           appendarray(&buf_8,const_1_21,192);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_223: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_12,160);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              reset(&buf_9);
              concat(&buf_9,&buf_10);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              consume(2);
              goto l1_226;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_7,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_9,120);
           reset(&buf_11);
           appendarray(&buf_11,const_1_11,152);
           appendarray(&buf_10,const_1_33,160);
           appendarray(&buf_9,const_1_33,160);
           appendarray(&buf_8,const_1_33,160);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           appendarray(&buf_3,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_24,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,128);
           reset(&buf_11);
           appendarray(&buf_11,const_1_22,160);
           appendarray(&buf_10,const_1_22,160);
           appendarray(&buf_9,const_1_22,160);
           appendarray(&buf_8,const_1_22,160);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_224: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_14,192);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              output(&buf_1);
              consume(2);
              goto l1_227;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           reset(&buf_10);
           appendarray(&buf_10,const_1_11,152);
           reset(&buf_9);
           appendarray(&buf_9,const_1_13,184);
           appendarray(&buf_8,const_1_34,192);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           reset(&buf_10);
           appendarray(&buf_10,const_1_22,160);
           reset(&buf_9);
           appendarray(&buf_9,const_1_21,192);
           appendarray(&buf_8,const_1_21,192);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_225: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              consume(2);
              goto l1_229;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           reset(&buf_10);
           appendarray(&buf_10,const_1_11,152);
           reset(&buf_9);
           appendarray(&buf_9,const_1_13,184);
           reset(&buf_8);
           appendarray(&buf_8,const_1_15,216);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           reset(&buf_10);
           appendarray(&buf_10,const_1_22,160);
           reset(&buf_9);
           appendarray(&buf_9,const_1_21,192);
           reset(&buf_8);
           appendarray(&buf_8,const_1_20,224);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_226: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_14,192);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              reset(&buf_8);
              concat(&buf_8,&buf_9);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              consume(2);
              goto l1_228;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_7,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_9,120);
           reset(&buf_11);
           appendarray(&buf_11,const_1_11,152);
           reset(&buf_10);
           appendarray(&buf_10,const_1_13,184);
           appendarray(&buf_9,const_1_34,192);
           appendarray(&buf_8,const_1_34,192);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           appendarray(&buf_2,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_24,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,128);
           reset(&buf_11);
           appendarray(&buf_11,const_1_22,160);
           reset(&buf_10);
           appendarray(&buf_10,const_1_21,192);
           appendarray(&buf_9,const_1_21,192);
           appendarray(&buf_8,const_1_21,192);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_227: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_16,224);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_227;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_5,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_7,88);
           reset(&buf_11);
           appendarray(&buf_11,const_1_9,120);
           reset(&buf_10);
           appendarray(&buf_10,const_1_11,152);
           reset(&buf_9);
           appendarray(&buf_9,const_1_13,184);
           reset(&buf_8);
           appendarray(&buf_8,const_1_15,216);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_25,64);
           reset(&buf_12);
           appendarray(&buf_12,const_1_24,96);
           reset(&buf_11);
           appendarray(&buf_11,const_1_23,128);
           reset(&buf_10);
           appendarray(&buf_10,const_1_22,160);
           reset(&buf_9);
           appendarray(&buf_9,const_1_21,192);
           reset(&buf_8);
           appendarray(&buf_8,const_1_20,224);
           reset(&buf_6);
           appendarray(&buf_6,const_1_37,48);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_158;
        }
        goto fail1;
l1_228: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_8);
           outputarray(const_1_16,224);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              output(&buf_1);
              consume(2);
              goto l1_229;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_7,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_9,120);
           reset(&buf_11);
           appendarray(&buf_11,const_1_11,152);
           reset(&buf_10);
           appendarray(&buf_10,const_1_13,184);
           reset(&buf_9);
           appendarray(&buf_9,const_1_15,216);
           appendarray(&buf_8,const_1_35,224);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           appendarray(&buf_1,const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_24,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,128);
           reset(&buf_11);
           appendarray(&buf_11,const_1_22,160);
           reset(&buf_10);
           appendarray(&buf_10,const_1_21,192);
           reset(&buf_9);
           appendarray(&buf_9,const_1_20,224);
           appendarray(&buf_8,const_1_20,224);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           consume(1);
           goto l1_174;
        }
        goto fail1;
l1_229: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_18,256);
           consume(1);
           goto l1_17;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              outputarray(const_1_36,16);
              consume(2);
              goto l1_229;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_5,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_7,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_9,120);
           reset(&buf_11);
           appendarray(&buf_11,const_1_11,152);
           reset(&buf_10);
           appendarray(&buf_10,const_1_13,184);
           reset(&buf_9);
           appendarray(&buf_9,const_1_15,216);
           reset(&buf_8);
           appendarray(&buf_8,const_1_17,248);
           reset(&buf_7);
           appendarray(&buf_7,const_1_36,16);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           outputarray(const_1_28,8);
           consume(1);
           goto l1_179;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_25,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_24,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,128);
           reset(&buf_11);
           appendarray(&buf_11,const_1_22,160);
           reset(&buf_10);
           appendarray(&buf_10,const_1_21,192);
           reset(&buf_9);
           appendarray(&buf_9,const_1_20,224);
           reset(&buf_8);
           appendarray(&buf_8,const_1_19,256);
           reset(&buf_7);
           appendarray(&buf_7,const_1_37,48);
           reset(&buf_6);
           appendarray(&buf_6,const_1_36,16);
           reset(&buf_5);
           appendarray(&buf_5,const_1_36,16);
           reset(&buf_4);
           appendarray(&buf_4,const_1_36,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_36,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_36,16);
           reset(&buf_1);
           appendarray(&buf_1,const_1_36,16);
           consume(1);
           goto l1_174;
        }
        goto fail1;
  accept1:
    return;
  fail1:
    fprintf(stderr, "Match error at input symbol %zu!\n", count);
    exit(1);
}

void match(int phase)
{
  switch(phase) {
    case 1: match1(); break;
    default:
      fprintf(stderr, "Invalid phase: %d given\n", phase);
      exit(1);
  }
}
