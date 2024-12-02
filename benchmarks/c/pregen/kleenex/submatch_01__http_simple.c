
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
// \x9
const buffer_unit_t const_1_0[1] = {0x9};
// \xa
const buffer_unit_t const_1_1[1] = {0xa};
// \xa\x9
const buffer_unit_t const_1_2[2] = {0xa,0x9};
// \xa\xa
const buffer_unit_t const_1_3[2] = {0xa,0xa};
// \xa 
const buffer_unit_t const_1_4[2] = {0xa,0x20};
// \xaheader: 
const buffer_unit_t const_1_5[9] = {0xa,0x68,0x65,0x61,0x64,0x65,0x72,0x3a,0x20};
// \xarequest: 
const buffer_unit_t const_1_6[10] = {0xa,0x72,0x65,0x71,0x75,0x65,0x73,0x74,0x3a,0x20};
// \xaversion: 
const buffer_unit_t const_1_7[10] = {0xa,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x3a,0x20};
//  
const buffer_unit_t const_1_8[1] = {0x20};
//  \x9
const buffer_unit_t const_1_9[2] = {0x20,0x9};
//  \xa
const buffer_unit_t const_1_10[2] = {0x20,0xa};
//  \xa\x9
const buffer_unit_t const_1_11[3] = {0x20,0xa,0x9};
//   
const buffer_unit_t const_1_12[2] = {0x20,0x20};
// *
const buffer_unit_t const_1_13[1] = {0x2a};
// /
const buffer_unit_t const_1_14[1] = {0x2f};
// //
const buffer_unit_t const_1_15[2] = {0x2f,0x2f};
// //\xaversion: 
const buffer_unit_t const_1_16[12] = {0x2f,0x2f,0xa,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x3a,0x20};
// //?
const buffer_unit_t const_1_17[3] = {0x2f,0x2f,0x3f};
// :
const buffer_unit_t const_1_18[1] = {0x3a};
// :\xaversion: 
const buffer_unit_t const_1_19[11] = {0x3a,0xa,0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x3a,0x20};
// ?
const buffer_unit_t const_1_20[1] = {0x3f};
// @
const buffer_unit_t const_1_21[1] = {0x40};
// header: 
const buffer_unit_t const_1_22[8] = {0x68,0x65,0x61,0x64,0x65,0x72,0x3a,0x20};
// method: 
const buffer_unit_t const_1_23[8] = {0x6d,0x65,0x74,0x68,0x6f,0x64,0x3a,0x20};
// method: H
const buffer_unit_t const_1_24[9] = {0x6d,0x65,0x74,0x68,0x6f,0x64,0x3a,0x20,0x48};
// reason: 
const buffer_unit_t const_1_25[8] = {0x72,0x65,0x61,0x73,0x6f,0x6e,0x3a,0x20};
// status: 
const buffer_unit_t const_1_26[8] = {0x73,0x74,0x61,0x74,0x75,0x73,0x3a,0x20};
// version: 
const buffer_unit_t const_1_27[9] = {0x76,0x65,0x72,0x73,0x69,0x6f,0x6e,0x3a,0x20};
void printCompilationInfo()
{
  fprintf(stdout, "No object file generated!\nOptions:\nSST optimization level:  3\nWord size:               UInt8T\nIdentity tables removed: False\n\nSource file: ../../../benchmarks/submatch_dfa_aot/src/kleenex/01__http_simple.kex\nSource md5:   2 ee21853c04e314c3015eabc9a afe\nSST states:  51\n");
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
}
void match1()
{
  int i = 0;
goto l1_0;
l1_0: if (!readnext(1, 8))
      {
         goto accept1;
      }
      if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'G')) || ((('I' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~')))))))))) && 1)))
      {
         outputarray(const_1_23,64);
         outputconst(next[0],8);
         consume(1);
         goto l1_9;
      }
      if (((avail >= 1) && ((next[0] == 'H') && 1)))
      {
         if (((avail >= 8) && (cmp(&next[1],(unsigned char *) "TTP/",4) && ((('0' <= next[5]) && (next[5] <= '9')) && ((next[6] == '.') && ((('0' <= next[7]) && (next[7] <= '9')) && 1))))))
         {
            outputarray(const_1_27,72);
            for(i = 0; i < 8; i++)
            {  outputconst(next[0 + i],8);
            }
            outputarray(const_1_1,8);
            consume(8);
            goto l1_3;
         }
         outputarray(const_1_24,72);
         consume(1);
         goto l1_9;
      }
      goto fail1;
l1_1: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 10) && 1)))
      {
         consume(1);
         goto l1_7;
      }
      goto fail1;
