
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
buffer_t buf_15;
buffer_t buf_16;
buffer_t buf_17;
buffer_t buf_18;
buffer_t buf_19;
buffer_t buf_20;
buffer_t buf_21;
buffer_t buf_22;
// \xa
const buffer_unit_t const_1_0[1] = {0xa};
// .
const buffer_unit_t const_1_1[1] = {0x2e};
// .a
const buffer_unit_t const_1_2[2] = {0x2e,0x61};
// .a.a
const buffer_unit_t const_1_3[4] = {0x2e,0x61,0x2e,0x61};
// .a.aa
const buffer_unit_t const_1_4[5] = {0x2e,0x61,0x2e,0x61,0x61};
// .aaaa
const buffer_unit_t const_1_5[5] = {0x2e,0x61,0x61,0x61,0x61};
// .aaaa\xa
const buffer_unit_t const_1_6[6] = {0x2e,0x61,0x61,0x61,0x61,0xa};
// .aaaa.
const buffer_unit_t const_1_7[6] = {0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa..a
const buffer_unit_t const_1_8[8] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa..aa
const buffer_unit_t const_1_9[9] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa..aaaa
const buffer_unit_t const_1_10[11] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa\xa
const buffer_unit_t const_1_11[12] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0xa};
// .aaaa..aaaa.
const buffer_unit_t const_1_12[12] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa..aaaa..a
const buffer_unit_t const_1_13[14] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa..aaaa..aa
const buffer_unit_t const_1_14[15] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa..aaaa..aaaa
const buffer_unit_t const_1_15[17] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa..aaaa\xa
const buffer_unit_t const_1_16[18] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0xa};
// .aaaa..aaaa..aaaa.
const buffer_unit_t const_1_17[18] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa..aaaa..aaaa..a
const buffer_unit_t const_1_18[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa..aaaa..aaaa..aa
const buffer_unit_t const_1_19[21] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa..aaaa..aaaa..aaaa
const buffer_unit_t const_1_20[23] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa..aaaa..aaaa\xa
const buffer_unit_t const_1_21[24] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0xa};
// .aaaa..aaaa..aaaa..aaaab
const buffer_unit_t const_1_22[24] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa..aaaa..aaaa.a
const buffer_unit_t const_1_23[19] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa..aaaa..aaaa.a.a
const buffer_unit_t const_1_24[21] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa..aaaa..aaaa.a.aa
const buffer_unit_t const_1_25[22] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// .aaaa..aaaa..aaaab
const buffer_unit_t const_1_26[18] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa..aaaa.a
const buffer_unit_t const_1_27[13] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa..aaaa.a.a
const buffer_unit_t const_1_28[15] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa..aaaa.a.aa
const buffer_unit_t const_1_29[16] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// .aaaa..aaaa.a.aaaa
const buffer_unit_t const_1_30[18] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa.a.aaaa..a
const buffer_unit_t const_1_31[21] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa..aaaa.a.aaaa..aa
const buffer_unit_t const_1_32[22] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa..aaaa.a.aaaa..aaaa
const buffer_unit_t const_1_33[24] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa.aa.aaaa
const buffer_unit_t const_1_34[19] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa.aa.aaaa.
const buffer_unit_t const_1_35[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa..aaaa.aa.aaaa..aaaa
const buffer_unit_t const_1_36[25] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa..aaaa.aa.aaaa.a
const buffer_unit_t const_1_37[21] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa..aaaa.aa.aaaa.a.a
const buffer_unit_t const_1_38[23] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa..aaaa.aa.aaaab
const buffer_unit_t const_1_39[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa..aaaab
const buffer_unit_t const_1_40[12] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa.a
const buffer_unit_t const_1_41[7] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa.a.a
const buffer_unit_t const_1_42[9] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa.a.aa
const buffer_unit_t const_1_43[10] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// .aaaa.a.aaaa
const buffer_unit_t const_1_44[12] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.a.aaaa.
const buffer_unit_t const_1_45[13] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa.a.aaaa..a
const buffer_unit_t const_1_46[15] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa.a.aaaa..aa
const buffer_unit_t const_1_47[16] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa.a.aaaa..aaaa
const buffer_unit_t const_1_48[18] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.a.aaaa..aaaa.
const buffer_unit_t const_1_49[19] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa.a.aaaa..aaaa..a
const buffer_unit_t const_1_50[21] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa.a.aaaa..aaaa..aa
const buffer_unit_t const_1_51[22] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa.a.aaaa..aaaa..aaaa
const buffer_unit_t const_1_52[24] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.a.aaaa..aaaa.a
const buffer_unit_t const_1_53[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa.a.aaaa..aaaa.a.a
const buffer_unit_t const_1_54[22] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa.a.aaaa..aaaa.a.aa
const buffer_unit_t const_1_55[23] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// .aaaa.a.aaaa..aaaab
const buffer_unit_t const_1_56[19] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa.a.aaaa.a
const buffer_unit_t const_1_57[14] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa.a.aaaa.a.a
const buffer_unit_t const_1_58[16] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa.a.aaaa.a.aa
const buffer_unit_t const_1_59[17] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// .aaaa.a.aaaa.a.aaaa
const buffer_unit_t const_1_60[19] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.a.aaaa.a.aaaa..a
const buffer_unit_t const_1_61[22] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa.a.aaaa.a.aaaa..aa
const buffer_unit_t const_1_62[23] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// .aaaa.a.aaaab
const buffer_unit_t const_1_63[13] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa.aa.aaaa
const buffer_unit_t const_1_64[13] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.aa.aaaa.
const buffer_unit_t const_1_65[14] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa.aa.aaaa..aaaa
const buffer_unit_t const_1_66[19] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.aa.aaaa..aaaa.
const buffer_unit_t const_1_67[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e};
// .aaaa.aa.aaaa..aaaa..aaaa
const buffer_unit_t const_1_68[25] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.aa.aaaa..aaaa.a
const buffer_unit_t const_1_69[21] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa.aa.aaaa..aaaa.a.a
const buffer_unit_t const_1_70[23] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa.aa.aaaa..aaaab
const buffer_unit_t const_1_71[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaa.aa.aaaa.a
const buffer_unit_t const_1_72[15] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// .aaaa.aa.aaaa.a.a
const buffer_unit_t const_1_73[17] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// .aaaa.aa.aaaa.a.aaaa
const buffer_unit_t const_1_74[20] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61};
// .aaaa.aa.aaaa.a.aaaa..a
const buffer_unit_t const_1_75[23] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// .aaaa.aa.aaaab
const buffer_unit_t const_1_76[14] = {0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// .aaaab
const buffer_unit_t const_1_77[6] = {0x2e,0x61,0x61,0x61,0x61,0x62};
// a
const buffer_unit_t const_1_78[1] = {0x61};
// a.aaaa
const buffer_unit_t const_1_79[6] = {0x61,0x2e,0x61,0x61,0x61,0x61};
// a.aaaa.
const buffer_unit_t const_1_80[7] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// a.aaaa..a
const buffer_unit_t const_1_81[9] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// a.aaaa..aa
const buffer_unit_t const_1_82[10] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aaaa..aaaa
const buffer_unit_t const_1_83[12] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// a.aaaa..aaaa..a
const buffer_unit_t const_1_84[15] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// a.aaaa..aaaa..aaaa
const buffer_unit_t const_1_85[18] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// a.aaaa..aaaa.a
const buffer_unit_t const_1_86[14] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// a.aaaa..aaaa.a.aa
const buffer_unit_t const_1_87[17] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// a.aaaa..aaaab
const buffer_unit_t const_1_88[13] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// a.aaaa.a
const buffer_unit_t const_1_89[8] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// a.aaaa.a.a
const buffer_unit_t const_1_90[10] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// a.aaaa.a.aa
const buffer_unit_t const_1_91[11] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// a.aaaa.a.aaaa
const buffer_unit_t const_1_92[13] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61};
// a.aaaa.a.aaaa..a
const buffer_unit_t const_1_93[16] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// a.aaaa.a.aaaa..aa
const buffer_unit_t const_1_94[17] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61};
// a.aaaa.a.aaaa..aaaa
const buffer_unit_t const_1_95[19] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// a.aaaa.aa.aaaa.
const buffer_unit_t const_1_96[15] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// a.aaaa.aa.aaaa.a
const buffer_unit_t const_1_97[16] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// a.aaaa.aa.aaaa.a.a
const buffer_unit_t const_1_98[18] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// a.aaaa.aa.aaaab
const buffer_unit_t const_1_99[15] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// a.aaaab
const buffer_unit_t const_1_100[7] = {0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// aa
const buffer_unit_t const_1_101[2] = {0x61,0x61};
// aa..a
const buffer_unit_t const_1_102[5] = {0x61,0x61,0x2e,0x2e,0x61};
// aa..aa
const buffer_unit_t const_1_103[6] = {0x61,0x61,0x2e,0x2e,0x61,0x61};
// aa.aaaa
const buffer_unit_t const_1_104[7] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61};
// aa.aaaa.
const buffer_unit_t const_1_105[8] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// aa.aaaa..aaaa
const buffer_unit_t const_1_106[13] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// aa.aaaa..aaaa.
const buffer_unit_t const_1_107[14] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e};
// aa.aaaa..aaaa..aaaa
const buffer_unit_t const_1_108[19] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// aa.aaaa..aaaa.a
const buffer_unit_t const_1_109[15] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// aa.aaaa..aaaa.a.a
const buffer_unit_t const_1_110[17] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// aa.aaaa..aaaab
const buffer_unit_t const_1_111[14] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x62};
// aa.aaaa.a
const buffer_unit_t const_1_112[9] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// aa.aaaa.a.a
const buffer_unit_t const_1_113[11] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// aa.aaaa.a.aaaa
const buffer_unit_t const_1_114[14] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61};
// aa.aaaa.a.aaaa.
const buffer_unit_t const_1_115[15] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e};
// aa.aaaa.a.aaaa..a
const buffer_unit_t const_1_116[17] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61};
// aa.aaaa.a.aaaa.a
const buffer_unit_t const_1_117[16] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61};
// aa.aaaa.a.aaaa.a.a
const buffer_unit_t const_1_118[18] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61};
// aa.aaaa.a.aaaa.a.aa
const buffer_unit_t const_1_119[19] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61};
// aa.aaaa.a.aaaab
const buffer_unit_t const_1_120[15] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// aa.aaaab
const buffer_unit_t const_1_121[8] = {0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// aaa
const buffer_unit_t const_1_122[3] = {0x61,0x61,0x61};
// aaa..a
const buffer_unit_t const_1_123[6] = {0x61,0x61,0x61,0x2e,0x2e,0x61};
// aaa.aaaa
const buffer_unit_t const_1_124[8] = {0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61};
// aaa.aaaa..aaaa
const buffer_unit_t const_1_125[14] = {0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// aaa.aaaa..aaaa..aaaa
const buffer_unit_t const_1_126[20] = {0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61,0x2e,0x2e,0x61,0x61,0x61,0x61};
// aaa.aaaab
const buffer_unit_t const_1_127[9] = {0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// aaaa
const buffer_unit_t const_1_128[4] = {0x61,0x61,0x61,0x61};
// aaaa.aaaab
const buffer_unit_t const_1_129[10] = {0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// aaaaa
const buffer_unit_t const_1_130[5] = {0x61,0x61,0x61,0x61,0x61};
// aaaaa.aaaab
const buffer_unit_t const_1_131[11] = {0x61,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// aaaaaa
const buffer_unit_t const_1_132[6] = {0x61,0x61,0x61,0x61,0x61,0x61};
// aaaaaa.aaaab
const buffer_unit_t const_1_133[12] = {0x61,0x61,0x61,0x61,0x61,0x61,0x2e,0x61,0x61,0x61,0x61,0x62};
// b
const buffer_unit_t const_1_134[1] = {0x62};
void printCompilationInfo()
{
  fprintf(stdout, "No object file generated!\nOptions:\nSST optimization level:  3\nWord size:               UInt8T\nIdentity tables removed: False\n\nSource file: ../../../benchmarks/submatch_dfa_aot/src/kleenex/cat4_4.kex\nSource md5:  d22b112582db7a72c60d0b40e104788f\nSST states:  173\n");
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
init_buffer(&buf_15);
init_buffer(&buf_16);
init_buffer(&buf_17);
init_buffer(&buf_18);
init_buffer(&buf_19);
init_buffer(&buf_20);
init_buffer(&buf_21);
init_buffer(&buf_22);
}
void match1()
{
  int i = 0;
goto l1_0;
l1_0: if (!readnext(1, 4))
      {
         goto accept1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            consume(4);
            goto l1_36;
         }
         outputarray(const_1_78,8);
         consume(1);
         goto l1_1;
      }
      goto fail1;
l1_1: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            consume(4);
            goto l1_36;
         }
         outputarray(const_1_78,8);
         consume(1);
         goto l1_1;
      }
      goto fail1;
l1_2: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            consume(4);
            goto l1_40;
         }
         outputarray(const_1_78,8);
         consume(1);
         goto l1_2;
      }
      goto fail1;
l1_3: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            consume(4);
            goto l1_43;
         }
         outputarray(const_1_78,8);
         consume(1);
         goto l1_3;
      }
      goto fail1;
l1_4: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            consume(4);
            goto l1_45;
         }
         outputarray(const_1_78,8);
         consume(1);
         goto l1_4;
      }
      goto fail1;
l1_5: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            outputarray(const_1_1,8);
            consume(4);
            goto l1_40;
         }
         outputarray(const_1_2,16);
         consume(1);
         goto l1_2;
      }
      if (((avail >= 1) && ((next[0] == 'b') && 1)))
      {
         outputarray(const_1_134,8);
         consume(1);
         goto l1_5;
      }
      goto fail1;
l1_6: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            outputarray(const_1_1,8);
            consume(4);
            goto l1_43;
         }
         outputarray(const_1_2,16);
         consume(1);
         goto l1_3;
      }
      if (((avail >= 1) && ((next[0] == 'b') && 1)))
      {
         outputarray(const_1_134,8);
         consume(1);
         goto l1_6;
      }
      goto fail1;
l1_7: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            outputarray(const_1_1,8);
            consume(4);
            goto l1_45;
         }
         outputarray(const_1_2,16);
         consume(1);
         goto l1_4;
      }
      if (((avail >= 1) && ((next[0] == 'b') && 1)))
      {
         outputarray(const_1_134,8);
         consume(1);
         goto l1_7;
      }
      goto fail1;
l1_8: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 10) && 1)))
      {
         outputarray(const_1_0,8);
         consume(1);
         goto l1_9;
      }
      if (((avail >= 1) && ((next[0] == 'b') && 1)))
      {
         outputarray(const_1_134,8);
         consume(1);
         goto l1_8;
      }
      goto fail1;
l1_9: if (!readnext(1, 4))
      {
         goto accept1;
      }
      if (((avail >= 1) && ((next[0] == 'a') && 1)))
      {
         if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
         {
            consume(4);
            goto l1_36;
         }
         outputarray(const_1_78,8);
         consume(1);
         goto l1_1;
      }
      goto fail1;
l1_10: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             consume(4);
             goto l1_46;
          }
          appendarray(&buf_12,const_1_78,8);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_10;
       }
       goto fail1;
