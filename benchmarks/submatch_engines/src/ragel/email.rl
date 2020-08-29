#include "common.h"

/* From the Ragel manual:
    "To guard against this kind of problem one must ensure that the machine
     specification is divided up using boundaries that do not allow 
     ambiguities from one portion of the machine to the next."
*/

char *mark;

%%{
    machine email_fst;
    action mark {
        mark = p;
    }
    action print {
        fputs(mark, stdout);
    }

    estr = /[a-z0-9!#$%&'*+/=?^_`{|}~\-]/;
    beforeAt = estr+ ('.' estr+)*;
    az09 = /[a-z0-9]/;
    az09dash = /[a-z0-9\-]*[a-z0-9]/;
    part = az09 az09dash? '.';
    afterAt = part+ az09 az09dash?;

    email = beforeAt '@' afterAt;

    fb = /[^\n]*/;

    main := ((email >mark %print | (fb - email)) '\n')* ;
}%%

/*
Call "mark" upon entry to the sub-machine "email".
Call "print" when exiting the sub-maching "email".
*/

%% write data;

int main(int argc, char **argv)
{
    PRE

    while (fgets(buffer, sizeof(buffer), stdin)) {
        INIT_LINE;
        %% write init;
        %% write exec;

        if (p != pe) {
            FAIL;
        }
    }

    POST
    return 0;
}
