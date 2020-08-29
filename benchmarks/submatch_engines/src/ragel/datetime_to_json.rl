#include "common.h"

#define P(C) fputs(C, stdout);

int echo = 0;

%%{
  machine datetime;

    action echo_on  { echo = 1; }
    action echo_off { echo = 0; }
    action dump {
        if (echo) {
            fputc(fc, stdout);
        }
    }

    year     = (([1-9] [0-9]*)? [0-9]{4})                              > { P("{'year'='") };
    month    = ('1' [0-2] | '0' [1-9])                                 > { P("', 'month'='") };
    day      = ('3' [0-1] | '0' [1-9] | [1-2] [0-9])                   > { P("', 'day'='") };
    hours    = ('2' [0-3] | [0-1] [0-9])                               > { P("', 'hours'='") };
    minutes  = ([0-5] [0-9])                                           > { P("', 'minutes'='") };
    seconds  = ([0-5] [0-9])                                           > { P("', 'seconds'='") };
    timezone = ('Z' | [+\-] ('2' [0-3] | [0-1] [0-9]) ':' [0-5] [0-9]) > { P("', 'tz'='") };

    dateTime = year     > echo_on % echo_off '-'
               month    > echo_on % echo_off '-'
               day      > echo_on % echo_off 'T'
               hours    > echo_on % echo_off ':'
               minutes  > echo_on % echo_off ':'
               seconds  > echo_on
               timezone % { P("'}") };

    main := (dateTime '\n') $ dump;
}%%

%% write data;

int main(int argc, char **argv)
{
    PRE;

    while(fgets(buffer, sizeof(buffer), stdin)) {
        INIT_LINE;
        %% write init;
        %% write exec;

        if (p != pe) {
            FAIL;
        }
    }

    POST;
    return 0;
}