l1_11: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             appendarray(&buf_12,const_1_7,48);
             reset(&buf_1);
             appendarray(&buf_1,const_1_128,32);
             consume(4);
             goto l1_46;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_10;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_5;
       }
       goto fail1;
l1_12: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             consume(4);
             goto l1_52;
          }
          appendarray(&buf_12,const_1_78,8);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_12;
       }
       goto fail1;
l1_13: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             appendarray(&buf_12,const_1_7,48);
             reset(&buf_1);
             appendarray(&buf_1,const_1_128,32);
             consume(4);
             goto l1_52;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_6;
       }
       goto fail1;
l1_14: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             consume(4);
             goto l1_58;
          }
          appendarray(&buf_12,const_1_78,8);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_14;
       }
       goto fail1;
l1_15: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             appendarray(&buf_12,const_1_7,48);
             reset(&buf_1);
             appendarray(&buf_1,const_1_128,32);
             consume(4);
             goto l1_58;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_7;
       }
       goto fail1;
l1_16: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             outputarray(const_1_128,32);
             consume(4);
             goto l1_45;
          }
          outputarray(const_1_130,40);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_8;
       }
       goto fail1;
l1_17: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             appendarray(&buf_12,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(4);
             goto l1_52;
          }
          appendarray(&buf_12,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_134,8);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_18: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             appendarray(&buf_12,const_1_1,8);
             appendarray(&buf_1,const_1_1,8);
             consume(4);
             goto l1_58;
          }
          appendarray(&buf_12,const_1_2,16);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_134,8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_19: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             output(&buf_1);
             outputarray(const_1_1,8);
             consume(4);
             goto l1_45;
          }
          output(&buf_1);
          outputarray(const_1_2,16);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_134,8);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_20: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             consume(4);
             goto l1_61;
          }
          appendarray(&buf_13,const_1_78,8);
          appendarray(&buf_12,const_1_78,8);
          appendarray(&buf_2,const_1_78,8);
          consume(1);
          goto l1_20;
       }
       goto fail1;
l1_21: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_13);
             appendarray(&buf_13,const_1_7,48);
             appendarray(&buf_12,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_128,32);
             consume(4);
             goto l1_61;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_22: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             consume(4);
             goto l1_69;
          }
          appendarray(&buf_13,const_1_78,8);
          appendarray(&buf_12,const_1_78,8);
          appendarray(&buf_2,const_1_78,8);
          consume(1);
          goto l1_22;
       }
       goto fail1;
l1_23: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_13);
             appendarray(&buf_13,const_1_7,48);
             appendarray(&buf_12,const_1_1,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_128,32);
             consume(4);
             goto l1_69;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_24: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             appendarray(&buf_12,const_1_7,48);
             output(&buf_1);
             reset(&buf_1);
             appendarray(&buf_1,const_1_128,32);
             consume(4);
             goto l1_58;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_25: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                outputarray(const_1_128,32);
                consume(4);
                goto l1_45;
             }
             outputarray(const_1_122,24);
             consume(3);
             goto l1_34;
          }
          outputarray(const_1_130,40);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_8;
       }
       goto fail1;
l1_26: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             appendarray(&buf_13,const_1_1,8);
             appendarray(&buf_12,const_1_1,8);
             appendarray(&buf_2,const_1_1,8);
             consume(4);
             goto l1_69;
          }
          appendarray(&buf_13,const_1_2,16);
          appendarray(&buf_12,const_1_2,16);
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_2,const_1_134,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_27: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_1,8);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             appendarray(&buf_1,const_1_1,8);
             consume(4);
             goto l1_58;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_2,const_1_134,8);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_28: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                consume(4);
                goto l1_76;
             }
             consume(3);
             goto l1_48;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_10;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_100,56);
          consume(1);
          goto l1_5;
       }
       goto fail1;
l1_29: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             consume(4);
             goto l1_77;
          }
          appendarray(&buf_14,const_1_78,8);
          appendarray(&buf_13,const_1_78,8);
          appendarray(&buf_12,const_1_78,8);
          appendarray(&buf_3,const_1_78,8);
          consume(1);
          goto l1_29;
       }
       goto fail1;
l1_30: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_14);
             appendarray(&buf_14,const_1_7,48);
             appendarray(&buf_13,const_1_1,8);
             appendarray(&buf_12,const_1_1,8);
             reset(&buf_3);
             appendarray(&buf_3,const_1_128,32);
             consume(4);
             goto l1_77;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          appendarray(&buf_13,const_1_2,16);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_31: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                consume(4);
                goto l1_87;
             }
             consume(3);
             goto l1_54;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_100,56);
          consume(1);
          goto l1_6;
       }
       goto fail1;
l1_32: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_1,8);
             reset(&buf_13);
             appendarray(&buf_13,const_1_7,48);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             appendarray(&buf_2,const_1_128,32);
             consume(4);
             goto l1_69;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_33: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                outputarray(const_1_78,8);
                consume(4);
                goto l1_74;
             }
             reset(&buf_12);
             appendarray(&buf_12,const_1_10,88);
             reset(&buf_1);
             appendarray(&buf_1,const_1_78,8);
             consume(3);
             goto l1_60;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_100,56);
          consume(1);
          goto l1_7;
       }
       goto fail1;
l1_34: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   outputarray(const_1_128,32);
                   consume(4);
                   goto l1_45;
                }
                outputarray(const_1_122,24);
                consume(3);
                goto l1_34;
             }
             outputarray(const_1_101,16);
             consume(2);
             goto l1_25;
          }
          outputarray(const_1_130,40);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_8;
       }
       goto fail1;
l1_35: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
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
             appendarray(&buf_2,const_1_1,8);
             consume(4);
             goto l1_69;
          }
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
          appendarray(&buf_2,const_1_2,16);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_14,const_1_134,8);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_3,const_1_134,8);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_36: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_93;
                }
                outputarray(const_1_78,8);
                consume(3);
                goto l1_47;
             }
             outputarray(const_1_78,8);
             consume(2);
             goto l1_28;
          }
          outputarray(const_1_78,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_5;
       }
       goto fail1;
l1_37: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                consume(4);
                goto l1_94;
             }
             consume(3);
             goto l1_63;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_38: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                consume(4);
                goto l1_95;
             }
             consume(3);
             goto l1_64;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          appendarray(&buf_12,const_1_89,64);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_100,56);
          appendarray(&buf_1,const_1_100,56);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_39: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "aaa",3) && 1)))
          {
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_1,8);
             reset(&buf_13);
             concat(&buf_13,&buf_14);
             appendarray(&buf_13,const_1_1,8);
             reset(&buf_14);
             appendarray(&buf_14,const_1_7,48);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             concat(&buf_2,&buf_3);
             reset(&buf_3);
             appendarray(&buf_3,const_1_128,32);
             consume(4);
             goto l1_77;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_2,16);
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_14,const_1_134,8);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_3,const_1_77,48);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_40: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_106;
                }
                outputarray(const_1_78,8);
                consume(3);
                goto l1_53;
             }
             outputarray(const_1_78,8);
             consume(2);
             goto l1_31;
          }
          outputarray(const_1_78,8);
          consume(1);
          goto l1_13;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_6;
       }
       goto fail1;
l1_41: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_13);
                appendarray(&buf_13,const_1_46,120);
                reset(&buf_12);
                appendarray(&buf_12,const_1_12,96);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                reset(&buf_1);
                appendarray(&buf_1,const_1_101,16);
                consume(4);
                goto l1_107;
             }
             consume(3);
             goto l1_71;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_42: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_13);
                appendarray(&buf_13,const_1_13,112);
                appendarray(&buf_12,const_1_80,56);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(4);
                goto l1_107;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_9);
             appendarray(&buf_9,const_1_89,64);
             consume(3);
             goto l1_72;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          appendarray(&buf_12,const_1_89,64);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_100,56);
          appendarray(&buf_1,const_1_100,56);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_43: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_112;
                }
                outputarray(const_1_78,8);
                consume(3);
                goto l1_59;
             }
             outputarray(const_1_78,8);
             consume(2);
             goto l1_33;
          }
          outputarray(const_1_78,8);
          consume(1);
          goto l1_15;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_7;
       }
       goto fail1;
l1_44: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                output(&buf_1);
                output(&buf_2);
                consume(4);
                goto l1_74;
             }
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_122,24);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             consume(3);
             goto l1_60;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          output(&buf_1);
          output(&buf_2);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_45: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   outputarray(const_1_128,32);
                   consume(4);
                   goto l1_45;
                }
                outputarray(const_1_122,24);
                consume(3);
                goto l1_34;
             }
             outputarray(const_1_101,16);
             consume(2);
             goto l1_25;
          }
          outputarray(const_1_78,8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_77,48);
          consume(1);
          goto l1_8;
       }
       goto fail1;
l1_46: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_113;
                }
                appendarray(&buf_12,const_1_78,8);
                appendarray(&buf_1,const_1_78,8);
                consume(3);
                goto l1_62;
             }
             appendarray(&buf_12,const_1_78,8);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_38;
          }
          appendarray(&buf_12,const_1_79,48);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_77,48);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_47: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_114;
                }
                consume(3);
                goto l1_78;
             }
             consume(2);
             goto l1_37;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_10;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_121,64);
          consume(1);
          goto l1_5;
       }
       goto fail1;
l1_48: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_115;
                }
                consume(3);
                goto l1_79;
             }
             reset(&buf_14);
             appendarray(&buf_14,const_1_42,72);
             reset(&buf_13);
             appendarray(&buf_13,const_1_44,96);
             reset(&buf_12);
             appendarray(&buf_12,const_1_28,120);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             consume(2);
             goto l1_49;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_49: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                appendarray(&buf_14,const_1_123,48);
                appendarray(&buf_13,const_1_1,8);
                appendarray(&buf_12,const_1_123,48);
                consume(4);
                goto l1_116;
             }
             appendarray(&buf_14,const_1_122,24);
             appendarray(&buf_13,const_1_2,16);
             appendarray(&buf_12,const_1_122,24);
             consume(3);
             goto l1_81;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_122,24);
          concat(&buf_1,&buf_3);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_122,24);
          concat(&buf_1,&buf_3);
          appendarray(&buf_1,const_1_77,48);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_50: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_20);
                appendarray(&buf_20,const_1_12,96);
                reset(&buf_9);
                appendarray(&buf_9,const_1_116,136);
                consume(4);
                goto l1_117;
             }
             consume(3);
             goto l1_82;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_13);
          appendarray(&buf_13,const_1_27,104);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_51: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                appendarray(&buf_12,const_1_80,56);
                consume(4);
                goto l1_118;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_9);
             appendarray(&buf_9,const_1_89,64);
             consume(3);
             goto l1_83;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          appendarray(&buf_13,const_1_89,64);
          appendarray(&buf_12,const_1_89,64);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          appendarray(&buf_2,const_1_78,8);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_100,56);
          appendarray(&buf_12,const_1_100,56);
          appendarray(&buf_2,const_1_100,56);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_52: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_129;
                }
                appendarray(&buf_12,const_1_78,8);
                appendarray(&buf_1,const_1_78,8);
                consume(3);
                goto l1_70;
             }
             appendarray(&buf_12,const_1_78,8);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_42;
          }
          appendarray(&buf_12,const_1_79,48);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_23;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_77,48);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_53: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_130;
                }
                consume(3);
                goto l1_88;
             }
             consume(2);
             goto l1_41;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_121,64);
          consume(1);
          goto l1_6;
       }
       goto fail1;
l1_54: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_12,96);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_78,8);
                   consume(4);
                   goto l1_131;
                }
                consume(3);
                goto l1_89;
             }
             reset(&buf_14);
             appendarray(&buf_14,const_1_42,72);
             reset(&buf_13);
             appendarray(&buf_13,const_1_44,96);
             reset(&buf_12);
             appendarray(&buf_12,const_1_28,120);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             consume(2);
             goto l1_55;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_55: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_1,8);
                reset(&buf_13);
                concat(&buf_13,&buf_14);
                appendarray(&buf_13,const_1_123,48);
                reset(&buf_2);
                concat(&buf_2,&buf_3);
                reset(&buf_1);
                appendarray(&buf_1,const_1_122,24);
                outputarray(const_1_78,8);
                consume(4);
                goto l1_107;
             }
             appendarray(&buf_14,const_1_122,24);
             appendarray(&buf_13,const_1_2,16);
             appendarray(&buf_12,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_122,24);
             reset(&buf_1);
             appendarray(&buf_1,const_1_78,8);
             consume(3);
             goto l1_91;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_122,24);
          concat(&buf_1,&buf_3);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_122,24);
          concat(&buf_1,&buf_3);
          appendarray(&buf_1,const_1_77,48);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_56: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          output(&buf_20);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_13);
                appendarray(&buf_13,const_1_46,120);
                reset(&buf_12);
                appendarray(&buf_12,const_1_12,96);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                output(&buf_1);
                reset(&buf_1);
                appendarray(&buf_1,const_1_101,16);
                consume(4);
                goto l1_107;
             }
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_27,104);
             concat(&buf_12,&buf_9);
             appendarray(&buf_12,const_1_122,24);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             consume(3);
             goto l1_91;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          concat(&buf_12,&buf_20);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_57: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_80,56);
                reset(&buf_13);
                appendarray(&buf_13,const_1_13,112);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(4);
                goto l1_107;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             reset(&buf_9);
             appendarray(&buf_9,const_1_89,64);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             consume(3);
             goto l1_72;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_89,64);
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_78,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_100,56);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_2,const_1_100,56);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_58: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   output(&buf_1);
                   consume(4);
                   goto l1_112;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_9,72);
                appendarray(&buf_12,const_1_124,64);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                appendarray(&buf_1,const_1_78,8);
                consume(3);
                goto l1_75;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_8,64);
             appendarray(&buf_12,const_1_104,56);
             reset(&buf_2);
             appendarray(&buf_2,const_1_78,8);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_44;
          }
          appendarray(&buf_12,const_1_79,48);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_77,48);
          appendarray(&buf_1,const_1_77,48);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_59: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   outputarray(const_1_101,16);
                   consume(4);
                   goto l1_92;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_43,80);
                reset(&buf_12);
                appendarray(&buf_12,const_1_10,88);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                reset(&buf_1);
                appendarray(&buf_1,const_1_78,8);
                outputarray(const_1_78,8);
                consume(3);
                goto l1_75;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_42,72);
             reset(&buf_12);
             appendarray(&buf_12,const_1_10,88);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             reset(&buf_1);
             appendarray(&buf_1,const_1_101,16);
             consume(2);
             goto l1_44;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          outputarray(const_1_121,64);
          consume(1);
          goto l1_7;
       }
       goto fail1;