l1_2: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == ' ') && 1)))
      {
         outputarray(const_1_25,64);
         consume(1);
         goto l1_15;
      }
      goto fail1;
l1_3: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == ' ') && 1)))
      {
         outputarray(const_1_26,64);
         consume(1);
         goto l1_4;
      }
      goto fail1;
l1_4: if (!readnext(3, 3))
      {
         goto fail1;
      }
      if (((avail >= 3) && ((('0' <= next[0]) && (next[0] <= '9')) && ((('0' <= next[1]) && (next[1] <= '9')) && ((('0' <= next[2]) && (next[2] <= '9')) && 1)))))
      {
         for(i = 0; i < 3; i++)
         {  outputconst(next[0 + i],8);
         }
         outputarray(const_1_1,8);
         consume(3);
         goto l1_2;
      }
      goto fail1;
l1_5: if (!readnext(8, 8))
      {
         goto fail1;
      }
      if (((avail >= 8) && (cmp(&next[0],(unsigned char *) "HTTP/",5) && ((('0' <= next[5]) && (next[5] <= '9')) && ((next[6] == '.') && ((('0' <= next[7]) && (next[7] <= '9')) && 1))))))
      {
         for(i = 0; i < 8; i++)
         {  outputconst(next[0 + i],8);
         }
         outputarray(const_1_1,8);
         consume(8);
         goto l1_1;
      }
      goto fail1;
l1_6: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
      {
         outputconst(next[0],8);
         consume(1);
         goto l1_18;
      }
      if (((avail >= 1) && (((next[0] == ':') || ((next[0] == '[') || (next[0] == ']'))) && 1)))
      {
         outputconst(next[0],8);
         consume(1);
         goto l1_18;
      }
      goto fail1;
l1_7: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == 10) && 1)))
      {
         outputarray(const_1_1,8);
         consume(1);
         goto l1_23;
      }
      if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~'))))))))) && 1)))
      {
         outputarray(const_1_22,64);
         outputconst(next[0],8);
         consume(1);
         goto l1_8;
      }
      goto fail1;
l1_8: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~'))))))))) && 1)))
      {
         outputconst(next[0],8);
         consume(1);
         goto l1_8;
      }
      if (((avail >= 1) && ((next[0] == ':') && 1)))
      {
         outputarray(const_1_18,8);
         consume(1);
         goto l1_11;
      }
      goto fail1;
l1_9: if (!readnext(1, 1))
      {
         goto fail1;
      }
      if (((avail >= 1) && ((next[0] == ' ') && 1)))
      {
         outputarray(const_1_6,80);
         consume(1);
         goto l1_39;
      }
      if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~'))))))))) && 1)))
      {
         outputconst(next[0],8);
         consume(1);
         goto l1_9;
      }
      goto fail1;
l1_10: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          outputarray(const_1_0,8);
          consume(1);
          goto l1_10;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          consume(1);
          goto l1_7;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_10;
       }
       goto fail1;
l1_11: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          outputarray(const_1_0,8);
          consume(1);
          goto l1_11;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          consume(1);
          goto l1_27;
       }
       goto fail1;
l1_12: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          outputarray(const_1_2,16);
          consume(1);
          goto l1_13;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_3,16);
          consume(1);
          goto l1_23;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_4,16);
          consume(1);
          goto l1_13;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~'))))))))) && 1)))
       {
          outputarray(const_1_5,72);
          outputconst(next[0],8);
          consume(1);
          goto l1_8;
       }
       goto fail1;
l1_13: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          outputarray(const_1_0,8);
          consume(1);
          goto l1_13;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          consume(1);
          goto l1_29;
       }
       goto fail1;
l1_14: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_2,16);
          reset(&buf_1);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_31;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          consume(1);
          goto l1_32;
       }
       goto fail1;
l1_15: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          outputarray(const_1_0,8);
          consume(1);
          goto l1_15;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_1,8);
          consume(1);
          goto l1_7;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_15;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_15;
       }
       goto fail1;
l1_16: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_40;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_17: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_18,8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_18: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_41;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_19: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_42;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          appendarray(&buf_5,const_1_18,8);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_42;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_20: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && (((next[0] == '/') || ((next[0] == ':') || (next[0] == '@'))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       goto fail1;
l1_21: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '/') || ((next[0] == ':') || (('?' <= next[0]) && (next[0] <= '@')))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_21;
       }
       goto fail1;
