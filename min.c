#if 0
#!/usr/bin/env sh
set -e # stop on first error
cc "$0" -o a.out && ./a.out
exit
#endif

/*
 * Does exactly the same thing as main.c but the code
 * has been reduced to its minimalistic C form.
 */

#include <search.h>
#include <stdio.h>
#include <stdlib.h>

static char *data[] = { "alpha", "bravo", "charlie", "delta",
    "echo", "foxtrot", "golf", "hotel", "india", "juliet",
    "kilo", "lima", "mike", "november", "oscar", "papa",
    "quebec", "romeo", "sierra", "tango", "uniform",
    "victor", "whisky", "x-ray", "yankee", "zulu"
};

#define LEN(a) (sizeof(a)/sizeof(*a))
#define FORMAT "%9.9s -> %9.9s:%d\n"

int main(void)
{
    size_t i;
    ENTRY *e;
    hcreate(LEN(data)*2);
    /* insert all but two last elements */
    for (i=0;i<LEN(data)-2;i++) hsearch((ENTRY){data[i],(void*)i}, ENTER);
    /* try to find last four elements - two should be missing */
    for (i=LEN(data)-4;i<LEN(data);i++) {
        if(e = hsearch((ENTRY){data[i]}, FIND))
             printf(FORMAT, data[i], e->key, (size_t)(e->data));
        else printf(FORMAT, data[i], "NULL", 0);
    }
    return 0;
}