l1_60: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   output(&buf_1);
                   outputarray(const_1_122,24);
                   consume(4);
                   goto l1_92;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_43,80);
                reset(&buf_12);
                appendarray(&buf_12,const_1_64,104);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                output(&buf_1);
                reset(&buf_1);
                appendarray(&buf_1,const_1_122,24);
                consume(3);
                goto l1_75;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_42,72);
             reset(&buf_12);
             appendarray(&buf_12,const_1_44,96);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             output(&buf_1);
             reset(&buf_1);
             appendarray(&buf_1,const_1_122,24);
             consume(2);
             goto l1_44;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          output(&buf_1);
          outputarray(const_1_122,24);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_1,const_1_127,72);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_61: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_133;
                }
                appendarray(&buf_13,const_1_78,8);
                appendarray(&buf_12,const_1_78,8);
                appendarray(&buf_2,const_1_78,8);
                consume(3);
                goto l1_80;
             }
             appendarray(&buf_13,const_1_78,8);
             appendarray(&buf_12,const_1_78,8);
             appendarray(&buf_2,const_1_78,8);
             consume(2);
             goto l1_51;
          }
          appendarray(&buf_13,const_1_79,48);
          appendarray(&buf_12,const_1_79,48);
          appendarray(&buf_2,const_1_78,8);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_77,48);
          appendarray(&buf_12,const_1_77,48);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_62: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_134;
                }
                consume(3);
                goto l1_97;
             }
             consume(2);
             goto l1_50;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          appendarray(&buf_12,const_1_112,72);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          appendarray(&buf_1,const_1_101,16);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_121,64);
          appendarray(&buf_1,const_1_121,64);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_63: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_135;
                }
                consume(3);
                goto l1_99;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_58,128);
             reset(&buf_12);
             appendarray(&buf_12,const_1_30,144);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             reset(&buf_1);
             appendarray(&buf_1,const_1_101,16);
             consume(2);
             goto l1_65;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_57,112);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_63,104);
          reset(&buf_1);
          appendarray(&buf_1,const_1_131,88);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_64: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_20);
                   appendarray(&buf_20,const_1_12,96);
                   reset(&buf_9);
                   appendarray(&buf_9,const_1_89,64);
                   consume(4);
                   goto l1_136;
                }
                consume(3);
                goto l1_100;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_28,120);
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_28,120);
             reset(&buf_9);
             appendarray(&buf_9,const_1_92,104);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             consume(2);
             goto l1_66;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_13);
          appendarray(&buf_13,const_1_27,104);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_65: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                appendarray(&buf_15,const_1_123,48);
                appendarray(&buf_14,const_1_1,8);
                appendarray(&buf_13,const_1_123,48);
                appendarray(&buf_12,const_1_1,8);
                consume(4);
                goto l1_137;
             }
             appendarray(&buf_15,const_1_122,24);
             appendarray(&buf_14,const_1_2,16);
             appendarray(&buf_13,const_1_122,24);
             appendarray(&buf_12,const_1_2,16);
             consume(3);
             goto l1_102;
          }
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_2,16);
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          appendarray(&buf_12,const_1_2,16);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          concat(&buf_2,&buf_4);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          concat(&buf_2,&buf_4);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_66: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                appendarray(&buf_15,const_1_123,48);
                appendarray(&buf_14,const_1_1,8);
                appendarray(&buf_13,const_1_123,48);
                concat(&buf_12,&buf_9);
                appendarray(&buf_12,const_1_1,8);
                reset(&buf_3);
                appendarray(&buf_3,const_1_122,24);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(4);
                goto l1_137;
             }
             appendarray(&buf_20,const_1_122,24);
             appendarray(&buf_15,const_1_122,24);
             appendarray(&buf_14,const_1_2,16);
             appendarray(&buf_13,const_1_122,24);
             appendarray(&buf_9,const_1_2,16);
             consume(3);
             goto l1_103;
          }
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_2,16);
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          concat(&buf_12,&buf_9);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_122,24);
          concat(&buf_2,&buf_4);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_134,8);
          concat(&buf_12,&buf_9);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_122,24);
          concat(&buf_2,&buf_4);
          appendarray(&buf_2,const_1_77,48);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_67: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          output(&buf_20);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_20);
                appendarray(&buf_20,const_1_12,96);
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                reset(&buf_9);
                appendarray(&buf_9,const_1_116,136);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                consume(4);
                goto l1_117;
             }
             concat(&buf_12,&buf_9);
             appendarray(&buf_12,const_1_122,24);
             consume(3);
             goto l1_104;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_13);
          appendarray(&buf_13,const_1_27,104);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_14);
          appendarray(&buf_14,const_1_40,96);
          appendarray(&buf_13,const_1_40,96);
          concat(&buf_12,&buf_20);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_129,80);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_68: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_80,56);
                reset(&buf_13);
                concat(&buf_13,&buf_14);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                concat(&buf_2,&buf_3);
                consume(4);
                goto l1_118;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             reset(&buf_13);
             concat(&buf_13,&buf_14);
             reset(&buf_9);
             appendarray(&buf_9,const_1_89,64);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             concat(&buf_2,&buf_3);
             consume(3);
             goto l1_83;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_89,64);
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_89,64);
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          appendarray(&buf_2,const_1_78,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_14,const_1_100,56);
          appendarray(&buf_13,const_1_100,56);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_3,const_1_100,56);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_69: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   concat(&buf_12,&buf_13);
                   output(&buf_1);
                   reset(&buf_1);
                   concat(&buf_1,&buf_2);
                   consume(4);
                   goto l1_129;
                }
                appendarray(&buf_13,const_1_78,8);
                appendarray(&buf_12,const_1_124,64);
                appendarray(&buf_2,const_1_78,8);
                consume(3);
                goto l1_90;
             }
             appendarray(&buf_13,const_1_78,8);
             appendarray(&buf_12,const_1_104,56);
             appendarray(&buf_2,const_1_78,8);
             consume(2);
             goto l1_57;
          }
          appendarray(&buf_13,const_1_79,48);
          appendarray(&buf_12,const_1_79,48);
          appendarray(&buf_2,const_1_78,8);
          consume(1);
          goto l1_32;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_77,48);
          appendarray(&buf_12,const_1_77,48);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_70: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_14,120);
                   appendarray(&buf_12,const_1_105,64);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_78,8);
                   consume(4);
                   goto l1_146;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_10,88);
                reset(&buf_13);
                appendarray(&buf_13,const_1_13,112);
                appendarray(&buf_12,const_1_78,8);
                reset(&buf_9);
                appendarray(&buf_9,const_1_91,88);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(3);
                goto l1_109;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_9);
             appendarray(&buf_9,const_1_113,88);
             consume(2);
             goto l1_56;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          appendarray(&buf_12,const_1_112,72);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          appendarray(&buf_1,const_1_101,16);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_121,64);
          appendarray(&buf_1,const_1_121,64);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_71: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_45,104);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_101,16);
                   outputarray(const_1_101,16);
                   consume(4);
                   goto l1_131;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_59,136);
                reset(&buf_12);
                appendarray(&buf_12,const_1_34,152);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                reset(&buf_1);
                appendarray(&buf_1,const_1_101,16);
                consume(3);
                goto l1_111;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_58,128);
             reset(&buf_12);
             appendarray(&buf_12,const_1_30,144);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             reset(&buf_1);
             appendarray(&buf_1,const_1_101,16);
             consume(2);
             goto l1_73;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_57,112);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_63,104);
          reset(&buf_1);
          appendarray(&buf_1,const_1_131,88);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_72: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          output(&buf_20);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_12,96);
                   output(&buf_1);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_78,8);
                   consume(4);
                   goto l1_131;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_29,128);
                concat(&buf_12,&buf_9);
                appendarray(&buf_12,const_1_79,48);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(3);
                goto l1_111;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_28,120);
             concat(&buf_12,&buf_9);
             appendarray(&buf_12,const_1_5,40);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_78,8);
             consume(2);
             goto l1_73;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          concat(&buf_12,&buf_20);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_73: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_13);
                concat(&buf_13,&buf_15);
                appendarray(&buf_13,const_1_123,48);
                reset(&buf_12);
                concat(&buf_12,&buf_14);
                appendarray(&buf_12,const_1_1,8);
                output(&buf_1);
                output(&buf_2);
                reset(&buf_2);
                concat(&buf_2,&buf_4);
                reset(&buf_1);
                concat(&buf_1,&buf_3);
                consume(4);
                goto l1_107;
             }
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_122,24);
             reset(&buf_13);
             concat(&buf_13,&buf_14);
             appendarray(&buf_13,const_1_2,16);
             reset(&buf_14);
             concat(&buf_14,&buf_15);
             appendarray(&buf_14,const_1_122,24);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             concat(&buf_2,&buf_3);
             reset(&buf_3);
             concat(&buf_3,&buf_4);
             consume(3);
             goto l1_91;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_14);
          appendarray(&buf_12,const_1_2,16);
          output(&buf_1);
          output(&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          concat(&buf_1,&buf_3);
          concat(&buf_1,&buf_4);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          concat(&buf_2,&buf_4);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_74: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_11,96);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   outputarray(const_1_128,32);
                   consume(4);
                   goto l1_112;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_9,72);
                reset(&buf_12);
                appendarray(&buf_12,const_1_10,88);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                reset(&buf_1);
                appendarray(&buf_1,const_1_101,16);
                outputarray(const_1_122,24);
                consume(3);
                goto l1_75;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_8,64);
             reset(&buf_12);
             appendarray(&buf_12,const_1_64,104);
             reset(&buf_2);
             appendarray(&buf_2,const_1_78,8);
             reset(&buf_1);
             appendarray(&buf_1,const_1_130,40);
             consume(2);
             goto l1_44;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_44,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_75: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   output(&buf_1);
                   output(&buf_2);
                   outputarray(const_1_78,8);
                   consume(4);
                   goto l1_92;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_43,80);
                reset(&buf_12);
                appendarray(&buf_12,const_1_10,88);
                output(&buf_1);
                output(&buf_2);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                reset(&buf_1);
                appendarray(&buf_1,const_1_78,8);
                consume(3);
                goto l1_75;
             }
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_101,16);
             reset(&buf_13);
             appendarray(&buf_13,const_1_42,72);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             appendarray(&buf_1,const_1_78,8);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             consume(2);
             goto l1_44;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_41,56);
          output(&buf_1);
          output(&buf_2);
          outputarray(const_1_78,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_12,const_1_134,8);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_100,56);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_76: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_147;
                }
                consume(3);
                goto l1_98;
             }
             reset(&buf_12);
             appendarray(&buf_12,const_1_41,56);
             reset(&buf_1);
             appendarray(&buf_1,const_1_130,40);
             outputarray(const_1_78,8);
             consume(2);
             goto l1_38;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_44,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_77: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_6,48);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   concat(&buf_12,&buf_13);
                   reset(&buf_13);
                   concat(&buf_13,&buf_14);
                   output(&buf_1);
                   reset(&buf_1);
                   concat(&buf_1,&buf_2);
                   reset(&buf_2);
                   concat(&buf_2,&buf_3);
                   consume(4);
                   goto l1_133;
                }
                appendarray(&buf_14,const_1_78,8);
                appendarray(&buf_13,const_1_78,8);
                appendarray(&buf_12,const_1_124,64);
                appendarray(&buf_3,const_1_78,8);
                consume(3);
                goto l1_101;
             }
             appendarray(&buf_14,const_1_78,8);
             appendarray(&buf_13,const_1_78,8);
             appendarray(&buf_12,const_1_104,56);
             appendarray(&buf_3,const_1_78,8);
             consume(2);
             goto l1_68;
          }
          appendarray(&buf_14,const_1_79,48);
          appendarray(&buf_13,const_1_79,48);
          appendarray(&buf_12,const_1_79,48);
          appendarray(&buf_3,const_1_78,8);
          consume(1);
          goto l1_39;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_14,const_1_77,48);
          appendarray(&buf_13,const_1_77,48);
          appendarray(&buf_12,const_1_77,48);
          appendarray(&buf_3,const_1_77,48);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_78: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_148;
                }
                consume(3);
                goto l1_119;
             }
             reset(&buf_14);
             appendarray(&buf_14,const_1_42,72);
             reset(&buf_13);
             appendarray(&buf_13,const_1_44,96);
             reset(&buf_12);
             appendarray(&buf_12,const_1_28,120);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             outputarray(const_1_78,8);
             consume(2);
             goto l1_49;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_79: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_149;
                }
                consume(3);
                goto l1_121;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_73,136);
             reset(&buf_12);
             appendarray(&buf_12,const_1_30,144);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_122,24);
             reset(&buf_1);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_65;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_72,120);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_132,48);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_76,112);
          reset(&buf_1);
          appendarray(&buf_1,const_1_133,96);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_80: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   appendarray(&buf_12,const_1_105,64);
                   consume(4);
                   goto l1_150;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_10,88);
                appendarray(&buf_12,const_1_78,8);
                reset(&buf_9);
                appendarray(&buf_9,const_1_91,88);
                consume(3);
                goto l1_122;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_9);
             appendarray(&buf_9,const_1_113,88);
             consume(2);
             goto l1_67;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          appendarray(&buf_13,const_1_112,72);
          appendarray(&buf_12,const_1_112,72);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          appendarray(&buf_2,const_1_101,16);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_121,64);
          appendarray(&buf_12,const_1_121,64);
          appendarray(&buf_2,const_1_121,64);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_81: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   appendarray(&buf_14,const_1_1,8);
                   appendarray(&buf_12,const_1_1,8);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_122,24);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_78,8);
                   consume(4);
                   goto l1_151;
                }
                appendarray(&buf_14,const_1_4,40);
                appendarray(&buf_12,const_1_4,40);
                consume(3);
                goto l1_125;
             }
             reset(&buf_16);
             appendarray(&buf_16,const_1_42,72);
             reset(&buf_15);
             appendarray(&buf_15,const_1_44,96);
             appendarray(&buf_14,const_1_3,32);
             appendarray(&buf_13,const_1_5,40);
             appendarray(&buf_12,const_1_3,32);
             reset(&buf_5);
             appendarray(&buf_5,const_1_101,16);
             reset(&buf_4);
             appendarray(&buf_4,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_122,24);
             reset(&buf_1);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_84;
          }
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_2,16);
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          appendarray(&buf_2,const_1_122,24);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          appendarray(&buf_2,const_1_127,72);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_82: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_14);
                   appendarray(&buf_14,const_1_45,104);
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_27,104);
                   appendarray(&buf_12,const_1_115,120);
                   reset(&buf_3);
                   appendarray(&buf_3,const_1_101,16);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_101,16);
                   consume(4);
                   goto l1_151;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_34,152);
                reset(&buf_9);
                appendarray(&buf_9,const_1_119,152);
                consume(3);
                goto l1_126;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_30,144);
             reset(&buf_16);
             appendarray(&buf_16,const_1_42,72);
             reset(&buf_15);
             appendarray(&buf_15,const_1_44,96);
             reset(&buf_14);
             appendarray(&buf_14,const_1_58,128);
             reset(&buf_13);
             appendarray(&buf_13,const_1_30,144);
             reset(&buf_9);
             appendarray(&buf_9,const_1_118,144);
             reset(&buf_5);
             appendarray(&buf_5,const_1_101,16);
             reset(&buf_4);
             appendarray(&buf_4,const_1_122,24);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             consume(2);
             goto l1_85;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_13);
          appendarray(&buf_13,const_1_57,112);
          appendarray(&buf_12,const_1_117,128);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          appendarray(&buf_1,const_1_101,16);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_63,104);
          appendarray(&buf_12,const_1_120,120);
          reset(&buf_2);
          appendarray(&buf_2,const_1_131,88);
          appendarray(&buf_1,const_1_101,16);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_83: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          output(&buf_20);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_20);
                   appendarray(&buf_20,const_1_12,96);
                   reset(&buf_12);
                   concat(&buf_12,&buf_13);
                   reset(&buf_9);
                   appendarray(&buf_9,const_1_89,64);
                   output(&buf_1);
                   reset(&buf_1);
                   concat(&buf_1,&buf_2);
                   consume(4);
                   goto l1_136;
                }
                concat(&buf_12,&buf_9);
                appendarray(&buf_12,const_1_79,48);
                consume(3);
                goto l1_127;
             }
             reset(&buf_21);
             appendarray(&buf_21,const_1_28,120);
             reset(&buf_16);
             appendarray(&buf_16,const_1_42,72);
             reset(&buf_15);
             appendarray(&buf_15,const_1_44,96);
             reset(&buf_14);
             appendarray(&buf_14,const_1_28,120);
             concat(&buf_12,&buf_9);
             appendarray(&buf_12,const_1_5,40);
             reset(&buf_10);
             appendarray(&buf_10,const_1_92,104);
             reset(&buf_5);
             appendarray(&buf_5,const_1_101,16);
             consume(2);
             goto l1_86;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_13);
          appendarray(&buf_13,const_1_27,104);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_14);
          appendarray(&buf_14,const_1_40,96);
          appendarray(&buf_13,const_1_40,96);
          concat(&buf_12,&buf_20);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_129,80);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_84: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_1,8);
                reset(&buf_13);
                concat(&buf_13,&buf_14);
                appendarray(&buf_13,const_1_123,48);
                reset(&buf_14);
                concat(&buf_14,&buf_15);
                appendarray(&buf_14,const_1_1,8);
                reset(&buf_15);
                concat(&buf_15,&buf_16);
                appendarray(&buf_15,const_1_123,48);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                concat(&buf_2,&buf_3);
                reset(&buf_3);
                concat(&buf_3,&buf_4);
                reset(&buf_4);
                concat(&buf_4,&buf_5);
                consume(4);
                goto l1_137;
             }
             appendarray(&buf_16,const_1_122,24);
             appendarray(&buf_15,const_1_2,16);
             appendarray(&buf_14,const_1_122,24);
             appendarray(&buf_13,const_1_2,16);
             appendarray(&buf_12,const_1_122,24);
             consume(3);
             goto l1_128;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          concat(&buf_13,&buf_15);
          appendarray(&buf_13,const_1_2,16);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          concat(&buf_1,&buf_3);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          concat(&buf_2,&buf_4);
          concat(&buf_2,&buf_5);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_13);
          concat(&buf_13,&buf_15);
          appendarray(&buf_13,const_1_134,8);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          concat(&buf_1,&buf_3);
          reset(&buf_2);
          concat(&buf_2,&buf_4);
          concat(&buf_2,&buf_5);
          appendarray(&buf_2,const_1_77,48);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_85: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          output(&buf_20);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_1,8);
                reset(&buf_13);
                concat(&buf_13,&buf_14);
                appendarray(&buf_13,const_1_123,48);
                reset(&buf_14);
                concat(&buf_14,&buf_15);
                appendarray(&buf_14,const_1_1,8);
                reset(&buf_15);
                concat(&buf_15,&buf_16);
                appendarray(&buf_15,const_1_123,48);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                concat(&buf_2,&buf_3);
                reset(&buf_3);
                concat(&buf_3,&buf_4);
                reset(&buf_4);
                concat(&buf_4,&buf_5);
                consume(4);
                goto l1_137;
             }
             appendarray(&buf_16,const_1_122,24);
             appendarray(&buf_15,const_1_2,16);
             appendarray(&buf_14,const_1_122,24);
             appendarray(&buf_13,const_1_2,16);
             concat(&buf_12,&buf_9);
             appendarray(&buf_12,const_1_122,24);
             consume(3);
             goto l1_128;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          concat(&buf_13,&buf_15);
          appendarray(&buf_13,const_1_2,16);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          concat(&buf_1,&buf_3);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          concat(&buf_2,&buf_4);
          concat(&buf_2,&buf_5);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_14);
          concat(&buf_14,&buf_15);
          appendarray(&buf_14,const_1_134,8);
          appendarray(&buf_13,const_1_134,8);
          concat(&buf_12,&buf_20);
          appendarray(&buf_12,const_1_134,8);
          concat(&buf_2,&buf_3);
          reset(&buf_3);
          concat(&buf_3,&buf_4);
          concat(&buf_3,&buf_5);
          appendarray(&buf_3,const_1_77,48);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_86: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
          {
             if (((avail >= 4) && ((next[3] == 'a') && 1)))
             {
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                concat(&buf_12,&buf_10);
                appendarray(&buf_12,const_1_1,8);
                reset(&buf_13);
                concat(&buf_13,&buf_14);
                appendarray(&buf_13,const_1_123,48);
                reset(&buf_14);
                concat(&buf_14,&buf_15);
                appendarray(&buf_14,const_1_1,8);
                reset(&buf_15);
                concat(&buf_15,&buf_16);
                appendarray(&buf_15,const_1_123,48);
                reset(&buf_4);
                concat(&buf_4,&buf_5);
                reset(&buf_3);
                appendarray(&buf_3,const_1_122,24);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(4);
                goto l1_137;
             }
             reset(&buf_20);
             concat(&buf_20,&buf_21);
             appendarray(&buf_20,const_1_122,24);
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             reset(&buf_13);
             concat(&buf_13,&buf_14);
             appendarray(&buf_13,const_1_122,24);
             reset(&buf_14);
             concat(&buf_14,&buf_15);
             appendarray(&buf_14,const_1_2,16);
             reset(&buf_15);
             concat(&buf_15,&buf_16);
             appendarray(&buf_15,const_1_122,24);
             reset(&buf_9);
             concat(&buf_9,&buf_10);
             appendarray(&buf_9,const_1_2,16);
             reset(&buf_4);
             concat(&buf_4,&buf_5);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             consume(3);
             goto l1_103;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          concat(&buf_12,&buf_10);
          appendarray(&buf_12,const_1_2,16);
          reset(&buf_13);
          concat(&buf_13,&buf_15);
          appendarray(&buf_13,const_1_2,16);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_78,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_122,24);
          concat(&buf_2,&buf_5);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_14);
          concat(&buf_14,&buf_15);
          appendarray(&buf_14,const_1_134,8);
          concat(&buf_13,&buf_10);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_122,24);
          concat(&buf_3,&buf_5);
          appendarray(&buf_3,const_1_77,48);
          appendarray(&buf_2,const_1_78,8);
          consume(1);
          goto l1_35;
       }
       goto fail1;