l1_22: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          output(&buf_5);
          outputarray(const_1_0,8);
          consume(1);
          goto l1_13;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          outputarray(const_1_1,8);
          consume(1);
          goto l1_23;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_8,8);
          consume(1);
          goto l1_13;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~'))))))))) && 1)))
       {
          output(&buf_1);
          outputarray(const_1_22,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_8;
       }
       goto fail1;
l1_23: if (!readnext(1, 8))
       {
          goto accept1;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('#' <= next[0]) && (next[0] <= 39)) || ((('*' <= next[0]) && (next[0] <= '+')) || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'G')) || ((('I' <= next[0]) && (next[0] <= 'Z')) || ((('^' <= next[0]) && (next[0] <= 'z')) || ((next[0] == '|') || (next[0] == '~')))))))))) && 1)))
       {
          outputarray(const_1_23,64);
          outputconst(next[0],8);
          consume(1);
          goto l1_9;
       }
       if (((avail >= 1) && ((next[0] == 'H') && 1)))
       {
          if (((avail >= 8) && (cmp(&next[1],(unsigned char *) "TTP/",4) && ((('0' <= next[5]) && (next[5] <= '9')) && ((next[6] == '.') && ((('0' <= next[7]) && (next[7] <= '9')) && 1))))))
          {
             outputarray(const_1_27,72);
             for(i = 0; i < 8; i++)
             {  outputconst(next[0 + i],8);
             }
             outputarray(const_1_1,8);
             consume(8);
             goto l1_3;
          }
          outputarray(const_1_24,72);
          consume(1);
          goto l1_9;
       }
       goto fail1;
l1_24: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          outputarray(const_1_2,16);
          consume(1);
          goto l1_10;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_14;
       }
       goto fail1;
l1_25: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          appendarray(&buf_5,const_1_0,8);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_25;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_7;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_26: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          appendarray(&buf_5,const_1_9,16);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_25;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          appendarray(&buf_5,const_1_10,16);
          consume(1);
          goto l1_22;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          reset(&buf_1);
          appendarray(&buf_1,const_1_8,8);
          append(&buf_1,next[0],8);
          output(&buf_5);
          reset(&buf_5);
          appendarray(&buf_5,const_1_8,8);
          append(&buf_5,next[0],8);
          consume(1);
          goto l1_43;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          appendarray(&buf_5,const_1_8,8);
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_26;
       }
       goto fail1;
l1_27: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_9,16);
          reset(&buf_1);
          appendarray(&buf_1,const_1_9,16);
          consume(1);
          goto l1_28;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputarray(const_1_8,8);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_12,16);
          reset(&buf_1);
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_44;
       }
       goto fail1;
l1_28: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          appendarray(&buf_5,const_1_0,8);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_28;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          appendarray(&buf_5,const_1_8,8);
          consume(1);
          goto l1_44;
       }
       goto fail1;
l1_29: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_9,16);
          reset(&buf_1);
          appendarray(&buf_1,const_1_9,16);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          outputarray(const_1_8,8);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_12,16);
          reset(&buf_1);
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_45;
       }
       goto fail1;
l1_30: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          appendarray(&buf_5,const_1_0,8);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          appendarray(&buf_5,const_1_8,8);
          consume(1);
          goto l1_45;
       }
       goto fail1;
l1_31: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          appendarray(&buf_5,const_1_0,8);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_31;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_5);
          consume(1);
          goto l1_7;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_24;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_32;
       }
       goto fail1;
l1_32: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_11,24);
          reset(&buf_1);
          appendarray(&buf_1,const_1_9,16);
          consume(1);
          goto l1_31;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_8,8);
          append(&buf_5,next[0],8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_8,8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_43;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_8,8);
          consume(1);
          goto l1_32;
       }
       goto fail1;
l1_33: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_2,16);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_0,8);
          consume(1);
          goto l1_31;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_32;
       }
       goto fail1;
