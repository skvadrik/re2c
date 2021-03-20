
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
buffer_t buf_23;
buffer_t buf_24;
buffer_t buf_25;
buffer_t buf_26;
buffer_t buf_27;
buffer_t buf_28;
buffer_t buf_29;
buffer_t buf_30;
buffer_t buf_31;
buffer_t buf_32;
buffer_t buf_33;
buffer_t buf_34;
buffer_t buf_35;
buffer_t buf_36;
buffer_t buf_37;
buffer_t buf_38;
buffer_t buf_39;
buffer_t buf_40;
buffer_t buf_41;
buffer_t buf_42;
buffer_t buf_43;
buffer_t buf_44;
buffer_t buf_45;
buffer_t buf_46;
buffer_t buf_47;
buffer_t buf_48;
buffer_t buf_49;
buffer_t buf_50;
buffer_t buf_51;
buffer_t buf_52;
buffer_t buf_53;
buffer_t buf_54;
buffer_t buf_55;
buffer_t buf_56;
buffer_t buf_57;
buffer_t buf_58;
buffer_t buf_59;
buffer_t buf_60;
buffer_t buf_61;
buffer_t buf_62;
buffer_t buf_63;
buffer_t buf_64;
buffer_t buf_65;
buffer_t buf_66;
buffer_t buf_67;
buffer_t buf_68;
// \xa
const buffer_unit_t const_1_0[1] = {0xa};
// \xa\xa
const buffer_unit_t const_1_1[2] = {0xa,0xa};
// \xafragment: 
const buffer_unit_t const_1_2[11] = {0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// \xapath-1: \xa\xa
const buffer_unit_t const_1_3[11] = {0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0xa};
// \xapath-1: \xafragment: 
const buffer_unit_t const_1_4[20] = {0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// \xapath-1: \xaquery: 
const buffer_unit_t const_1_5[17] = {0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// \xapath-1: /
const buffer_unit_t const_1_6[10] = {0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0x2f};
// \xaport: 
const buffer_unit_t const_1_7[7] = {0xa,0x70,0x6f,0x72,0x74,0x3a,0x20};
// \xaquery: 
const buffer_unit_t const_1_8[8] = {0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// .
const buffer_unit_t const_1_9[1] = {0x2e};
// /
const buffer_unit_t const_1_10[1] = {0x2f};
// 0
const buffer_unit_t const_1_11[1] = {0x30};
// 0\xa
const buffer_unit_t const_1_12[2] = {0x30,0xa};
// 0.
const buffer_unit_t const_1_13[2] = {0x30,0x2e};
// 0:
const buffer_unit_t const_1_14[2] = {0x30,0x3a};
// 1
const buffer_unit_t const_1_15[1] = {0x31};
// 1\xa
const buffer_unit_t const_1_16[2] = {0x31,0xa};
// 2
const buffer_unit_t const_1_17[1] = {0x32};
// 2\xa
const buffer_unit_t const_1_18[2] = {0x32,0xa};
// 2: 
const buffer_unit_t const_1_19[3] = {0x32,0x3a,0x20};
// 2: 0.
const buffer_unit_t const_1_20[5] = {0x32,0x3a,0x20,0x30,0x2e};
// 3: 
const buffer_unit_t const_1_21[3] = {0x33,0x3a,0x20};
// 3: 0
const buffer_unit_t const_1_22[4] = {0x33,0x3a,0x20,0x30};
// 3: 0\xapath-1: \xa\xa
const buffer_unit_t const_1_23[15] = {0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0xa};
// 3: 0\xapath-1: \xafragment: 
const buffer_unit_t const_1_24[24] = {0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// 3: 0\xapath-1: \xaquery: 
const buffer_unit_t const_1_25[21] = {0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// 3: 0\xapath-1: /
const buffer_unit_t const_1_26[14] = {0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0x2f};
// 3: 0\xaport: 
const buffer_unit_t const_1_27[11] = {0x33,0x3a,0x20,0x30,0xa,0x70,0x6f,0x72,0x74,0x3a,0x20};
// 3: 0.
const buffer_unit_t const_1_28[5] = {0x33,0x3a,0x20,0x30,0x2e};
// 3: 1
const buffer_unit_t const_1_29[4] = {0x33,0x3a,0x20,0x31};
// 3: 2
const buffer_unit_t const_1_30[4] = {0x33,0x3a,0x20,0x32};
// :
const buffer_unit_t const_1_31[1] = {0x3a};
// ::
const buffer_unit_t const_1_32[2] = {0x3a,0x3a};
// ::0
const buffer_unit_t const_1_33[3] = {0x3a,0x3a,0x30};
// ::0.
const buffer_unit_t const_1_34[4] = {0x3a,0x3a,0x30,0x2e};
// ::0:
const buffer_unit_t const_1_35[4] = {0x3a,0x3a,0x30,0x3a};
// ::0]\xa
const buffer_unit_t const_1_36[5] = {0x3a,0x3a,0x30,0x5d,0xa};
// ::1
const buffer_unit_t const_1_37[3] = {0x3a,0x3a,0x31};
// ::2
const buffer_unit_t const_1_38[3] = {0x3a,0x3a,0x32};
// ::]\xa
const buffer_unit_t const_1_39[4] = {0x3a,0x3a,0x5d,0xa};
// :]\xa
const buffer_unit_t const_1_40[3] = {0x3a,0x5d,0xa};
// ]\xa
const buffer_unit_t const_1_41[2] = {0x5d,0xa};
// host-
const buffer_unit_t const_1_42[5] = {0x68,0x6f,0x73,0x74,0x2d};
// host-1: [
const buffer_unit_t const_1_43[9] = {0x68,0x6f,0x73,0x74,0x2d,0x31,0x3a,0x20,0x5b};
// host-3: 
const buffer_unit_t const_1_44[8] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20};
// host-3: \xapath-1: \xa\xa
const buffer_unit_t const_1_45[19] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0xa};
// host-3: \xapath-1: \xafragment: 
const buffer_unit_t const_1_46[28] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// host-3: \xapath-1: \xaquery: 
const buffer_unit_t const_1_47[25] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// host-3: \xapath-1: /
const buffer_unit_t const_1_48[18] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0x2f};
// host-3: \xaport: 
const buffer_unit_t const_1_49[15] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0xa,0x70,0x6f,0x72,0x74,0x3a,0x20};
// host-3: 0
const buffer_unit_t const_1_50[9] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0x30};
// host-3: 0\xapath-1: \xa\xa
const buffer_unit_t const_1_51[20] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0xa};
// host-3: 0\xapath-1: \xafragment: 
const buffer_unit_t const_1_52[29] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// host-3: 0\xapath-1: \xaquery: 
const buffer_unit_t const_1_53[26] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// host-3: 0\xapath-1: /
const buffer_unit_t const_1_54[19] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0x30,0xa,0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0x2f};
// host-3: 0\xaport: 
const buffer_unit_t const_1_55[16] = {0x68,0x6f,0x73,0x74,0x2d,0x33,0x3a,0x20,0x30,0xa,0x70,0x6f,0x72,0x74,0x3a,0x20};
// path-1: \xa\xa
const buffer_unit_t const_1_56[10] = {0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0xa};
// path-1: \xafragment: 
const buffer_unit_t const_1_57[19] = {0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// path-1: \xaquery: 
const buffer_unit_t const_1_58[16] = {0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// path-1: /
const buffer_unit_t const_1_59[9] = {0x70,0x61,0x74,0x68,0x2d,0x31,0x3a,0x20,0x2f};
// path-2: 
const buffer_unit_t const_1_60[8] = {0x70,0x61,0x74,0x68,0x2d,0x32,0x3a,0x20};
// path-2: \xa\xa
const buffer_unit_t const_1_61[10] = {0x70,0x61,0x74,0x68,0x2d,0x32,0x3a,0x20,0xa,0xa};
// path-2: \xafragment: 
const buffer_unit_t const_1_62[19] = {0x70,0x61,0x74,0x68,0x2d,0x32,0x3a,0x20,0xa,0x66,0x72,0x61,0x67,0x6d,0x65,0x6e,0x74,0x3a,0x20};
// path-2: \xaquery: 
const buffer_unit_t const_1_63[16] = {0x70,0x61,0x74,0x68,0x2d,0x32,0x3a,0x20,0xa,0x71,0x75,0x65,0x72,0x79,0x3a,0x20};
// path-2: /
const buffer_unit_t const_1_64[9] = {0x70,0x61,0x74,0x68,0x2d,0x32,0x3a,0x20,0x2f};
// port: 
const buffer_unit_t const_1_65[6] = {0x70,0x6f,0x72,0x74,0x3a,0x20};
// scheme: 
const buffer_unit_t const_1_66[8] = {0x73,0x63,0x68,0x65,0x6d,0x65,0x3a,0x20};
// user: 
const buffer_unit_t const_1_67[6] = {0x75,0x73,0x65,0x72,0x3a,0x20};
// user: \xa
const buffer_unit_t const_1_68[7] = {0x75,0x73,0x65,0x72,0x3a,0x20,0xa};
// user: 0
const buffer_unit_t const_1_69[7] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x30};
// user: 0\xa
const buffer_unit_t const_1_70[8] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x30,0xa};
// user: 0.
const buffer_unit_t const_1_71[8] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x30,0x2e};
// user: 0:
const buffer_unit_t const_1_72[8] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x30,0x3a};
// user: 1
const buffer_unit_t const_1_73[7] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x31};
// user: 2
const buffer_unit_t const_1_74[7] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x32};
// user: :
const buffer_unit_t const_1_75[7] = {0x75,0x73,0x65,0x72,0x3a,0x20,0x3a};
void printCompilationInfo()
{
  fprintf(stdout, "No object file generated!\nOptions:\nSST optimization level:  3\nWord size:               UInt8T\nIdentity tables removed: False\n\nSource file: ../../../benchmarks/submatch_dfa_aot/src/kleenex/02__uri_rfc3986.kex\nSource md5:  6452c3d426 b8519 d859bfeb5cfd96e\nSST states:  206\n");
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
init_buffer(&buf_23);
init_buffer(&buf_24);
init_buffer(&buf_25);
init_buffer(&buf_26);
init_buffer(&buf_27);
init_buffer(&buf_28);
init_buffer(&buf_29);
init_buffer(&buf_30);
init_buffer(&buf_31);
init_buffer(&buf_32);
init_buffer(&buf_33);
init_buffer(&buf_34);
init_buffer(&buf_35);
init_buffer(&buf_36);
init_buffer(&buf_37);
init_buffer(&buf_38);
init_buffer(&buf_39);
init_buffer(&buf_40);
init_buffer(&buf_41);
init_buffer(&buf_42);
init_buffer(&buf_43);
init_buffer(&buf_44);
init_buffer(&buf_45);
init_buffer(&buf_46);
init_buffer(&buf_47);
init_buffer(&buf_48);
init_buffer(&buf_49);
init_buffer(&buf_50);
init_buffer(&buf_51);
init_buffer(&buf_52);
init_buffer(&buf_53);
init_buffer(&buf_54);
init_buffer(&buf_55);
init_buffer(&buf_56);
init_buffer(&buf_57);
init_buffer(&buf_58);
init_buffer(&buf_59);
init_buffer(&buf_60);
init_buffer(&buf_61);
init_buffer(&buf_62);
init_buffer(&buf_63);
init_buffer(&buf_64);
init_buffer(&buf_65);
init_buffer(&buf_66);
init_buffer(&buf_67);
init_buffer(&buf_68);
}
void match1()
{
  int i = 0;
goto l1_0;
l1_0: if (!readnext(1, 1))
      {
         goto accept1;
      }
      if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
      {
         outputarray(const_1_66,64);
         outputconst(next[0],8);
         consume(1);
         goto l1_47;
      }
      goto fail1;
l1_1: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == '.') && 1)))
      {
         outputarray(const_1_9,8);
         consume(1);
         goto l1_7;
      }
      goto fail1;
l1_2: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == '.') && 1)))
      {
         outputarray(const_1_9,8);
         consume(1);
         goto l1_5;
      }
      goto fail1;
l1_3: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == ']') && 1)))
      {
         outputarray(const_1_41,16);
         consume(1);
         goto l1_38;
      }
      goto fail1;
l1_4: if (!readnext(1, 1))
      {
         goto accept1;
      }
      if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
      {
         outputarray(const_1_66,64);
         outputconst(next[0],8);
         consume(1);
         goto l1_47;
      }
      goto fail1;
l1_5: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == '0') && 1)))
      {
         outputarray(const_1_11,8);
         consume(1);
         goto l1_1;
      }
      if (((avail >= 1) && ((next[0] == '1') && 1)))
      {
         if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            consume(4);
            goto l1_7;
         }
         reset(&buf_37);
         appendarray(&buf_37,const_1_15,8);
         reset(&buf_1);
         appendarray(&buf_1,const_1_15,8);
         consume(1);
         goto l1_40;
      }
      if (((avail >= 1) && ((next[0] == '2') && 1)))
      {
         if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            consume(4);
            goto l1_7;
         }
         if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            consume(4);
            goto l1_7;
         }
         reset(&buf_37);
         appendarray(&buf_37,const_1_17,8);
         reset(&buf_1);
         appendarray(&buf_1,const_1_17,8);
         consume(1);
         goto l1_40;
      }
      if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
      {
         reset(&buf_37);
         append(&buf_37,next[0],8);
         reset(&buf_1);
         append(&buf_1,next[0],8);
         consume(1);
         goto l1_40;
      }
      goto fail1;
l1_6: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == '0') && 1)))
      {
         outputarray(const_1_11,8);
         consume(1);
         goto l1_2;
      }
      if (((avail >= 1) && ((next[0] == '1') && 1)))
      {
         if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            consume(4);
            goto l1_5;
         }
         reset(&buf_37);
         appendarray(&buf_37,const_1_15,8);
         reset(&buf_1);
         appendarray(&buf_1,const_1_15,8);
         consume(1);
         goto l1_42;
      }
      if (((avail >= 1) && ((next[0] == '2') && 1)))
      {
         if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            consume(4);
            goto l1_5;
         }
         if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            consume(4);
            goto l1_5;
         }
         reset(&buf_37);
         appendarray(&buf_37,const_1_17,8);
         reset(&buf_1);
         appendarray(&buf_1,const_1_17,8);
         consume(1);
         goto l1_42;
      }
      if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
      {
         reset(&buf_37);
         append(&buf_37,next[0],8);
         reset(&buf_1);
         append(&buf_1,next[0],8);
         consume(1);
         goto l1_42;
      }
      goto fail1;
l1_7: if (!readnext(1, 4))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == '0') && 1)))
      {
         outputarray(const_1_11,8);
         consume(1);
         goto l1_3;
      }
      if (((avail >= 1) && ((next[0] == '1') && 1)))
      {
         if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == ']') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            outputarray(const_1_0,8);
            consume(4);
            goto l1_38;
         }
         reset(&buf_37);
         appendarray(&buf_37,const_1_15,8);
         reset(&buf_1);
         appendarray(&buf_1,const_1_15,8);
         consume(1);
         goto l1_45;
      }
      if (((avail >= 1) && ((next[0] == '2') && 1)))
      {
         if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == ']') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            outputarray(const_1_0,8);
            consume(4);
            goto l1_38;
         }
         if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == ']') && 1)))))
         {
            for(i = 0; i < 4; i++)
            {  outputconst(next[0 + i],8);
            }
            outputarray(const_1_0,8);
            consume(4);
            goto l1_38;
         }
         reset(&buf_37);
         appendarray(&buf_37,const_1_17,8);
         reset(&buf_1);
         appendarray(&buf_1,const_1_17,8);
         consume(1);
         goto l1_45;
      }
      if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
      {
         reset(&buf_37);
         append(&buf_37,next[0],8);
         reset(&buf_1);
         append(&buf_1,next[0],8);
         consume(1);
         goto l1_45;
      }
      goto fail1;
l1_8: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 10) && 1)))
      {
         outputarray(const_1_3,88);
         consume(1);
         goto l1_4;
      }
      if (((avail >= 1) && ((next[0] == '#') && 1)))
      {
         outputarray(const_1_4,160);
         consume(1);
         goto l1_205;
      }
      if (((avail >= 1) && ((next[0] == '/') && 1)))
      {
         outputarray(const_1_6,80);
         consume(1);
         goto l1_156;
      }
      if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
      {
         outputconst(next[0],8);
         consume(1);
         goto l1_8;
      }
      if (((avail >= 1) && ((next[0] == '?') && 1)))
      {
         outputarray(const_1_5,136);
         consume(1);
         goto l1_204;
      }
      goto fail1;
l1_9: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
      {
         reset(&buf_37);
         append(&buf_37,next[0],8);
         reset(&buf_1);
         append(&buf_1,next[0],8);
         consume(1);
         goto l1_82;
      }
      goto fail1;
l1_10: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_52);
          concat(&buf_44,&buf_23);
          reset(&buf_52);
          append(&buf_52,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_4);
          append(&buf_9,next[0],8);
          reset(&buf_17);
          append(&buf_17,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_84;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             output(&buf_57);
             output(&buf_60);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_37);
          concat(&buf_37,&buf_17);
          concat(&buf_37,&buf_40);
          appendarray(&buf_37,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       goto fail1;
l1_11: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_44,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_85;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_46);
          appendarray(&buf_46,const_1_15,8);
          appendarray(&buf_44,const_1_15,8);
          reset(&buf_11);
          appendarray(&buf_11,const_1_15,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_86;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_46);
          appendarray(&buf_46,const_1_17,8);
          appendarray(&buf_44,const_1_17,8);
          reset(&buf_11);
          appendarray(&buf_11,const_1_17,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_86;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_46);
          append(&buf_46,next[0],8);
          append(&buf_44,next[0],8);
          reset(&buf_11);
          append(&buf_11,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_86;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_44,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_83;
       }
       goto fail1;
l1_12: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_52,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_88;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_52,const_1_15,8);
          reset(&buf_47);
          appendarray(&buf_47,const_1_15,8);
          reset(&buf_12);
          appendarray(&buf_12,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_89;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_52,const_1_17,8);
          reset(&buf_47);
          appendarray(&buf_47,const_1_17,8);
          reset(&buf_12);
          appendarray(&buf_12,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_89;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_52,next[0],8);
          reset(&buf_47);
          append(&buf_47,next[0],8);
          reset(&buf_12);
          append(&buf_12,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_89;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_87;
       }
       goto fail1;
l1_13: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_52,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_91;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_52,const_1_15,8);
          reset(&buf_47);
          appendarray(&buf_47,const_1_15,8);
          reset(&buf_12);
          appendarray(&buf_12,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_52,const_1_17,8);
          reset(&buf_47);
          appendarray(&buf_47,const_1_17,8);
          reset(&buf_12);
          appendarray(&buf_12,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_52,next[0],8);
          reset(&buf_47);
          append(&buf_47,next[0],8);
          reset(&buf_12);
          append(&buf_12,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_90;
       }
       goto fail1;
l1_14: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_91;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_15,8);
          reset(&buf_47);
          appendarray(&buf_47,const_1_15,8);
          reset(&buf_12);
          appendarray(&buf_12,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_17);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_17,8);
          reset(&buf_47);
          appendarray(&buf_47,const_1_17,8);
          reset(&buf_12);
          appendarray(&buf_12,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          append(&buf_52,next[0],8);
          reset(&buf_47);
          append(&buf_47,next[0],8);
          reset(&buf_12);
          append(&buf_12,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_92;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_90;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_15: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_60);
          append(&buf_60,next[0],8);
          reset(&buf_52);
          concat(&buf_52,&buf_57);
          concat(&buf_52,&buf_27);
          reset(&buf_57);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_4);
          append(&buf_9,next[0],8);
          reset(&buf_17);
          concat(&buf_17,&buf_23);
          concat(&buf_17,&buf_5);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_93;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             output(&buf_60);
             output(&buf_62);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_44);
          concat(&buf_44,&buf_23);
          concat(&buf_44,&buf_41);
          concat(&buf_44,&buf_48);
          appendarray(&buf_44,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          appendarray(&buf_1,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_40);
          appendarray(&buf_9,const_1_31,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_16: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_57,const_1_11,8);
          appendarray(&buf_17,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_95;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_57,const_1_15,8);
          reset(&buf_48);
          appendarray(&buf_48,const_1_15,8);
          appendarray(&buf_17,const_1_15,8);
          reset(&buf_13);
          appendarray(&buf_13,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_5);
          appendarray(&buf_5,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_96;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_57,const_1_17,8);
          reset(&buf_48);
          appendarray(&buf_48,const_1_17,8);
          appendarray(&buf_17,const_1_17,8);
          reset(&buf_13);
          appendarray(&buf_13,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_5);
          appendarray(&buf_5,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_96;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_57,next[0],8);
          reset(&buf_48);
          append(&buf_48,next[0],8);
          append(&buf_17,next[0],8);
          reset(&buf_13);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_96;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_94;
       }
       goto fail1;
l1_17: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_57,const_1_11,8);
          appendarray(&buf_17,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_98;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_57,const_1_15,8);
          reset(&buf_48);
          appendarray(&buf_48,const_1_15,8);
          appendarray(&buf_17,const_1_15,8);
          reset(&buf_13);
          appendarray(&buf_13,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_5);
          appendarray(&buf_5,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_99;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_57,const_1_17,8);
          reset(&buf_48);
          appendarray(&buf_48,const_1_17,8);
          appendarray(&buf_17,const_1_17,8);
          reset(&buf_13);
          appendarray(&buf_13,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_5);
          appendarray(&buf_5,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_99;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_57,next[0],8);
          reset(&buf_48);
          append(&buf_48,next[0],8);
          append(&buf_17,next[0],8);
          reset(&buf_13);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_99;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_97;
       }
       goto fail1;
l1_18: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_11,8);
          appendarray(&buf_17,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_98;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_15,8);
          reset(&buf_48);
          appendarray(&buf_48,const_1_15,8);
          appendarray(&buf_17,const_1_15,8);
          reset(&buf_13);
          appendarray(&buf_13,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_5);
          appendarray(&buf_5,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_99;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_23);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_17,8);
          reset(&buf_48);
          appendarray(&buf_48,const_1_17,8);
          appendarray(&buf_17,const_1_17,8);
          reset(&buf_13);
          appendarray(&buf_13,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_5);
          appendarray(&buf_5,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_99;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          append(&buf_57,next[0],8);
          reset(&buf_48);
          append(&buf_48,next[0],8);
          append(&buf_17,next[0],8);
          reset(&buf_13);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_99;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_97;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_60);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_19: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_63);
          append(&buf_63,next[0],8);
          reset(&buf_62);
          reset(&buf_57);
          concat(&buf_57,&buf_60);
          concat(&buf_57,&buf_29);
          reset(&buf_48);
          append(&buf_48,next[0],8);
          reset(&buf_41);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_30);
          append(&buf_30,next[0],8);
          reset(&buf_29);
          append(&buf_29,next[0],8);
          reset(&buf_13);
          append(&buf_13,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_4);
          append(&buf_9,next[0],8);
          reset(&buf_17);
          concat(&buf_17,&buf_23);
          concat(&buf_17,&buf_5);
          reset(&buf_23);
          concat(&buf_23,&buf_27);
          concat(&buf_23,&buf_6);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_100;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_60);
             output(&buf_62);
             output(&buf_63);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_27);
          concat(&buf_52,&buf_42);
          concat(&buf_52,&buf_49);
          appendarray(&buf_52,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          appendarray(&buf_1,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_40);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_23);
          concat(&buf_17,&buf_41);
          concat(&buf_17,&buf_48);
          appendarray(&buf_17,const_1_31,8);
          consume(1);
          goto l1_13;
       }
       goto fail1;