l1_87: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   outputarray(const_1_78,8);
                   consume(4);
                   goto l1_145;
                }
                reset(&buf_12);
                appendarray(&buf_12,const_1_15,136);
                reset(&buf_1);
                appendarray(&buf_1,const_1_78,8);
                consume(3);
                goto l1_110;
             }
             reset(&buf_12);
             appendarray(&buf_12,const_1_41,56);
             reset(&buf_1);
             appendarray(&buf_1,const_1_130,40);
             outputarray(const_1_78,8);
             consume(2);
             goto l1_42;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_44,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_23;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_88: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_47,128);
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_12,96);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_101,16);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_78,8);
                   outputarray(const_1_78,8);
                   consume(4);
                   goto l1_146;
                }
                reset(&buf_16);
                appendarray(&buf_16,const_1_43,80);
                reset(&buf_14);
                appendarray(&buf_14,const_1_46,120);
                reset(&buf_13);
                appendarray(&buf_13,const_1_29,128);
                reset(&buf_12);
                appendarray(&buf_12,const_1_15,136);
                reset(&buf_5);
                appendarray(&buf_5,const_1_101,16);
                reset(&buf_4);
                appendarray(&buf_4,const_1_78,8);
                reset(&buf_3);
                appendarray(&buf_3,const_1_101,16);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                reset(&buf_1);
                appendarray(&buf_1,const_1_78,8);
                consume(3);
                goto l1_132;
             }
             reset(&buf_14);
             appendarray(&buf_14,const_1_42,72);
             reset(&buf_13);
             appendarray(&buf_13,const_1_44,96);
             reset(&buf_12);
             appendarray(&buf_12,const_1_28,120);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             outputarray(const_1_78,8);
             consume(2);
             goto l1_55;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_89: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_47,128);
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_65,112);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_101,16);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_122,24);
                   outputarray(const_1_78,8);
                   consume(4);
                   goto l1_146;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_10,88);
                reset(&buf_13);
                appendarray(&buf_13,const_1_46,120);
                reset(&buf_12);
                appendarray(&buf_12,const_1_41,56);
                reset(&buf_9);
                appendarray(&buf_9,const_1_91,88);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                reset(&buf_1);
                appendarray(&buf_1,const_1_122,24);
                outputarray(const_1_78,8);
                consume(3);
                goto l1_109;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_73,136);
             reset(&buf_12);
             appendarray(&buf_12,const_1_30,144);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_122,24);
             reset(&buf_1);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_73;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_72,120);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_132,48);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_76,112);
          reset(&buf_1);
          appendarray(&buf_1,const_1_133,96);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_90: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   concat(&buf_12,&buf_13);
                   appendarray(&buf_12,const_1_105,64);
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_14,120);
                   output(&buf_1);
                   reset(&buf_1);
                   concat(&buf_1,&buf_2);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_78,8);
                   consume(4);
                   goto l1_146;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_10,88);
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_78,8);
                reset(&buf_13);
                appendarray(&buf_13,const_1_13,112);
                reset(&buf_9);
                appendarray(&buf_9,const_1_91,88);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                consume(3);
                goto l1_109;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_10,88);
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             reset(&buf_9);
             appendarray(&buf_9,const_1_113,88);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             consume(2);
             goto l1_56;
          }
          reset(&buf_12);
          concat(&buf_12,&buf_13);
          appendarray(&buf_12,const_1_112,72);
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          output(&buf_1);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_101,16);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          appendarray(&buf_13,const_1_121,64);
          appendarray(&buf_12,const_1_134,8);
          appendarray(&buf_2,const_1_121,64);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_91: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_12);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_12);
                   concat(&buf_12,&buf_14);
                   appendarray(&buf_12,const_1_1,8);
                   output(&buf_1);
                   output(&buf_2);
                   reset(&buf_1);
                   concat(&buf_1,&buf_3);
                   consume(4);
                   goto l1_131;
                }
                reset(&buf_12);
                concat(&buf_12,&buf_13);
                appendarray(&buf_12,const_1_79,48);
                reset(&buf_13);
                concat(&buf_13,&buf_14);
                appendarray(&buf_13,const_1_4,40);
                output(&buf_1);
                reset(&buf_1);
                concat(&buf_1,&buf_2);
                reset(&buf_2);
                concat(&buf_2,&buf_3);
                consume(3);
                goto l1_111;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_12);
             concat(&buf_12,&buf_13);
             appendarray(&buf_12,const_1_5,40);
             reset(&buf_13);
             concat(&buf_13,&buf_14);
             appendarray(&buf_13,const_1_3,32);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             output(&buf_1);
             reset(&buf_1);
             concat(&buf_1,&buf_2);
             reset(&buf_2);
             concat(&buf_2,&buf_3);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             consume(2);
             goto l1_73;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          concat(&buf_12,&buf_14);
          appendarray(&buf_12,const_1_2,16);
          output(&buf_1);
          output(&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          concat(&buf_1,&buf_3);
          appendarray(&buf_1,const_1_122,24);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          concat(&buf_13,&buf_14);
          appendarray(&buf_13,const_1_134,8);
          appendarray(&buf_12,const_1_134,8);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          concat(&buf_2,&buf_3);
          appendarray(&buf_2,const_1_127,72);
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_92: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_11,96);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   outputarray(const_1_128,32);
                   consume(4);
                   goto l1_112;
                }
                reset(&buf_13);
                appendarray(&buf_13,const_1_9,72);
                reset(&buf_12);
                appendarray(&buf_12,const_1_10,88);
                reset(&buf_2);
                appendarray(&buf_2,const_1_78,8);
                reset(&buf_1);
                appendarray(&buf_1,const_1_101,16);
                outputarray(const_1_122,24);
                consume(3);
                goto l1_75;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_8,64);
             reset(&buf_12);
             appendarray(&buf_12,const_1_10,88);
             reset(&buf_2);
             appendarray(&buf_2,const_1_78,8);
             reset(&buf_1);
             appendarray(&buf_1,const_1_122,24);
             outputarray(const_1_101,16);
             consume(2);
             goto l1_44;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_44,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_130,40);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_19;
       }
       goto fail1;
