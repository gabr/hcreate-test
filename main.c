#if 0
#!/usr/bin/env sh
set -e # stop on first error
CFLAGS="-std=c99 -Wall -Wextra -Wshadow -Wno-pointer-to-int-cast -Wno-misleading-indentation -Wmissing-declarations -Wswitch-enum -Wno-deprecated-declarations -pedantic -ggdb"
cc "$0" $CFLAGS -o a.out && ./a.out
exit
#endif

#include <search.h>
#include <stdio.h>
#include <stdlib.h>

static char *data[] = { "alpha", "bravo", "charlie", "delta",
    "echo", "foxtrot", "golf", "hotel", "india", "juliet",
    "kilo", "lima", "mike", "november", "oscar", "papa",
    "quebec", "romeo", "sierra", "tango", "uniform",
    "victor", "whisky", "x-ray", "yankee", "zulu"
};

int
main(void)
{
   ENTRY e;
   ENTRY *ep;

   hcreate(30);

   for (size_t i = 0; i < 24; i++) {
       e.key = data[i];
       /* data is just an integer, instead of a
          pointer to something */
       e.data = (void *) i;
       ep = hsearch(e, ENTER);
       /* there should be no failures */
       if (ep == NULL) {
           fprintf(stderr, "entry failed\n");
           exit(EXIT_FAILURE);
       }
   }

   for (size_t i = 22; i < 26; i++) {
       /* print two entries from the table, and
          show that two are not in the table */
       e.key = data[i];
       ep = hsearch(e, FIND);
       printf("%9.9s -> %9.9s:%d\n", e.key,
              ep ? ep->key : "NULL", ep ? (int)(ep->data) : 0);
   }
   hdestroy();
   exit(EXIT_SUCCESS);
}