l1_20: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_60,const_1_11,8);
          appendarray(&buf_23,const_1_11,8);
          appendarray(&buf_17,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_102;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_60,const_1_15,8);
          reset(&buf_49);
          appendarray(&buf_49,const_1_15,8);
          appendarray(&buf_23,const_1_15,8);
          appendarray(&buf_17,const_1_15,8);
          reset(&buf_14);
          appendarray(&buf_14,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_6);
          appendarray(&buf_6,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_103;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_60,const_1_17,8);
          reset(&buf_49);
          appendarray(&buf_49,const_1_17,8);
          appendarray(&buf_23,const_1_17,8);
          appendarray(&buf_17,const_1_17,8);
          reset(&buf_14);
          appendarray(&buf_14,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_6);
          appendarray(&buf_6,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_103;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_60,next[0],8);
          reset(&buf_49);
          append(&buf_49,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          reset(&buf_14);
          append(&buf_14,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_6);
          append(&buf_6,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_103;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_60,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_101;
       }
       goto fail1;
l1_21: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_60,const_1_11,8);
          appendarray(&buf_23,const_1_11,8);
          appendarray(&buf_17,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_105;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_60,const_1_15,8);
          reset(&buf_49);
          appendarray(&buf_49,const_1_15,8);
          appendarray(&buf_23,const_1_15,8);
          appendarray(&buf_17,const_1_15,8);
          reset(&buf_14);
          appendarray(&buf_14,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_6);
          appendarray(&buf_6,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_106;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          appendarray(&buf_60,const_1_17,8);
          reset(&buf_49);
          appendarray(&buf_49,const_1_17,8);
          appendarray(&buf_23,const_1_17,8);
          appendarray(&buf_17,const_1_17,8);
          reset(&buf_14);
          appendarray(&buf_14,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_6);
          appendarray(&buf_6,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_106;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_60,next[0],8);
          reset(&buf_49);
          append(&buf_49,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          reset(&buf_14);
          append(&buf_14,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_6);
          append(&buf_6,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_106;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_60,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_104;
       }
       goto fail1;
l1_22: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          appendarray(&buf_60,const_1_11,8);
          appendarray(&buf_23,const_1_11,8);
          appendarray(&buf_17,const_1_11,8);
          appendarray(&buf_9,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_105;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          appendarray(&buf_60,const_1_15,8);
          reset(&buf_49);
          appendarray(&buf_49,const_1_15,8);
          appendarray(&buf_23,const_1_15,8);
          appendarray(&buf_17,const_1_15,8);
          reset(&buf_14);
          appendarray(&buf_14,const_1_15,8);
          appendarray(&buf_9,const_1_15,8);
          reset(&buf_6);
          appendarray(&buf_6,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_106;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_27);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          appendarray(&buf_60,const_1_17,8);
          reset(&buf_49);
          appendarray(&buf_49,const_1_17,8);
          appendarray(&buf_23,const_1_17,8);
          appendarray(&buf_17,const_1_17,8);
          reset(&buf_14);
          appendarray(&buf_14,const_1_17,8);
          appendarray(&buf_9,const_1_17,8);
          reset(&buf_6);
          appendarray(&buf_6,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_106;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          append(&buf_60,next[0],8);
          reset(&buf_49);
          append(&buf_49,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          reset(&buf_14);
          append(&buf_14,next[0],8);
          append(&buf_9,next[0],8);
          reset(&buf_6);
          append(&buf_6,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_106;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          append(&buf_60,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_104;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_62);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_23: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_65);
          append(&buf_65,next[0],8);
          reset(&buf_64);
          reset(&buf_60);
          concat(&buf_60,&buf_62);
          concat(&buf_60,&buf_30);
          reset(&buf_55);
          append(&buf_55,next[0],8);
          reset(&buf_49);
          reset(&buf_48);
          append(&buf_48,next[0],8);
          reset(&buf_41);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_32);
          append(&buf_32,next[0],8);
          reset(&buf_31);
          append(&buf_31,next[0],8);
          reset(&buf_30);
          append(&buf_30,next[0],8);
          reset(&buf_20);
          append(&buf_20,next[0],8);
          reset(&buf_14);
          append(&buf_14,next[0],8);
          reset(&buf_13);
          append(&buf_13,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_4);
          append(&buf_9,next[0],8);
          reset(&buf_17);
          concat(&buf_17,&buf_23);
          concat(&buf_17,&buf_5);
          reset(&buf_23);
          concat(&buf_23,&buf_27);
          concat(&buf_23,&buf_6);
          reset(&buf_27);
          concat(&buf_27,&buf_29);
          concat(&buf_27,&buf_7);
          reset(&buf_29);
          append(&buf_29,next[0],8);
          reset(&buf_6);
          append(&buf_6,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_107;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_62);
             output(&buf_63);
             output(&buf_64);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_57);
          concat(&buf_57,&buf_29);
          concat(&buf_57,&buf_43);
          concat(&buf_57,&buf_50);
          appendarray(&buf_57,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          appendarray(&buf_1,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_40);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_23);
          concat(&buf_17,&buf_41);
          concat(&buf_17,&buf_48);
          appendarray(&buf_17,const_1_31,8);
          reset(&buf_23);
          concat(&buf_23,&buf_27);
          concat(&buf_23,&buf_42);
          concat(&buf_23,&buf_49);
          appendarray(&buf_23,const_1_31,8);
          consume(1);
          goto l1_17;
       }
       goto fail1;
l1_24: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          consume(1);
          goto l1_109;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             outputarray(const_1_32,16);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_62);
          appendarray(&buf_62,const_1_37,24);
          reset(&buf_50);
          appendarray(&buf_50,const_1_15,8);
          reset(&buf_27);
          appendarray(&buf_27,const_1_37,24);
          reset(&buf_23);
          appendarray(&buf_23,const_1_37,24);
          reset(&buf_17);
          appendarray(&buf_17,const_1_37,24);
          reset(&buf_15);
          appendarray(&buf_15,const_1_15,8);
          reset(&buf_9);
          appendarray(&buf_9,const_1_37,24);
          reset(&buf_7);
          appendarray(&buf_7,const_1_15,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_37,24);
          consume(1);
          goto l1_110;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             outputarray(const_1_32,16);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             outputarray(const_1_32,16);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_62);
          appendarray(&buf_62,const_1_38,24);
          reset(&buf_50);
          appendarray(&buf_50,const_1_17,8);
          reset(&buf_27);
          appendarray(&buf_27,const_1_38,24);
          reset(&buf_23);
          appendarray(&buf_23,const_1_38,24);
          reset(&buf_17);
          appendarray(&buf_17,const_1_38,24);
          reset(&buf_15);
          appendarray(&buf_15,const_1_17,8);
          reset(&buf_9);
          appendarray(&buf_9,const_1_38,24);
          reset(&buf_7);
          appendarray(&buf_7,const_1_17,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_38,24);
          consume(1);
          goto l1_110;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_62);
          appendarray(&buf_62,const_1_32,16);
          append(&buf_62,next[0],8);
          reset(&buf_50);
          append(&buf_50,next[0],8);
          reset(&buf_27);
          appendarray(&buf_27,const_1_32,16);
          append(&buf_27,next[0],8);
          reset(&buf_23);
          appendarray(&buf_23,const_1_32,16);
          append(&buf_23,next[0],8);
          reset(&buf_17);
          appendarray(&buf_17,const_1_32,16);
          append(&buf_17,next[0],8);
          reset(&buf_15);
          append(&buf_15,next[0],8);
          reset(&buf_9);
          appendarray(&buf_9,const_1_32,16);
          append(&buf_9,next[0],8);
          reset(&buf_7);
          append(&buf_7,next[0],8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_32,16);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_110;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_62);
          appendarray(&buf_62,const_1_32,16);
          append(&buf_62,next[0],8);
          reset(&buf_29);
          appendarray(&buf_29,const_1_32,16);
          append(&buf_29,next[0],8);
          reset(&buf_27);
          appendarray(&buf_27,const_1_32,16);
          append(&buf_27,next[0],8);
          reset(&buf_23);
          appendarray(&buf_23,const_1_32,16);
          append(&buf_23,next[0],8);
          reset(&buf_17);
          appendarray(&buf_17,const_1_32,16);
          append(&buf_17,next[0],8);
          reset(&buf_9);
          appendarray(&buf_9,const_1_32,16);
          append(&buf_9,next[0],8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_32,16);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_108;
       }
       goto fail1;
l1_25: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_67);
          append(&buf_67,next[0],8);
          reset(&buf_66);
          reset(&buf_62);
          concat(&buf_62,&buf_31);
          reset(&buf_59);
          append(&buf_59,next[0],8);
          reset(&buf_56);
          reset(&buf_55);
          append(&buf_55,next[0],8);
          reset(&buf_49);
          reset(&buf_48);
          append(&buf_48,next[0],8);
          reset(&buf_41);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_34);
          append(&buf_34,next[0],8);
          reset(&buf_33);
          append(&buf_33,next[0],8);
          reset(&buf_32);
          append(&buf_32,next[0],8);
          reset(&buf_31);
          append(&buf_31,next[0],8);
          reset(&buf_30);
          append(&buf_30,next[0],8);
          reset(&buf_29);
          concat(&buf_29,&buf_8);
          reset(&buf_27);
          concat(&buf_27,&buf_7);
          reset(&buf_25);
          append(&buf_25,next[0],8);
          reset(&buf_23);
          concat(&buf_23,&buf_6);
          reset(&buf_21);
          append(&buf_21,next[0],8);
          reset(&buf_20);
          append(&buf_20,next[0],8);
          reset(&buf_17);
          concat(&buf_17,&buf_5);
          reset(&buf_15);
          append(&buf_15,next[0],8);
          reset(&buf_14);
          append(&buf_14,next[0],8);
          reset(&buf_13);
          append(&buf_13,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_4);
          append(&buf_9,next[0],8);
          reset(&buf_7);
          append(&buf_7,next[0],8);
          reset(&buf_6);
          append(&buf_6,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_111;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_65);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_60);
          concat(&buf_60,&buf_51);
          appendarray(&buf_60,const_1_31,8);
          reset(&buf_27);
          concat(&buf_27,&buf_50);
          appendarray(&buf_27,const_1_31,8);
          reset(&buf_23);
          concat(&buf_23,&buf_49);
          appendarray(&buf_23,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_48);
          appendarray(&buf_17,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          appendarray(&buf_1,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_40);
          appendarray(&buf_9,const_1_31,8);
          consume(1);
          goto l1_21;
       }
       goto fail1;
l1_26: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_44,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_130;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_46);
          appendarray(&buf_46,const_1_15,8);
          appendarray(&buf_44,const_1_15,8);
          reset(&buf_11);
          appendarray(&buf_11,const_1_15,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_131;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_46);
          appendarray(&buf_46,const_1_17,8);
          appendarray(&buf_44,const_1_17,8);
          reset(&buf_11);
          appendarray(&buf_11,const_1_17,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_131;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_46);
          append(&buf_46,next[0],8);
          append(&buf_44,next[0],8);
          reset(&buf_11);
          append(&buf_11,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_131;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          append(&buf_44,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_129;
       }
       goto fail1;
l1_27: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_130;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_46);
          appendarray(&buf_46,const_1_15,8);
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_15,8);
          reset(&buf_11);
          appendarray(&buf_11,const_1_15,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_15,8);
          appendarray(&buf_1,const_1_15,8);
          consume(1);
          goto l1_131;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             output(&buf_9);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(4);
             goto l1_6;
          }
          reset(&buf_46);
          appendarray(&buf_46,const_1_17,8);
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_17,8);
          reset(&buf_11);
          appendarray(&buf_11,const_1_17,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_17,8);
          appendarray(&buf_1,const_1_17,8);
          consume(1);
          goto l1_131;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_46);
          append(&buf_46,next[0],8);
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          append(&buf_44,next[0],8);
          reset(&buf_11);
          append(&buf_11,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_131;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          append(&buf_44,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_129;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_28: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "::]",3) && 1)))
          {
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(4);
             goto l1_38;
          }
          outputconst(next[0],8);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 3) && (cmp(&next[0],(unsigned char *) "::]",3) && 1)))
       {
          outputarray(const_1_39,32);
          consume(3);
          goto l1_38;
       }
       goto fail1;
l1_29: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          outputconst(next[0],8);
          consume(1);
          goto l1_31;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_30: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 4) && (cmp(&next[1],(unsigned char *) "::]",3) && 1)))
          {
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(4);
             goto l1_38;
          }
          outputconst(next[0],8);
          consume(1);
          goto l1_32;
       }
       if (((avail >= 3) && (cmp(&next[0],(unsigned char *) "::]",3) && 1)))
       {
          outputarray(const_1_39,32);
          consume(3);
          goto l1_38;
       }
       goto fail1;
l1_31: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          outputconst(next[0],8);
          consume(1);
          goto l1_34;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_32: if (!readnext(3, 4))
       {
          goto fail1;
       }
       if (((avail >= 4) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && (cmp(&next[1],(unsigned char *) "::]",3) && 1))))
       {
          for(i = 0; i < 4; i++)
          {  outputconst(next[0 + i],8);
          }
          outputarray(const_1_0,8);
          consume(4);
          goto l1_38;
       }
       if (((avail >= 3) && (cmp(&next[0],(unsigned char *) "::]",3) && 1)))
       {
          outputarray(const_1_39,32);
          consume(3);
          goto l1_38;
       }
       goto fail1;
l1_33: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          outputarray(const_1_9,8);
          consume(1);
          goto l1_48;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_33;
       }
       goto fail1;
l1_34: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ']') && 1))))
       {
          for(i = 0; i < 2; i++)
          {  outputconst(next[0 + i],8);
          }
          outputarray(const_1_0,8);
          consume(2);
          goto l1_38;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_35: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_37);
          concat(&buf_37,&buf_44);
          concat(&buf_37,&buf_17);
          reset(&buf_44);
          append(&buf_44,next[0],8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          concat(&buf_1,&buf_3);
          append(&buf_1,next[0],8);
          reset(&buf_9);
          append(&buf_9,next[0],8);
          consume(1);
          goto l1_134;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_44);
             output(&buf_52);
             output(&buf_57);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_37);
          concat(&buf_37,&buf_9);
          concat(&buf_37,&buf_39);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       goto fail1;
l1_36: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_62);
          append(&buf_62,next[0],8);
          reset(&buf_60);
          reset(&buf_52);
          concat(&buf_52,&buf_57);
          concat(&buf_52,&buf_27);
          reset(&buf_47);
          append(&buf_47,next[0],8);
          reset(&buf_40);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_29);
          append(&buf_29,next[0],8);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          reset(&buf_12);
          append(&buf_12,next[0],8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          concat(&buf_1,&buf_3);
          append(&buf_1,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_4);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_17);
          concat(&buf_17,&buf_23);
          concat(&buf_17,&buf_5);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          consume(1);
          goto l1_132;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             output(&buf_60);
             output(&buf_62);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          concat(&buf_52,&buf_41);
          concat(&buf_52,&buf_48);
          appendarray(&buf_52,const_1_31,8);
          concat(&buf_17,&buf_40);
          concat(&buf_17,&buf_47);
          appendarray(&buf_17,const_1_31,8);
          concat(&buf_9,&buf_39);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_13;
       }
       goto fail1;
l1_37: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          reset(&buf_57);
          append(&buf_57,next[0],8);
          reset(&buf_44);
          concat(&buf_44,&buf_52);
          concat(&buf_44,&buf_23);
          reset(&buf_52);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          reset(&buf_1);
          concat(&buf_1,&buf_9);
          concat(&buf_1,&buf_3);
          append(&buf_1,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_9);
          concat(&buf_9,&buf_17);
          concat(&buf_9,&buf_4);
          reset(&buf_17);
          append(&buf_17,next[0],8);
          consume(1);
          goto l1_133;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             output(&buf_57);
             output(&buf_60);
             outputarray(const_1_40,24);
             consume(2);
             goto l1_38;
          }
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          concat(&buf_44,&buf_40);
          concat(&buf_44,&buf_47);
          appendarray(&buf_44,const_1_31,8);
          concat(&buf_9,&buf_39);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_38: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_56,80);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          outputarray(const_1_57,152);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          outputarray(const_1_59,72);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          outputarray(const_1_65,48);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_58,128);
          consume(1);
          goto l1_204;
       }
       goto fail1;
l1_39: if (!readnext(1, 3))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_37);
          outputarray(const_1_3,88);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_4,160);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          output(&buf_37);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          appendarray(&buf_37,const_1_9,8);
          appendarray(&buf_1,const_1_9,8);
          consume(1);
          goto l1_49;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_6,80);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_7,56);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_5,136);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       goto fail1;
l1_40: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_7;
       }
       if (((avail >= 2) && ((('0' <= next[0]) && (next[0] <= '9')) && ((next[1] == '.') && 1))))
       {
          output(&buf_37);
          for(i = 0; i < 2; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(2);
          goto l1_7;
       }
       goto fail1;
l1_41: if (!readnext(1, 3))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_37);
          outputarray(const_1_3,88);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_4,160);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          output(&buf_37);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          appendarray(&buf_37,const_1_9,8);
          appendarray(&buf_1,const_1_9,8);
          consume(1);
          goto l1_50;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_6,80);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_7,56);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_5,136);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       goto fail1;
l1_42: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 2) && ((('0' <= next[0]) && (next[0] <= '9')) && ((next[1] == '.') && 1))))
       {
          output(&buf_37);
          for(i = 0; i < 2; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(2);
          goto l1_5;
       }
       goto fail1;
l1_43: if (!readnext(1, 3))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_23,120);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          outputarray(const_1_22,32);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          outputarray(const_1_24,192);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          outputarray(const_1_22,32);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          outputarray(const_1_22,32);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          reset(&buf_37);
          appendarray(&buf_37,const_1_28,40);
          reset(&buf_1);
          appendarray(&buf_1,const_1_20,40);
          consume(1);
          goto l1_51;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          outputarray(const_1_26,112);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          outputarray(const_1_22,32);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          outputarray(const_1_27,88);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_25,168);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          outputarray(const_1_22,32);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       goto fail1;
l1_44: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_45,152);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          outputarray(const_1_44,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          outputarray(const_1_46,224);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          outputarray(const_1_44,64);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          outputarray(const_1_44,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          outputarray(const_1_48,144);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          outputarray(const_1_42,40);
          consume(1);
          goto l1_43;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             reset(&buf_37);
             appendarray(&buf_37,const_1_21,24);
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             reset(&buf_1);
             appendarray(&buf_1,const_1_19,24);
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             outputarray(const_1_42,40);
             consume(4);
             goto l1_51;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_15,8);
          reset(&buf_37);
          appendarray(&buf_37,const_1_29,32);
          reset(&buf_2);
          appendarray(&buf_2,const_1_15,8);
          outputarray(const_1_42,40);
          consume(1);
          goto l1_152;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             reset(&buf_37);
             appendarray(&buf_37,const_1_21,24);
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             reset(&buf_1);
             appendarray(&buf_1,const_1_19,24);
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             outputarray(const_1_42,40);
             consume(4);
             goto l1_51;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             reset(&buf_37);
             appendarray(&buf_37,const_1_21,24);
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             reset(&buf_1);
             appendarray(&buf_1,const_1_19,24);
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             outputarray(const_1_42,40);
             consume(4);
             goto l1_51;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_17,8);
          reset(&buf_37);
          appendarray(&buf_37,const_1_30,32);
          reset(&buf_2);
          appendarray(&buf_2,const_1_17,8);
          outputarray(const_1_42,40);
          consume(1);
          goto l1_152;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_37);
          appendarray(&buf_37,const_1_21,24);
          append(&buf_37,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          outputarray(const_1_42,40);
          consume(1);
          goto l1_152;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          outputarray(const_1_49,120);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_47,200);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          outputarray(const_1_44,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '[') && 1)))
       {
          outputarray(const_1_43,72);
          consume(1);
          goto l1_117;
       }
       goto fail1;
l1_45: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 2) && ((('0' <= next[0]) && (next[0] <= '9')) && ((next[1] == ']') && 1))))
       {
          output(&buf_37);
          for(i = 0; i < 2; i++)
          {  outputconst(next[0 + i],8);
          }
          outputarray(const_1_0,8);
          consume(2);
          goto l1_38;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_46: if (!readnext(1, 3))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_61,80);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          outputarray(const_1_60,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_160;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          outputarray(const_1_62,152);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          outputarray(const_1_60,64);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_160;
       }
       if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          outputarray(const_1_60,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_160;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          if (((avail >= 2) && ((next[1] == '/') && 1)))
          {
             consume(2);
             goto l1_194;
          }
          outputarray(const_1_64,72);
          consume(1);
          goto l1_158;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          outputarray(const_1_60,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_160;
       }
       if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
       {
          outputarray(const_1_60,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_160;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_63,128);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          outputarray(const_1_60,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_160;
       }
       goto fail1;
l1_47: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((next[0] == '+') || (('-' <= next[0]) && (next[0] <= '.'))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          outputarray(const_1_0,8);
          consume(1);
          goto l1_46;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_47;
       }
       goto fail1;
l1_48: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_154;
       }
       if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_154;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_154;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          outputarray(const_1_31,8);
          consume(1);
          goto l1_154;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_154;
       }
       goto fail1;
l1_49: if (!readnext(1, 3))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_37);
          outputarray(const_1_3,88);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_4,160);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          output(&buf_37);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_6,80);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_37,const_1_11,8);
          appendarray(&buf_1,const_1_12,16);
          consume(1);
          goto l1_149;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 3) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && 1))))
          {
             for(i = 0; i < 3; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             appendarray(&buf_1,const_1_0,8);
             consume(3);
             goto l1_149;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_15,8);
          appendarray(&buf_37,const_1_15,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_16,16);
          consume(1);
          goto l1_189;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 3) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && 1))))
          {
             for(i = 0; i < 3; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             appendarray(&buf_1,const_1_0,8);
             consume(3);
             goto l1_149;
          }
          if (((avail >= 3) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && 1))))
          {
             for(i = 0; i < 3; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             appendarray(&buf_1,const_1_0,8);
             consume(3);
             goto l1_149;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_17,8);
          appendarray(&buf_37,const_1_17,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_18,16);
          consume(1);
          goto l1_189;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_38);
          append(&buf_38,next[0],8);
          append(&buf_37,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          appendarray(&buf_2,const_1_0,8);
          consume(1);
          goto l1_189;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_7,56);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_5,136);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       goto fail1;
l1_50: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_37);
          outputarray(const_1_3,88);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_4,160);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          output(&buf_37);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_6,80);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_37,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_39;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(4);
             goto l1_49;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_15,8);
          appendarray(&buf_37,const_1_15,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_15,8);
          consume(1);
          goto l1_150;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(4);
             goto l1_49;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(4);
             goto l1_49;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_17,8);
          appendarray(&buf_37,const_1_17,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_17,8);
          consume(1);
          goto l1_150;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_38);
          append(&buf_38,next[0],8);
          append(&buf_37,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_150;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_7,56);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_5,136);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       goto fail1;
l1_51: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_37);
          outputarray(const_1_3,88);
          consume(1);
          goto l1_4;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '#') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_4,160);
          consume(1);
          goto l1_205;
       }
       if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
       {
          output(&buf_37);
          for(i = 0; i < 3; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(3);
          goto l1_155;
       }
       if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_6,80);
          consume(1);
          goto l1_156;
       }
       if (((avail >= 1) && ((next[0] == '0') && 1)))
       {
          appendarray(&buf_37,const_1_11,8);
          appendarray(&buf_1,const_1_11,8);
          consume(1);
          goto l1_41;
       }
       if (((avail >= 1) && ((next[0] == '1') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(4);
             goto l1_50;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_15,8);
          appendarray(&buf_37,const_1_15,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_15,8);
          consume(1);
          goto l1_151;
       }
       if (((avail >= 1) && ((next[0] == '2') && 1)))
       {
          if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
          {
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(4);
             goto l1_50;
          }
          if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
          {
             for(i = 0; i < 4; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 4; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(4);
             goto l1_50;
          }
          reset(&buf_38);
          appendarray(&buf_38,const_1_17,8);
          appendarray(&buf_37,const_1_17,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_17,8);
          consume(1);
          goto l1_151;
       }
       if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_38);
          append(&buf_38,next[0],8);
          append(&buf_37,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_151;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_7,56);
          consume(1);
          goto l1_8;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_37);
          outputarray(const_1_5,136);
          consume(1);
          goto l1_204;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
       {
          output(&buf_37);
          outputconst(next[0],8);
          consume(1);
          goto l1_155;
       }
       goto fail1;
l1_52: if (!readnext(2, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
          {
             output(&buf_1);
             for(i = 0; i < 3; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(3);
             goto l1_28;
          }
          if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
          {
             output(&buf_37);
             for(i = 0; i < 4; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(4);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             output(&buf_1);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_28;
          }
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
          {
             output(&buf_37);
             outputarray(const_1_39,32);
             consume(3);
             goto l1_38;
          }
       }
       goto fail1;
l1_53: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_37);
             concat(&buf_37,&buf_9);
             for(i = 0; i < 2; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_119;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_44);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_37);
          concat(&buf_37,&buf_9);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_44);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_54: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && ((next[2] == ':') && 1)))
          {
             if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
             {
                output(&buf_9);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                consume(4);
                goto l1_29;
             }
             if (((avail >= 4) && ((next[3] == ']') && 1)))
             {
                output(&buf_44);
                output(&buf_52);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
          }
          reset(&buf_37);
          concat(&buf_37,&buf_44);
          concat(&buf_37,&buf_17);
          for(i = 0; i < 2; i++)
          {  append(&buf_37,next[0 + i],8);
          }
          for(i = 0; i < 2; i++)
          {  append(&buf_1,next[0 + i],8);
          }
          consume(2);
          goto l1_118;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                output(&buf_9);
                for(i = 0; i < 3; i++)
                {  outputconst(next[0 + i],8);
                }
                consume(3);
                goto l1_29;
             }
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_44);
                output(&buf_52);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
          }
          reset(&buf_37);
          concat(&buf_37,&buf_44);
          concat(&buf_37,&buf_17);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_118;
       }
       goto fail1;