l1_93: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_157;
                }
                outputarray(const_1_78,8);
                consume(3);
                goto l1_96;
             }
             reset(&buf_14);
             appendarray(&buf_14,const_1_8,64);
             reset(&buf_13);
             appendarray(&buf_13,const_1_10,88);
             reset(&buf_12);
             appendarray(&buf_12,const_1_13,112);
             reset(&buf_3);
             appendarray(&buf_3,const_1_78,8);
             outputarray(const_1_78,8);
             consume(2);
             goto l1_49;
          }
          reset(&buf_12);
          appendarray(&buf_12,const_1_10,88);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          outputarray(const_1_78,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_94: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_50,168);
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_12,96);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_101,16);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_101,16);
                   consume(4);
                   goto l1_158;
                }
                consume(3);
                goto l1_123;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_41,56);
             reset(&buf_12);
             appendarray(&buf_12,const_1_27,104);
             reset(&buf_2);
             appendarray(&buf_2,const_1_130,40);
             reset(&buf_1);
             appendarray(&buf_1,const_1_128,32);
             consume(2);
             goto l1_51;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_44,96);
          reset(&buf_12);
          appendarray(&buf_12,const_1_30,144);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          reset(&buf_12);
          appendarray(&buf_12,const_1_26,144);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_95: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_18,160);
                   appendarray(&buf_12,const_1_80,56);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_78,8);
                   consume(4);
                   goto l1_158;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_15,136);
                reset(&buf_9);
                appendarray(&buf_9,const_1_89,64);
                consume(3);
                goto l1_124;
             }
             reset(&buf_13);
             appendarray(&buf_13,const_1_41,56);
             appendarray(&buf_12,const_1_89,64);
             reset(&buf_2);
             appendarray(&buf_2,const_1_130,40);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_51;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_44,96);
          appendarray(&buf_12,const_1_92,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          appendarray(&buf_12,const_1_88,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_96: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   consume(4);
                   goto l1_159;
                }
                reset(&buf_17);
                appendarray(&buf_17,const_1_43,80);
                reset(&buf_14);
                appendarray(&buf_14,const_1_29,128);
                reset(&buf_6);
                appendarray(&buf_6,const_1_101,16);
                reset(&buf_5);
                appendarray(&buf_5,const_1_78,8);
                consume(3);
                goto l1_138;
             }
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_10,88);
             reset(&buf_13);
             appendarray(&buf_13,const_1_28,120);
             reset(&buf_12);
             appendarray(&buf_12,const_1_15,136);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             reset(&buf_1);
             appendarray(&buf_1,const_1_101,16);
             consume(2);
             goto l1_65;
          }
          reset(&buf_13);
          appendarray(&buf_13,const_1_41,56);
          reset(&buf_12);
          appendarray(&buf_12,const_1_27,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_130,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_12);
          appendarray(&buf_12,const_1_40,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_129,80);
          outputarray(const_1_101,16);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_97: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_20);
                   appendarray(&buf_20,const_1_12,96);
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_18,160);
                   appendarray(&buf_12,const_1_78,8);
                   reset(&buf_9);
                   appendarray(&buf_9,const_1_94,136);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_78,8);
                   consume(4);
                   goto l1_160;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_15,136);
                reset(&buf_9);
                appendarray(&buf_9,const_1_78,8);
                consume(3);
                goto l1_139;
             }
             reset(&buf_20);
             appendarray(&buf_20,const_1_28,120);
             reset(&buf_15);
             appendarray(&buf_15,const_1_42,72);
             reset(&buf_14);
             appendarray(&buf_14,const_1_44,96);
             reset(&buf_13);
             appendarray(&buf_13,const_1_28,120);
             appendarray(&buf_12,const_1_78,8);
             reset(&buf_9);
             appendarray(&buf_9,const_1_92,104);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_66;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_13);
          appendarray(&buf_13,const_1_27,104);
          appendarray(&buf_12,const_1_86,112);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_128,32);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          appendarray(&buf_12,const_1_88,104);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          appendarray(&buf_1,const_1_78,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_98: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_21);
                   appendarray(&buf_21,const_1_14,120);
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_17,144);
                   reset(&buf_10);
                   appendarray(&buf_10,const_1_84,120);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_78,8);
                   consume(4);
                   goto l1_161;
                }
                reset(&buf_17);
                appendarray(&buf_17,const_1_43,80);
                reset(&buf_14);
                appendarray(&buf_14,const_1_29,128);
                reset(&buf_12);
                appendarray(&buf_12,const_1_25,176);
                reset(&buf_6);
                appendarray(&buf_6,const_1_101,16);
                reset(&buf_5);
                appendarray(&buf_5,const_1_78,8);
                consume(3);
                goto l1_140;
             }
             reset(&buf_16);
             appendarray(&buf_16,const_1_42,72);
             reset(&buf_15);
             appendarray(&buf_15,const_1_10,88);
             reset(&buf_14);
             appendarray(&buf_14,const_1_28,120);
             reset(&buf_13);
             appendarray(&buf_13,const_1_48,144);
             reset(&buf_12);
             appendarray(&buf_12,const_1_24,168);
             reset(&buf_5);
             appendarray(&buf_5,const_1_101,16);
             reset(&buf_4);
             appendarray(&buf_4,const_1_101,16);
             reset(&buf_3);
             appendarray(&buf_3,const_1_101,16);
             reset(&buf_2);
             appendarray(&buf_2,const_1_122,24);
             reset(&buf_1);
             appendarray(&buf_1,const_1_78,8);
             consume(2);
             goto l1_84;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_13);
          appendarray(&buf_13,const_1_27,104);
          reset(&buf_12);
          appendarray(&buf_12,const_1_23,152);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_128,32);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_40,96);
          reset(&buf_12);
          appendarray(&buf_12,const_1_26,144);
          reset(&buf_2);
          appendarray(&buf_2,const_1_129,80);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_99: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 'a') && 1)))
       {
          if (((avail >= 2) && ((next[1] == 'a') && 1)))
          {
             if (((avail >= 3) && ((next[2] == 'a') && 1)))
             {
                if (((avail >= 4) && ((next[3] == 'a') && 1)))
                {
                   reset(&buf_13);
                   appendarray(&buf_13,const_1_62,184);
                   reset(&buf_12);
                   appendarray(&buf_12,const_1_35,160);
                   reset(&buf_2);
                   appendarray(&buf_2,const_1_101,16);
                   reset(&buf_1);
                   appendarray(&buf_1,const_1_101,16);
                   consume(4);
                   goto l1_162;
                }
                reset(&buf_20);
                appendarray(&buf_20,const_1_10,88);
                reset(&buf_13);
                appendarray(&buf_13,const_1_61,176);
                reset(&buf_12);
                appendarray(&buf_12,const_1_27,104);
                reset(&buf_9);
                appendarray(&buf_9,const_1_91,88);
                reset(&buf_2);
                appendarray(&buf_2,const_1_101,16);
                reset(&buf_1);
                appendarray(&buf_1,const_1_101,16);
                consume(3);
                goto l1_142;
             }
             reset(&buf_16);
             appendarray(&buf_16,const_1_42,72);
             reset(&buf_15);
             appendarray(&buf_15,const_1_44,96);
             reset(&buf_14);
             appendarray(&buf_14,const_1_73,136);
             reset(&buf_13);
             appendarray(&buf_13,const_1_60,152);
             reset(&buf_12);
             appendarray(&buf_12,const_1_38,184);
             reset(&buf_5);
             appendarray(&buf_5,const_1_101,16);
             reset(&buf_4);
             appendarray(&buf_4,const_1_122,24);
             reset(&buf_3);
             appendarray(&buf_3,const_1_122,24);
             reset(&buf_2);
             appendarray(&buf_2,const_1_101,16);
             reset(&buf_1);
             appendarray(&buf_1,const_1_101,16);
             consume(2);
             goto l1_84;
          }
          reset(&buf_14);
          appendarray(&buf_14,const_1_41,56);
          reset(&buf_13);
          appendarray(&buf_13,const_1_72,120);
          reset(&buf_12);
          appendarray(&buf_12,const_1_37,168);
          reset(&buf_3);
          appendarray(&buf_3,const_1_130,40);
          reset(&buf_2);
          appendarray(&buf_2,const_1_132,48);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_29;
       }
       if (((avail >= 1) && ((next[0] == 'b') && 1)))
       {
          reset(&buf_13);
          appendarray(&buf_13,const_1_76,112);
          reset(&buf_12);
          appendarray(&buf_12,const_1_39,160);
          reset(&buf_2);
          appendarray(&buf_2,const_1_133,96);
          reset(&buf_1);
          appendarray(&buf_1,const_1_128,32);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_100: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_32,176);
                    appendarray(&buf_12,const_1_96,120);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_162;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_31,168);
                 appendarray(&buf_12,const_1_89,64);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_142;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_30,144);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_44,96);
              reset(&buf_14);
              appendarray(&buf_14,const_1_73,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_30,144);
              reset(&buf_9);
              appendarray(&buf_9,const_1_98,144);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_85;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_72,120);
           appendarray(&buf_12,const_1_97,128);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           appendarray(&buf_1,const_1_78,8);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_76,112);
           appendarray(&buf_12,const_1_99,120);
           reset(&buf_2);
           appendarray(&buf_2,const_1_133,96);
           appendarray(&buf_1,const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_101: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_105,64);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    concat(&buf_2,&buf_3);
                    consume(4);
                    goto l1_150;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_78,8);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_3);
                 consume(3);
                 goto l1_122;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_10,88);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              reset(&buf_9);
              appendarray(&buf_9,const_1_113,88);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              consume(2);
              goto l1_67;
           }
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_112,72);
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_112,72);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           appendarray(&buf_2,const_1_101,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           appendarray(&buf_14,const_1_121,64);
           appendarray(&buf_13,const_1_121,64);
           appendarray(&buf_12,const_1_134,8);
           appendarray(&buf_3,const_1_121,64);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_102: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    reset(&buf_14);
                    concat(&buf_14,&buf_15);
                    appendarray(&buf_14,const_1_1,8);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    concat(&buf_2,&buf_3);
                    reset(&buf_3);
                    concat(&buf_3,&buf_4);
                    consume(4);
                    goto l1_151;
                 }
                 appendarray(&buf_15,const_1_4,40);
                 appendarray(&buf_13,const_1_4,40);
                 appendarray(&buf_12,const_1_79,48);
                 consume(3);
                 goto l1_144;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              appendarray(&buf_15,const_1_3,32);
              appendarray(&buf_14,const_1_5,40);
              appendarray(&buf_13,const_1_3,32);
              appendarray(&buf_12,const_1_5,40);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_13);
           concat(&buf_13,&buf_15);
           appendarray(&buf_13,const_1_2,16);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           concat(&buf_1,&buf_3);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           appendarray(&buf_2,const_1_122,24);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_13);
           concat(&buf_13,&buf_15);
           appendarray(&buf_13,const_1_134,8);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           concat(&buf_1,&buf_3);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           appendarray(&buf_2,const_1_127,72);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_103: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    reset(&buf_14);
                    concat(&buf_14,&buf_15);
                    appendarray(&buf_14,const_1_1,8);
                    reset(&buf_3);
                    concat(&buf_3,&buf_4);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_122,24);
                    output(&buf_1);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_151;
                 }
                 appendarray(&buf_15,const_1_4,40);
                 appendarray(&buf_13,const_1_4,40);
                 concat(&buf_12,&buf_9);
                 appendarray(&buf_12,const_1_79,48);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_122,24);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_144;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              appendarray(&buf_15,const_1_3,32);
              appendarray(&buf_14,const_1_5,40);
              appendarray(&buf_13,const_1_3,32);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_5,40);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_13);
           concat(&buf_13,&buf_15);
           appendarray(&buf_13,const_1_2,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           appendarray(&buf_2,const_1_122,24);
           output(&buf_1);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           concat(&buf_14,&buf_15);
           appendarray(&buf_14,const_1_134,8);
           appendarray(&buf_13,const_1_134,8);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           concat(&buf_3,&buf_4);
           appendarray(&buf_3,const_1_127,72);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_104: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_45,104);
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_115,120);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_27,104);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_101,16);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    consume(4);
                    goto l1_151;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_34,152);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_119,152);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 consume(3);
                 goto l1_126;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_30,144);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_44,96);
              reset(&buf_14);
              appendarray(&buf_14,const_1_58,128);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              reset(&buf_13);
              appendarray(&buf_13,const_1_30,144);
              reset(&buf_9);
              appendarray(&buf_9,const_1_118,144);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_85;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_117,128);
           reset(&buf_13);
           appendarray(&buf_13,const_1_57,112);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_101,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_63,104);
           appendarray(&buf_13,const_1_120,120);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_131,88);
           appendarray(&buf_2,const_1_101,16);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_105: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) "aa",2) && 1)))
           {
              if (((avail >= 4) && ((next[3] == 'a') && 1)))
              {
                 reset(&buf_13);
                 concat(&buf_13,&buf_15);
                 appendarray(&buf_13,const_1_123,48);
                 reset(&buf_15);
                 concat(&buf_15,&buf_17);
                 appendarray(&buf_15,const_1_123,48);
                 reset(&buf_12);
                 concat(&buf_12,&buf_14);
                 appendarray(&buf_12,const_1_1,8);
                 reset(&buf_14);
                 concat(&buf_14,&buf_16);
                 appendarray(&buf_14,const_1_1,8);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_4);
                 reset(&buf_4);
                 concat(&buf_4,&buf_6);
                 reset(&buf_1);
                 concat(&buf_1,&buf_3);
                 reset(&buf_3);
                 concat(&buf_3,&buf_5);
                 consume(4);
                 goto l1_137;
              }
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_122,24);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_2,16);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_122,24);
              reset(&buf_15);
              concat(&buf_15,&buf_16);
              appendarray(&buf_15,const_1_2,16);
              reset(&buf_16);
              concat(&buf_16,&buf_17);
              appendarray(&buf_16,const_1_122,24);
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
              consume(3);
              goto l1_128;
           }
           reset(&buf_13);
           concat(&buf_13,&buf_16);
           appendarray(&buf_13,const_1_2,16);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_5);
           concat(&buf_2,&buf_6);
           reset(&buf_1);
           concat(&buf_1,&buf_3);
           concat(&buf_1,&buf_4);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_134,8);
           reset(&buf_14);
           concat(&buf_14,&buf_16);
           appendarray(&buf_14,const_1_134,8);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           concat(&buf_2,&buf_4);
           reset(&buf_3);
           concat(&buf_3,&buf_5);
           concat(&buf_3,&buf_6);
           appendarray(&buf_3,const_1_77,48);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_106: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    consume(4);
                    goto l1_164;
                 }
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_108;
              }
              reset(&buf_14);
              appendarray(&buf_14,const_1_8,64);
              reset(&buf_13);
              appendarray(&buf_13,const_1_10,88);
              reset(&buf_12);
              appendarray(&buf_12,const_1_13,112);
              reset(&buf_3);
              appendarray(&buf_3,const_1_78,8);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_55;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_10,88);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_23;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_129,80);
           consume(1);
           goto l1_18;
        }
        goto fail1;
l1_107: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    output(&buf_2);
                    consume(4);
                    goto l1_145;
                 }
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 consume(3);
                 goto l1_110;
              }
              reset(&buf_13);
              appendarray(&buf_13,const_1_41,56);
              appendarray(&buf_12,const_1_104,56);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_130,40);
              consume(2);
              goto l1_57;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           appendarray(&buf_12,const_1_79,48);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_77,48);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_108: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_14,120);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_146;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_43,80);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_29,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_15,136);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_42,72);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_28,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_15,136);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_41,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_27,104);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_22;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_129,80);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_18;
        }
        goto fail1;
l1_109: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_47,128);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_146;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_43,80);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_46,120);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_29,128);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_42,72);
              reset(&buf_14);
              appendarray(&buf_14,const_1_44,96);
              reset(&buf_13);
              appendarray(&buf_13,const_1_28,120);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_41,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_27,104);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_22;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_110: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_14,120);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    output(&buf_1);
                    outputarray(const_1_122,24);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    consume(4);
                    goto l1_146;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_43,80);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_29,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_66,152);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_42,72);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_28,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_48,144);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_41,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_27,104);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           output(&buf_1);
           outputarray(const_1_122,24);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_22;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_111: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_47,128);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_65,112);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    consume(4);
                    goto l1_146;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_46,120);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_109;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_42,72);
              reset(&buf_14);
              appendarray(&buf_14,const_1_44,96);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_73,136);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_41,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_72,120);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_132,48);
           consume(1);
           goto l1_22;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_76,112);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_133,96);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_112: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_11,96);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_112;
                 }
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_9,72);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_10,88);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_75;
              }
              reset(&buf_13);
              appendarray(&buf_13,const_1_8,64);
              reset(&buf_12);
              appendarray(&buf_12,const_1_10,88);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              outputarray(const_1_101,16);
              consume(2);
              goto l1_44;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_10,88);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_24;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_129,80);
           consume(1);
           goto l1_19;
        }
        goto fail1;
l1_113: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    consume(4);
                    goto l1_165;
                 }
                 appendarray(&buf_12,const_1_78,8);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_120;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_13,112);
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_13,112);
              appendarray(&buf_12,const_1_78,8);
              reset(&buf_9);
              appendarray(&buf_9,const_1_83,96);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_66;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           appendarray(&buf_12,const_1_83,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_78,8);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_114: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    consume(4);
                    goto l1_166;
                 }
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_47,128);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 consume(3);
                 goto l1_138;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_46,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_15,136);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_65;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_44,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_21;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_129,80);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_17;
        }
        goto fail1;