l1_34: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_34;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_14,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_7);
          appendarray(&buf_7,const_1_18,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_18,8);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_35;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          appendarray(&buf_5,const_1_21,8);
          appendarray(&buf_1,const_1_21,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_35: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          output(&buf_3);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          concat(&buf_5,&buf_3);
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_34;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_5);
          output(&buf_3);
          outputarray(const_1_14,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_7,next[0],8);
          append(&buf_3,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_35;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_7);
          appendarray(&buf_7,const_1_18,8);
          concat(&buf_5,&buf_3);
          reset(&buf_3);
          appendarray(&buf_3,const_1_18,8);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_35;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          output(&buf_3);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          concat(&buf_5,&buf_3);
          appendarray(&buf_5,const_1_21,8);
          appendarray(&buf_1,const_1_21,8);
          consume(1);
          goto l1_17;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_5);
          output(&buf_3);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_36: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          outputarray(const_1_16,96);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_1);
          append(&buf_1,next[0],8);
          outputarray(const_1_15,16);
          consume(1);
          goto l1_34;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          outputarray(const_1_15,16);
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_18,8);
          outputarray(const_1_15,16);
          consume(1);
          goto l1_34;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          outputarray(const_1_17,24);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          outputarray(const_1_15,16);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_37: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_37;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_7);
          appendarray(&buf_7,const_1_18,8);
          reset(&buf_3);
          appendarray(&buf_3,const_1_18,8);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_38;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_21,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_38: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_5);
          output(&buf_3);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          concat(&buf_5,&buf_3);
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_37;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_7,next[0],8);
          append(&buf_3,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_38;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_7);
          appendarray(&buf_7,const_1_18,8);
          concat(&buf_5,&buf_3);
          reset(&buf_3);
          appendarray(&buf_3,const_1_18,8);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_38;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_21,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_5);
          output(&buf_3);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_39: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= ')')) || ((next[0] == ',') || ((next[0] == ';') || ((next[0] == '=') || ((next[0] == '_') || (next[0] == '~'))))))) && 1)))
       {
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_1);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_37;
       }
       if (((avail >= 1) && ((next[0] == '*') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_13,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_13,8);
          consume(1);
          goto l1_37;
       }
       if (((avail >= 1) && (((next[0] == '+') || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z')))))) && 1)))
       {
          reset(&buf_6);
          append(&buf_6,next[0],8);
          reset(&buf_5);
          append(&buf_5,next[0],8);
          reset(&buf_2);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_46;
       }
       if (((avail >= 2) && (cmp(&next[0],(unsigned char *) "//",2) && 1)))
       {
          outputarray(const_1_15,16);
          consume(2);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_1);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_37;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_40: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_40;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_18,8);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_40;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_16;
       }
       goto fail1;
l1_41: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_41;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_18,8);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_18,8);
          consume(1);
          goto l1_41;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_42: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_1);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          append(&buf_5,next[0],8);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_42;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_6);
          appendarray(&buf_6,const_1_18,8);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_2);
          appendarray(&buf_2,const_1_18,8);
          consume(1);
          goto l1_50;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_43: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          appendarray(&buf_5,const_1_0,8);
          appendarray(&buf_1,const_1_2,16);
          consume(1);
          goto l1_25;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          appendarray(&buf_5,const_1_8,8);
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_33;
       }
       goto fail1;
l1_44: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_9,16);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_9,16);
          consume(1);
          goto l1_28;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          outputarray(const_1_8,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputarray(const_1_8,8);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_12,16);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_44;
       }
       goto fail1;
l1_45: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == 9) && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_9,16);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_9,16);
          consume(1);
          goto l1_30;
       }
       if (((avail >= 1) && ((next[0] == 10) && 1)))
       {
          output(&buf_1);
          outputarray(const_1_8,8);
          consume(1);
          goto l1_12;
       }
       if (((avail >= 1) && (((next[0] == 31) || ((('!' <= next[0]) && (next[0] <= '~')) || ((128 <= next[0]) && (next[0] <= 255)))) && 1)))
       {
          output(&buf_1);
          outputarray(const_1_8,8);
          outputconst(next[0],8);
          consume(1);
          goto l1_14;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          reset(&buf_5);
          appendarray(&buf_5,const_1_12,16);
          output(&buf_1);
          reset(&buf_1);
          appendarray(&buf_1,const_1_8,8);
          consume(1);
          goto l1_45;
       }
       goto fail1;