l1_55: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_56: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_57: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_52);
             concat(&buf_44,&buf_23);
             for(i = 0; i < 3; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             reset(&buf_52);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(3);
             goto l1_84;
          }
          if (((avail >= 3) && ((next[2] == ':') && 1)))
          {
             if (((avail >= 4) && ((next[3] == ']') && 1)))
             {
                output(&buf_52);
                output(&buf_57);
                output(&buf_60);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
             reset(&buf_37);
             concat(&buf_37,&buf_17);
             concat(&buf_37,&buf_40);
             for(i = 0; i < 3; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(3);
             goto l1_119;
          }
          output(&buf_52);
          output(&buf_23);
          for(i = 0; i < 2; i++)
          {  outputconst(next[0 + i],8);
          }
          consume(2);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_52);
             concat(&buf_44,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             reset(&buf_52);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_84;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_52);
                output(&buf_57);
                output(&buf_60);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_37);
             concat(&buf_37,&buf_17);
             concat(&buf_37,&buf_40);
             appendarray(&buf_37,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             consume(2);
             goto l1_119;
          }
          output(&buf_52);
          output(&buf_23);
          outputarray(const_1_31,8);
          consume(1);
          goto l1_9;
       }
       goto fail1;
l1_58: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_59: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_60: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
          {
             reset(&buf_60);
             reset(&buf_52);
             concat(&buf_52,&buf_57);
             concat(&buf_52,&buf_27);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             reset(&buf_57);
             append(&buf_57,next[2],8);
             reset(&buf_40);
             reset(&buf_27);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             append(&buf_23,next[2],8);
             reset(&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(3);
             goto l1_93;
          }
          if (((avail >= 3) && ((next[2] == ':') && 1)))
          {
             if (((avail >= 4) && ((next[3] == ']') && 1)))
             {
                output(&buf_57);
                output(&buf_62);
                output(&buf_63);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
             reset(&buf_44);
             concat(&buf_44,&buf_23);
             concat(&buf_44,&buf_41);
             concat(&buf_44,&buf_48);
             for(i = 0; i < 3; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             consume(3);
             goto l1_26;
          }
          reset(&buf_37);
          concat(&buf_37,&buf_57);
          concat(&buf_37,&buf_27);
          for(i = 0; i < 2; i++)
          {  append(&buf_37,next[0 + i],8);
          }
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          for(i = 0; i < 2; i++)
          {  append(&buf_1,next[0 + i],8);
          }
          consume(2);
          goto l1_116;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_60);
             reset(&buf_52);
             concat(&buf_52,&buf_57);
             concat(&buf_52,&buf_27);
             append(&buf_52,next[0],8);
             reset(&buf_57);
             append(&buf_57,next[1],8);
             reset(&buf_40);
             reset(&buf_27);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             append(&buf_23,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_93;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_57);
                output(&buf_62);
                output(&buf_63);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_44);
             concat(&buf_44,&buf_23);
             concat(&buf_44,&buf_41);
             concat(&buf_44,&buf_48);
             appendarray(&buf_44,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             consume(2);
             goto l1_26;
          }
          reset(&buf_37);
          concat(&buf_37,&buf_57);
          concat(&buf_37,&buf_27);
          appendarray(&buf_37,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_116;
       }
       goto fail1;
l1_61: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_57);
             concat(&buf_57,&buf_27);
             for(i = 0; i < 2; i++)
             {  append(&buf_57,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_16;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_60);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_31,8);
          appendarray(&buf_23,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_60);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_62: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_57);
             concat(&buf_57,&buf_27);
             for(i = 0; i < 2; i++)
             {  append(&buf_57,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_16;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_60);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_31,8);
          appendarray(&buf_23,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_60);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_63: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
          {
             reset(&buf_63);
             reset(&buf_62);
             append(&buf_62,next[2],8);
             reset(&buf_57);
             concat(&buf_57,&buf_60);
             concat(&buf_57,&buf_29);
             for(i = 0; i < 2; i++)
             {  append(&buf_57,next[0 + i],8);
             }
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[2],8);
             reset(&buf_40);
             reset(&buf_30);
             reset(&buf_29);
             append(&buf_29,next[2],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_6);
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             reset(&buf_27);
             append(&buf_27,next[2],8);
             reset(&buf_5);
             append(&buf_5,next[2],8);
             reset(&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(3);
             goto l1_100;
          }
          if (((avail >= 3) && ((next[2] == ':') && 1)))
          {
             if (((avail >= 4) && ((next[3] == ']') && 1)))
             {
                output(&buf_60);
                output(&buf_64);
                output(&buf_65);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
             reset(&buf_52);
             concat(&buf_52,&buf_27);
             concat(&buf_52,&buf_49);
             concat(&buf_52,&buf_55);
             for(i = 0; i < 3; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_41);
             concat(&buf_17,&buf_48);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             consume(3);
             goto l1_13;
          }
          reset(&buf_44);
          concat(&buf_44,&buf_60);
          concat(&buf_44,&buf_29);
          for(i = 0; i < 2; i++)
          {  append(&buf_44,next[0 + i],8);
          }
          reset(&buf_9);
          concat(&buf_9,&buf_27);
          concat(&buf_9,&buf_6);
          for(i = 0; i < 2; i++)
          {  append(&buf_9,next[0 + i],8);
          }
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          for(i = 0; i < 2; i++)
          {  append(&buf_1,next[0 + i],8);
          }
          consume(2);
          goto l1_115;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_63);
             reset(&buf_62);
             append(&buf_62,next[1],8);
             reset(&buf_57);
             concat(&buf_57,&buf_60);
             concat(&buf_57,&buf_29);
             append(&buf_57,next[0],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[1],8);
             reset(&buf_40);
             reset(&buf_30);
             reset(&buf_29);
             append(&buf_29,next[1],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_6);
             append(&buf_23,next[0],8);
             reset(&buf_27);
             append(&buf_27,next[1],8);
             reset(&buf_5);
             append(&buf_5,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_100;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_60);
                output(&buf_64);
                output(&buf_65);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_52);
             concat(&buf_52,&buf_27);
             concat(&buf_52,&buf_49);
             concat(&buf_52,&buf_55);
             appendarray(&buf_52,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_41);
             concat(&buf_17,&buf_48);
             appendarray(&buf_17,const_1_32,16);
             consume(2);
             goto l1_13;
          }
          reset(&buf_44);
          concat(&buf_44,&buf_60);
          concat(&buf_44,&buf_29);
          appendarray(&buf_44,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_27);
          concat(&buf_9,&buf_6);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_115;
       }
       goto fail1;
l1_64: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_60);
             concat(&buf_60,&buf_29);
             for(i = 0; i < 2; i++)
             {  append(&buf_60,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_20;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_62);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          appendarray(&buf_60,const_1_31,8);
          appendarray(&buf_27,const_1_31,8);
          appendarray(&buf_23,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_62);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_65: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
          {
             reset(&buf_65);
             reset(&buf_64);
             append(&buf_64,next[2],8);
             reset(&buf_60);
             concat(&buf_60,&buf_62);
             concat(&buf_60,&buf_30);
             for(i = 0; i < 2; i++)
             {  append(&buf_60,next[0 + i],8);
             }
             reset(&buf_55);
             reset(&buf_49);
             append(&buf_49,next[2],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[2],8);
             reset(&buf_40);
             reset(&buf_32);
             reset(&buf_31);
             append(&buf_31,next[2],8);
             reset(&buf_30);
             append(&buf_30,next[2],8);
             reset(&buf_20);
             reset(&buf_14);
             append(&buf_14,next[2],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_6);
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             reset(&buf_27);
             concat(&buf_27,&buf_29);
             concat(&buf_27,&buf_7);
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             reset(&buf_29);
             append(&buf_29,next[2],8);
             reset(&buf_6);
             append(&buf_6,next[2],8);
             reset(&buf_5);
             append(&buf_5,next[2],8);
             reset(&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(3);
             goto l1_107;
          }
          if (((avail >= 3) && ((next[2] == ':') && 1)))
          {
             if (((avail >= 4) && ((next[3] == ']') && 1)))
             {
                output(&buf_62);
                output(&buf_66);
                output(&buf_67);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
             reset(&buf_57);
             concat(&buf_57,&buf_29);
             concat(&buf_57,&buf_56);
             concat(&buf_57,&buf_59);
             for(i = 0; i < 3; i++)
             {  append(&buf_57,next[0 + i],8);
             }
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_41);
             concat(&buf_17,&buf_48);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_49);
             concat(&buf_23,&buf_55);
             for(i = 0; i < 3; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             consume(3);
             goto l1_17;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_62);
          concat(&buf_52,&buf_30);
          for(i = 0; i < 2; i++)
          {  append(&buf_52,next[0 + i],8);
          }
          reset(&buf_17);
          concat(&buf_17,&buf_29);
          concat(&buf_17,&buf_7);
          for(i = 0; i < 2; i++)
          {  append(&buf_17,next[0 + i],8);
          }
          reset(&buf_9);
          concat(&buf_9,&buf_27);
          concat(&buf_9,&buf_6);
          for(i = 0; i < 2; i++)
          {  append(&buf_9,next[0 + i],8);
          }
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          for(i = 0; i < 2; i++)
          {  append(&buf_1,next[0 + i],8);
          }
          consume(2);
          goto l1_114;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_65);
             reset(&buf_64);
             append(&buf_64,next[1],8);
             reset(&buf_60);
             concat(&buf_60,&buf_62);
             concat(&buf_60,&buf_30);
             append(&buf_60,next[0],8);
             reset(&buf_55);
             reset(&buf_49);
             append(&buf_49,next[1],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[1],8);
             reset(&buf_40);
             reset(&buf_32);
             reset(&buf_31);
             append(&buf_31,next[1],8);
             reset(&buf_30);
             append(&buf_30,next[1],8);
             reset(&buf_20);
             reset(&buf_14);
             append(&buf_14,next[1],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_6);
             append(&buf_23,next[0],8);
             reset(&buf_27);
             concat(&buf_27,&buf_29);
             concat(&buf_27,&buf_7);
             append(&buf_27,next[0],8);
             reset(&buf_29);
             append(&buf_29,next[1],8);
             reset(&buf_6);
             append(&buf_6,next[1],8);
             reset(&buf_5);
             append(&buf_5,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_107;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_62);
                output(&buf_66);
                output(&buf_67);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_57);
             concat(&buf_57,&buf_29);
             concat(&buf_57,&buf_56);
             concat(&buf_57,&buf_59);
             appendarray(&buf_57,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_41);
             concat(&buf_17,&buf_48);
             appendarray(&buf_17,const_1_32,16);
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_49);
             concat(&buf_23,&buf_55);
             appendarray(&buf_23,const_1_32,16);
             consume(2);
             goto l1_17;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_62);
          concat(&buf_52,&buf_30);
          appendarray(&buf_52,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_29);
          concat(&buf_17,&buf_7);
          appendarray(&buf_17,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_27);
          concat(&buf_9,&buf_6);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_114;
       }
       goto fail1;
l1_66: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
       {
          if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
          {
             reset(&buf_67);
             reset(&buf_66);
             append(&buf_66,next[2],8);
             reset(&buf_62);
             concat(&buf_62,&buf_31);
             for(i = 0; i < 2; i++)
             {  append(&buf_62,next[0 + i],8);
             }
             reset(&buf_59);
             reset(&buf_56);
             append(&buf_56,next[2],8);
             reset(&buf_55);
             reset(&buf_49);
             append(&buf_49,next[2],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[2],8);
             reset(&buf_40);
             reset(&buf_34);
             reset(&buf_33);
             append(&buf_33,next[2],8);
             reset(&buf_32);
             append(&buf_32,next[2],8);
             reset(&buf_31);
             append(&buf_31,next[2],8);
             reset(&buf_30);
             append(&buf_30,next[2],8);
             reset(&buf_29);
             concat(&buf_29,&buf_8);
             for(i = 0; i < 2; i++)
             {  append(&buf_29,next[0 + i],8);
             }
             reset(&buf_27);
             concat(&buf_27,&buf_7);
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             reset(&buf_25);
             reset(&buf_23);
             concat(&buf_23,&buf_6);
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             reset(&buf_21);
             append(&buf_21,next[2],8);
             reset(&buf_20);
             reset(&buf_17);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_15);
             append(&buf_15,next[2],8);
             reset(&buf_14);
             append(&buf_14,next[2],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_7);
             append(&buf_7,next[2],8);
             reset(&buf_6);
             append(&buf_6,next[2],8);
             reset(&buf_5);
             append(&buf_5,next[2],8);
             reset(&buf_4);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(3);
             goto l1_111;
          }
          if (((avail >= 3) && ((next[2] == ':') && 1)))
          {
             if (((avail >= 4) && ((next[3] == ']') && 1)))
             {
                output(&buf_68);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
             reset(&buf_60);
             concat(&buf_60,&buf_61);
             for(i = 0; i < 3; i++)
             {  append(&buf_60,next[0 + i],8);
             }
             reset(&buf_27);
             concat(&buf_27,&buf_59);
             for(i = 0; i < 3; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_55);
             for(i = 0; i < 3; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_48);
             for(i = 0; i < 3; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             for(i = 0; i < 3; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             reset(&buf_9);
             concat(&buf_9,&buf_40);
             for(i = 0; i < 3; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             consume(3);
             goto l1_21;
          }
          reset(&buf_57);
          concat(&buf_57,&buf_31);
          for(i = 0; i < 2; i++)
          {  append(&buf_57,next[0 + i],8);
          }
          reset(&buf_23);
          concat(&buf_23,&buf_8);
          for(i = 0; i < 2; i++)
          {  append(&buf_23,next[0 + i],8);
          }
          reset(&buf_17);
          concat(&buf_17,&buf_7);
          for(i = 0; i < 2; i++)
          {  append(&buf_17,next[0 + i],8);
          }
          reset(&buf_9);
          concat(&buf_9,&buf_6);
          for(i = 0; i < 2; i++)
          {  append(&buf_9,next[0 + i],8);
          }
          reset(&buf_1);
          concat(&buf_1,&buf_5);
          for(i = 0; i < 2; i++)
          {  append(&buf_1,next[0 + i],8);
          }
          consume(2);
          goto l1_113;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_67);
             reset(&buf_66);
             append(&buf_66,next[1],8);
             reset(&buf_62);
             concat(&buf_62,&buf_31);
             append(&buf_62,next[0],8);
             reset(&buf_59);
             reset(&buf_56);
             append(&buf_56,next[1],8);
             reset(&buf_55);
             reset(&buf_49);
             append(&buf_49,next[1],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[1],8);
             reset(&buf_40);
             reset(&buf_34);
             reset(&buf_33);
             append(&buf_33,next[1],8);
             reset(&buf_32);
             append(&buf_32,next[1],8);
             reset(&buf_31);
             append(&buf_31,next[1],8);
             reset(&buf_30);
             append(&buf_30,next[1],8);
             reset(&buf_29);
             concat(&buf_29,&buf_8);
             append(&buf_29,next[0],8);
             reset(&buf_27);
             concat(&buf_27,&buf_7);
             append(&buf_27,next[0],8);
             reset(&buf_25);
             reset(&buf_23);
             concat(&buf_23,&buf_6);
             append(&buf_23,next[0],8);
             reset(&buf_21);
             append(&buf_21,next[1],8);
             reset(&buf_20);
             reset(&buf_17);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_15);
             append(&buf_15,next[1],8);
             reset(&buf_14);
             append(&buf_14,next[1],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_7);
             append(&buf_7,next[1],8);
             reset(&buf_6);
             append(&buf_6,next[1],8);
             reset(&buf_5);
             append(&buf_5,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_111;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_68);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_60);
             concat(&buf_60,&buf_61);
             appendarray(&buf_60,const_1_32,16);
             reset(&buf_27);
             concat(&buf_27,&buf_59);
             appendarray(&buf_27,const_1_32,16);
             reset(&buf_23);
             concat(&buf_23,&buf_55);
             appendarray(&buf_23,const_1_32,16);
             reset(&buf_17);
             concat(&buf_17,&buf_48);
             appendarray(&buf_17,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             consume(2);
             goto l1_21;
          }
          reset(&buf_57);
          concat(&buf_57,&buf_31);
          appendarray(&buf_57,const_1_31,8);
          reset(&buf_23);
          concat(&buf_23,&buf_8);
          appendarray(&buf_23,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_7);
          appendarray(&buf_17,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_6);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_113;
       }
       goto fail1;
l1_67: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                output(&buf_1);
                for(i = 0; i < 3; i++)
                {  outputconst(next[0 + i],8);
                }
                consume(3);
                goto l1_28;
             }
             if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
             {
                output(&buf_37);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
          }
          append(&buf_37,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_52;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             output(&buf_1);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_28;
          }
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
          {
             output(&buf_37);
             outputarray(const_1_39,32);
             consume(3);
             goto l1_38;
          }
       }
       goto fail1;
l1_68: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_37);
             concat(&buf_37,&buf_9);
             for(i = 0; i < 2; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_119;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_44);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_44,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_53;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_37);
          concat(&buf_37,&buf_9);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_44);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_69: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
                {
                   output(&buf_9);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   consume(4);
                   goto l1_29;
                }
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_44);
                   output(&buf_52);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_121;
          }
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_54;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                output(&buf_9);
                for(i = 0; i < 3; i++)
                {  outputconst(next[0 + i],8);
                }
                consume(3);
                goto l1_29;
             }
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_44);
                output(&buf_52);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
          }
          reset(&buf_37);
          concat(&buf_37,&buf_44);
          concat(&buf_37,&buf_17);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_118;
       }
       goto fail1;
l1_70: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_55;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_71: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_56;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_72: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                reset(&buf_44);
                concat(&buf_44,&buf_52);
                concat(&buf_44,&buf_23);
                for(i = 0; i < 3; i++)
                {  append(&buf_44,next[0 + i],8);
                }
                reset(&buf_52);
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                consume(3);
                goto l1_84;
             }
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_52);
                   output(&buf_57);
                   output(&buf_60);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
                reset(&buf_44);
                concat(&buf_44,&buf_52);
                concat(&buf_44,&buf_57);
                concat(&buf_44,&buf_60);
                for(i = 0; i < 3; i++)
                {  append(&buf_44,next[0 + i],8);
                }
                reset(&buf_1);
                concat(&buf_1,&buf_9);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_40);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                consume(3);
                goto l1_120;
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_60,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_40,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_4,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_10;
          }
          append(&buf_60,next[0],8);
          append(&buf_40,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_57;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_52);
             concat(&buf_44,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             reset(&buf_52);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_84;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_52);
                output(&buf_57);
                output(&buf_60);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_37);
             concat(&buf_37,&buf_17);
             concat(&buf_37,&buf_40);
             appendarray(&buf_37,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             consume(2);
             goto l1_119;
          }
          output(&buf_52);
          output(&buf_23);
          outputarray(const_1_31,8);
          consume(1);
          goto l1_9;
       }
       goto fail1;
l1_73: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_58;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_74: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_59;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_75: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                reset(&buf_60);
                reset(&buf_52);
                concat(&buf_52,&buf_57);
                concat(&buf_52,&buf_27);
                for(i = 0; i < 2; i++)
                {  append(&buf_52,next[0 + i],8);
                }
                reset(&buf_57);
                append(&buf_57,next[2],8);
                reset(&buf_40);
                reset(&buf_27);
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_23);
                concat(&buf_17,&buf_5);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_23);
                append(&buf_23,next[2],8);
                reset(&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                consume(3);
                goto l1_93;
             }
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_57);
                   output(&buf_62);
                   output(&buf_63);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
                reset(&buf_52);
                concat(&buf_52,&buf_57);
                concat(&buf_52,&buf_62);
                concat(&buf_52,&buf_63);
                for(i = 0; i < 3; i++)
                {  append(&buf_52,next[0 + i],8);
                }
                reset(&buf_1);
                concat(&buf_1,&buf_9);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_40);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_23);
                concat(&buf_17,&buf_41);
                concat(&buf_17,&buf_48);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                consume(3);
                goto l1_27;
             }
             reset(&buf_60);
             concat(&buf_60,&buf_62);
             reset(&buf_62);
             concat(&buf_62,&buf_63);
             for(i = 0; i < 2; i++)
             {  append(&buf_62,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_48,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_40,next[0 + i],8);
             }
             reset(&buf_29);
             concat(&buf_29,&buf_30);
             for(i = 0; i < 2; i++)
             {  append(&buf_29,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_13,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_5,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_4,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_15;
          }
          append(&buf_63,next[0],8);
          append(&buf_48,next[0],8);
          append(&buf_40,next[0],8);
          append(&buf_30,next[0],8);
          append(&buf_29,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_60;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_60);
             reset(&buf_52);
             concat(&buf_52,&buf_57);
             concat(&buf_52,&buf_27);
             append(&buf_52,next[0],8);
             reset(&buf_57);
             append(&buf_57,next[1],8);
             reset(&buf_40);
             reset(&buf_27);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             append(&buf_23,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_93;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_57);
                output(&buf_62);
                output(&buf_63);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_44);
             concat(&buf_44,&buf_23);
             concat(&buf_44,&buf_41);
             concat(&buf_44,&buf_48);
             appendarray(&buf_44,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             consume(2);
             goto l1_26;
          }
          reset(&buf_37);
          concat(&buf_37,&buf_57);
          concat(&buf_37,&buf_27);
          appendarray(&buf_37,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_116;
       }
       goto fail1;