l1_115: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_167;
                 }
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_47,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_32,176);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 consume(3);
                 goto l1_140;
              }
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_46,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_48,144);
              reset(&buf_12);
              appendarray(&buf_12,const_1_31,168);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_84;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_30,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_116: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    appendarray(&buf_13,const_1_123,48);
                    reset(&buf_2);
                    concat(&buf_2,&buf_3);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_158;
                 }
                 appendarray(&buf_14,const_1_122,24);
                 appendarray(&buf_13,const_1_78,8);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_122,24);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_143;
              }
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_78,8);
              reset(&buf_13);
              appendarray(&buf_13,const_1_41,56);
              reset(&buf_2);
              appendarray(&buf_2,const_1_130,40);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              concat(&buf_1,&buf_3);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_51;
           }
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_3);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_3);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_117: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_50,168);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    output(&buf_1);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    consume(4);
                    goto l1_158;
                 }
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_48,144);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_27,104);
                 concat(&buf_12,&buf_9);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 consume(3);
                 goto l1_143;
              }
              reset(&buf_14);
              appendarray(&buf_14,const_1_41,56);
              reset(&buf_13);
              appendarray(&buf_13,const_1_27,104);
              concat(&buf_12,&buf_20);
              appendarray(&buf_12,const_1_104,56);
              reset(&buf_3);
              appendarray(&buf_3,const_1_130,40);
              reset(&buf_2);
              appendarray(&buf_2,const_1_128,32);
              consume(2);
              goto l1_68;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_30,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_118: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_80,56);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_18,160);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_158;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_89,64);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 consume(3);
                 goto l1_124;
              }
              reset(&buf_14);
              appendarray(&buf_14,const_1_41,56);
              appendarray(&buf_13,const_1_89,64);
              appendarray(&buf_12,const_1_104,56);
              reset(&buf_3);
              appendarray(&buf_3,const_1_130,40);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_68;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           appendarray(&buf_13,const_1_92,104);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_13,const_1_88,104);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_119: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    appendarray(&buf_16,const_1_47,128);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_50,168);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_32,176);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_17,144);
                    reset(&buf_5);
                    appendarray(&buf_5,const_1_101,16);
                    reset(&buf_4);
                    appendarray(&buf_4,const_1_78,8);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_101,16);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_46,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_48,144);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_31,168);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_25,176);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 consume(3);
                 goto l1_152;
              }
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_44,96);
              reset(&buf_14);
              appendarray(&buf_14,const_1_28,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_30,144);
              reset(&buf_12);
              appendarray(&buf_12,const_1_24,168);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_78,8);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_84;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,152);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_120: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    appendarray(&buf_16,const_1_14,120);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_18,160);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_19,168);
                    appendarray(&buf_12,const_1_107,112);
                    reset(&buf_5);
                    appendarray(&buf_5,const_1_78,8);
                    reset(&buf_4);
                    appendarray(&buf_4,const_1_101,16);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_78,8);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_18,160);
                 appendarray(&buf_12,const_1_78,8);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_87,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_15,136);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_28,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_15,136);
              reset(&buf_9);
              appendarray(&buf_9,const_1_110,136);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_85;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           appendarray(&buf_12,const_1_109,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_101,16);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_111,112);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           appendarray(&buf_1,const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_121: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_20);
                    appendarray(&buf_20,const_1_12,96);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_50,168);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_41,56);
                    reset(&buf_9);
                    appendarray(&buf_9,const_1_94,136);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_160;
                 }
                 reset(&buf_21);
                 appendarray(&buf_21,const_1_29,128);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_46,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_48,144);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_33,192);
                 reset(&buf_10);
                 appendarray(&buf_10,const_1_93,128);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_154;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_28,120);
              reset(&buf_15);
              appendarray(&buf_15,const_1_42,72);
              reset(&buf_14);
              appendarray(&buf_14,const_1_44,96);
              reset(&buf_13);
              appendarray(&buf_13,const_1_28,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_41,56);
              reset(&buf_9);
              appendarray(&buf_9,const_1_92,104);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_130,40);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_66;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_53,160);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_56,152);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_122: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_20);
                    appendarray(&buf_20,const_1_12,96);
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_78,8);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_18,160);
                    reset(&buf_9);
                    appendarray(&buf_9,const_1_94,136);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_160;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_78,8);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 consume(3);
                 goto l1_139;
              }
              reset(&buf_21);
              appendarray(&buf_21,const_1_28,120);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_44,96);
              reset(&buf_14);
              appendarray(&buf_14,const_1_28,120);
              appendarray(&buf_13,const_1_78,8);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_10);
              appendarray(&buf_10,const_1_92,104);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_86;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_86,112);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_78,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_13,const_1_88,104);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_123: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_21);
                    appendarray(&buf_21,const_1_14,120);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_49,152);
                    reset(&buf_10);
                    appendarray(&buf_10,const_1_84,120);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_161;
                 }
                 reset(&buf_22);
                 appendarray(&buf_22,const_1_13,112);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_55,184);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_36,200);
                 reset(&buf_11);
                 appendarray(&buf_11,const_1_83,96);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 consume(3);
                 goto l1_155;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_54,176);
              reset(&buf_12);
              appendarray(&buf_12,const_1_33,192);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_53,160);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_56,152);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_124: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_21);
                    appendarray(&buf_21,const_1_14,120);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_17,144);
                    reset(&buf_10);
                    appendarray(&buf_10,const_1_84,120);
                    output(&buf_1);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_161;
                 }
                 reset(&buf_22);
                 appendarray(&buf_22,const_1_13,112);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_25,176);
                 concat(&buf_12,&buf_9);
                 appendarray(&buf_12,const_1_83,96);
                 reset(&buf_11);
                 appendarray(&buf_11,const_1_83,96);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_155;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_24,168);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_10,88);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,152);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           output(&buf_1);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_125: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_80,56);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_2);
                    concat(&buf_2,&buf_3);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_162;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_102,40);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 reset(&buf_2);
                 concat(&buf_2,&buf_3);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_142;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              reset(&buf_15);
              appendarray(&buf_15,const_1_73,136);
              appendarray(&buf_14,const_1_101,16);
              appendarray(&buf_13,const_1_90,80);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_89,64);
           reset(&buf_13);
           appendarray(&buf_13,const_1_72,120);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_3);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_100,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_76,112);
           reset(&buf_2);
           appendarray(&buf_2,const_1_133,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_3);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_126: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_62,184);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_35,160);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    output(&buf_1);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    consume(4);
                    goto l1_162;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_61,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_27,104);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 consume(3);
                 goto l1_142;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              reset(&buf_15);
              appendarray(&buf_15,const_1_73,136);
              reset(&buf_14);
              appendarray(&buf_14,const_1_60,152);
              reset(&buf_13);
              appendarray(&buf_13,const_1_38,184);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_72,120);
           reset(&buf_12);
           appendarray(&buf_12,const_1_37,168);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           output(&buf_1);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_76,112);
           reset(&buf_13);
           appendarray(&buf_13,const_1_39,160);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_133,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_127: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_96,120);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_32,176);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_162;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_89,64);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_31,168);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_142;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_30,144);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_44,96);
              reset(&buf_14);
              appendarray(&buf_14,const_1_73,136);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              reset(&buf_13);
              appendarray(&buf_13,const_1_30,144);
              reset(&buf_9);
              appendarray(&buf_9,const_1_98,144);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_85;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_97,128);
           reset(&buf_13);
           appendarray(&buf_13,const_1_72,120);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_78,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_76,112);
           appendarray(&buf_13,const_1_99,120);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_133,96);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_128: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_14);
                    concat(&buf_14,&buf_16);
                    appendarray(&buf_14,const_1_1,8);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    concat(&buf_2,&buf_4);
                    reset(&buf_1);
                    concat(&buf_1,&buf_3);
                    reset(&buf_3);
                    concat(&buf_3,&buf_5);
                    consume(4);
                    goto l1_151;
                 }
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_79,48);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_4,40);
                 reset(&buf_14);
                 concat(&buf_14,&buf_15);
                 reset(&buf_15);
                 concat(&buf_15,&buf_16);
                 appendarray(&buf_15,const_1_4,40);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_3);
                 reset(&buf_3);
                 concat(&buf_3,&buf_4);
                 reset(&buf_4);
                 concat(&buf_4,&buf_5);
                 consume(3);
                 goto l1_144;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_5,40);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_3,32);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_5,40);
              reset(&buf_15);
              concat(&buf_15,&buf_16);
              appendarray(&buf_15,const_1_3,32);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
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
              appendarray(&buf_5,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           concat(&buf_13,&buf_16);
           appendarray(&buf_13,const_1_2,16);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_5);
           appendarray(&buf_2,const_1_122,24);
           reset(&buf_1);
           concat(&buf_1,&buf_3);
           concat(&buf_1,&buf_4);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_134,8);
           reset(&buf_14);
           concat(&buf_14,&buf_16);
           appendarray(&buf_14,const_1_134,8);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           concat(&buf_2,&buf_4);
           reset(&buf_3);
           concat(&buf_3,&buf_5);
           appendarray(&buf_3,const_1_127,72);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_129: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_11,96);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    consume(4);
                    goto l1_164;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_14,120);
                 appendarray(&buf_12,const_1_125,112);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_13,112);
              appendarray(&buf_12,const_1_106,104);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           appendarray(&buf_12,const_1_83,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_78,8);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_130: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_156;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_47,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_15,136);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_46,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_15,136);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_73;
           }
           reset(&buf_12);
           appendarray(&buf_12,const_1_44,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_23;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_12);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_1);
           appendarray(&buf_1,const_1_129,80);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_18;
        }
        goto fail1;
