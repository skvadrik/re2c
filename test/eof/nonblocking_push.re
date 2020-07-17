// re2c $INPUT -o $OUTPUT -fi
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <assert.h>

/*!max:re2c*/
static const size_t SIZE = 4096;

struct input_t {
  char buf[SIZE + YYMAXFILL];
  char *lim;
  char *cur;
  char *tok;
  char *mark;
  int state;
  unsigned yyaccept;
  char yych;
  FILE *file;

  input_t(FILE * file)
    : buf()
    , lim(buf + SIZE)
    , cur(lim)
    , tok(lim)
    , mark(lim)
    , state(0)
    , yyaccept(0)
    , yych(0)
    , file(file)
  {}

  bool fill()
  {
    const size_t free = (tok - buf) + SIZE - (lim - buf);
    if (free < 1) return false;
    const size_t prefix = (tok - buf);

    memmove(buf, tok, buf - tok + SIZE);
    lim -= prefix;
    cur -= prefix;
    tok -= prefix;
    mark -= prefix;
    size_t to_read = SIZE - (lim - buf);
    printf("> Reading input, can take up to %lu bytes\n", to_read);
    size_t bytes_read = fread(lim, 1, to_read, file);
    lim += bytes_read;
    lim[0] = 0;

    // quick make a copy of buffer with newlines replaced w/ _
    char b[40];
    snprintf(b, 40, "%s", buf);
    for(int i = 0; i < 40; i++) {
      if ('\n' == b[i]) { b[i] = '_'; }
    }
    printf("> Read %lu bytes from input, current buffer: >%.40s<\n", bytes_read, b);

    return true;
  }
};

enum status_t {
  OK,
  FAIL,
  NEED_MORE_INPUT,
  WHITESPACE,
  WORD,
  THING
};
const char * STATUSES[] = {
  "OK",
  "FAIL",
  "NEED_MORE_INPUT",
  "WHITESPACE",
  "WORD",
  "THING"
};

#define YYGETSTATE()  in.state
#define YYSETSTATE(s) in.state = s
#define YYFILL() do { \
  printf("< Returning for more input\n"); \
  return NEED_MORE_INPUT; \
} while (0)

static status_t lex(input_t &in)
{
/*!getstate:re2c*/
/*!re2c
    re2c:define:YYCTYPE  = char;
    re2c:define:YYCURSOR = in.cur;
    re2c:define:YYLIMIT  = in.lim;
    re2c:define:YYMARKER = in.mark;
    re2c:variable:yych   = in.yych;
    re2c:eof             = 0;

    *                       { printf("< Unexpected character >%c<\n", in.yych); return FAIL; }
    $                       { printf("< EOF\n");                                return OK; }
    [\n ]+                  { printf("< whitespace\n");                         return WHITESPACE; }
    [a-zA-Z]+               { printf("< word\n");                               return WORD; }
    "THING\nWITH\nNEWLINES" { printf("< Thing w/ newlines\n");                  return THING; }
*/
}

int main()
{
  int fds[2];
  pipe(fds);
  fcntl(fds[0], F_SETFL, fcntl(fds[0], F_GETFL) | O_NONBLOCK);
  FILE * write = fdopen(fds[1], "w");
  FILE * read = fdopen(fds[0], "r");
  input_t in(read);

  const char * packets[] = {
    "THING\n",
    "WITH\n",
    "NEWLINES\n",
    "H", "E", "L", "O", "\n",
    "HELO\n",
    "THING\nWITH\n",
    "NEWLINES"
  };
  size_t num_packets = sizeof(packets) / sizeof(char *);
  size_t current_packet = 0;

  enum status_t result = NEED_MORE_INPUT;

  while (OK != result) {
    switch (result) {
      case NEED_MORE_INPUT:
        if (current_packet == num_packets) {
          printf("Not enough input\n");
          goto end;
        }

        fwrite(packets[current_packet], strlen(packets[current_packet]), 1, write);
        fflush(write);
        current_packet++;
        printf("Packet %lu / %lu written\n", current_packet, num_packets);

        if (current_packet == num_packets) {
          printf("%lu / %lu packets sent, Closing down communication channel\n",
            current_packet, num_packets);
          fclose(write);
          write = NULL;
        }

        in.fill();
        break;

      case FAIL:
        goto end;

      default:
        // careful, need to reset state (re2c forgets to do it)
        YYSETSTATE(0);
        break;
    }

    result = lex(in);
    printf("Received response from lexer: %s\n", STATUSES[result]);
  }

end:

  // cleanup
  fclose(read);
  if (write) {
    fclose(write);
  }

  return result == OK ? 0 : 1;
}

#undef YYGETSTATE
#undef YYSETSTATE
#undef YYFILL