l1_76: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_57);
             concat(&buf_57,&buf_27);
             for(i = 0; i < 2; i++)
             {  append(&buf_57,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_16;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_60);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_60,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_61;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_31,8);
          appendarray(&buf_23,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_60);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_77: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_57);
             concat(&buf_57,&buf_27);
             for(i = 0; i < 2; i++)
             {  append(&buf_57,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_16;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_60);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_60,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_62;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_57);
          concat(&buf_57,&buf_27);
          appendarray(&buf_57,const_1_31,8);
          appendarray(&buf_23,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_60);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_78: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                reset(&buf_63);
                reset(&buf_62);
                append(&buf_62,next[2],8);
                reset(&buf_57);
                concat(&buf_57,&buf_60);
                concat(&buf_57,&buf_29);
                for(i = 0; i < 2; i++)
                {  append(&buf_57,next[0 + i],8);
                }
                reset(&buf_48);
                reset(&buf_41);
                append(&buf_41,next[2],8);
                reset(&buf_40);
                reset(&buf_30);
                reset(&buf_29);
                append(&buf_29,next[2],8);
                reset(&buf_13);
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_23);
                concat(&buf_17,&buf_5);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_23);
                concat(&buf_23,&buf_27);
                concat(&buf_23,&buf_6);
                for(i = 0; i < 2; i++)
                {  append(&buf_23,next[0 + i],8);
                }
                reset(&buf_27);
                append(&buf_27,next[2],8);
                reset(&buf_5);
                append(&buf_5,next[2],8);
                reset(&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                consume(3);
                goto l1_100;
             }
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_60);
                   output(&buf_64);
                   output(&buf_65);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
                reset(&buf_57);
                concat(&buf_57,&buf_60);
                concat(&buf_57,&buf_64);
                concat(&buf_57,&buf_65);
                for(i = 0; i < 3; i++)
                {  append(&buf_57,next[0 + i],8);
                }
                reset(&buf_1);
                concat(&buf_1,&buf_9);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_40);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_23);
                concat(&buf_17,&buf_41);
                concat(&buf_17,&buf_48);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_23);
                concat(&buf_23,&buf_27);
                concat(&buf_23,&buf_49);
                concat(&buf_23,&buf_55);
                for(i = 0; i < 3; i++)
                {  append(&buf_23,next[0 + i],8);
                }
                consume(3);
                goto l1_14;
             }
             reset(&buf_63);
             concat(&buf_63,&buf_65);
             for(i = 0; i < 2; i++)
             {  append(&buf_63,next[0 + i],8);
             }
             reset(&buf_62);
             concat(&buf_62,&buf_64);
             for(i = 0; i < 2; i++)
             {  append(&buf_48,next[0 + i],8);
             }
             reset(&buf_42);
             concat(&buf_42,&buf_49);
             reset(&buf_49);
             concat(&buf_49,&buf_55);
             for(i = 0; i < 2; i++)
             {  append(&buf_49,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_40,next[0 + i],8);
             }
             reset(&buf_30);
             concat(&buf_30,&buf_32);
             for(i = 0; i < 2; i++)
             {  append(&buf_30,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_29,next[0 + i],8);
             }
             reset(&buf_14);
             concat(&buf_14,&buf_20);
             for(i = 0; i < 2; i++)
             {  append(&buf_14,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_13,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_6,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_5,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_4,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_19;
          }
          append(&buf_65,next[0],8);
          append(&buf_55,next[0],8);
          append(&buf_48,next[0],8);
          append(&buf_40,next[0],8);
          append(&buf_32,next[0],8);
          append(&buf_31,next[0],8);
          append(&buf_30,next[0],8);
          append(&buf_29,next[0],8);
          append(&buf_20,next[0],8);
          append(&buf_14,next[0],8);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_63;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_63);
             reset(&buf_62);
             append(&buf_62,next[1],8);
             reset(&buf_57);
             concat(&buf_57,&buf_60);
             concat(&buf_57,&buf_29);
             append(&buf_57,next[0],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[1],8);
             reset(&buf_40);
             reset(&buf_30);
             reset(&buf_29);
             append(&buf_29,next[1],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_6);
             append(&buf_23,next[0],8);
             reset(&buf_27);
             append(&buf_27,next[1],8);
             reset(&buf_5);
             append(&buf_5,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_100;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_60);
                output(&buf_64);
                output(&buf_65);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_52);
             concat(&buf_52,&buf_27);
             concat(&buf_52,&buf_49);
             concat(&buf_52,&buf_55);
             appendarray(&buf_52,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_41);
             concat(&buf_17,&buf_48);
             appendarray(&buf_17,const_1_32,16);
             consume(2);
             goto l1_13;
          }
          reset(&buf_44);
          concat(&buf_44,&buf_60);
          concat(&buf_44,&buf_29);
          appendarray(&buf_44,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_27);
          concat(&buf_9,&buf_6);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_115;
       }
       goto fail1;
l1_79: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_60);
             concat(&buf_60,&buf_29);
             for(i = 0; i < 2; i++)
             {  append(&buf_60,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_20;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_62);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_62,next[0],8);
          append(&buf_29,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_64;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_60);
          concat(&buf_60,&buf_29);
          appendarray(&buf_60,const_1_31,8);
          appendarray(&buf_27,const_1_31,8);
          appendarray(&buf_23,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_62);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_80: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                reset(&buf_65);
                reset(&buf_64);
                append(&buf_64,next[2],8);
                reset(&buf_60);
                concat(&buf_60,&buf_62);
                concat(&buf_60,&buf_30);
                for(i = 0; i < 2; i++)
                {  append(&buf_60,next[0 + i],8);
                }
                reset(&buf_55);
                reset(&buf_49);
                append(&buf_49,next[2],8);
                reset(&buf_48);
                reset(&buf_41);
                append(&buf_41,next[2],8);
                reset(&buf_40);
                reset(&buf_32);
                reset(&buf_31);
                append(&buf_31,next[2],8);
                reset(&buf_30);
                append(&buf_30,next[2],8);
                reset(&buf_20);
                reset(&buf_14);
                append(&buf_14,next[2],8);
                reset(&buf_13);
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_23);
                concat(&buf_17,&buf_5);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_23);
                concat(&buf_23,&buf_27);
                concat(&buf_23,&buf_6);
                for(i = 0; i < 2; i++)
                {  append(&buf_23,next[0 + i],8);
                }
                reset(&buf_27);
                concat(&buf_27,&buf_29);
                concat(&buf_27,&buf_7);
                for(i = 0; i < 2; i++)
                {  append(&buf_27,next[0 + i],8);
                }
                reset(&buf_29);
                append(&buf_29,next[2],8);
                reset(&buf_6);
                append(&buf_6,next[2],8);
                reset(&buf_5);
                append(&buf_5,next[2],8);
                reset(&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                consume(3);
                goto l1_107;
             }
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_62);
                   output(&buf_66);
                   output(&buf_67);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
                reset(&buf_60);
                concat(&buf_60,&buf_62);
                concat(&buf_60,&buf_66);
                concat(&buf_60,&buf_67);
                for(i = 0; i < 3; i++)
                {  append(&buf_60,next[0 + i],8);
                }
                reset(&buf_1);
                concat(&buf_1,&buf_9);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_40);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_23);
                concat(&buf_17,&buf_41);
                concat(&buf_17,&buf_48);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_23);
                concat(&buf_23,&buf_27);
                concat(&buf_23,&buf_49);
                concat(&buf_23,&buf_55);
                for(i = 0; i < 3; i++)
                {  append(&buf_23,next[0 + i],8);
                }
                reset(&buf_27);
                concat(&buf_27,&buf_29);
                concat(&buf_27,&buf_56);
                concat(&buf_27,&buf_59);
                for(i = 0; i < 3; i++)
                {  append(&buf_27,next[0 + i],8);
                }
                consume(3);
                goto l1_18;
             }
             reset(&buf_64);
             concat(&buf_64,&buf_67);
             for(i = 0; i < 2; i++)
             {  append(&buf_64,next[0 + i],8);
             }
             reset(&buf_63);
             concat(&buf_63,&buf_66);
             reset(&buf_50);
             concat(&buf_50,&buf_59);
             for(i = 0; i < 2; i++)
             {  append(&buf_50,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_48,next[0 + i],8);
             }
             reset(&buf_43);
             concat(&buf_43,&buf_56);
             reset(&buf_42);
             concat(&buf_42,&buf_49);
             reset(&buf_49);
             concat(&buf_49,&buf_55);
             for(i = 0; i < 2; i++)
             {  append(&buf_49,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_40,next[0 + i],8);
             }
             reset(&buf_31);
             concat(&buf_31,&buf_34);
             for(i = 0; i < 2; i++)
             {  append(&buf_31,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_30,next[0 + i],8);
             }
             reset(&buf_15);
             concat(&buf_15,&buf_25);
             for(i = 0; i < 2; i++)
             {  append(&buf_15,next[0 + i],8);
             }
             reset(&buf_14);
             concat(&buf_14,&buf_20);
             for(i = 0; i < 2; i++)
             {  append(&buf_14,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_13,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_7,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_6,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_5,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_4,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_23;
          }
          append(&buf_67,next[0],8);
          append(&buf_59,next[0],8);
          append(&buf_55,next[0],8);
          append(&buf_48,next[0],8);
          append(&buf_40,next[0],8);
          append(&buf_34,next[0],8);
          append(&buf_33,next[0],8);
          append(&buf_32,next[0],8);
          append(&buf_31,next[0],8);
          append(&buf_30,next[0],8);
          append(&buf_25,next[0],8);
          append(&buf_21,next[0],8);
          append(&buf_20,next[0],8);
          append(&buf_15,next[0],8);
          append(&buf_14,next[0],8);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_7,next[0],8);
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_65;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_65);
             reset(&buf_64);
             append(&buf_64,next[1],8);
             reset(&buf_60);
             concat(&buf_60,&buf_62);
             concat(&buf_60,&buf_30);
             append(&buf_60,next[0],8);
             reset(&buf_55);
             reset(&buf_49);
             append(&buf_49,next[1],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[1],8);
             reset(&buf_40);
             reset(&buf_32);
             reset(&buf_31);
             append(&buf_31,next[1],8);
             reset(&buf_30);
             append(&buf_30,next[1],8);
             reset(&buf_20);
             reset(&buf_14);
             append(&buf_14,next[1],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_6);
             append(&buf_23,next[0],8);
             reset(&buf_27);
             concat(&buf_27,&buf_29);
             concat(&buf_27,&buf_7);
             append(&buf_27,next[0],8);
             reset(&buf_29);
             append(&buf_29,next[1],8);
             reset(&buf_6);
             append(&buf_6,next[1],8);
             reset(&buf_5);
             append(&buf_5,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_107;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_62);
                output(&buf_66);
                output(&buf_67);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_57);
             concat(&buf_57,&buf_29);
             concat(&buf_57,&buf_56);
             concat(&buf_57,&buf_59);
             appendarray(&buf_57,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             reset(&buf_17);
             concat(&buf_17,&buf_23);
             concat(&buf_17,&buf_41);
             concat(&buf_17,&buf_48);
             appendarray(&buf_17,const_1_32,16);
             reset(&buf_23);
             concat(&buf_23,&buf_27);
             concat(&buf_23,&buf_49);
             concat(&buf_23,&buf_55);
             appendarray(&buf_23,const_1_32,16);
             consume(2);
             goto l1_17;
          }
          reset(&buf_52);
          concat(&buf_52,&buf_62);
          concat(&buf_52,&buf_30);
          appendarray(&buf_52,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_29);
          concat(&buf_17,&buf_7);
          appendarray(&buf_17,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_27);
          concat(&buf_9,&buf_6);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_23);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_114;
       }
       goto fail1;
l1_81: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                reset(&buf_67);
                reset(&buf_66);
                append(&buf_66,next[2],8);
                reset(&buf_62);
                concat(&buf_62,&buf_31);
                for(i = 0; i < 2; i++)
                {  append(&buf_62,next[0 + i],8);
                }
                reset(&buf_59);
                reset(&buf_56);
                append(&buf_56,next[2],8);
                reset(&buf_55);
                reset(&buf_49);
                append(&buf_49,next[2],8);
                reset(&buf_48);
                reset(&buf_41);
                append(&buf_41,next[2],8);
                reset(&buf_40);
                reset(&buf_34);
                reset(&buf_33);
                append(&buf_33,next[2],8);
                reset(&buf_32);
                append(&buf_32,next[2],8);
                reset(&buf_31);
                append(&buf_31,next[2],8);
                reset(&buf_30);
                append(&buf_30,next[2],8);
                reset(&buf_29);
                concat(&buf_29,&buf_8);
                for(i = 0; i < 2; i++)
                {  append(&buf_29,next[0 + i],8);
                }
                reset(&buf_27);
                concat(&buf_27,&buf_7);
                for(i = 0; i < 2; i++)
                {  append(&buf_27,next[0 + i],8);
                }
                reset(&buf_25);
                reset(&buf_23);
                concat(&buf_23,&buf_6);
                for(i = 0; i < 2; i++)
                {  append(&buf_23,next[0 + i],8);
                }
                reset(&buf_21);
                append(&buf_21,next[2],8);
                reset(&buf_20);
                reset(&buf_17);
                concat(&buf_17,&buf_5);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_15);
                append(&buf_15,next[2],8);
                reset(&buf_14);
                append(&buf_14,next[2],8);
                reset(&buf_13);
                reset(&buf_9);
                concat(&buf_9,&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_7);
                append(&buf_7,next[2],8);
                reset(&buf_6);
                append(&buf_6,next[2],8);
                reset(&buf_5);
                append(&buf_5,next[2],8);
                reset(&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                consume(3);
                goto l1_111;
             }
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_68);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
                reset(&buf_62);
                concat(&buf_62,&buf_68);
                for(i = 0; i < 3; i++)
                {  append(&buf_62,next[0 + i],8);
                }
                reset(&buf_29);
                concat(&buf_29,&buf_61);
                for(i = 0; i < 3; i++)
                {  append(&buf_29,next[0 + i],8);
                }
                reset(&buf_27);
                concat(&buf_27,&buf_59);
                for(i = 0; i < 3; i++)
                {  append(&buf_27,next[0 + i],8);
                }
                reset(&buf_23);
                concat(&buf_23,&buf_55);
                for(i = 0; i < 3; i++)
                {  append(&buf_23,next[0 + i],8);
                }
                reset(&buf_17);
                concat(&buf_17,&buf_48);
                for(i = 0; i < 3; i++)
                {  append(&buf_17,next[0 + i],8);
                }
                reset(&buf_1);
                concat(&buf_1,&buf_9);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                reset(&buf_9);
                concat(&buf_9,&buf_40);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                consume(3);
                goto l1_22;
             }
             reset(&buf_65);
             concat(&buf_65,&buf_68);
             for(i = 0; i < 2; i++)
             {  append(&buf_65,next[0 + i],8);
             }
             reset(&buf_51);
             concat(&buf_51,&buf_61);
             for(i = 0; i < 2; i++)
             {  append(&buf_51,next[0 + i],8);
             }
             reset(&buf_50);
             concat(&buf_50,&buf_59);
             for(i = 0; i < 2; i++)
             {  append(&buf_50,next[0 + i],8);
             }
             reset(&buf_49);
             concat(&buf_49,&buf_55);
             for(i = 0; i < 2; i++)
             {  append(&buf_49,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_48,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_40,next[0 + i],8);
             }
             reset(&buf_32);
             concat(&buf_32,&buf_36);
             for(i = 0; i < 2; i++)
             {  append(&buf_32,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_31,next[0 + i],8);
             }
             reset(&buf_16);
             concat(&buf_16,&buf_28);
             for(i = 0; i < 2; i++)
             {  append(&buf_16,next[0 + i],8);
             }
             reset(&buf_15);
             concat(&buf_15,&buf_25);
             for(i = 0; i < 2; i++)
             {  append(&buf_15,next[0 + i],8);
             }
             reset(&buf_14);
             concat(&buf_14,&buf_20);
             for(i = 0; i < 2; i++)
             {  append(&buf_14,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_13,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_8,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_7,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_6,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_5,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_4,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_25;
          }
          append(&buf_68,next[0],8);
          append(&buf_61,next[0],8);
          append(&buf_59,next[0],8);
          append(&buf_55,next[0],8);
          append(&buf_48,next[0],8);
          append(&buf_40,next[0],8);
          append(&buf_36,next[0],8);
          append(&buf_35,next[0],8);
          append(&buf_34,next[0],8);
          append(&buf_33,next[0],8);
          append(&buf_32,next[0],8);
          append(&buf_31,next[0],8);
          append(&buf_28,next[0],8);
          append(&buf_26,next[0],8);
          append(&buf_25,next[0],8);
          append(&buf_22,next[0],8);
          append(&buf_21,next[0],8);
          append(&buf_20,next[0],8);
          append(&buf_16,next[0],8);
          append(&buf_15,next[0],8);
          append(&buf_14,next[0],8);
          append(&buf_13,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_8,next[0],8);
          append(&buf_7,next[0],8);
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_66;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_67);
             reset(&buf_66);
             append(&buf_66,next[1],8);
             reset(&buf_62);
             concat(&buf_62,&buf_31);
             append(&buf_62,next[0],8);
             reset(&buf_59);
             reset(&buf_56);
             append(&buf_56,next[1],8);
             reset(&buf_55);
             reset(&buf_49);
             append(&buf_49,next[1],8);
             reset(&buf_48);
             reset(&buf_41);
             append(&buf_41,next[1],8);
             reset(&buf_40);
             reset(&buf_34);
             reset(&buf_33);
             append(&buf_33,next[1],8);
             reset(&buf_32);
             append(&buf_32,next[1],8);
             reset(&buf_31);
             append(&buf_31,next[1],8);
             reset(&buf_30);
             append(&buf_30,next[1],8);
             reset(&buf_29);
             concat(&buf_29,&buf_8);
             append(&buf_29,next[0],8);
             reset(&buf_27);
             concat(&buf_27,&buf_7);
             append(&buf_27,next[0],8);
             reset(&buf_25);
             reset(&buf_23);
             concat(&buf_23,&buf_6);
             append(&buf_23,next[0],8);
             reset(&buf_21);
             append(&buf_21,next[1],8);
             reset(&buf_20);
             reset(&buf_17);
             concat(&buf_17,&buf_5);
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             reset(&buf_15);
             append(&buf_15,next[1],8);
             reset(&buf_14);
             append(&buf_14,next[1],8);
             reset(&buf_13);
             reset(&buf_9);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_7);
             append(&buf_7,next[1],8);
             reset(&buf_6);
             append(&buf_6,next[1],8);
             reset(&buf_5);
             append(&buf_5,next[1],8);
             reset(&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_111;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_68);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_60);
             concat(&buf_60,&buf_61);
             appendarray(&buf_60,const_1_32,16);
             reset(&buf_27);
             concat(&buf_27,&buf_59);
             appendarray(&buf_27,const_1_32,16);
             reset(&buf_23);
             concat(&buf_23,&buf_55);
             appendarray(&buf_23,const_1_32,16);
             reset(&buf_17);
             concat(&buf_17,&buf_48);
             appendarray(&buf_17,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             reset(&buf_9);
             concat(&buf_9,&buf_40);
             appendarray(&buf_9,const_1_32,16);
             consume(2);
             goto l1_21;
          }
          reset(&buf_57);
          concat(&buf_57,&buf_31);
          appendarray(&buf_57,const_1_31,8);
          reset(&buf_23);
          concat(&buf_23,&buf_8);
          appendarray(&buf_23,const_1_31,8);
          reset(&buf_17);
          concat(&buf_17,&buf_7);
          appendarray(&buf_17,const_1_31,8);
          reset(&buf_9);
          concat(&buf_9,&buf_6);
          appendarray(&buf_9,const_1_31,8);
          reset(&buf_1);
          concat(&buf_1,&buf_5);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_113;
       }
       goto fail1;
l1_82: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                output(&buf_1);
                for(i = 0; i < 3; i++)
                {  outputconst(next[0 + i],8);
                }
                consume(3);
                goto l1_28;
             }
             if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
             {
                output(&buf_37);
                for(i = 0; i < 4; i++)
                {  outputconst(next[0 + i],8);
                }
                outputarray(const_1_0,8);
                consume(4);
                goto l1_38;
             }
          }
          append(&buf_37,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_67;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             output(&buf_1);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_28;
          }
          if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
          {
             output(&buf_37);
             outputarray(const_1_39,32);
             consume(3);
             goto l1_38;
          }
       }
       goto fail1;
l1_83: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_37);
             concat(&buf_37,&buf_9);
             for(i = 0; i < 2; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_119;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_44);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_44,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_68;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_37);
          concat(&buf_37,&buf_9);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_44);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_84: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
                {
                   output(&buf_9);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   consume(4);
                   goto l1_29;
                }
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_44);
                   output(&buf_52);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_121;
          }
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_69;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                output(&buf_9);
                for(i = 0; i < 3; i++)
                {  outputconst(next[0 + i],8);
                }
                consume(3);
                goto l1_29;
             }
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_44);
                output(&buf_52);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
          }
          reset(&buf_37);
          concat(&buf_37,&buf_44);
          concat(&buf_37,&buf_17);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_118;
       }
       goto fail1;
l1_85: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_9);
          outputarray(const_1_13,16);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_37);
             concat(&buf_37,&buf_9);
             appendarray(&buf_37,const_1_11,8);
             for(i = 0; i < 2; i++)
             {  append(&buf_37,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_119;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_44);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_44,next[0],8);
          appendarray(&buf_9,const_1_11,8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_68;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_37);
          concat(&buf_37,&buf_9);
          appendarray(&buf_37,const_1_14,16);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_44);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_86: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_9);
          output(&buf_11);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          if (((avail >= 2) && ((next[1] == '.') && 1)))
          {
             output(&buf_9);
             output(&buf_46);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_6;
          }
          reset(&buf_52);
          append(&buf_52,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_17);
          append(&buf_17,next[0],8);
          concat(&buf_9,&buf_3);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_170;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_37);
          concat(&buf_37,&buf_9);
          concat(&buf_37,&buf_3);
          appendarray(&buf_37,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_119;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_52);
          append(&buf_52,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_17);
          append(&buf_17,next[0],8);
          concat(&buf_9,&buf_3);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_170;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_44);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_87: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_70;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_88: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_17);
          outputarray(const_1_13,16);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             appendarray(&buf_44,const_1_11,8);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_52,next[0],8);
          appendarray(&buf_17,const_1_11,8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_70;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_14,16);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_89: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_17);
          output(&buf_12);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          if (((avail >= 2) && ((next[1] == '.') && 1)))
          {
             output(&buf_17);
             output(&buf_47);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_6;
          }
          reset(&buf_57);
          append(&buf_57,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          concat(&buf_17,&buf_4);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_171;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          concat(&buf_44,&buf_4);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_57);
          append(&buf_57,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          concat(&buf_17,&buf_4);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_171;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_90: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_52,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_71;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_91: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_17);
          outputarray(const_1_13,16);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_17);
             appendarray(&buf_44,const_1_11,8);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_11;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_52);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_52,next[0],8);
          appendarray(&buf_17,const_1_11,8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_71;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          appendarray(&buf_44,const_1_14,16);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_92: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_17);
          output(&buf_12);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          if (((avail >= 2) && ((next[1] == '.') && 1)))
          {
             output(&buf_17);
             output(&buf_47);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_6;
          }
          reset(&buf_57);
          append(&buf_57,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          concat(&buf_17,&buf_4);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_172;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_44);
          concat(&buf_44,&buf_17);
          concat(&buf_44,&buf_4);
          appendarray(&buf_44,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_57);
          append(&buf_57,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_23);
          append(&buf_23,next[0],8);
          concat(&buf_17,&buf_4);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_172;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_52);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_93: if (!readnext(1, 4))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
             {
                reset(&buf_44);
                concat(&buf_44,&buf_52);
                concat(&buf_44,&buf_23);
                for(i = 0; i < 3; i++)
                {  append(&buf_44,next[0 + i],8);
                }
                reset(&buf_52);
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_4);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                reset(&buf_17);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                consume(3);
                goto l1_84;
             }
             if (((avail >= 3) && ((next[2] == ':') && 1)))
             {
                if (((avail >= 4) && ((next[3] == ']') && 1)))
                {
                   output(&buf_52);
                   output(&buf_57);
                   output(&buf_60);
                   for(i = 0; i < 4; i++)
                   {  outputconst(next[0 + i],8);
                   }
                   outputarray(const_1_0,8);
                   consume(4);
                   goto l1_38;
                }
                reset(&buf_44);
                concat(&buf_44,&buf_52);
                concat(&buf_44,&buf_57);
                concat(&buf_44,&buf_60);
                for(i = 0; i < 3; i++)
                {  append(&buf_44,next[0 + i],8);
                }
                reset(&buf_1);
                concat(&buf_1,&buf_9);
                for(i = 0; i < 3; i++)
                {  append(&buf_1,next[0 + i],8);
                }
                reset(&buf_9);
                concat(&buf_9,&buf_17);
                concat(&buf_9,&buf_40);
                for(i = 0; i < 3; i++)
                {  append(&buf_9,next[0 + i],8);
                }
                consume(3);
                goto l1_120;
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_60,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_40,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_27,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_23,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_4,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_10;
          }
          append(&buf_60,next[0],8);
          append(&buf_40,next[0],8);
          append(&buf_27,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_72;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
          {
             reset(&buf_44);
             concat(&buf_44,&buf_52);
             concat(&buf_44,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_44,next[0 + i],8);
             }
             reset(&buf_52);
             reset(&buf_9);
             concat(&buf_9,&buf_17);
             concat(&buf_9,&buf_4);
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             reset(&buf_17);
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_84;
          }
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             if (((avail >= 3) && ((next[2] == ']') && 1)))
             {
                output(&buf_52);
                output(&buf_57);
                output(&buf_60);
                outputarray(const_1_39,32);
                consume(3);
                goto l1_38;
             }
             reset(&buf_37);
             concat(&buf_37,&buf_17);
             concat(&buf_37,&buf_40);
             appendarray(&buf_37,const_1_32,16);
             reset(&buf_1);
             concat(&buf_1,&buf_9);
             appendarray(&buf_1,const_1_32,16);
             consume(2);
             goto l1_119;
          }
          output(&buf_52);
          output(&buf_23);
          outputarray(const_1_31,8);
          consume(1);
          goto l1_9;
       }
       goto fail1;