l1_131: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    outputarray(const_1_122,24);
                    consume(4);
                    goto l1_156;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_47,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_66,152);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_46,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_48,144);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_132: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_16);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    output(&buf_1);
                    output(&buf_2);
                    output(&buf_3);
                    reset(&buf_2);
                    concat(&buf_2,&buf_5);
                    reset(&buf_1);
                    concat(&buf_1,&buf_4);
                    consume(4);
                    goto l1_146;
                 }
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_29,128);
                 reset(&buf_12);
                 concat(&buf_12,&buf_14);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_14);
                 concat(&buf_14,&buf_16);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_43,80);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_4);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_1);
                 concat(&buf_1,&buf_3);
                 reset(&buf_3);
                 concat(&buf_3,&buf_5);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_42,72);
              reset(&buf_14);
              concat(&buf_14,&buf_16);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_28,120);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              concat(&buf_1,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_5);
              appendarray(&buf_3,const_1_78,8);
              reset(&buf_2);
              concat(&buf_2,&buf_4);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_41,56);
           reset(&buf_12);
           appendarray(&buf_12,const_1_27,104);
           output(&buf_1);
           output(&buf_2);
           output(&buf_3);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           concat(&buf_1,&buf_4);
           concat(&buf_1,&buf_5);
           appendarray(&buf_1,const_1_78,8);
           consume(1);
           goto l1_22;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           concat(&buf_1,&buf_3);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           concat(&buf_2,&buf_5);
           appendarray(&buf_2,const_1_100,56);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_133: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_11,96);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    consume(4);
                    goto l1_165;
                 }
                 appendarray(&buf_13,const_1_78,8);
                 appendarray(&buf_12,const_1_125,112);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_141;
              }
              reset(&buf_21);
              appendarray(&buf_21,const_1_13,112);
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_13,112);
              appendarray(&buf_13,const_1_78,8);
              appendarray(&buf_12,const_1_106,104);
              reset(&buf_10);
              appendarray(&buf_10,const_1_83,96);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_86;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           appendarray(&buf_13,const_1_83,96);
           appendarray(&buf_12,const_1_83,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_134: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_19,168);
                    appendarray(&buf_12,const_1_105,64);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_18,160);
                 appendarray(&buf_12,const_1_78,8);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_94,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_15,136);
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_46,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_15,136);
              reset(&buf_9);
              appendarray(&buf_9,const_1_116,136);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_85;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           appendarray(&buf_12,const_1_114,112);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           appendarray(&buf_1,const_1_101,16);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_111,112);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           appendarray(&buf_1,const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_135: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_45,104);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_167;
                 }
                 reset(&buf_22);
                 appendarray(&buf_22,const_1_13,112);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_62,184);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_36,200);
                 reset(&buf_11);
                 appendarray(&buf_11,const_1_83,96);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 consume(3);
                 goto l1_155;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_61,176);
              reset(&buf_12);
              appendarray(&buf_12,const_1_33,192);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_60,152);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_56,152);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_136: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    output(&buf_1);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_167;
                 }
                 reset(&buf_22);
                 appendarray(&buf_22,const_1_13,112);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_32,176);
                 concat(&buf_12,&buf_9);
                 appendarray(&buf_12,const_1_83,96);
                 reset(&buf_11);
                 appendarray(&buf_11,const_1_83,96);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_155;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_31,168);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_10,88);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_30,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_137: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    appendarray(&buf_13,const_1_123,48);
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    concat(&buf_2,&buf_4);
                    reset(&buf_1);
                    concat(&buf_1,&buf_3);
                    consume(4);
                    goto l1_158;
                 }
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_78,8);
                 reset(&buf_14);
                 concat(&buf_14,&buf_15);
                 appendarray(&buf_14,const_1_122,24);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_3);
                 reset(&buf_3);
                 concat(&buf_3,&buf_4);
                 consume(3);
                 goto l1_143;
              }
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_78,8);
              reset(&buf_14);
              appendarray(&buf_14,const_1_41,56);
              appendarray(&buf_12,const_1_104,56);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              concat(&buf_2,&buf_4);
              reset(&buf_3);
              appendarray(&buf_3,const_1_130,40);
              consume(2);
              goto l1_68;
           }
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_79,48);
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           appendarray(&buf_12,const_1_79,48);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           concat(&buf_2,&buf_4);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_77,48);
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_12,const_1_77,48);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           concat(&buf_2,&buf_4);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_138: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    concat(&buf_16,&buf_17);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_18,160);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_17,144);
                    reset(&buf_4);
                    concat(&buf_4,&buf_5);
                    reset(&buf_5);
                    concat(&buf_5,&buf_6);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_78,8);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_43,80);
                 appendarray(&buf_17,const_1_102,40);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_29,128);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_25,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_101,16);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              concat(&buf_15,&buf_17);
              appendarray(&buf_15,const_1_101,16);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_101,16);
              reset(&buf_14);
              appendarray(&buf_14,const_1_28,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_24,168);
              reset(&buf_4);
              concat(&buf_4,&buf_6);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              concat(&buf_3,&buf_5);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_84;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,152);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_5);
           concat(&buf_2,&buf_6);
           appendarray(&buf_2,const_1_78,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           concat(&buf_2,&buf_5);
           concat(&buf_2,&buf_6);
           appendarray(&buf_2,const_1_100,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_139: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    appendarray(&buf_16,const_1_47,128);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_50,168);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_32,176);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_17,144);
                    reset(&buf_5);
                    appendarray(&buf_5,const_1_101,16);
                    reset(&buf_4);
                    appendarray(&buf_4,const_1_78,8);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_101,16);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    output(&buf_1);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_43,80);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_46,120);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_29,128);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_48,144);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_31,168);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_25,176);
                 concat(&buf_12,&buf_9);
                 appendarray(&buf_12,const_1_95,152);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_101,16);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_30,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_24,168);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_30,144);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,152);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           output(&buf_1);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_140: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    concat(&buf_16,&buf_17);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_13);
                    concat(&buf_13,&buf_14);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_18,160);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_67,160);
                    reset(&buf_4);
                    concat(&buf_4,&buf_5);
                    reset(&buf_5);
                    concat(&buf_5,&buf_6);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_78,8);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_16);
                 concat(&buf_16,&buf_17);
                 appendarray(&buf_16,const_1_102,40);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_102,40);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_87,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_4);
                 concat(&buf_4,&buf_5);
                 reset(&buf_5);
                 concat(&buf_5,&buf_6);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_16);
              concat(&buf_16,&buf_17);
              appendarray(&buf_16,const_1_101,16);
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_70,184);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_4);
              concat(&buf_4,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_6);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_69,168);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_5);
           concat(&buf_2,&buf_6);
           appendarray(&buf_2,const_1_78,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_132,48);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_71,160);
           reset(&buf_2);
           concat(&buf_2,&buf_5);
           concat(&buf_2,&buf_6);
           appendarray(&buf_2,const_1_100,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_132,48);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_141: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    appendarray(&buf_16,const_1_14,120);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_18,160);
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_107,112);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_19,168);
                    reset(&buf_5);
                    appendarray(&buf_5,const_1_78,8);
                    reset(&buf_4);
                    appendarray(&buf_4,const_1_101,16);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_78,8);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_78,8);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_18,160);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_87,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_15,136);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_28,120);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              reset(&buf_13);
              appendarray(&buf_13,const_1_15,136);
              reset(&buf_9);
              appendarray(&buf_9,const_1_110,136);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_85;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_12);
           concat(&buf_12,&buf_13);
           appendarray(&buf_12,const_1_109,120);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           reset(&buf_1);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_101,16);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_13,const_1_111,112);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           appendarray(&buf_2,const_1_101,16);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_142: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_20);
                    appendarray(&buf_20,const_1_12,96);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_50,168);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_41,56);
                    reset(&buf_9);
                    appendarray(&buf_9,const_1_94,136);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    consume(4);
                    goto l1_160;
                 }
                 reset(&buf_21);
                 appendarray(&buf_21,const_1_29,128);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_46,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_48,144);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_10);
                 appendarray(&buf_10,const_1_93,128);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 consume(3);
                 goto l1_154;
              }
              reset(&buf_21);
              appendarray(&buf_21,const_1_28,120);
              reset(&buf_16);
              appendarray(&buf_16,const_1_42,72);
              reset(&buf_15);
              appendarray(&buf_15,const_1_44,96);
              reset(&buf_14);
              appendarray(&buf_14,const_1_28,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_41,56);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_10);
              appendarray(&buf_10,const_1_92,104);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_130,40);
              consume(2);
              goto l1_86;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_53,160);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_56,152);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_143: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_21);
                    appendarray(&buf_21,const_1_14,120);
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_10);
                    appendarray(&buf_10,const_1_84,120);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_1);
                    concat(&buf_1,&buf_3);
                    consume(4);
                    goto l1_161;
                 }
                 reset(&buf_22);
                 appendarray(&buf_22,const_1_13,112);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_83,96);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_4,40);
                 reset(&buf_11);
                 appendarray(&buf_11,const_1_83,96);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_3);
                 consume(3);
                 goto l1_155;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_10,88);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_3,32);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_101,16);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_122,24);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_134,8);
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           appendarray(&buf_2,const_1_122,24);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_144: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    appendarray(&buf_12,const_1_80,56);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    concat(&buf_2,&buf_4);
                    reset(&buf_1);
                    concat(&buf_1,&buf_3);
                    consume(4);
                    goto l1_162;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_10,88);
                 reset(&buf_13);
                 concat(&buf_13,&buf_15);
                 appendarray(&buf_13,const_1_102,40);
                 reset(&buf_12);
                 concat(&buf_12,&buf_14);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_91,88);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_4);
                 reset(&buf_1);
                 concat(&buf_1,&buf_3);
                 consume(3);
                 goto l1_142;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              appendarray(&buf_16,const_1_44,96);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_90,80);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_15);
              appendarray(&buf_15,const_1_73,136);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_72,120);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_89,64);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           reset(&buf_1);
           concat(&buf_1,&buf_3);
           concat(&buf_1,&buf_4);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_100,56);
           reset(&buf_14);
           appendarray(&buf_14,const_1_76,112);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           concat(&buf_2,&buf_4);
           reset(&buf_3);
           appendarray(&buf_3,const_1_133,96);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_145: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_16,144);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_164;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_14,120);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_15,136);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_13,112);
              reset(&buf_12);
              appendarray(&buf_12,const_1_66,152);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_130,40);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_48,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_146: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    output(&buf_2);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_156;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_47,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_15,136);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_46,120);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              appendarray(&buf_1,const_1_78,8);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           appendarray(&buf_12,const_1_79,48);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_78,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           appendarray(&buf_12,const_1_77,48);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_78,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_147: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_169;
                 }
                 reset(&buf_21);
                 appendarray(&buf_21,const_1_14,120);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_14,120);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_15,136);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_10);
                 appendarray(&buf_10,const_1_84,120);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_154;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_13,112);
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_13,112);
              reset(&buf_12);
              appendarray(&buf_12,const_1_41,56);
              reset(&buf_9);
              appendarray(&buf_9,const_1_83,96);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_130,40);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_66;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_48,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_148: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_51,176);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_47,128);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_50,168);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_32,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_46,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_48,144);
              reset(&buf_12);
              appendarray(&buf_12,const_1_31,168);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_84;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_30,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_149: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_51,176);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_65,112);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_50,168);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_94,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_75,184);
              reset(&buf_12);
              appendarray(&buf_12,const_1_33,192);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_74,160);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_132,48);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_71,160);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_132,48);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_150: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_13);
                    appendarray(&buf_12,const_1_105,64);
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_19,168);
                    output(&buf_1);
                    reset(&buf_1);
                    concat(&buf_1,&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_78,8);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_18,160);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_94,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_20);
              appendarray(&buf_20,const_1_15,136);
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_46,120);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              reset(&buf_13);
              appendarray(&buf_13,const_1_15,136);
              reset(&buf_9);
              appendarray(&buf_9,const_1_116,136);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_85;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           appendarray(&buf_13,const_1_114,112);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           appendarray(&buf_2,const_1_101,16);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_13,const_1_111,112);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           appendarray(&buf_2,const_1_101,16);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_151: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_1);
                    concat(&buf_1,&buf_3);
                    consume(4);
                    goto l1_167;
                 }
                 reset(&buf_22);
                 appendarray(&buf_22,const_1_13,112);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_83,96);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_82,80);
                 reset(&buf_11);
                 appendarray(&buf_11,const_1_83,96);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_3);
                 consume(3);
                 goto l1_155;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_10,88);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_81,72);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              concat(&buf_2,&buf_3);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_79,48);
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           appendarray(&buf_12,const_1_79,48);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           appendarray(&buf_2,const_1_122,24);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_77,48);
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_12,const_1_77,48);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_3);
           appendarray(&buf_2,const_1_122,24);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_152: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_14);
                    concat(&buf_14,&buf_16);
                    appendarray(&buf_14,const_1_123,48);
                    reset(&buf_16);
                    concat(&buf_16,&buf_18);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_4);
                    concat(&buf_4,&buf_6);
                    reset(&buf_3);
                    concat(&buf_3,&buf_5);
                    reset(&buf_5);
                    concat(&buf_5,&buf_7);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_43,80);
                 reset(&buf_17);
                 concat(&buf_17,&buf_18);
                 appendarray(&buf_17,const_1_102,40);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_4,40);
                 reset(&buf_14);
                 concat(&buf_14,&buf_15);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_15);
                 concat(&buf_15,&buf_16);
                 appendarray(&buf_15,const_1_122,24);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_29,128);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_101,16);
                 reset(&buf_4);
                 concat(&buf_4,&buf_5);
                 reset(&buf_5);
                 concat(&buf_5,&buf_6);
                 reset(&buf_6);
                 concat(&buf_6,&buf_7);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              concat(&buf_16,&buf_18);
              appendarray(&buf_16,const_1_101,16);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_3,32);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_4);
              concat(&buf_4,&buf_6);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_78,8);
              concat(&buf_3,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_7);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_6);
           concat(&buf_2,&buf_7);
           appendarray(&buf_2,const_1_78,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_5);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_2);
           concat(&buf_2,&buf_6);
           concat(&buf_2,&buf_7);
           appendarray(&buf_2,const_1_100,56);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_5);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_153: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_14);
                    concat(&buf_14,&buf_16);
                    appendarray(&buf_14,const_1_123,48);
                    reset(&buf_16);
                    concat(&buf_16,&buf_18);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_17,144);
                    reset(&buf_3);
                    concat(&buf_3,&buf_5);
                    reset(&buf_5);
                    concat(&buf_5,&buf_7);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    concat(&buf_2,&buf_4);
                    reset(&buf_4);
                    concat(&buf_4,&buf_6);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_43,80);
                 reset(&buf_17);
                 concat(&buf_17,&buf_18);
                 appendarray(&buf_17,const_1_102,40);
                 reset(&buf_14);
                 concat(&buf_14,&buf_15);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_15);
                 concat(&buf_15,&buf_16);
                 appendarray(&buf_15,const_1_122,24);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_29,128);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_25,176);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_101,16);
                 reset(&buf_3);
                 concat(&buf_3,&buf_4);
                 reset(&buf_4);
                 concat(&buf_4,&buf_5);
                 reset(&buf_5);
                 concat(&buf_5,&buf_6);
                 reset(&buf_6);
                 concat(&buf_6,&buf_7);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              concat(&buf_16,&buf_18);
              appendarray(&buf_16,const_1_101,16);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_13);
              appendarray(&buf_13,const_1_24,168);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_3);
              concat(&buf_3,&buf_4);
              concat(&buf_3,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_7);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              concat(&buf_4,&buf_6);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_23,152);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_6);
           concat(&buf_2,&buf_7);
           appendarray(&buf_2,const_1_78,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_78,8);
           concat(&buf_1,&buf_4);
           concat(&buf_1,&buf_5);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           concat(&buf_3,&buf_6);
           concat(&buf_3,&buf_7);
           appendarray(&buf_3,const_1_100,56);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_78,8);
           concat(&buf_2,&buf_4);
           concat(&buf_2,&buf_5);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_154: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    concat(&buf_12,&buf_14);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_14);
                    concat(&buf_14,&buf_16);
                    appendarray(&buf_14,const_1_123,48);
                    reset(&buf_16);
                    concat(&buf_16,&buf_18);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_4);
                    concat(&buf_4,&buf_6);
                    reset(&buf_3);
                    concat(&buf_3,&buf_5);
                    reset(&buf_5);
                    concat(&buf_5,&buf_7);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    output(&buf_1);
                    outputarray(const_1_122,24);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_43,80);
                 reset(&buf_17);
                 concat(&buf_17,&buf_18);
                 appendarray(&buf_17,const_1_102,40);
                 reset(&buf_13);
                 concat(&buf_13,&buf_14);
                 appendarray(&buf_13,const_1_4,40);
                 reset(&buf_14);
                 concat(&buf_14,&buf_15);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_15);
                 concat(&buf_15,&buf_16);
                 appendarray(&buf_15,const_1_122,24);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_29,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 concat(&buf_12,&buf_10);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_101,16);
                 reset(&buf_4);
                 concat(&buf_4,&buf_5);
                 reset(&buf_5);
                 concat(&buf_5,&buf_6);
                 reset(&buf_6);
                 concat(&buf_6,&buf_7);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              concat(&buf_16,&buf_18);
              appendarray(&buf_16,const_1_101,16);
              reset(&buf_13);
              concat(&buf_13,&buf_14);
              appendarray(&buf_13,const_1_3,32);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_12);
              appendarray(&buf_12,const_1_41,56);
              concat(&buf_12,&buf_21);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_4);
              concat(&buf_4,&buf_6);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_78,8);
              concat(&buf_3,&buf_5);
              reset(&buf_5);
              concat(&buf_5,&buf_7);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           concat(&buf_12,&buf_14);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_6);
           concat(&buf_2,&buf_7);
           appendarray(&buf_2,const_1_78,8);
           output(&buf_1);
           outputarray(const_1_122,24);
           reset(&buf_1);
           appendarray(&buf_1,const_1_122,24);
           concat(&buf_1,&buf_5);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           concat(&buf_13,&buf_14);
           appendarray(&buf_13,const_1_134,8);
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           concat(&buf_3,&buf_6);
           concat(&buf_3,&buf_7);
           appendarray(&buf_3,const_1_100,56);
           reset(&buf_2);
           appendarray(&buf_2,const_1_122,24);
           concat(&buf_2,&buf_5);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_155: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_16);
                    concat(&buf_16,&buf_18);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_14);
                    appendarray(&buf_14,const_1_18,160);
                    reset(&buf_13);
                    concat(&buf_13,&buf_15);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_41,56);
                    concat(&buf_12,&buf_11);
                    appendarray(&buf_12,const_1_1,8);
                    reset(&buf_5);
                    concat(&buf_5,&buf_7);
                    reset(&buf_4);
                    concat(&buf_4,&buf_6);
                    reset(&buf_3);
                    appendarray(&buf_3,const_1_78,8);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_20);
                 concat(&buf_20,&buf_22);
                 appendarray(&buf_20,const_1_122,24);
                 reset(&buf_16);
                 concat(&buf_16,&buf_18);
                 appendarray(&buf_16,const_1_102,40);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_43,80);
                 reset(&buf_13);
                 concat(&buf_13,&buf_15);
                 appendarray(&buf_13,const_1_102,40);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_29,128);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 reset(&buf_9);
                 concat(&buf_9,&buf_11);
                 appendarray(&buf_9,const_1_4,40);
                 reset(&buf_5);
                 concat(&buf_5,&buf_7);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_4);
                 concat(&buf_4,&buf_6);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_16);
              concat(&buf_16,&buf_18);
              appendarray(&buf_16,const_1_101,16);
              reset(&buf_14);
              concat(&buf_14,&buf_15);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_41,56);
              concat(&buf_13,&buf_11);
              appendarray(&buf_13,const_1_3,32);
              reset(&buf_5);
              concat(&buf_5,&buf_7);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              concat(&buf_4,&buf_6);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           appendarray(&buf_12,const_1_41,56);
           concat(&buf_12,&buf_11);
           appendarray(&buf_12,const_1_2,16);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           output(&buf_1);
           output(&buf_2);
           reset(&buf_2);
           concat(&buf_2,&buf_6);
           concat(&buf_2,&buf_7);
           appendarray(&buf_2,const_1_78,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_132,48);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_41,56);
           concat(&buf_13,&buf_11);
           appendarray(&buf_13,const_1_134,8);
           appendarray(&buf_12,const_1_134,8);
           reset(&buf_3);
           concat(&buf_3,&buf_6);
           concat(&buf_3,&buf_7);
           appendarray(&buf_3,const_1_100,56);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_156: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_16,144);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_164;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_14,120);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_15,136);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_13,112);
              reset(&buf_12);
              appendarray(&buf_12,const_1_15,136);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              outputarray(const_1_101,16);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_48,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_157: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    consume(4);
                    goto l1_172;
                 }
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_14,120);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_15,136);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_18,160);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_19,168);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_152;
              }
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_13,112);
              reset(&buf_13);
              appendarray(&buf_13,const_1_15,136);
              reset(&buf_12);
              appendarray(&buf_12,const_1_18,160);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_4);
              appendarray(&buf_4,const_1_122,24);
              reset(&buf_3);
              appendarray(&buf_3,const_1_78,8);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              reset(&buf_1);
              appendarray(&buf_1,const_1_78,8);
              outputarray(const_1_78,8);
              consume(2);
              goto l1_84;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_15,136);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_158: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_11,96);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    output(&buf_2);
                    consume(4);
                    goto l1_169;
                 }
                 reset(&buf_21);
                 appendarray(&buf_21,const_1_14,120);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_14,120);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_15,136);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_10);
                 appendarray(&buf_10,const_1_84,120);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 consume(3);
                 goto l1_154;
              }
              reset(&buf_21);
              appendarray(&buf_21,const_1_13,112);
              reset(&buf_16);
              appendarray(&buf_16,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_10,88);
              reset(&buf_14);
              appendarray(&buf_14,const_1_13,112);
              reset(&buf_13);
              appendarray(&buf_13,const_1_41,56);
              appendarray(&buf_12,const_1_106,104);
              reset(&buf_10);
              appendarray(&buf_10,const_1_83,96);
              reset(&buf_5);
              appendarray(&buf_5,const_1_78,8);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_130,40);
              consume(2);
              goto l1_86;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_48,144);
           appendarray(&buf_12,const_1_83,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_159: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_19,168);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_47,128);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_32,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_31,168);
              reset(&buf_12);
              appendarray(&buf_12,const_1_20,184);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_44,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_30,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_160: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           output(&buf_20);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_51,176);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_78,8);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_47,128);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_50,168);
                 reset(&buf_12);
                 concat(&buf_12,&buf_13);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_32,176);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 concat(&buf_1,&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_13);
              appendarray(&buf_13,const_1_31,168);
              concat(&buf_12,&buf_9);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_30,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           concat(&buf_12,&buf_20);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_161: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_19,168);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_78,8);
                    output(&buf_1);
                    outputarray(const_1_122,24);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_101,16);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_47,128);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_32,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 concat(&buf_12,&buf_10);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_31,168);
              reset(&buf_12);
              appendarray(&buf_12,const_1_41,56);
              concat(&buf_12,&buf_21);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_101,16);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_30,144);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_162: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    appendarray(&buf_13,const_1_51,176);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_65,112);
                    output(&buf_1);
                    output(&buf_2);
                    reset(&buf_2);
                    appendarray(&buf_2,const_1_101,16);
                    reset(&buf_1);
                    appendarray(&buf_1,const_1_122,24);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_20);
                 appendarray(&buf_20,const_1_15,136);
                 reset(&buf_18);
                 appendarray(&buf_18,const_1_9,72);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_47,128);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_50,168);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_41,56);
                 reset(&buf_9);
                 appendarray(&buf_9,const_1_94,136);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_101,16);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_153;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              appendarray(&buf_14,const_1_48,144);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_75,184);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              reset(&buf_2);
              appendarray(&buf_2,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_74,160);
           appendarray(&buf_12,const_1_79,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_71,160);
           appendarray(&buf_12,const_1_77,48);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           appendarray(&buf_2,const_1_132,48);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_163: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_14);
                    concat(&buf_14,&buf_17);
                    appendarray(&buf_14,const_1_123,48);
                    reset(&buf_13);
                    concat(&buf_13,&buf_16);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_16);
                    concat(&buf_16,&buf_19);
                    appendarray(&buf_16,const_1_103,48);
                    reset(&buf_12);
                    concat(&buf_12,&buf_15);
                    appendarray(&buf_12,const_1_1,8);
                    output(&buf_1);
                    output(&buf_2);
                    output(&buf_3);
                    reset(&buf_3);
                    concat(&buf_3,&buf_6);
                    reset(&buf_2);
                    concat(&buf_2,&buf_5);
                    reset(&buf_5);
                    concat(&buf_5,&buf_8);
                    reset(&buf_1);
                    concat(&buf_1,&buf_4);
                    reset(&buf_4);
                    concat(&buf_4,&buf_7);
                    consume(4);
                    goto l1_168;
                 }
                 reset(&buf_13);
                 concat(&buf_13,&buf_15);
                 appendarray(&buf_13,const_1_4,40);
                 reset(&buf_15);
                 concat(&buf_15,&buf_17);
                 appendarray(&buf_15,const_1_122,24);
                 reset(&buf_17);
                 concat(&buf_17,&buf_19);
                 appendarray(&buf_17,const_1_102,40);
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_43,80);
                 reset(&buf_12);
                 concat(&buf_12,&buf_14);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_14);
                 concat(&buf_14,&buf_16);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_29,128);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_4);
                 reset(&buf_4);
                 concat(&buf_4,&buf_6);
                 reset(&buf_6);
                 concat(&buf_6,&buf_8);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_101,16);
                 reset(&buf_1);
                 concat(&buf_1,&buf_3);
                 reset(&buf_3);
                 concat(&buf_3,&buf_5);
                 reset(&buf_5);
                 concat(&buf_5,&buf_7);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_42,72);
              reset(&buf_14);
              concat(&buf_14,&buf_16);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_16);
              concat(&buf_16,&buf_19);
              appendarray(&buf_16,const_1_101,16);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              concat(&buf_13,&buf_15);
              appendarray(&buf_13,const_1_3,32);
              reset(&buf_15);
              appendarray(&buf_15,const_1_28,120);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              concat(&buf_1,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_5);
              concat(&buf_3,&buf_6);
              reset(&buf_6);
              appendarray(&buf_6,const_1_101,16);
              reset(&buf_5);
              concat(&buf_5,&buf_8);
              appendarray(&buf_5,const_1_78,8);
              reset(&buf_2);
              concat(&buf_2,&buf_4);
              reset(&buf_4);
              concat(&buf_4,&buf_7);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_41,56);
           reset(&buf_13);
           appendarray(&buf_13,const_1_27,104);
           reset(&buf_12);
           concat(&buf_12,&buf_15);
           appendarray(&buf_12,const_1_2,16);
           output(&buf_1);
           output(&buf_2);
           output(&buf_3);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_7);
           concat(&buf_2,&buf_8);
           appendarray(&buf_2,const_1_78,8);
           reset(&buf_1);
           concat(&buf_1,&buf_4);
           concat(&buf_1,&buf_5);
           concat(&buf_1,&buf_6);
           consume(1);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           concat(&buf_13,&buf_15);
           appendarray(&buf_13,const_1_134,8);
           appendarray(&buf_12,const_1_134,8);
           concat(&buf_1,&buf_2);
           concat(&buf_1,&buf_3);
           reset(&buf_3);
           concat(&buf_3,&buf_7);
           concat(&buf_3,&buf_8);
           appendarray(&buf_3,const_1_100,56);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           concat(&buf_2,&buf_5);
           concat(&buf_2,&buf_6);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_164: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_16,144);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_164;
                 }
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_9,72);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_13,112);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_14,120);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_15,136);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_132;
              }
              reset(&buf_15);
              appendarray(&buf_15,const_1_8,64);
              reset(&buf_14);
              appendarray(&buf_14,const_1_10,88);
              reset(&buf_13);
              appendarray(&buf_13,const_1_13,112);
              reset(&buf_12);
              appendarray(&buf_12,const_1_15,136);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              outputarray(const_1_101,16);
              consume(2);
              goto l1_73;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_15,136);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_32;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_27;
        }
        goto fail1;
