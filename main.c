#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool ONE_LINER = false;

void
usage (const char *progname)
{
  fprintf (stderr, " \
%s [-1] <file> \n\
\n\
Converts a TTML subtitle file to a text file, written on STDOUT. \n\
\n\
Options: \n\
\n\
`-1`: print all in one line (eg to facilitate grepping). \n", progname);
}

int
main (int argc, char **argv)
{
  if (argc > 1 && strncmp (argv[1], "-1", 3))
    ONE_LINER = true;

  if (argc == 1 || (ONE_LINER && argc == 2))
    {
      fprintf (stderr, "No file provided.\n");
      usage (argv[0]);
      exit (1);
    }
}