l1_94: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_73;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_95: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_23);
          outputarray(const_1_13,16);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             appendarray(&buf_52,const_1_11,8);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_57,next[0],8);
          appendarray(&buf_23,const_1_11,8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_73;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_14,16);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_96: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_23);
          output(&buf_13);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          if (((avail >= 2) && ((next[1] == '.') && 1)))
          {
             output(&buf_23);
             output(&buf_48);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_6;
          }
          reset(&buf_60);
          append(&buf_60,next[0],8);
          reset(&buf_41);
          append(&buf_41,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          concat(&buf_23,&buf_5);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_173;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          concat(&buf_52,&buf_5);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_60);
          append(&buf_60,next[0],8);
          reset(&buf_41);
          append(&buf_41,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          concat(&buf_23,&buf_5);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_173;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_97: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_57,next[0],8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_74;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_98: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_23);
          outputarray(const_1_13,16);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
       {
          if (((avail >= 2) && ((next[1] == ':') && 1)))
          {
             reset(&buf_52);
             concat(&buf_52,&buf_23);
             appendarray(&buf_52,const_1_11,8);
             for(i = 0; i < 2; i++)
             {  append(&buf_52,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_17,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_9,next[0 + i],8);
             }
             for(i = 0; i < 2; i++)
             {  append(&buf_1,next[0 + i],8);
             }
             consume(2);
             goto l1_12;
          }
          if (((avail >= 2) && ((next[1] == ']') && 1)))
          {
             output(&buf_57);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_0,8);
             consume(2);
             goto l1_38;
          }
          append(&buf_57,next[0],8);
          appendarray(&buf_23,const_1_11,8);
          append(&buf_23,next[0],8);
          append(&buf_17,next[0],8);
          append(&buf_9,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_74;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          appendarray(&buf_52,const_1_14,16);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_99: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == '.') && 1)))
       {
          output(&buf_23);
          output(&buf_13);
          outputarray(const_1_9,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          if (((avail >= 2) && ((next[1] == '.') && 1)))
          {
             output(&buf_23);
             output(&buf_48);
             for(i = 0; i < 2; i++)
             {  outputconst(next[0 + i],8);
             }
             consume(2);
             goto l1_6;
          }
          reset(&buf_60);
          append(&buf_60,next[0],8);
          reset(&buf_41);
          append(&buf_41,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          concat(&buf_23,&buf_5);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_174;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_52);
          concat(&buf_52,&buf_23);
          concat(&buf_52,&buf_5);
          appendarray(&buf_52,const_1_31,8);
          appendarray(&buf_17,const_1_31,8);
          appendarray(&buf_9,const_1_31,8);
          appendarray(&buf_1,const_1_31,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
       {
          reset(&buf_60);
          append(&buf_60,next[0],8);
          reset(&buf_41);
          append(&buf_41,next[0],8);
          reset(&buf_40);
          append(&buf_40,next[0],8);
          reset(&buf_39);
          append(&buf_39,next[0],8);
          reset(&buf_38);
          append(&buf_38,next[0],8);
          reset(&buf_27);
          append(&buf_27,next[0],8);
          concat(&buf_23,&buf_5);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          append(&buf_4,next[0],8);
          reset(&buf_3);
          append(&buf_3,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_174;
       }
       if (((avail >= 1) && ((next[0] == ']') && 1)))
       {
          output(&buf_57);
          outputarray(const_1_41,16);
          consume(1);
          goto l1_38;
       }
       goto fail1;
l1_100: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_60);
                 reset(&buf_52);
                 concat(&buf_52,&buf_57);
                 concat(&buf_52,&buf_27);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 reset(&buf_57);
                 append(&buf_57,next[2],8);
                 reset(&buf_40);
                 reset(&buf_27);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_5);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 append(&buf_23,next[2],8);
                 reset(&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_93;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_57);
                    output(&buf_62);
                    output(&buf_63);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 reset(&buf_52);
                 concat(&buf_52,&buf_57);
                 concat(&buf_52,&buf_62);
                 concat(&buf_52,&buf_63);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_40);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_41);
                 concat(&buf_17,&buf_48);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_27;
              }
              reset(&buf_60);
              concat(&buf_60,&buf_62);
              reset(&buf_62);
              concat(&buf_62,&buf_63);
              for(i = 0; i < 2; i++)
              {  append(&buf_62,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_40,next[0 + i],8);
              }
              reset(&buf_29);
              concat(&buf_29,&buf_30);
              for(i = 0; i < 2; i++)
              {  append(&buf_29,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_15;
           }
           append(&buf_63,next[0],8);
           append(&buf_48,next[0],8);
           append(&buf_40,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_75;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_60);
              reset(&buf_52);
              concat(&buf_52,&buf_57);
              concat(&buf_52,&buf_27);
              append(&buf_52,next[0],8);
              reset(&buf_57);
              append(&buf_57,next[1],8);
              reset(&buf_40);
              reset(&buf_27);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_23);
              append(&buf_23,next[1],8);
              reset(&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_93;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_62);
                 output(&buf_63);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_23);
              concat(&buf_44,&buf_41);
              concat(&buf_44,&buf_48);
              appendarray(&buf_44,const_1_32,16);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              appendarray(&buf_1,const_1_32,16);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_40);
              appendarray(&buf_9,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_57);
           concat(&buf_37,&buf_27);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_23);
           concat(&buf_1,&buf_5);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_101: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_57);
              concat(&buf_57,&buf_27);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_16;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_60);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_60,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_76;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           appendarray(&buf_57,const_1_31,8);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_102: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_27);
           outputarray(const_1_13,16);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_57);
              concat(&buf_57,&buf_27);
              appendarray(&buf_57,const_1_11,8);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_16;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_60);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_60,next[0],8);
           appendarray(&buf_27,const_1_11,8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_76;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           appendarray(&buf_57,const_1_14,16);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_103: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_27);
           output(&buf_14);
           outputarray(const_1_9,8);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              output(&buf_27);
              output(&buf_49);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_6;
           }
           reset(&buf_62);
           append(&buf_62,next[0],8);
           reset(&buf_42);
           append(&buf_42,next[0],8);
           reset(&buf_41);
           append(&buf_41,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           concat(&buf_27,&buf_6);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_175;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           concat(&buf_57,&buf_6);
           appendarray(&buf_57,const_1_31,8);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_62);
           append(&buf_62,next[0],8);
           reset(&buf_42);
           append(&buf_42,next[0],8);
           reset(&buf_41);
           append(&buf_41,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           concat(&buf_27,&buf_6);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_175;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_104: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_57);
              concat(&buf_57,&buf_27);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_16;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_60);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_60,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_77;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           appendarray(&buf_57,const_1_31,8);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_105: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_27);
           outputarray(const_1_13,16);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_57);
              concat(&buf_57,&buf_27);
              appendarray(&buf_57,const_1_11,8);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_16;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_60);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_60,next[0],8);
           appendarray(&buf_27,const_1_11,8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_77;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           appendarray(&buf_57,const_1_14,16);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_106: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_27);
           output(&buf_14);
           outputarray(const_1_9,8);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              output(&buf_27);
              output(&buf_49);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_6;
           }
           reset(&buf_62);
           append(&buf_62,next[0],8);
           reset(&buf_42);
           append(&buf_42,next[0],8);
           reset(&buf_41);
           append(&buf_41,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           concat(&buf_27,&buf_6);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_176;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           concat(&buf_57,&buf_6);
           appendarray(&buf_57,const_1_31,8);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_62);
           append(&buf_62,next[0],8);
           reset(&buf_42);
           append(&buf_42,next[0],8);
           reset(&buf_41);
           append(&buf_41,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           concat(&buf_27,&buf_6);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_176;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_107: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_63);
                 reset(&buf_62);
                 append(&buf_62,next[2],8);
                 reset(&buf_57);
                 concat(&buf_57,&buf_60);
                 concat(&buf_57,&buf_29);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 reset(&buf_48);
                 reset(&buf_41);
                 append(&buf_41,next[2],8);
                 reset(&buf_40);
                 reset(&buf_30);
                 reset(&buf_29);
                 append(&buf_29,next[2],8);
                 reset(&buf_13);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_5);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 concat(&buf_23,&buf_27);
                 concat(&buf_23,&buf_6);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 reset(&buf_5);
                 append(&buf_5,next[2],8);
                 reset(&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_100;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_60);
                    output(&buf_64);
                    output(&buf_65);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 reset(&buf_57);
                 concat(&buf_57,&buf_60);
                 concat(&buf_57,&buf_64);
                 concat(&buf_57,&buf_65);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_40);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_41);
                 concat(&buf_17,&buf_48);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 concat(&buf_23,&buf_27);
                 concat(&buf_23,&buf_49);
                 concat(&buf_23,&buf_55);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_14;
              }
              reset(&buf_63);
              concat(&buf_63,&buf_65);
              for(i = 0; i < 2; i++)
              {  append(&buf_63,next[0 + i],8);
              }
              reset(&buf_62);
              concat(&buf_62,&buf_64);
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              reset(&buf_42);
              concat(&buf_42,&buf_49);
              reset(&buf_49);
              concat(&buf_49,&buf_55);
              for(i = 0; i < 2; i++)
              {  append(&buf_49,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_40,next[0 + i],8);
              }
              reset(&buf_30);
              concat(&buf_30,&buf_32);
              for(i = 0; i < 2; i++)
              {  append(&buf_30,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_29,next[0 + i],8);
              }
              reset(&buf_14);
              concat(&buf_14,&buf_20);
              for(i = 0; i < 2; i++)
              {  append(&buf_14,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_6,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_19;
           }
           append(&buf_65,next[0],8);
           append(&buf_55,next[0],8);
           append(&buf_48,next[0],8);
           append(&buf_40,next[0],8);
           append(&buf_32,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_20,next[0],8);
           append(&buf_14,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_6,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_78;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_63);
              reset(&buf_62);
              append(&buf_62,next[1],8);
              reset(&buf_57);
              concat(&buf_57,&buf_60);
              concat(&buf_57,&buf_29);
              append(&buf_57,next[0],8);
              reset(&buf_48);
              reset(&buf_41);
              append(&buf_41,next[1],8);
              reset(&buf_40);
              reset(&buf_30);
              reset(&buf_29);
              append(&buf_29,next[1],8);
              reset(&buf_13);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_23);
              concat(&buf_23,&buf_27);
              concat(&buf_23,&buf_6);
              append(&buf_23,next[0],8);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_5);
              append(&buf_5,next[1],8);
              reset(&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_100;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_60);
                 output(&buf_64);
                 output(&buf_65);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_27);
              concat(&buf_52,&buf_49);
              concat(&buf_52,&buf_55);
              appendarray(&buf_52,const_1_32,16);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              appendarray(&buf_1,const_1_32,16);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_40);
              appendarray(&buf_9,const_1_32,16);
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_41);
              concat(&buf_17,&buf_48);
              appendarray(&buf_17,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_60);
           concat(&buf_44,&buf_29);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_27);
           concat(&buf_9,&buf_6);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_23);
           concat(&buf_1,&buf_5);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_108: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_60);
              concat(&buf_60,&buf_29);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_20;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_62);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_62,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_79;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_60);
           concat(&buf_60,&buf_29);
           appendarray(&buf_60,const_1_31,8);
           appendarray(&buf_27,const_1_31,8);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_20;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_62);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_109: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           outputarray(const_1_34,32);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_60);
              appendarray(&buf_60,const_1_33,24);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              reset(&buf_27);
              appendarray(&buf_27,const_1_33,24);
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              reset(&buf_23);
              appendarray(&buf_23,const_1_33,24);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              reset(&buf_17);
              appendarray(&buf_17,const_1_33,24);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_9);
              appendarray(&buf_9,const_1_33,24);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_1);
              appendarray(&buf_1,const_1_33,24);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_20;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              outputarray(const_1_33,24);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           reset(&buf_62);
           appendarray(&buf_62,const_1_33,24);
           append(&buf_62,next[0],8);
           reset(&buf_29);
           appendarray(&buf_29,const_1_33,24);
           append(&buf_29,next[0],8);
           reset(&buf_27);
           appendarray(&buf_27,const_1_33,24);
           append(&buf_27,next[0],8);
           reset(&buf_23);
           appendarray(&buf_23,const_1_33,24);
           append(&buf_23,next[0],8);
           reset(&buf_17);
           appendarray(&buf_17,const_1_33,24);
           append(&buf_17,next[0],8);
           reset(&buf_9);
           appendarray(&buf_9,const_1_33,24);
           append(&buf_9,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_33,24);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_79;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_60);
           appendarray(&buf_60,const_1_35,32);
           reset(&buf_27);
           appendarray(&buf_27,const_1_35,32);
           reset(&buf_23);
           appendarray(&buf_23,const_1_35,32);
           reset(&buf_17);
           appendarray(&buf_17,const_1_35,32);
           reset(&buf_9);
           appendarray(&buf_9,const_1_35,32);
           reset(&buf_1);
           appendarray(&buf_1,const_1_35,32);
           consume(1);
           goto l1_20;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           outputarray(const_1_36,40);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_110: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           outputarray(const_1_32,16);
           output(&buf_15);
           outputarray(const_1_9,8);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              outputarray(const_1_32,16);
              output(&buf_50);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_6;
           }
           reset(&buf_63);
           append(&buf_63,next[0],8);
           reset(&buf_43);
           append(&buf_43,next[0],8);
           reset(&buf_42);
           append(&buf_42,next[0],8);
           reset(&buf_41);
           append(&buf_41,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_30);
           append(&buf_30,next[0],8);
           reset(&buf_29);
           appendarray(&buf_29,const_1_32,16);
           concat(&buf_29,&buf_7);
           reset(&buf_7);
           append(&buf_7,next[0],8);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_177;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_60);
           appendarray(&buf_60,const_1_32,16);
           concat(&buf_60,&buf_7);
           appendarray(&buf_60,const_1_31,8);
           appendarray(&buf_27,const_1_31,8);
           appendarray(&buf_23,const_1_31,8);
           appendarray(&buf_17,const_1_31,8);
           appendarray(&buf_9,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_20;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_63);
           append(&buf_63,next[0],8);
           reset(&buf_43);
           append(&buf_43,next[0],8);
           reset(&buf_42);
           append(&buf_42,next[0],8);
           reset(&buf_41);
           append(&buf_41,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_30);
           append(&buf_30,next[0],8);
           reset(&buf_29);
           appendarray(&buf_29,const_1_32,16);
           concat(&buf_29,&buf_7);
           reset(&buf_7);
           append(&buf_7,next[0],8);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_177;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_62);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_111: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_65);
                 reset(&buf_64);
                 append(&buf_64,next[2],8);
                 reset(&buf_60);
                 concat(&buf_60,&buf_62);
                 concat(&buf_60,&buf_30);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_60,next[0 + i],8);
                 }
                 reset(&buf_55);
                 reset(&buf_49);
                 append(&buf_49,next[2],8);
                 reset(&buf_48);
                 reset(&buf_41);
                 append(&buf_41,next[2],8);
                 reset(&buf_40);
                 reset(&buf_32);
                 reset(&buf_31);
                 append(&buf_31,next[2],8);
                 reset(&buf_30);
                 append(&buf_30,next[2],8);
                 reset(&buf_20);
                 reset(&buf_14);
                 append(&buf_14,next[2],8);
                 reset(&buf_13);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_5);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 concat(&buf_23,&buf_27);
                 concat(&buf_23,&buf_6);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_27);
                 concat(&buf_27,&buf_29);
                 concat(&buf_27,&buf_7);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_27,next[0 + i],8);
                 }
                 reset(&buf_29);
                 append(&buf_29,next[2],8);
                 reset(&buf_6);
                 append(&buf_6,next[2],8);
                 reset(&buf_5);
                 append(&buf_5,next[2],8);
                 reset(&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_107;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_62);
                    output(&buf_66);
                    output(&buf_67);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 reset(&buf_60);
                 concat(&buf_60,&buf_62);
                 concat(&buf_60,&buf_66);
                 concat(&buf_60,&buf_67);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_60,next[0 + i],8);
                 }
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_40);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_41);
                 concat(&buf_17,&buf_48);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 concat(&buf_23,&buf_27);
                 concat(&buf_23,&buf_49);
                 concat(&buf_23,&buf_55);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_27);
                 concat(&buf_27,&buf_29);
                 concat(&buf_27,&buf_56);
                 concat(&buf_27,&buf_59);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_27,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_18;
              }
              reset(&buf_64);
              concat(&buf_64,&buf_67);
              for(i = 0; i < 2; i++)
              {  append(&buf_64,next[0 + i],8);
              }
              reset(&buf_63);
              concat(&buf_63,&buf_66);
              reset(&buf_50);
              concat(&buf_50,&buf_59);
              for(i = 0; i < 2; i++)
              {  append(&buf_50,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              reset(&buf_43);
              concat(&buf_43,&buf_56);
              reset(&buf_42);
              concat(&buf_42,&buf_49);
              reset(&buf_49);
              concat(&buf_49,&buf_55);
              for(i = 0; i < 2; i++)
              {  append(&buf_49,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_40,next[0 + i],8);
              }
              reset(&buf_31);
              concat(&buf_31,&buf_34);
              for(i = 0; i < 2; i++)
              {  append(&buf_31,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_30,next[0 + i],8);
              }
              reset(&buf_15);
              concat(&buf_15,&buf_25);
              for(i = 0; i < 2; i++)
              {  append(&buf_15,next[0 + i],8);
              }
              reset(&buf_14);
              concat(&buf_14,&buf_20);
              for(i = 0; i < 2; i++)
              {  append(&buf_14,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_7,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_6,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_23;
           }
           append(&buf_67,next[0],8);
           append(&buf_59,next[0],8);
           append(&buf_55,next[0],8);
           append(&buf_48,next[0],8);
           append(&buf_40,next[0],8);
           append(&buf_34,next[0],8);
           append(&buf_33,next[0],8);
           append(&buf_32,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_25,next[0],8);
           append(&buf_21,next[0],8);
           append(&buf_20,next[0],8);
           append(&buf_15,next[0],8);
           append(&buf_14,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_7,next[0],8);
           append(&buf_6,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_80;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_65);
              reset(&buf_64);
              append(&buf_64,next[1],8);
              reset(&buf_60);
              concat(&buf_60,&buf_62);
              concat(&buf_60,&buf_30);
              append(&buf_60,next[0],8);
              reset(&buf_55);
              reset(&buf_49);
              append(&buf_49,next[1],8);
              reset(&buf_48);
              reset(&buf_41);
              append(&buf_41,next[1],8);
              reset(&buf_40);
              reset(&buf_32);
              reset(&buf_31);
              append(&buf_31,next[1],8);
              reset(&buf_30);
              append(&buf_30,next[1],8);
              reset(&buf_20);
              reset(&buf_14);
              append(&buf_14,next[1],8);
              reset(&buf_13);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_23);
              concat(&buf_23,&buf_27);
              concat(&buf_23,&buf_6);
              append(&buf_23,next[0],8);
              reset(&buf_27);
              concat(&buf_27,&buf_29);
              concat(&buf_27,&buf_7);
              append(&buf_27,next[0],8);
              reset(&buf_29);
              append(&buf_29,next[1],8);
              reset(&buf_6);
              append(&buf_6,next[1],8);
              reset(&buf_5);
              append(&buf_5,next[1],8);
              reset(&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_107;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_62);
                 output(&buf_66);
                 output(&buf_67);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_57);
              concat(&buf_57,&buf_29);
              concat(&buf_57,&buf_56);
              concat(&buf_57,&buf_59);
              appendarray(&buf_57,const_1_32,16);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              appendarray(&buf_1,const_1_32,16);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_40);
              appendarray(&buf_9,const_1_32,16);
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_41);
              concat(&buf_17,&buf_48);
              appendarray(&buf_17,const_1_32,16);
              reset(&buf_23);
              concat(&buf_23,&buf_27);
              concat(&buf_23,&buf_49);
              concat(&buf_23,&buf_55);
              appendarray(&buf_23,const_1_32,16);
              consume(2);
              goto l1_17;
           }
           reset(&buf_52);
           concat(&buf_52,&buf_62);
           concat(&buf_52,&buf_30);
           appendarray(&buf_52,const_1_31,8);
           reset(&buf_17);
           concat(&buf_17,&buf_29);
           concat(&buf_17,&buf_7);
           appendarray(&buf_17,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_27);
           concat(&buf_9,&buf_6);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_23);
           concat(&buf_1,&buf_5);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_112: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_67);
                 reset(&buf_66);
                 append(&buf_66,next[2],8);
                 reset(&buf_62);
                 concat(&buf_62,&buf_31);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_62,next[0 + i],8);
                 }
                 reset(&buf_59);
                 reset(&buf_56);
                 append(&buf_56,next[2],8);
                 reset(&buf_55);
                 reset(&buf_49);
                 append(&buf_49,next[2],8);
                 reset(&buf_48);
                 reset(&buf_41);
                 append(&buf_41,next[2],8);
                 reset(&buf_40);
                 reset(&buf_34);
                 reset(&buf_33);
                 append(&buf_33,next[2],8);
                 reset(&buf_32);
                 append(&buf_32,next[2],8);
                 reset(&buf_31);
                 append(&buf_31,next[2],8);
                 reset(&buf_30);
                 append(&buf_30,next[2],8);
                 reset(&buf_29);
                 concat(&buf_29,&buf_8);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_29,next[0 + i],8);
                 }
                 reset(&buf_27);
                 concat(&buf_27,&buf_7);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_27,next[0 + i],8);
                 }
                 reset(&buf_25);
                 reset(&buf_23);
                 concat(&buf_23,&buf_6);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_21);
                 append(&buf_21,next[2],8);
                 reset(&buf_20);
                 reset(&buf_17);
                 concat(&buf_17,&buf_5);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_15);
                 append(&buf_15,next[2],8);
                 reset(&buf_14);
                 append(&buf_14,next[2],8);
                 reset(&buf_13);
                 reset(&buf_9);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_7);
                 append(&buf_7,next[2],8);
                 reset(&buf_6);
                 append(&buf_6,next[2],8);
                 reset(&buf_5);
                 append(&buf_5,next[2],8);
                 reset(&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_111;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_68);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 reset(&buf_62);
                 concat(&buf_62,&buf_68);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_62,next[0 + i],8);
                 }
                 reset(&buf_29);
                 concat(&buf_29,&buf_61);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_29,next[0 + i],8);
                 }
                 reset(&buf_27);
                 concat(&buf_27,&buf_59);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_27,next[0 + i],8);
                 }
                 reset(&buf_23);
                 concat(&buf_23,&buf_55);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_17);
                 concat(&buf_17,&buf_48);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_9);
                 concat(&buf_9,&buf_40);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_22;
              }
              reset(&buf_65);
              concat(&buf_65,&buf_68);
              for(i = 0; i < 2; i++)
              {  append(&buf_65,next[0 + i],8);
              }
              reset(&buf_51);
              concat(&buf_51,&buf_61);
              for(i = 0; i < 2; i++)
              {  append(&buf_51,next[0 + i],8);
              }
              reset(&buf_50);
              concat(&buf_50,&buf_59);
              for(i = 0; i < 2; i++)
              {  append(&buf_50,next[0 + i],8);
              }
              reset(&buf_49);
              concat(&buf_49,&buf_55);
              for(i = 0; i < 2; i++)
              {  append(&buf_49,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_40,next[0 + i],8);
              }
              reset(&buf_32);
              concat(&buf_32,&buf_36);
              for(i = 0; i < 2; i++)
              {  append(&buf_32,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_31,next[0 + i],8);
              }
              reset(&buf_16);
              concat(&buf_16,&buf_28);
              for(i = 0; i < 2; i++)
              {  append(&buf_16,next[0 + i],8);
              }
              reset(&buf_15);
              concat(&buf_15,&buf_25);
              for(i = 0; i < 2; i++)
              {  append(&buf_15,next[0 + i],8);
              }
              reset(&buf_14);
              concat(&buf_14,&buf_20);
              for(i = 0; i < 2; i++)
              {  append(&buf_14,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_8,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_7,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_6,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_25;
           }
           append(&buf_68,next[0],8);
           append(&buf_61,next[0],8);
           append(&buf_59,next[0],8);
           append(&buf_55,next[0],8);
           append(&buf_48,next[0],8);
           append(&buf_40,next[0],8);
           append(&buf_36,next[0],8);
           append(&buf_35,next[0],8);
           append(&buf_34,next[0],8);
           append(&buf_33,next[0],8);
           append(&buf_32,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_28,next[0],8);
           append(&buf_26,next[0],8);
           append(&buf_25,next[0],8);
           append(&buf_22,next[0],8);
           append(&buf_21,next[0],8);
           append(&buf_20,next[0],8);
           append(&buf_16,next[0],8);
           append(&buf_15,next[0],8);
           append(&buf_14,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_8,next[0],8);
           append(&buf_7,next[0],8);
           append(&buf_6,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_81;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_67);
              reset(&buf_66);
              append(&buf_66,next[1],8);
              reset(&buf_62);
              concat(&buf_62,&buf_31);
              append(&buf_62,next[0],8);
              reset(&buf_59);
              reset(&buf_56);
              append(&buf_56,next[1],8);
              reset(&buf_55);
              reset(&buf_49);
              append(&buf_49,next[1],8);
              reset(&buf_48);
              reset(&buf_41);
              append(&buf_41,next[1],8);
              reset(&buf_40);
              reset(&buf_34);
              reset(&buf_33);
              append(&buf_33,next[1],8);
              reset(&buf_32);
              append(&buf_32,next[1],8);
              reset(&buf_31);
              append(&buf_31,next[1],8);
              reset(&buf_30);
              append(&buf_30,next[1],8);
              reset(&buf_29);
              concat(&buf_29,&buf_8);
              append(&buf_29,next[0],8);
              reset(&buf_27);
              concat(&buf_27,&buf_7);
              append(&buf_27,next[0],8);
              reset(&buf_25);
              reset(&buf_23);
              concat(&buf_23,&buf_6);
              append(&buf_23,next[0],8);
              reset(&buf_21);
              append(&buf_21,next[1],8);
              reset(&buf_20);
              reset(&buf_17);
              concat(&buf_17,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_15);
              append(&buf_15,next[1],8);
              reset(&buf_14);
              append(&buf_14,next[1],8);
              reset(&buf_13);
              reset(&buf_9);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_7);
              append(&buf_7,next[1],8);
              reset(&buf_6);
              append(&buf_6,next[1],8);
              reset(&buf_5);
              append(&buf_5,next[1],8);
              reset(&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_111;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_68);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_60);
              concat(&buf_60,&buf_61);
              appendarray(&buf_60,const_1_32,16);
              reset(&buf_27);
              concat(&buf_27,&buf_59);
              appendarray(&buf_27,const_1_32,16);
              reset(&buf_23);
              concat(&buf_23,&buf_55);
              appendarray(&buf_23,const_1_32,16);
              reset(&buf_17);
              concat(&buf_17,&buf_48);
              appendarray(&buf_17,const_1_32,16);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              appendarray(&buf_1,const_1_32,16);
              reset(&buf_9);
              concat(&buf_9,&buf_40);
              appendarray(&buf_9,const_1_32,16);
              consume(2);
              goto l1_21;
           }
           reset(&buf_57);
           concat(&buf_57,&buf_31);
           appendarray(&buf_57,const_1_31,8);
           reset(&buf_23);
           concat(&buf_23,&buf_8);
           appendarray(&buf_23,const_1_31,8);
           reset(&buf_17);
           concat(&buf_17,&buf_7);
           appendarray(&buf_17,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_6);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_5);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_113;
        }
        goto fail1;