l1_165: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_16,144);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    consume(4);
                    goto l1_172;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_19,168);
                 appendarray(&buf_12,const_1_126,160);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_18,160);
              appendarray(&buf_12,const_1_108,152);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              appendarray(&buf_1,const_1_78,8);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_15,136);
           appendarray(&buf_12,const_1_85,144);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_78,8);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_166: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_101,16);
                    consume(4);
                    goto l1_171;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_51,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 outputarray(const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_50,168);
              reset(&buf_12);
              appendarray(&buf_12,const_1_20,184);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              reset(&buf_1);
              appendarray(&buf_1,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_13);
           appendarray(&buf_13,const_1_10,88);
           reset(&buf_12);
           appendarray(&buf_12,const_1_48,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_30;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_13);
           appendarray(&buf_13,const_1_40,96);
           reset(&buf_12);
           appendarray(&buf_12,const_1_26,144);
           reset(&buf_2);
           appendarray(&buf_2,const_1_129,80);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_101,16);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_167: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_11,96);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    outputarray(const_1_122,24);
                    consume(4);
                    goto l1_171;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_51,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_68,200);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 output(&buf_1);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_122,24);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_50,168);
              reset(&buf_12);
              appendarray(&buf_12,const_1_52,192);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              output(&buf_1);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_48,144);
           appendarray(&buf_12,const_1_83,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           appendarray(&buf_1,const_1_122,24);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_168: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_6,48);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    reset(&buf_13);
                    concat(&buf_13,&buf_16);
                    appendarray(&buf_13,const_1_103,48);
                    reset(&buf_12);
                    appendarray(&buf_12,const_1_12,96);
                    output(&buf_1);
                    output(&buf_2);
                    output(&buf_3);
                    reset(&buf_2);
                    concat(&buf_2,&buf_5);
                    reset(&buf_1);
                    concat(&buf_1,&buf_4);
                    consume(4);
                    goto l1_170;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_32,176);
                 reset(&buf_12);
                 concat(&buf_12,&buf_14);
                 appendarray(&buf_12,const_1_122,24);
                 reset(&buf_14);
                 concat(&buf_14,&buf_16);
                 appendarray(&buf_14,const_1_102,40);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_47,128);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 concat(&buf_2,&buf_4);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_78,8);
                 reset(&buf_1);
                 concat(&buf_1,&buf_3);
                 reset(&buf_3);
                 concat(&buf_3,&buf_5);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_101,16);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_15);
              appendarray(&buf_15,const_1_46,120);
              reset(&buf_14);
              concat(&buf_14,&buf_16);
              appendarray(&buf_14,const_1_101,16);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_31,168);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              concat(&buf_1,&buf_3);
              reset(&buf_3);
              concat(&buf_3,&buf_5);
              appendarray(&buf_3,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_2);
              concat(&buf_2,&buf_4);
              reset(&buf_4);
              appendarray(&buf_4,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_44,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_30,144);
           appendarray(&buf_12,const_1_79,48);
           concat(&buf_1,&buf_2);
           concat(&buf_1,&buf_3);
           reset(&buf_3);
           appendarray(&buf_3,const_1_130,40);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           concat(&buf_2,&buf_5);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           appendarray(&buf_12,const_1_77,48);
           concat(&buf_1,&buf_2);
           concat(&buf_1,&buf_3);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           concat(&buf_2,&buf_4);
           concat(&buf_2,&buf_5);
           appendarray(&buf_2,const_1_78,8);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_169: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_21,192);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_172;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_19,168);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_18,160);
              reset(&buf_12);
              appendarray(&buf_12,const_1_68,200);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_130,40);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_15,136);
           reset(&buf_12);
           appendarray(&buf_12,const_1_52,192);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           reset(&buf_12);
           appendarray(&buf_12,const_1_22,192);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_170: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_12);
           outputarray(const_1_11,96);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    output(&buf_1);
                    output(&buf_2);
                    outputarray(const_1_78,8);
                    consume(4);
                    goto l1_171;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_51,176);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 output(&buf_1);
                 output(&buf_2);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_101,16);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_78,8);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_12);
              concat(&buf_12,&buf_13);
              appendarray(&buf_12,const_1_101,16);
              reset(&buf_13);
              appendarray(&buf_13,const_1_50,168);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              output(&buf_1);
              reset(&buf_1);
              concat(&buf_1,&buf_2);
              appendarray(&buf_1,const_1_78,8);
              reset(&buf_2);
              appendarray(&buf_2,const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_48,144);
           appendarray(&buf_12,const_1_83,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_78,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_130,40);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           appendarray(&buf_12,const_1_40,96);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_78,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_171: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_21,192);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_172;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_19,168);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_18,160);
              reset(&buf_12);
              appendarray(&buf_12,const_1_20,184);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              outputarray(const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_15,136);
           reset(&buf_12);
           appendarray(&buf_12,const_1_52,192);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_130,40);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           reset(&buf_12);
           appendarray(&buf_12,const_1_22,192);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_35;
        }
        goto fail1;
l1_172: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_21,192);
           consume(1);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == 'a') && 1)))
        {
           if (((avail >= 2) && ((next[1] == 'a') && 1)))
           {
              if (((avail >= 3) && ((next[2] == 'a') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == 'a') && 1)))
                 {
                    outputarray(const_1_128,32);
                    consume(4);
                    goto l1_172;
                 }
                 reset(&buf_19);
                 appendarray(&buf_19,const_1_9,72);
                 reset(&buf_17);
                 appendarray(&buf_17,const_1_13,112);
                 reset(&buf_16);
                 appendarray(&buf_16,const_1_14,120);
                 reset(&buf_15);
                 appendarray(&buf_15,const_1_15,136);
                 reset(&buf_14);
                 appendarray(&buf_14,const_1_18,160);
                 reset(&buf_13);
                 appendarray(&buf_13,const_1_19,168);
                 reset(&buf_12);
                 appendarray(&buf_12,const_1_20,184);
                 reset(&buf_8);
                 appendarray(&buf_8,const_1_78,8);
                 reset(&buf_7);
                 appendarray(&buf_7,const_1_101,16);
                 reset(&buf_6);
                 appendarray(&buf_6,const_1_78,8);
                 reset(&buf_5);
                 appendarray(&buf_5,const_1_78,8);
                 reset(&buf_4);
                 appendarray(&buf_4,const_1_101,16);
                 reset(&buf_3);
                 appendarray(&buf_3,const_1_78,8);
                 reset(&buf_2);
                 appendarray(&buf_2,const_1_78,8);
                 reset(&buf_1);
                 appendarray(&buf_1,const_1_101,16);
                 outputarray(const_1_122,24);
                 consume(3);
                 goto l1_163;
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_8,64);
              reset(&buf_16);
              appendarray(&buf_16,const_1_10,88);
              reset(&buf_15);
              appendarray(&buf_15,const_1_13,112);
              reset(&buf_14);
              appendarray(&buf_14,const_1_15,136);
              reset(&buf_13);
              appendarray(&buf_13,const_1_18,160);
              reset(&buf_12);
              appendarray(&buf_12,const_1_20,184);
              reset(&buf_6);
              appendarray(&buf_6,const_1_78,8);
              reset(&buf_5);
              appendarray(&buf_5,const_1_122,24);
              reset(&buf_4);
              appendarray(&buf_4,const_1_78,8);
              reset(&buf_3);
              appendarray(&buf_3,const_1_122,24);
              reset(&buf_2);
              appendarray(&buf_2,const_1_78,8);
              reset(&buf_1);
              appendarray(&buf_1,const_1_122,24);
              outputarray(const_1_101,16);
              consume(2);
              goto l1_105;
           }
           reset(&buf_14);
           appendarray(&buf_14,const_1_10,88);
           reset(&buf_13);
           appendarray(&buf_13,const_1_15,136);
           reset(&buf_12);
           appendarray(&buf_12,const_1_20,184);
           reset(&buf_3);
           appendarray(&buf_3,const_1_128,32);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           outputarray(const_1_78,8);
           consume(1);
           goto l1_39;
        }
        if (((avail >= 1) && ((next[0] == 'b') && 1)))
        {
           reset(&buf_14);
           appendarray(&buf_14,const_1_40,96);
           reset(&buf_13);
           appendarray(&buf_13,const_1_26,144);
           reset(&buf_12);
           appendarray(&buf_12,const_1_22,192);
           reset(&buf_3);
           appendarray(&buf_3,const_1_129,80);
           reset(&buf_2);
           appendarray(&buf_2,const_1_128,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_128,32);
           consume(1);
           goto l1_35;
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