l1_46: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_6);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '*')) || ((next[0] == ',') || ((next[0] == ';') || ((next[0] == '=') || ((next[0] == '_') || (next[0] == '~'))))))) && 1)))
       {
          reset(&buf_5);
          concat(&buf_5,&buf_6);
          append(&buf_5,next[0],8);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_37;
       }
       if (((avail >= 1) && (((next[0] == '+') || ((('-' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((('A' <= next[0]) && (next[0] <= 'Z')) || (('a' <= next[0]) && (next[0] <= 'z')))))) && 1)))
       {
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_46;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          appendarray(&buf_5,const_1_18,8);
          appendarray(&buf_2,const_1_18,8);
          consume(1);
          goto l1_48;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          output(&buf_2);
          outputarray(const_1_21,8);
          consume(1);
          goto l1_6;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_6);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_47: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_6);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((('0' <= next[0]) && (next[0] <= '9')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~'))))))))) && 1)))
       {
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_14,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_18,8);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_18,8);
          appendarray(&buf_2,const_1_18,8);
          consume(1);
          goto l1_49;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          appendarray(&buf_5,const_1_21,8);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_21,8);
          consume(1);
          goto l1_19;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_6);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_48: if (!readnext(1, 2))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_6);
          outputarray(const_1_19,88);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          appendarray(&buf_6,const_1_18,8);
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          if (((avail >= 2) && ((next[1] == '/') && 1)))
          {
             output(&buf_5);
             consume(2);
             goto l1_36;
          }
          output(&buf_5);
          outputarray(const_1_14,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_18,8);
          append(&buf_8,next[0],8);
          append(&buf_5,next[0],8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_18,8);
          append(&buf_4,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_49;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_18,8);
          appendarray(&buf_6,const_1_18,8);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_18,8);
          appendarray(&buf_2,const_1_18,8);
          consume(1);
          goto l1_49;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          appendarray(&buf_5,const_1_21,8);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_21,8);
          consume(1);
          goto l1_19;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_6);
          outputarray(const_1_18,8);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_49: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_6);
          output(&buf_4);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          concat(&buf_6,&buf_4);
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_47;
       }
       if (((avail >= 1) && ((next[0] == '/') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_14,8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_8,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_4,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_49;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_8);
          appendarray(&buf_8,const_1_18,8);
          concat(&buf_6,&buf_4);
          appendarray(&buf_5,const_1_18,8);
          reset(&buf_4);
          appendarray(&buf_4,const_1_18,8);
          appendarray(&buf_2,const_1_18,8);
          consume(1);
          goto l1_49;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && ((next[0] == '@') && 1)))
       {
          appendarray(&buf_5,const_1_21,8);
          reset(&buf_1);
          concat(&buf_1,&buf_2);
          appendarray(&buf_1,const_1_21,8);
          consume(1);
          goto l1_19;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_6);
          output(&buf_4);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
       }
       goto fail1;
l1_50: if (!readnext(1, 1))
       {
          goto fail1;
       }
       if (((avail >= 1) && ((next[0] == ' ') && 1)))
       {
          output(&buf_1);
          output(&buf_2);
          outputarray(const_1_7,80);
          consume(1);
          goto l1_5;
       }
       if (((avail >= 1) && (((next[0] == '!') || ((('$' <= next[0]) && (next[0] <= '.')) || ((next[0] == ';') || ((next[0] == '=') || ((('A' <= next[0]) && (next[0] <= 'Z')) || ((next[0] == '_') || ((('a' <= next[0]) && (next[0] <= 'z')) || (next[0] == '~')))))))) && 1)))
       {
          append(&buf_5,next[0],8);
          concat(&buf_1,&buf_2);
          append(&buf_1,next[0],8);
          consume(1);
          goto l1_42;
       }
       if (((avail >= 1) && (((next[0] == '/') || (next[0] == '@')) && 1)))
       {
          output(&buf_5);
          outputconst(next[0],8);
          consume(1);
          goto l1_20;
       }
       if (((avail >= 1) && ((('0' <= next[0]) && (next[0] <= '9')) && 1)))
       {
          append(&buf_6,next[0],8);
          append(&buf_5,next[0],8);
          append(&buf_2,next[0],8);
          consume(1);
          goto l1_50;
       }
       if (((avail >= 1) && ((next[0] == ':') && 1)))
       {
          reset(&buf_6);
          appendarray(&buf_6,const_1_18,8);
          appendarray(&buf_5,const_1_18,8);
          concat(&buf_1,&buf_2);
          reset(&buf_2);
          appendarray(&buf_2,const_1_18,8);
          consume(1);
          goto l1_50;
       }
       if (((avail >= 1) && ((next[0] == '?') && 1)))
       {
          output(&buf_5);
          outputarray(const_1_20,8);
          consume(1);
          goto l1_21;
       }
       if (((avail >= 1) && (((next[0] == '[') || (next[0] == ']')) && 1)))
       {
          output(&buf_1);
          output(&buf_2);
          outputconst(next[0],8);
          consume(1);
          goto l1_18;
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