l1_113: if (!readnext(1, 1))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_65);
           append(&buf_65,next[0],8);
           reset(&buf_58);
           append(&buf_58,next[0],8);
           reset(&buf_53);
           append(&buf_53,next[0],8);
           reset(&buf_46);
           append(&buf_46,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_32);
           append(&buf_32,next[0],8);
           reset(&buf_31);
           append(&buf_31,next[0],8);
           reset(&buf_30);
           append(&buf_30,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           reset(&buf_27);
           append(&buf_27,next[0],8);
           reset(&buf_24);
           append(&buf_24,next[0],8);
           reset(&buf_19);
           append(&buf_19,next[0],8);
           reset(&buf_18);
           append(&buf_18,next[0],8);
           reset(&buf_13);
           append(&buf_13,next[0],8);
           reset(&buf_12);
           append(&buf_12,next[0],8);
           reset(&buf_11);
           append(&buf_11,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_178;
        }
        goto fail1;
l1_114: if (!readnext(1, 1))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_63);
           append(&buf_63,next[0],8);
           reset(&buf_53);
           append(&buf_53,next[0],8);
           reset(&buf_46);
           append(&buf_46,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_30);
           append(&buf_30,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           reset(&buf_27);
           append(&buf_27,next[0],8);
           reset(&buf_23);
           append(&buf_23,next[0],8);
           reset(&buf_18);
           append(&buf_18,next[0],8);
           reset(&buf_12);
           append(&buf_12,next[0],8);
           reset(&buf_11);
           append(&buf_11,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_179;
        }
        goto fail1;
l1_115: if (!readnext(1, 1))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_60);
           append(&buf_60,next[0],8);
           reset(&buf_46);
           append(&buf_46,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_27);
           append(&buf_27,next[0],8);
           reset(&buf_23);
           append(&buf_23,next[0],8);
           reset(&buf_17);
           append(&buf_17,next[0],8);
           reset(&buf_11);
           append(&buf_11,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_180;
        }
        goto fail1;
l1_116: if (!readnext(1, 1))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_52);
           append(&buf_52,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_17);
           append(&buf_17,next[0],8);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_181;
        }
        goto fail1;
l1_117: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_68);
           append(&buf_68,next[0],8);
           reset(&buf_61);
           append(&buf_61,next[0],8);
           reset(&buf_59);
           append(&buf_59,next[0],8);
           reset(&buf_55);
           append(&buf_55,next[0],8);
           reset(&buf_48);
           append(&buf_48,next[0],8);
           reset(&buf_40);
           append(&buf_40,next[0],8);
           reset(&buf_36);
           append(&buf_36,next[0],8);
           reset(&buf_35);
           append(&buf_35,next[0],8);
           reset(&buf_34);
           append(&buf_34,next[0],8);
           reset(&buf_33);
           append(&buf_33,next[0],8);
           reset(&buf_32);
           append(&buf_32,next[0],8);
           reset(&buf_31);
           append(&buf_31,next[0],8);
           reset(&buf_28);
           append(&buf_28,next[0],8);
           reset(&buf_26);
           append(&buf_26,next[0],8);
           reset(&buf_25);
           append(&buf_25,next[0],8);
           reset(&buf_22);
           append(&buf_22,next[0],8);
           reset(&buf_21);
           append(&buf_21,next[0],8);
           reset(&buf_20);
           append(&buf_20,next[0],8);
           reset(&buf_16);
           append(&buf_16,next[0],8);
           reset(&buf_15);
           append(&buf_15,next[0],8);
           reset(&buf_14);
           append(&buf_14,next[0],8);
           reset(&buf_13);
           append(&buf_13,next[0],8);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           reset(&buf_8);
           append(&buf_8,next[0],8);
           reset(&buf_7);
           append(&buf_7,next[0],8);
           reset(&buf_6);
           append(&buf_6,next[0],8);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_1);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_112;
        }
        if (((avail >= 2) && (cmp(&next[0],(unsigned char *) "::",2) && 1)))
        {
           if (((avail >= 3) && ((next[2] == ']') && 1)))
           {
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
           consume(2);
           goto l1_24;
        }
        if (((avail >= 2) && ((next[0] == 'v') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_33;
        }
        goto fail1;
l1_118: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           appendarray(&buf_37,const_1_11,8);
           consume(1);
           goto l1_182;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_15,8);
           appendarray(&buf_37,const_1_15,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_15,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_15,8);
           consume(1);
           goto l1_184;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_17,8);
           appendarray(&buf_37,const_1_17,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_17,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_17,8);
           consume(1);
           goto l1_184;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_45);
           append(&buf_45,next[0],8);
           append(&buf_37,next[0],8);
           reset(&buf_10);
           append(&buf_10,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_184;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_126;
        }
        goto fail1;
l1_119: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           appendarray(&buf_37,const_1_11,8);
           consume(1);
           goto l1_183;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_15,8);
           appendarray(&buf_37,const_1_15,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_15,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_15,8);
           consume(1);
           goto l1_185;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_17,8);
           appendarray(&buf_37,const_1_17,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_17,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_17,8);
           consume(1);
           goto l1_185;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_45);
           append(&buf_45,next[0],8);
           append(&buf_37,next[0],8);
           reset(&buf_10);
           append(&buf_10,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_185;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_127;
        }
        goto fail1;
l1_120: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_11,8);
           consume(1);
           goto l1_183;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_15,8);
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_15,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_15,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_15,8);
           consume(1);
           goto l1_185;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_17,8);
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_17,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_17,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_17,8);
           consume(1);
           goto l1_185;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_45);
           append(&buf_45,next[0],8);
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           append(&buf_37,next[0],8);
           reset(&buf_10);
           append(&buf_10,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_185;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_127;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_121: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           appendarray(&buf_37,const_1_11,8);
           consume(1);
           goto l1_182;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_15,8);
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           appendarray(&buf_37,const_1_15,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_15,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_15,8);
           consume(1);
           goto l1_184;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              output(&buf_1);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(4);
              goto l1_6;
           }
           reset(&buf_45);
           appendarray(&buf_45,const_1_17,8);
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           appendarray(&buf_37,const_1_17,8);
           reset(&buf_10);
           appendarray(&buf_10,const_1_17,8);
           reset(&buf_2);
           appendarray(&buf_2,const_1_17,8);
           consume(1);
           goto l1_184;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_45);
           append(&buf_45,next[0],8);
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           append(&buf_37,next[0],8);
           reset(&buf_10);
           append(&buf_10,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_184;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_9);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              output(&buf_52);
              outputarray(const_1_40,24);
              consume(2);
              goto l1_38;
           }
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_126;
        }
        goto fail1;
l1_122: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_64);
           append(&buf_64,next[0],8);
           reset(&buf_63);
           concat(&buf_57,&buf_27);
           reset(&buf_54);
           append(&buf_54,next[0],8);
           reset(&buf_48);
           reset(&buf_47);
           append(&buf_47,next[0],8);
           reset(&buf_40);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_31);
           append(&buf_31,next[0],8);
           reset(&buf_30);
           append(&buf_30,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           reset(&buf_27);
           append(&buf_27,next[0],8);
           concat(&buf_23,&buf_5);
           reset(&buf_19);
           append(&buf_19,next[0],8);
           concat(&buf_17,&buf_4);
           reset(&buf_13);
           append(&buf_13,next[0],8);
           reset(&buf_12);
           append(&buf_12,next[0],8);
           concat(&buf_9,&buf_3);
           reset(&buf_5);
           append(&buf_5,next[0],8);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_128;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_57);
              output(&buf_62);
              outputarray(const_1_40,24);
              consume(2);
              goto l1_38;
           }
           reset(&buf_52);
           concat(&buf_52,&buf_23);
           concat(&buf_52,&buf_48);
           appendarray(&buf_52,const_1_31,8);
           concat(&buf_17,&buf_47);
           appendarray(&buf_17,const_1_31,8);
           concat(&buf_9,&buf_46);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_38);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_13;
        }
        goto fail1;
l1_123: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_62);
           append(&buf_62,next[0],8);
           reset(&buf_60);
           concat(&buf_52,&buf_23);
           reset(&buf_47);
           append(&buf_47,next[0],8);
           reset(&buf_40);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_29);
           append(&buf_29,next[0],8);
           reset(&buf_27);
           append(&buf_27,next[0],8);
           reset(&buf_23);
           append(&buf_23,next[0],8);
           concat(&buf_17,&buf_4);
           reset(&buf_12);
           append(&buf_12,next[0],8);
           concat(&buf_9,&buf_3);
           reset(&buf_4);
           append(&buf_4,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_132;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_52);
              output(&buf_60);
              outputarray(const_1_40,24);
              consume(2);
              goto l1_38;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_17);
           concat(&buf_44,&buf_47);
           appendarray(&buf_44,const_1_31,8);
           concat(&buf_9,&buf_46);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_38);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_26;
        }
        goto fail1;
l1_124: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_57);
           append(&buf_57,next[0],8);
           reset(&buf_52);
           concat(&buf_44,&buf_17);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_23);
           append(&buf_23,next[0],8);
           reset(&buf_17);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_133;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              output(&buf_57);
              outputarray(const_1_40,24);
              consume(2);
              goto l1_38;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           concat(&buf_37,&buf_46);
           appendarray(&buf_37,const_1_31,8);
           concat(&buf_1,&buf_38);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        goto fail1;
l1_125: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           reset(&buf_44);
           append(&buf_44,next[0],8);
           concat(&buf_37,&buf_9);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_134;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              output(&buf_38);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_37);
              output(&buf_52);
              outputarray(const_1_40,24);
              consume(2);
              goto l1_38;
           }
        }
        goto fail1;
l1_126: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
              {
                 output(&buf_37);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
           }
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_135;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
        }
        goto fail1;
l1_127: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 3) && ((next[1] == ':') && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1))))
           {
              output(&buf_1);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_37);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_136;
        }
        if (((avail >= 2) && ((next[0] == ':') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           output(&buf_1);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_128: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_62);
                 reset(&buf_60);
                 append(&buf_60,next[2],8);
                 reset(&buf_52);
                 concat(&buf_52,&buf_57);
                 concat(&buf_52,&buf_27);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 reset(&buf_47);
                 reset(&buf_40);
                 append(&buf_40,next[2],8);
                 reset(&buf_39);
                 reset(&buf_29);
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 reset(&buf_12);
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 concat(&buf_1,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_3);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_4);
                 append(&buf_4,next[2],8);
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_5);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 append(&buf_23,next[2],8);
                 consume(3);
                 goto l1_132;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_57);
                    output(&buf_63);
                    output(&buf_64);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_57,&buf_63);
                 concat(&buf_57,&buf_64);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 concat(&buf_23,&buf_48);
                 concat(&buf_23,&buf_54);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_40);
                 concat(&buf_17,&buf_47);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_39);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_14;
              }
              reset(&buf_62);
              concat(&buf_62,&buf_64);
              for(i = 0; i < 2; i++)
              {  append(&buf_62,next[0 + i],8);
              }
              reset(&buf_60);
              concat(&buf_60,&buf_63);
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              reset(&buf_41);
              concat(&buf_41,&buf_48);
              reset(&buf_48);
              concat(&buf_48,&buf_54);
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_39,next[0 + i],8);
              }
              reset(&buf_29);
              concat(&buf_29,&buf_31);
              for(i = 0; i < 2; i++)
              {  append(&buf_29,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              reset(&buf_13);
              concat(&buf_13,&buf_19);
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_36;
           }
           append(&buf_64,next[0],8);
           append(&buf_54,next[0],8);
           append(&buf_47,next[0],8);
           append(&buf_39,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_19,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_137;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[1],8);
              reset(&buf_52);
              concat(&buf_52,&buf_57);
              concat(&buf_52,&buf_27);
              append(&buf_52,next[0],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_12);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              append(&buf_17,next[0],8);
              reset(&buf_23);
              append(&buf_23,next[1],8);
              consume(2);
              goto l1_132;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_63);
                 output(&buf_64);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_48);
              concat(&buf_52,&buf_54);
              appendarray(&buf_52,const_1_32,16);
              concat(&buf_17,&buf_40);
              concat(&buf_17,&buf_47);
              appendarray(&buf_17,const_1_32,16);
              concat(&buf_9,&buf_39);
              appendarray(&buf_9,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_57);
           concat(&buf_44,&buf_27);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_23);
           concat(&buf_9,&buf_5);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_129: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_119;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_44,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_138;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_130: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_9);
           outputarray(const_1_13,16);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              appendarray(&buf_37,const_1_11,8);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_119;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_44,next[0],8);
           appendarray(&buf_9,const_1_11,8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_138;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_14,16);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_131: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_9);
           output(&buf_11);
           outputarray(const_1_9,8);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              output(&buf_9);
              output(&buf_46);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_6;
           }
           reset(&buf_52);
           append(&buf_52,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_17);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_188;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           concat(&buf_37,&buf_3);
           appendarray(&buf_37,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_52);
           append(&buf_52,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_17);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_188;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_132: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_57);
                 reset(&buf_44);
                 concat(&buf_44,&buf_52);
                 concat(&buf_44,&buf_23);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 reset(&buf_52);
                 append(&buf_52,next[2],8);
                 reset(&buf_39);
                 reset(&buf_23);
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 concat(&buf_1,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_3);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 append(&buf_17,next[2],8);
                 consume(3);
                 goto l1_133;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_52);
                    output(&buf_60);
                    output(&buf_62);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_52,&buf_60);
                 concat(&buf_52,&buf_62);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_40);
                 concat(&buf_17,&buf_47);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_39);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_27;
              }
              reset(&buf_57);
              concat(&buf_57,&buf_60);
              reset(&buf_60);
              concat(&buf_60,&buf_62);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_39,next[0 + i],8);
              }
              reset(&buf_27);
              concat(&buf_27,&buf_29);
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_37;
           }
           append(&buf_62,next[0],8);
           append(&buf_47,next[0],8);
           append(&buf_39,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_139;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_44);
              concat(&buf_44,&buf_52);
              concat(&buf_44,&buf_23);
              append(&buf_44,next[0],8);
              reset(&buf_52);
              append(&buf_52,next[1],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              append(&buf_17,next[1],8);
              consume(2);
              goto l1_133;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_60);
                 output(&buf_62);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_40);
              concat(&buf_44,&buf_47);
              appendarray(&buf_44,const_1_32,16);
              concat(&buf_9,&buf_39);
              appendarray(&buf_9,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_52);
           concat(&buf_37,&buf_23);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_133: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_37);
                 concat(&buf_37,&buf_44);
                 concat(&buf_37,&buf_17);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_37,next[0 + i],8);
                 }
                 reset(&buf_44);
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 concat(&buf_1,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_9);
                 consume(3);
                 goto l1_134;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_44);
                    output(&buf_52);
                    output(&buf_57);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_44,&buf_52);
                 concat(&buf_44,&buf_57);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_39);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_120;
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_39,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_35;
           }
           append(&buf_57,next[0],8);
           append(&buf_39,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_140;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_44);
              concat(&buf_37,&buf_17);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_44);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_9);
              consume(2);
              goto l1_134;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_52);
                 output(&buf_57);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_39);
              appendarray(&buf_37,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_119;
           }
           output(&buf_44);
           output(&buf_17);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_9;
        }
        goto fail1;
l1_134: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_37);
                 output(&buf_9);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_28;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
                 {
                    output(&buf_1);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    consume(4);
                    goto l1_29;
                 }
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_37);
                    output(&buf_44);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
              }
           }
           append(&buf_44,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_141;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_37);
              output(&buf_9);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_28;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_44);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
           }
        }
        goto fail1;
l1_135: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
              {
                 output(&buf_37);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
           }
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_142;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
        }
        goto fail1;
l1_136: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 3) && ((next[1] == ':') && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1))))
           {
              output(&buf_1);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_37);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_143;
        }
        if (((avail >= 2) && ((next[0] == ':') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           output(&buf_1);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_137: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_62);
                 reset(&buf_60);
                 append(&buf_60,next[2],8);
                 reset(&buf_52);
                 concat(&buf_52,&buf_57);
                 concat(&buf_52,&buf_27);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 reset(&buf_47);
                 reset(&buf_40);
                 append(&buf_40,next[2],8);
                 reset(&buf_39);
                 reset(&buf_29);
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 reset(&buf_12);
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 concat(&buf_1,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_3);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_4);
                 append(&buf_4,next[2],8);
                 reset(&buf_17);
                 concat(&buf_17,&buf_23);
                 concat(&buf_17,&buf_5);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_23);
                 append(&buf_23,next[2],8);
                 consume(3);
                 goto l1_132;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_57);
                    output(&buf_63);
                    output(&buf_64);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_57,&buf_63);
                 concat(&buf_57,&buf_64);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 concat(&buf_23,&buf_48);
                 concat(&buf_23,&buf_54);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_40);
                 concat(&buf_17,&buf_47);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_39);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_14;
              }
              reset(&buf_62);
              concat(&buf_62,&buf_64);
              for(i = 0; i < 2; i++)
              {  append(&buf_62,next[0 + i],8);
              }
              reset(&buf_60);
              concat(&buf_60,&buf_63);
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              reset(&buf_41);
              concat(&buf_41,&buf_48);
              reset(&buf_48);
              concat(&buf_48,&buf_54);
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_39,next[0 + i],8);
              }
              reset(&buf_29);
              concat(&buf_29,&buf_31);
              for(i = 0; i < 2; i++)
              {  append(&buf_29,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              reset(&buf_13);
              concat(&buf_13,&buf_19);
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_36;
           }
           append(&buf_64,next[0],8);
           append(&buf_54,next[0],8);
           append(&buf_47,next[0],8);
           append(&buf_39,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_19,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_144;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[1],8);
              reset(&buf_52);
              concat(&buf_52,&buf_57);
              concat(&buf_52,&buf_27);
              append(&buf_52,next[0],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_12);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              append(&buf_17,next[0],8);
              reset(&buf_23);
              append(&buf_23,next[1],8);
              consume(2);
              goto l1_132;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_63);
                 output(&buf_64);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_48);
              concat(&buf_52,&buf_54);
              appendarray(&buf_52,const_1_32,16);
              concat(&buf_17,&buf_40);
              concat(&buf_17,&buf_47);
              appendarray(&buf_17,const_1_32,16);
              concat(&buf_9,&buf_39);
              appendarray(&buf_9,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_57);
           concat(&buf_44,&buf_27);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_23);
           concat(&buf_9,&buf_5);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_138: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_119;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_44,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_145;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_139: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_57);
                 reset(&buf_44);
                 concat(&buf_44,&buf_52);
                 concat(&buf_44,&buf_23);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 reset(&buf_52);
                 append(&buf_52,next[2],8);
                 reset(&buf_39);
                 reset(&buf_23);
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 concat(&buf_1,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_3);
                 reset(&buf_9);
                 concat(&buf_9,&buf_17);
                 concat(&buf_9,&buf_4);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_17);
                 append(&buf_17,next[2],8);
                 consume(3);
                 goto l1_133;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_52);
                    output(&buf_60);
                    output(&buf_62);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_52,&buf_60);
                 concat(&buf_52,&buf_62);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_40);
                 concat(&buf_17,&buf_47);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_39);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_27;
              }
              reset(&buf_57);
              concat(&buf_57,&buf_60);
              reset(&buf_60);
              concat(&buf_60,&buf_62);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_39,next[0 + i],8);
              }
              reset(&buf_27);
              concat(&buf_27,&buf_29);
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_37;
           }
           append(&buf_62,next[0],8);
           append(&buf_47,next[0],8);
           append(&buf_39,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_146;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_44);
              concat(&buf_44,&buf_52);
              concat(&buf_44,&buf_23);
              append(&buf_44,next[0],8);
              reset(&buf_52);
              append(&buf_52,next[1],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              append(&buf_17,next[1],8);
              consume(2);
              goto l1_133;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_60);
                 output(&buf_62);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_40);
              concat(&buf_44,&buf_47);
              appendarray(&buf_44,const_1_32,16);
              concat(&buf_9,&buf_39);
              appendarray(&buf_9,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_52);
           concat(&buf_37,&buf_23);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_140: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_37);
                 concat(&buf_37,&buf_44);
                 concat(&buf_37,&buf_17);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_37,next[0 + i],8);
                 }
                 reset(&buf_44);
                 reset(&buf_1);
                 concat(&buf_1,&buf_9);
                 concat(&buf_1,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 reset(&buf_9);
                 consume(3);
                 goto l1_134;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_44);
                    output(&buf_52);
                    output(&buf_57);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_44,&buf_52);
                 concat(&buf_44,&buf_57);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_39);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_120;
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_39,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_35;
           }
           append(&buf_57,next[0],8);
           append(&buf_39,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_147;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_44);
              concat(&buf_37,&buf_17);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_44);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_9);
              consume(2);
              goto l1_134;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_52);
                 output(&buf_57);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_39);
              appendarray(&buf_37,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_119;
           }
           output(&buf_44);
           output(&buf_17);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_9;
        }
        goto fail1;
l1_141: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_37);
                 output(&buf_9);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_28;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
                 {
                    output(&buf_1);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    consume(4);
                    goto l1_29;
                 }
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_37);
                    output(&buf_44);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
              }
           }
           append(&buf_44,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_148;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_37);
              output(&buf_9);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_28;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_44);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
           }
        }
        goto fail1;
l1_142: if (!readnext(2, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              output(&buf_1);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_29;
           }
           if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              for(i = 0; i < 4; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(4);
              goto l1_38;
           }
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
        }
        goto fail1;
l1_143: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 3) && ((next[1] == ':') && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1))))
           {
              output(&buf_1);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_37);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
        }
        if (((avail >= 2) && ((next[0] == ':') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           output(&buf_1);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_144: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[2],8);
              reset(&buf_52);
              concat(&buf_52,&buf_57);
              concat(&buf_52,&buf_27);
              for(i = 0; i < 2; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[2],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[2],8);
              reset(&buf_12);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[2],8);
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_23);
              append(&buf_23,next[2],8);
              consume(3);
              goto l1_132;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_63);
                 output(&buf_64);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_48);
              concat(&buf_52,&buf_54);
              for(i = 0; i < 3; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              concat(&buf_17,&buf_40);
              concat(&buf_17,&buf_47);
              for(i = 0; i < 3; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_39);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_13;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_57);
           concat(&buf_44,&buf_27);
           for(i = 0; i < 2; i++)
           {  append(&buf_44,next[0 + i],8);
           }
           reset(&buf_9);
           concat(&buf_9,&buf_23);
           concat(&buf_9,&buf_5);
           for(i = 0; i < 2; i++)
           {  append(&buf_9,next[0 + i],8);
           }
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           for(i = 0; i < 2; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(2);
           goto l1_115;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[1],8);
              reset(&buf_52);
              concat(&buf_52,&buf_57);
              concat(&buf_52,&buf_27);
              append(&buf_52,next[0],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_12);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_17);
              concat(&buf_17,&buf_23);
              concat(&buf_17,&buf_5);
              append(&buf_17,next[0],8);
              reset(&buf_23);
              append(&buf_23,next[1],8);
              consume(2);
              goto l1_132;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_63);
                 output(&buf_64);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_48);
              concat(&buf_52,&buf_54);
              appendarray(&buf_52,const_1_32,16);
              concat(&buf_17,&buf_40);
              concat(&buf_17,&buf_47);
              appendarray(&buf_17,const_1_32,16);
              concat(&buf_9,&buf_39);
              appendarray(&buf_9,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_57);
           concat(&buf_44,&buf_27);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_23);
           concat(&buf_9,&buf_5);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_145: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_119;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_31,8);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_146: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_44);
              concat(&buf_44,&buf_52);
              concat(&buf_44,&buf_23);
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              reset(&buf_52);
              append(&buf_52,next[2],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              append(&buf_17,next[2],8);
              consume(3);
              goto l1_133;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_60);
                 output(&buf_62);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_40);
              concat(&buf_44,&buf_47);
              for(i = 0; i < 3; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              concat(&buf_9,&buf_39);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_26;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_52);
           concat(&buf_37,&buf_23);
           for(i = 0; i < 2; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           for(i = 0; i < 2; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(2);
           goto l1_116;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_44);
              concat(&buf_44,&buf_52);
              concat(&buf_44,&buf_23);
              append(&buf_44,next[0],8);
              reset(&buf_52);
              append(&buf_52,next[1],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_3);
              reset(&buf_9);
              concat(&buf_9,&buf_17);
              concat(&buf_9,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_17);
              append(&buf_17,next[1],8);
              consume(2);
              goto l1_133;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_60);
                 output(&buf_62);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_40);
              concat(&buf_44,&buf_47);
              appendarray(&buf_44,const_1_32,16);
              concat(&buf_9,&buf_39);
              appendarray(&buf_9,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_52);
           concat(&buf_37,&buf_23);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_17);
           concat(&buf_1,&buf_4);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_147: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_44);
              concat(&buf_37,&buf_17);
              for(i = 0; i < 3; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_44);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_9);
              consume(3);
              goto l1_134;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_52);
                 output(&buf_57);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_39);
              for(i = 0; i < 3; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_119;
           }
           output(&buf_44);
           output(&buf_17);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_44);
              concat(&buf_37,&buf_17);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_44);
              reset(&buf_1);
              concat(&buf_1,&buf_9);
              concat(&buf_1,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              reset(&buf_9);
              consume(2);
              goto l1_134;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_52);
                 output(&buf_57);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_39);
              appendarray(&buf_37,const_1_32,16);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_119;
           }
           output(&buf_44);
           output(&buf_17);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_9;
        }
        goto fail1;
l1_148: if (!readnext(2, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              output(&buf_37);
              output(&buf_9);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_28;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(4);
                 goto l1_29;
              }
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_44);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
           }
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_37);
              output(&buf_9);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_28;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_44);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
           }
        }
        goto fail1;
l1_149: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_1);
           outputarray(const_1_56,80);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_57,152);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           output(&buf_37);
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_155;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_59,72);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_65,48);
           consume(1);
           goto l1_8;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_58,128);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        goto fail1;
l1_150: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_37);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           output(&buf_37);
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_155;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_37,const_1_9,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_49;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              concat(&buf_1,&buf_38);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_49;
           }
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_7,56);
           consume(1);
           goto l1_8;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        goto fail1;
l1_151: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_37);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           output(&buf_37);
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_155;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_37,const_1_9,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_50;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              concat(&buf_1,&buf_38);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_50;
           }
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_7,56);
           consume(1);
           goto l1_8;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        goto fail1;
l1_152: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_37);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           output(&buf_37);
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_155;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_37,const_1_9,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_19,24);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_51;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_1);
              appendarray(&buf_1,const_1_19,24);
              concat(&buf_1,&buf_38);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_51;
           }
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_7,56);
           consume(1);
           goto l1_8;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        goto fail1;
l1_153: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_153;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           outputarray(const_1_31,8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        goto fail1;
l1_154: if (!readnext(1, 1))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_154;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_154;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_154;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           outputarray(const_1_31,8);
           consume(1);
           goto l1_154;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_154;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_155: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_155;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           outputarray(const_1_7,56);
           consume(1);
           goto l1_8;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        goto fail1;
l1_156: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_156;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_10,8);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_8,64);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_156;
        }
        goto fail1;
l1_157: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_157;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_10,8);
           consume(1);
           goto l1_159;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_8,64);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_158: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_157;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_8,64);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_157;
        }
        goto fail1;
l1_159: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_159;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_159;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_159;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_10,8);
           consume(1);
           goto l1_159;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_159;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_159;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_8,64);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_159;
        }
        goto fail1;
l1_160: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_160;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_160;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_160;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_10,8);
           consume(1);
           goto l1_161;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_160;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_160;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_8,64);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_160;
        }
        goto fail1;
l1_161: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_161;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_161;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_161;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_10,8);
           consume(1);
           goto l1_161;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_161;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_161;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_8,64);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_161;
        }
        goto fail1;
l1_162: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_64);
              reset(&buf_63);
              append(&buf_63,next[2],8);
              concat(&buf_57,&buf_27);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              reset(&buf_54);
              reset(&buf_48);
              append(&buf_48,next[2],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[2],8);
              reset(&buf_39);
              reset(&buf_31);
              reset(&buf_30);
              append(&buf_30,next[2],8);
              reset(&buf_29);
              append(&buf_29,next[2],8);
              reset(&buf_27);
              append(&buf_27,next[2],8);
              concat(&buf_23,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              reset(&buf_19);
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_13);
              append(&buf_13,next[2],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_5);
              append(&buf_5,next[2],8);
              reset(&buf_4);
              append(&buf_4,next[2],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_128;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_65);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_58);
              for(i = 0; i < 3; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              concat(&buf_17,&buf_53);
              for(i = 0; i < 3; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_46);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_38);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_13;
           }
           reset(&buf_52);
           concat(&buf_52,&buf_57);
           concat(&buf_52,&buf_27);
           for(i = 0; i < 2; i++)
           {  append(&buf_52,next[0 + i],8);
           }
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           for(i = 0; i < 2; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           for(i = 0; i < 2; i++)
           {  append(&buf_9,next[0 + i],8);
           }
           reset(&buf_17);
           concat(&buf_17,&buf_23);
           concat(&buf_17,&buf_5);
           for(i = 0; i < 2; i++)
           {  append(&buf_17,next[0 + i],8);
           }
           consume(2);
           goto l1_114;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_64);
              reset(&buf_63);
              append(&buf_63,next[1],8);
              concat(&buf_57,&buf_27);
              append(&buf_57,next[0],8);
              reset(&buf_54);
              reset(&buf_48);
              append(&buf_48,next[1],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_31);
              reset(&buf_30);
              append(&buf_30,next[1],8);
              reset(&buf_29);
              append(&buf_29,next[1],8);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              concat(&buf_23,&buf_5);
              append(&buf_23,next[0],8);
              reset(&buf_19);
              concat(&buf_17,&buf_4);
              append(&buf_17,next[0],8);
              reset(&buf_13);
              append(&buf_13,next[1],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_5);
              append(&buf_5,next[1],8);
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_128;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_65);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_58);
              appendarray(&buf_52,const_1_32,16);
              concat(&buf_17,&buf_53);
              appendarray(&buf_17,const_1_32,16);
              concat(&buf_9,&buf_46);
              appendarray(&buf_9,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_52);
           concat(&buf_52,&buf_57);
           concat(&buf_52,&buf_27);
           appendarray(&buf_52,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_17);
           concat(&buf_17,&buf_23);
           concat(&buf_17,&buf_5);
           appendarray(&buf_17,const_1_31,8);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_163: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[2],8);
              concat(&buf_52,&buf_23);
              for(i = 0; i < 2; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[2],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[2],8);
              reset(&buf_23);
              append(&buf_23,next[2],8);
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[2],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_132;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_63);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_53);
              for(i = 0; i < 3; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              concat(&buf_9,&buf_46);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_38);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_26;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_52);
           concat(&buf_44,&buf_23);
           for(i = 0; i < 2; i++)
           {  append(&buf_44,next[0 + i],8);
           }
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           for(i = 0; i < 2; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           for(i = 0; i < 2; i++)
           {  append(&buf_9,next[0 + i],8);
           }
           consume(2);
           goto l1_115;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[1],8);
              concat(&buf_52,&buf_23);
              append(&buf_52,next[0],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_23);
              append(&buf_23,next[1],8);
              concat(&buf_17,&buf_4);
              append(&buf_17,next[0],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_132;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_63);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_53);
              appendarray(&buf_44,const_1_32,16);
              concat(&buf_9,&buf_46);
              appendarray(&buf_9,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_52);
           concat(&buf_44,&buf_23);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           appendarray(&buf_9,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_164: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_52);
              append(&buf_52,next[2],8);
              concat(&buf_44,&buf_17);
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_17);
              append(&buf_17,next[2],8);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_133;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_60);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_46);
              for(i = 0; i < 3; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              concat(&buf_1,&buf_38);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_119;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           for(i = 0; i < 2; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           for(i = 0; i < 2; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(2);
           goto l1_116;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_52);
              append(&buf_52,next[1],8);
              concat(&buf_44,&buf_17);
              append(&buf_44,next[0],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_17);
              append(&buf_17,next[1],8);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_133;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_60);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_46);
              appendarray(&buf_37,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_119;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_165: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 2) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && ((next[1] == ':') && 1))))
        {
           if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
           {
              reset(&buf_44);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 3; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_9);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_134;
           }
           if (((avail >= 3) && ((next[2] == ':') && 1)))
           {
              if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 output(&buf_38);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(4);
                 goto l1_29;
              }
              if (((avail >= 4) && ((next[3] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_52);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
           }
           output(&buf_37);
           output(&buf_9);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_9;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_44);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_9);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_134;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 output(&buf_38);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_52);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
           }
           output(&buf_37);
           output(&buf_9);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_9;
        }
        goto fail1;
l1_166: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_64);
                 reset(&buf_63);
                 append(&buf_63,next[2],8);
                 concat(&buf_57,&buf_27);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 reset(&buf_54);
                 reset(&buf_48);
                 append(&buf_48,next[2],8);
                 reset(&buf_47);
                 reset(&buf_40);
                 append(&buf_40,next[2],8);
                 reset(&buf_39);
                 reset(&buf_31);
                 reset(&buf_30);
                 append(&buf_30,next[2],8);
                 reset(&buf_29);
                 append(&buf_29,next[2],8);
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 concat(&buf_23,&buf_5);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_19);
                 concat(&buf_17,&buf_4);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_13);
                 append(&buf_13,next[2],8);
                 reset(&buf_12);
                 concat(&buf_9,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_5);
                 append(&buf_5,next[2],8);
                 reset(&buf_4);
                 append(&buf_4,next[2],8);
                 reset(&buf_3);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_128;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_57);
                    output(&buf_65);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_57,&buf_65);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 concat(&buf_23,&buf_58);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_53);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_46);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 concat(&buf_1,&buf_38);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_14;
              }
              reset(&buf_62);
              concat(&buf_62,&buf_65);
              for(i = 0; i < 2; i++)
              {  append(&buf_62,next[0 + i],8);
              }
              reset(&buf_48);
              concat(&buf_48,&buf_58);
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              reset(&buf_47);
              concat(&buf_47,&buf_53);
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_46,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              reset(&buf_29);
              concat(&buf_29,&buf_32);
              for(i = 0; i < 2; i++)
              {  append(&buf_29,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              reset(&buf_13);
              concat(&buf_13,&buf_24);
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              reset(&buf_12);
              concat(&buf_12,&buf_18);
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_11,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_122;
           }
           append(&buf_65,next[0],8);
           append(&buf_58,next[0],8);
           append(&buf_53,next[0],8);
           append(&buf_46,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_32,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_24,next[0],8);
           append(&buf_19,next[0],8);
           append(&buf_18,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_11,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_162;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_64);
              reset(&buf_63);
              append(&buf_63,next[1],8);
              concat(&buf_57,&buf_27);
              append(&buf_57,next[0],8);
              reset(&buf_54);
              reset(&buf_48);
              append(&buf_48,next[1],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_31);
              reset(&buf_30);
              append(&buf_30,next[1],8);
              reset(&buf_29);
              append(&buf_29,next[1],8);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              concat(&buf_23,&buf_5);
              append(&buf_23,next[0],8);
              reset(&buf_19);
              concat(&buf_17,&buf_4);
              append(&buf_17,next[0],8);
              reset(&buf_13);
              append(&buf_13,next[1],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_5);
              append(&buf_5,next[1],8);
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_128;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_65);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_58);
              appendarray(&buf_52,const_1_32,16);
              concat(&buf_17,&buf_53);
              appendarray(&buf_17,const_1_32,16);
              concat(&buf_9,&buf_46);
              appendarray(&buf_9,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_52);
           concat(&buf_52,&buf_57);
           concat(&buf_52,&buf_27);
           appendarray(&buf_52,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_17);
           concat(&buf_17,&buf_23);
           concat(&buf_17,&buf_5);
           appendarray(&buf_17,const_1_31,8);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_167: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_62);
                 reset(&buf_60);
                 append(&buf_60,next[2],8);
                 concat(&buf_52,&buf_23);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 reset(&buf_47);
                 reset(&buf_40);
                 append(&buf_40,next[2],8);
                 reset(&buf_39);
                 reset(&buf_29);
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 reset(&buf_23);
                 append(&buf_23,next[2],8);
                 concat(&buf_17,&buf_4);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_12);
                 concat(&buf_9,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_4);
                 append(&buf_4,next[2],8);
                 reset(&buf_3);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_132;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_52);
                    output(&buf_63);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_52,&buf_63);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_53);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_46);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 concat(&buf_1,&buf_38);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_27;
              }
              reset(&buf_60);
              concat(&buf_60,&buf_63);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              reset(&buf_47);
              concat(&buf_47,&buf_53);
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_46,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              reset(&buf_27);
              concat(&buf_27,&buf_30);
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              reset(&buf_12);
              concat(&buf_12,&buf_18);
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_11,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_123;
           }
           append(&buf_63,next[0],8);
           append(&buf_53,next[0],8);
           append(&buf_46,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_18,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_11,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_163;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[1],8);
              concat(&buf_52,&buf_23);
              append(&buf_52,next[0],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_23);
              append(&buf_23,next[1],8);
              concat(&buf_17,&buf_4);
              append(&buf_17,next[0],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_132;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_63);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_53);
              appendarray(&buf_44,const_1_32,16);
              concat(&buf_9,&buf_46);
              appendarray(&buf_9,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_52);
           concat(&buf_44,&buf_23);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           appendarray(&buf_9,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_168: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_57);
                 reset(&buf_52);
                 append(&buf_52,next[2],8);
                 concat(&buf_44,&buf_17);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 reset(&buf_39);
                 reset(&buf_23);
                 reset(&buf_17);
                 append(&buf_17,next[2],8);
                 concat(&buf_9,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_3);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_133;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_44);
                    output(&buf_60);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_44,&buf_60);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_46);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 concat(&buf_1,&buf_38);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_120;
              }
              reset(&buf_57);
              concat(&buf_57,&buf_60);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_46,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              reset(&buf_23);
              concat(&buf_23,&buf_27);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_11,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_124;
           }
           append(&buf_60,next[0],8);
           append(&buf_46,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_11,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_164;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_52);
              append(&buf_52,next[1],8);
              concat(&buf_44,&buf_17);
              append(&buf_44,next[0],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_17);
              append(&buf_17,next[1],8);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_133;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_60);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_46);
              appendarray(&buf_37,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_119;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_169: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_44);
                 concat(&buf_37,&buf_9);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_37,next[0 + i],8);
                 }
                 reset(&buf_9);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_134;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
                 {
                    output(&buf_1);
                    output(&buf_38);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    consume(4);
                    goto l1_29;
                 }
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_37);
                    output(&buf_52);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_125;
           }
           append(&buf_52,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_165;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_44);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_9);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_134;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 output(&buf_38);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_52);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
           }
           output(&buf_37);
           output(&buf_9);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_9;
        }
        goto fail1;
l1_170: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_119;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              output(&buf_17);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_44,&buf_17);
           append(&buf_44,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_53;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           concat(&buf_37,&buf_3);
           appendarray(&buf_37,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           output(&buf_17);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_171: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_11;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_52);
              output(&buf_23);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_52,&buf_23);
           append(&buf_52,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_55;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_44);
           concat(&buf_44,&buf_17);
           concat(&buf_44,&buf_4);
           appendarray(&buf_44,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_11;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_52);
           output(&buf_23);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_172: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_11;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_52);
              output(&buf_23);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_52,&buf_23);
           append(&buf_52,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_56;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_44);
           concat(&buf_44,&buf_17);
           concat(&buf_44,&buf_4);
           appendarray(&buf_44,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_11;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_52);
           output(&buf_23);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_173: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_12;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_57);
              output(&buf_27);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_57,&buf_27);
           append(&buf_57,next[0],8);
           concat(&buf_23,&buf_5);
           append(&buf_23,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_58;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_52);
           concat(&buf_52,&buf_23);
           concat(&buf_52,&buf_5);
           appendarray(&buf_52,const_1_31,8);
           concat(&buf_17,&buf_4);
           appendarray(&buf_17,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_12;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_57);
           output(&buf_27);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_174: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_12;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_57);
              output(&buf_27);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_57,&buf_27);
           append(&buf_57,next[0],8);
           concat(&buf_23,&buf_5);
           append(&buf_23,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_59;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_52);
           concat(&buf_52,&buf_23);
           concat(&buf_52,&buf_5);
           appendarray(&buf_52,const_1_31,8);
           concat(&buf_17,&buf_4);
           appendarray(&buf_17,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_12;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_57);
           output(&buf_27);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_175: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_57);
              concat(&buf_57,&buf_27);
              concat(&buf_57,&buf_6);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              concat(&buf_23,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_16;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_60);
              output(&buf_29);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_60,&buf_29);
           append(&buf_60,next[0],8);
           concat(&buf_27,&buf_6);
           append(&buf_27,next[0],8);
           concat(&buf_23,&buf_5);
           append(&buf_23,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_61;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           concat(&buf_57,&buf_6);
           appendarray(&buf_57,const_1_31,8);
           concat(&buf_23,&buf_5);
           appendarray(&buf_23,const_1_31,8);
           concat(&buf_17,&buf_4);
           appendarray(&buf_17,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           output(&buf_29);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_176: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_57);
              concat(&buf_57,&buf_27);
              concat(&buf_57,&buf_6);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              concat(&buf_23,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_16;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_60);
              output(&buf_29);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_60,&buf_29);
           append(&buf_60,next[0],8);
           concat(&buf_27,&buf_6);
           append(&buf_27,next[0],8);
           concat(&buf_23,&buf_5);
           append(&buf_23,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_62;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_57);
           concat(&buf_57,&buf_27);
           concat(&buf_57,&buf_6);
           appendarray(&buf_57,const_1_31,8);
           concat(&buf_23,&buf_5);
           appendarray(&buf_23,const_1_31,8);
           concat(&buf_17,&buf_4);
           appendarray(&buf_17,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_16;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_60);
           output(&buf_29);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_177: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_60);
              concat(&buf_60,&buf_29);
              concat(&buf_60,&buf_7);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              concat(&buf_27,&buf_6);
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              concat(&buf_23,&buf_5);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              concat(&buf_17,&buf_4);
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_20;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_62);
              output(&buf_30);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_62,&buf_30);
           append(&buf_62,next[0],8);
           concat(&buf_29,&buf_7);
           append(&buf_29,next[0],8);
           concat(&buf_27,&buf_6);
           append(&buf_27,next[0],8);
           concat(&buf_23,&buf_5);
           append(&buf_23,next[0],8);
           concat(&buf_17,&buf_4);
           append(&buf_17,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_64;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_60);
           concat(&buf_60,&buf_29);
           concat(&buf_60,&buf_7);
           appendarray(&buf_60,const_1_31,8);
           concat(&buf_27,&buf_6);
           appendarray(&buf_27,const_1_31,8);
           concat(&buf_23,&buf_5);
           appendarray(&buf_23,const_1_31,8);
           concat(&buf_17,&buf_4);
           appendarray(&buf_17,const_1_31,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_20;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_62);
           output(&buf_30);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_178: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_64);
                 reset(&buf_63);
                 append(&buf_63,next[2],8);
                 concat(&buf_57,&buf_27);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 reset(&buf_54);
                 reset(&buf_48);
                 append(&buf_48,next[2],8);
                 reset(&buf_47);
                 reset(&buf_40);
                 append(&buf_40,next[2],8);
                 reset(&buf_39);
                 reset(&buf_31);
                 reset(&buf_30);
                 append(&buf_30,next[2],8);
                 reset(&buf_29);
                 append(&buf_29,next[2],8);
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 concat(&buf_23,&buf_5);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 reset(&buf_19);
                 concat(&buf_17,&buf_4);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_13);
                 append(&buf_13,next[2],8);
                 reset(&buf_12);
                 concat(&buf_9,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_5);
                 append(&buf_5,next[2],8);
                 reset(&buf_4);
                 append(&buf_4,next[2],8);
                 reset(&buf_3);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_128;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_57);
                    output(&buf_65);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_57,&buf_65);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_57,next[0 + i],8);
                 }
                 concat(&buf_23,&buf_58);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_23,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_53);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_46);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 concat(&buf_1,&buf_38);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_14;
              }
              reset(&buf_62);
              concat(&buf_62,&buf_65);
              for(i = 0; i < 2; i++)
              {  append(&buf_62,next[0 + i],8);
              }
              reset(&buf_48);
              concat(&buf_48,&buf_58);
              for(i = 0; i < 2; i++)
              {  append(&buf_48,next[0 + i],8);
              }
              reset(&buf_47);
              concat(&buf_47,&buf_53);
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_46,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              reset(&buf_29);
              concat(&buf_29,&buf_32);
              for(i = 0; i < 2; i++)
              {  append(&buf_29,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              reset(&buf_13);
              concat(&buf_13,&buf_24);
              for(i = 0; i < 2; i++)
              {  append(&buf_13,next[0 + i],8);
              }
              reset(&buf_12);
              concat(&buf_12,&buf_18);
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_11,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_5,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_122;
           }
           append(&buf_65,next[0],8);
           append(&buf_58,next[0],8);
           append(&buf_53,next[0],8);
           append(&buf_46,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_32,next[0],8);
           append(&buf_31,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_24,next[0],8);
           append(&buf_19,next[0],8);
           append(&buf_18,next[0],8);
           append(&buf_13,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_11,next[0],8);
           append(&buf_5,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_166;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_64);
              reset(&buf_63);
              append(&buf_63,next[1],8);
              concat(&buf_57,&buf_27);
              append(&buf_57,next[0],8);
              reset(&buf_54);
              reset(&buf_48);
              append(&buf_48,next[1],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_31);
              reset(&buf_30);
              append(&buf_30,next[1],8);
              reset(&buf_29);
              append(&buf_29,next[1],8);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              concat(&buf_23,&buf_5);
              append(&buf_23,next[0],8);
              reset(&buf_19);
              concat(&buf_17,&buf_4);
              append(&buf_17,next[0],8);
              reset(&buf_13);
              append(&buf_13,next[1],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_5);
              append(&buf_5,next[1],8);
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_128;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_57);
                 output(&buf_65);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_52);
              concat(&buf_52,&buf_23);
              concat(&buf_52,&buf_58);
              appendarray(&buf_52,const_1_32,16);
              concat(&buf_17,&buf_53);
              appendarray(&buf_17,const_1_32,16);
              concat(&buf_9,&buf_46);
              appendarray(&buf_9,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_13;
           }
           reset(&buf_52);
           concat(&buf_52,&buf_57);
           concat(&buf_52,&buf_27);
           appendarray(&buf_52,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           appendarray(&buf_9,const_1_31,8);
           reset(&buf_17);
           concat(&buf_17,&buf_23);
           concat(&buf_17,&buf_5);
           appendarray(&buf_17,const_1_31,8);
           consume(1);
           goto l1_114;
        }
        goto fail1;
l1_179: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_62);
                 reset(&buf_60);
                 append(&buf_60,next[2],8);
                 concat(&buf_52,&buf_23);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 reset(&buf_47);
                 reset(&buf_40);
                 append(&buf_40,next[2],8);
                 reset(&buf_39);
                 reset(&buf_29);
                 reset(&buf_27);
                 append(&buf_27,next[2],8);
                 reset(&buf_23);
                 append(&buf_23,next[2],8);
                 concat(&buf_17,&buf_4);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 reset(&buf_12);
                 concat(&buf_9,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_4);
                 append(&buf_4,next[2],8);
                 reset(&buf_3);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_132;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_52);
                    output(&buf_63);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_52,&buf_63);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_52,next[0 + i],8);
                 }
                 concat(&buf_17,&buf_53);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_17,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_46);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 concat(&buf_1,&buf_38);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_27;
              }
              reset(&buf_60);
              concat(&buf_60,&buf_63);
              for(i = 0; i < 2; i++)
              {  append(&buf_60,next[0 + i],8);
              }
              reset(&buf_47);
              concat(&buf_47,&buf_53);
              for(i = 0; i < 2; i++)
              {  append(&buf_47,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_46,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              reset(&buf_27);
              concat(&buf_27,&buf_30);
              for(i = 0; i < 2; i++)
              {  append(&buf_27,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              reset(&buf_12);
              concat(&buf_12,&buf_18);
              for(i = 0; i < 2; i++)
              {  append(&buf_12,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_11,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_4,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_123;
           }
           append(&buf_63,next[0],8);
           append(&buf_53,next[0],8);
           append(&buf_46,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_30,next[0],8);
           append(&buf_29,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_18,next[0],8);
           append(&buf_12,next[0],8);
           append(&buf_11,next[0],8);
           append(&buf_4,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_167;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_62);
              reset(&buf_60);
              append(&buf_60,next[1],8);
              concat(&buf_52,&buf_23);
              append(&buf_52,next[0],8);
              reset(&buf_47);
              reset(&buf_40);
              append(&buf_40,next[1],8);
              reset(&buf_39);
              reset(&buf_29);
              reset(&buf_27);
              append(&buf_27,next[1],8);
              reset(&buf_23);
              append(&buf_23,next[1],8);
              concat(&buf_17,&buf_4);
              append(&buf_17,next[0],8);
              reset(&buf_12);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_4);
              append(&buf_4,next[1],8);
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_132;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_52);
                 output(&buf_63);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_44);
              concat(&buf_44,&buf_17);
              concat(&buf_44,&buf_53);
              appendarray(&buf_44,const_1_32,16);
              concat(&buf_9,&buf_46);
              appendarray(&buf_9,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_26;
           }
           reset(&buf_44);
           concat(&buf_44,&buf_52);
           concat(&buf_44,&buf_23);
           appendarray(&buf_44,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           reset(&buf_9);
           concat(&buf_9,&buf_17);
           concat(&buf_9,&buf_4);
           appendarray(&buf_9,const_1_31,8);
           consume(1);
           goto l1_115;
        }
        goto fail1;
l1_180: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_57);
                 reset(&buf_52);
                 append(&buf_52,next[2],8);
                 concat(&buf_44,&buf_17);
                 for(i = 0; i < 2; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 reset(&buf_39);
                 reset(&buf_23);
                 reset(&buf_17);
                 append(&buf_17,next[2],8);
                 concat(&buf_9,&buf_3);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 reset(&buf_3);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_133;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_44);
                    output(&buf_60);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
                 concat(&buf_44,&buf_60);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_44,next[0 + i],8);
                 }
                 concat(&buf_9,&buf_46);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_9,next[0 + i],8);
                 }
                 concat(&buf_1,&buf_38);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_120;
              }
              reset(&buf_57);
              concat(&buf_57,&buf_60);
              for(i = 0; i < 2; i++)
              {  append(&buf_57,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_46,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              reset(&buf_23);
              concat(&buf_23,&buf_27);
              for(i = 0; i < 2; i++)
              {  append(&buf_23,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_11,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_3,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_124;
           }
           append(&buf_60,next[0],8);
           append(&buf_46,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_27,next[0],8);
           append(&buf_23,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_11,next[0],8);
           append(&buf_3,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_168;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_57);
              reset(&buf_52);
              append(&buf_52,next[1],8);
              concat(&buf_44,&buf_17);
              append(&buf_44,next[0],8);
              reset(&buf_39);
              reset(&buf_23);
              reset(&buf_17);
              append(&buf_17,next[1],8);
              concat(&buf_9,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_3);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_133;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_44);
                 output(&buf_60);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_46);
              appendarray(&buf_37,const_1_32,16);
              concat(&buf_1,&buf_38);
              appendarray(&buf_1,const_1_32,16);
              consume(2);
              goto l1_119;
           }
           reset(&buf_37);
           concat(&buf_37,&buf_44);
           concat(&buf_37,&buf_17);
           appendarray(&buf_37,const_1_31,8);
           reset(&buf_1);
           concat(&buf_1,&buf_9);
           concat(&buf_1,&buf_3);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_116;
        }
        goto fail1;
l1_181: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 reset(&buf_44);
                 concat(&buf_37,&buf_9);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_37,next[0 + i],8);
                 }
                 reset(&buf_9);
                 concat(&buf_1,&buf_2);
                 for(i = 0; i < 3; i++)
                 {  append(&buf_1,next[0 + i],8);
                 }
                 consume(3);
                 goto l1_134;
              }
              if (((avail >= 3) && ((next[2] == ':') && 1)))
              {
                 if (((avail >= 4) && (((('0' <= next[3]) && (next[3] <= '9')) || ((('A' <= next[3]) && (next[3] <= 'F')) || (('a' <= next[3]) && (next[3] <= 'f')))) && 1)))
                 {
                    output(&buf_1);
                    output(&buf_38);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    consume(4);
                    goto l1_29;
                 }
                 if (((avail >= 4) && ((next[3] == ']') && 1)))
                 {
                    output(&buf_37);
                    output(&buf_52);
                    for(i = 0; i < 4; i++)
                    {  outputconst(next[0 + i],8);
                    }
                    outputarray(const_1_0,8);
                    consume(4);
                    goto l1_38;
                 }
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_52,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_38,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_17,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_2,next[0 + i],8);
              }
              consume(2);
              goto l1_125;
           }
           append(&buf_52,next[0],8);
           append(&buf_38,next[0],8);
           append(&buf_17,next[0],8);
           append(&buf_9,next[0],8);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_169;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              reset(&buf_44);
              concat(&buf_37,&buf_9);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              reset(&buf_9);
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_134;
           }
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 output(&buf_38);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 3) && ((next[2] == ']') && 1)))
              {
                 output(&buf_37);
                 output(&buf_52);
                 outputarray(const_1_39,32);
                 consume(3);
                 goto l1_38;
              }
           }
           output(&buf_37);
           output(&buf_9);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_9;
        }
        goto fail1;
l1_182: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_13,16);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 outputarray(const_1_11,8);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
              {
                 output(&buf_37);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
           }
           append(&buf_37,next[0],8);
           appendarray(&buf_1,const_1_11,8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_135;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              outputarray(const_1_11,8);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
        }
        goto fail1;
l1_183: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_13,16);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 3) && ((next[1] == ':') && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1))))
           {
              output(&buf_1);
              outputarray(const_1_11,8);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_37);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           append(&buf_37,next[0],8);
           appendarray(&buf_1,const_1_11,8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_136;
        }
        if (((avail >= 2) && ((next[0] == ':') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           output(&buf_1);
           outputarray(const_1_11,8);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_184: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_1);
           output(&buf_10);
           outputarray(const_1_9,8);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              output(&buf_1);
              output(&buf_45);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_6;
           }
           reset(&buf_44);
           append(&buf_44,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_186;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              output(&buf_2);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_44);
           append(&buf_44,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_186;
        }
        goto fail1;
l1_185: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           output(&buf_1);
           output(&buf_10);
           outputarray(const_1_9,8);
           consume(1);
           goto l1_6;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              output(&buf_1);
              output(&buf_45);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_6;
           }
           reset(&buf_44);
           append(&buf_44,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_187;
        }
        if (((avail >= 2) && ((next[0] == ':') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           output(&buf_1);
           output(&buf_2);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_29;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f'))) && 1)))
        {
           reset(&buf_44);
           append(&buf_44,next[0],8);
           reset(&buf_38);
           append(&buf_38,next[0],8);
           reset(&buf_9);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           reset(&buf_2);
           append(&buf_2,next[0],8);
           consume(1);
           goto l1_187;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_186: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              if (((avail >= 3) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))
              {
                 output(&buf_1);
                 output(&buf_2);
                 for(i = 0; i < 3; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 consume(3);
                 goto l1_29;
              }
              if (((avail >= 4) && (cmp(&next[2],(unsigned char *) ":]",2) && 1)))
              {
                 output(&buf_37);
                 output(&buf_9);
                 for(i = 0; i < 4; i++)
                 {  outputconst(next[0 + i],8);
                 }
                 outputarray(const_1_0,8);
                 consume(4);
                 goto l1_38;
              }
           }
           concat(&buf_37,&buf_9);
           append(&buf_37,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_142;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           if (((avail >= 2) && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1)))
           {
              output(&buf_1);
              output(&buf_2);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(2);
              goto l1_29;
           }
           if (((avail >= 3) && (cmp(&next[1],(unsigned char *) ":]",2) && 1)))
           {
              output(&buf_37);
              output(&buf_9);
              outputarray(const_1_39,32);
              consume(3);
              goto l1_38;
           }
        }
        goto fail1;
l1_187: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 3) && ((next[1] == ':') && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1))))
           {
              output(&buf_1);
              output(&buf_2);
              for(i = 0; i < 3; i++)
              {  outputconst(next[0 + i],8);
              }
              consume(3);
              goto l1_29;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_37);
              output(&buf_9);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_37,&buf_9);
           append(&buf_37,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_143;
        }
        if (((avail >= 2) && ((next[0] == ':') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && 1))))
        {
           output(&buf_1);
           output(&buf_2);
           for(i = 0; i < 2; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(2);
           goto l1_29;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_37);
           output(&buf_9);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_188: if (!readnext(1, 2))
        {
           goto fail1;
        }
        if (((avail >= 1) && (((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'F')) || (('a' <= next[0]) && (next[0] <= 'f')))) && 1)))
        {
           if (((avail >= 2) && ((next[1] == ':') && 1)))
           {
              reset(&buf_37);
              concat(&buf_37,&buf_9);
              concat(&buf_37,&buf_3);
              for(i = 0; i < 2; i++)
              {  append(&buf_37,next[0 + i],8);
              }
              concat(&buf_1,&buf_2);
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_119;
           }
           if (((avail >= 2) && ((next[1] == ']') && 1)))
           {
              output(&buf_44);
              output(&buf_17);
              for(i = 0; i < 2; i++)
              {  outputconst(next[0 + i],8);
              }
              outputarray(const_1_0,8);
              consume(2);
              goto l1_38;
           }
           concat(&buf_44,&buf_17);
           append(&buf_44,next[0],8);
           concat(&buf_9,&buf_3);
           append(&buf_9,next[0],8);
           concat(&buf_1,&buf_2);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_145;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           concat(&buf_37,&buf_9);
           concat(&buf_37,&buf_3);
           appendarray(&buf_37,const_1_31,8);
           concat(&buf_1,&buf_2);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_119;
        }
        if (((avail >= 1) && ((next[0] == ']') && 1)))
        {
           output(&buf_44);
           output(&buf_17);
           outputarray(const_1_41,16);
           consume(1);
           goto l1_38;
        }
        goto fail1;
l1_189: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_1);
           output(&buf_2);
           outputarray(const_1_56,80);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_1);
           output(&buf_2);
           outputarray(const_1_57,152);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           output(&buf_37);
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_155;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_1);
           output(&buf_2);
           outputarray(const_1_59,72);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_37,next[0],8);
           concat(&buf_1,&buf_38);
           append(&buf_1,next[0],8);
           appendarray(&buf_1,const_1_0,8);
           consume(1);
           goto l1_149;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           output(&buf_1);
           output(&buf_2);
           outputarray(const_1_65,48);
           consume(1);
           goto l1_8;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_1);
           output(&buf_2);
           outputarray(const_1_58,128);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           output(&buf_37);
           outputconst(next[0],8);
           consume(1);
           goto l1_155;
        }
        goto fail1;
l1_190: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_37);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           output(&buf_1);
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           output(&buf_1);
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_153;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           output(&buf_1);
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_31,8);
           consume(1);
           goto l1_153;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           output(&buf_1);
           outputconst(next[0],8);
           consume(1);
           goto l1_153;
        }
        goto fail1;
l1_191: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_44,const_1_9,8);
           appendarray(&buf_9,const_1_9,8);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_195;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_192: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_44,const_1_9,8);
           appendarray(&buf_9,const_1_9,8);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_196;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_193: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_51,160);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_50,72);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_69,56);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_52,232);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_50,72);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           reset(&buf_1);
           appendarray(&buf_1,const_1_69,56);
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_50,72);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_69,56);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           reset(&buf_44);
           appendarray(&buf_44,const_1_28,40);
           reset(&buf_9);
           appendarray(&buf_9,const_1_20,40);
           reset(&buf_1);
           appendarray(&buf_1,const_1_71,64);
           consume(1);
           goto l1_197;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_54,152);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_50,72);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_69,56);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_55,128);
           reset(&buf_1);
           appendarray(&buf_1,const_1_72,64);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_53,208);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           outputarray(const_1_70,64);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_50,72);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_69,56);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_194: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_45,152);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_44,64);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_67,48);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_46,224);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_44,64);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           reset(&buf_1);
           appendarray(&buf_1,const_1_67,48);
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_44,64);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_67,48);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_48,144);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           consume(1);
           goto l1_193;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              reset(&buf_44);
              appendarray(&buf_44,const_1_21,24);
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              reset(&buf_9);
              appendarray(&buf_9,const_1_19,24);
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_1);
              appendarray(&buf_1,const_1_67,48);
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_197;
           }
           reset(&buf_44);
           appendarray(&buf_44,const_1_29,32);
           reset(&buf_39);
           appendarray(&buf_39,const_1_15,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_15,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_73,56);
           consume(1);
           goto l1_201;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              reset(&buf_44);
              appendarray(&buf_44,const_1_21,24);
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              reset(&buf_9);
              appendarray(&buf_9,const_1_19,24);
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_1);
              appendarray(&buf_1,const_1_67,48);
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_197;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              reset(&buf_44);
              appendarray(&buf_44,const_1_21,24);
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              reset(&buf_9);
              appendarray(&buf_9,const_1_19,24);
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              reset(&buf_1);
              appendarray(&buf_1,const_1_67,48);
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_197;
           }
           reset(&buf_44);
           appendarray(&buf_44,const_1_30,32);
           reset(&buf_39);
           appendarray(&buf_39,const_1_17,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_17,8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_74,56);
           consume(1);
           goto l1_201;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_44);
           appendarray(&buf_44,const_1_21,24);
           append(&buf_44,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_67,48);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_201;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_49,120);
           reset(&buf_1);
           appendarray(&buf_1,const_1_75,56);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_47,200);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           outputarray(const_1_68,56);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_44,64);
           append(&buf_37,next[0],8);
           reset(&buf_1);
           appendarray(&buf_1,const_1_67,48);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '[') && 1)))
        {
           outputarray(const_1_43,72);
           consume(1);
           goto l1_117;
        }
        goto fail1;
l1_195: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           appendarray(&buf_44,const_1_11,8);
           appendarray(&buf_9,const_1_12,16);
           appendarray(&buf_1,const_1_11,8);
           consume(1);
           goto l1_198;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 3) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && 1))))
           {
              for(i = 0; i < 3; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              appendarray(&buf_9,const_1_0,8);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_198;
           }
           appendarray(&buf_44,const_1_15,8);
           reset(&buf_39);
           appendarray(&buf_39,const_1_15,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_16,16);
           appendarray(&buf_1,const_1_15,8);
           consume(1);
           goto l1_203;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 3) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && 1))))
           {
              for(i = 0; i < 3; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              appendarray(&buf_9,const_1_0,8);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_198;
           }
           if (((avail >= 3) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && 1))))
           {
              for(i = 0; i < 3; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 3; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              appendarray(&buf_9,const_1_0,8);
              for(i = 0; i < 3; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(3);
              goto l1_198;
           }
           appendarray(&buf_44,const_1_17,8);
           reset(&buf_39);
           appendarray(&buf_39,const_1_17,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_18,16);
           appendarray(&buf_1,const_1_17,8);
           consume(1);
           goto l1_203;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_44,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           appendarray(&buf_3,const_1_0,8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_203;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_196: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           appendarray(&buf_44,const_1_11,8);
           appendarray(&buf_9,const_1_11,8);
           appendarray(&buf_1,const_1_11,8);
           consume(1);
           goto l1_191;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_195;
           }
           appendarray(&buf_44,const_1_15,8);
           reset(&buf_39);
           appendarray(&buf_39,const_1_15,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_15,8);
           appendarray(&buf_1,const_1_15,8);
           consume(1);
           goto l1_199;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_195;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_195;
           }
           appendarray(&buf_44,const_1_17,8);
           reset(&buf_39);
           appendarray(&buf_39,const_1_17,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_17,8);
           appendarray(&buf_1,const_1_17,8);
           consume(1);
           goto l1_199;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_44,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_199;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_197: if (!readnext(1, 4))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((next[0] == '0') && 1)))
        {
           appendarray(&buf_44,const_1_11,8);
           appendarray(&buf_9,const_1_11,8);
           appendarray(&buf_1,const_1_11,8);
           consume(1);
           goto l1_192;
        }
        if (((avail >= 1) && ((next[0] == '1') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_196;
           }
           appendarray(&buf_44,const_1_15,8);
           reset(&buf_39);
           appendarray(&buf_39,const_1_15,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_15,8);
           appendarray(&buf_1,const_1_15,8);
           consume(1);
           goto l1_200;
        }
        if (((avail >= 1) && ((next[0] == '2') && 1)))
        {
           if (((avail >= 4) && ((('0' <= next[1]) && (next[1] <= '4')) && ((('0' <= next[2]) && (next[2] <= '9')) && ((next[3] == '.') && 1)))))
           {
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_196;
           }
           if (((avail >= 4) && ((next[1] == '5') && ((('0' <= next[2]) && (next[2] <= '5')) && ((next[3] == '.') && 1)))))
           {
              for(i = 0; i < 4; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 4; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(4);
              goto l1_196;
           }
           appendarray(&buf_44,const_1_17,8);
           reset(&buf_39);
           appendarray(&buf_39,const_1_17,8);
           reset(&buf_3);
           appendarray(&buf_3,const_1_17,8);
           appendarray(&buf_1,const_1_17,8);
           consume(1);
           goto l1_200;
        }
        if (((avail >= 1) && ((('3' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_44,next[0],8);
           reset(&buf_39);
           append(&buf_39,next[0],8);
           reset(&buf_3);
           append(&buf_3,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_200;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_198: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           outputarray(const_1_56,80);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           outputarray(const_1_57,152);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           outputarray(const_1_59,72);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_9);
           appendarray(&buf_37,const_1_65,48);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           outputarray(const_1_58,128);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_199: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_44,const_1_9,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_9,8);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_195;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              concat(&buf_9,&buf_39);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_195;
           }
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_200: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_44,const_1_9,8);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_9,8);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_196;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              concat(&buf_9,&buf_39);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_196;
           }
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_201: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((next[0] == '-') || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '.') && 1)))
        {
           appendarray(&buf_44,const_1_9,8);
           reset(&buf_9);
           appendarray(&buf_9,const_1_19,24);
           concat(&buf_9,&buf_3);
           appendarray(&buf_9,const_1_9,8);
           appendarray(&buf_1,const_1_9,8);
           consume(1);
           goto l1_197;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           if (((avail >= 2) && ((next[1] == '.') && 1)))
           {
              for(i = 0; i < 2; i++)
              {  append(&buf_44,next[0 + i],8);
              }
              reset(&buf_9);
              appendarray(&buf_9,const_1_19,24);
              concat(&buf_9,&buf_39);
              for(i = 0; i < 2; i++)
              {  append(&buf_9,next[0 + i],8);
              }
              for(i = 0; i < 2; i++)
              {  append(&buf_1,next[0 + i],8);
              }
              consume(2);
              goto l1_197;
           }
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_44);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_202: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           output(&buf_37);
           outputarray(const_1_3,88);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_4,160);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_6,80);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           appendarray(&buf_37,const_1_7,56);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           output(&buf_37);
           outputarray(const_1_5,136);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_203: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           output(&buf_3);
           outputarray(const_1_56,80);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           output(&buf_3);
           outputarray(const_1_57,152);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           for(i = 0; i < 3; i++)
           {  append(&buf_37,next[0 + i],8);
           }
           for(i = 0; i < 3; i++)
           {  append(&buf_1,next[0 + i],8);
           }
           consume(3);
           goto l1_202;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        if (((avail >= 1) && ((next[0] == '/') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           output(&buf_3);
           outputarray(const_1_59,72);
           consume(1);
           goto l1_156;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           append(&buf_44,next[0],8);
           concat(&buf_9,&buf_39);
           append(&buf_9,next[0],8);
           appendarray(&buf_9,const_1_0,8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_198;
        }
        if (((avail >= 1) && ((next[0] == ':') && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_9);
           concat(&buf_37,&buf_3);
           appendarray(&buf_37,const_1_65,48);
           appendarray(&buf_1,const_1_31,8);
           consume(1);
           goto l1_190;
        }
        if (((avail >= 1) && ((next[0] == '?') && 1)))
        {
           outputarray(const_1_42,40);
           output(&buf_9);
           output(&buf_3);
           outputarray(const_1_58,128);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '@') && 1)))
        {
           output(&buf_1);
           outputarray(const_1_0,8);
           consume(1);
           goto l1_44;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           reset(&buf_37);
           appendarray(&buf_37,const_1_42,40);
           concat(&buf_37,&buf_44);
           append(&buf_37,next[0],8);
           append(&buf_1,next[0],8);
           consume(1);
           goto l1_202;
        }
        goto fail1;
l1_204: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((next[0] == '#') && 1)))
        {
           outputarray(const_1_2,88);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_204;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((next[0] == '/') || (next[0] == '?')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_204;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_204;
        }
        goto fail1;
l1_205: if (!readnext(1, 3))
        {
           goto fail1;
        }
        if (((avail >= 1) && ((next[0] == 10) && 1)))
        {
           outputarray(const_1_1,16);
           consume(1);
           goto l1_4;
        }
        if (((avail >= 1) && (((next[0] == '!') || ((next[0] == '$') || ((('&' <= next[0]) && (next[0] <= ',')) || ((next[0] == ';') || (next[0] == '='))))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 3) && ((next[0] == '%') && (((('0' <= next[1]) && (next[1] <= '9')) || ((('A' <= next[1]) && (next[1] <= 'F')) || (('a' <= next[1]) && (next[1] <= 'f')))) && (((('0' <= next[2]) && (next[2] <= '9')) || ((('A' <= next[2]) && (next[2] <= 'F')) || (('a' <= next[2]) && (next[2] <= 'f')))) && 1)))))
        {
           for(i = 0; i < 3; i++)
           {  outputconst(next[0 + i],8);
           }
           consume(3);
           goto l1_205;
        }
        if (((avail >= 1) && (((('-' <= next[0]) && (next[0] <= '.')) || ((next[0] == '_') || (next[0] == '~'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 1) && (((next[0] == '/') || (next[0] == '?')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 1) && (((next[0] == ':') || (next[0] == '@')) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_205;
        }
        if (((avail >= 1) && (((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z'))) && 1)))
        {
           outputconst(next[0],8);
           consume(1);
           goto l1_205;
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
