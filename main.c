#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LEN 5000
#define QUOTE_ENTITY_LEN 5
bool ONE_LINER = false;

/*
 * Prints usage.
 */
static void
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

/*
 * Replace unicode entities quotes with ASCII ones.
 */
void
replace_quotes (char line[MAX_LINE_LEN])
{
  char modified_line[MAX_LINE_LEN] = {0};

  snprintf (modified_line, MAX_LINE_LEN - 1, "%s", line);
  char *read_ptr = line;
  char *last_read = read_ptr;
  char *write_ptr = modified_line;

  while ((read_ptr = strstr (read_ptr, "&#39;")))
    {
      write_ptr += read_ptr - last_read;
      read_ptr += QUOTE_ENTITY_LEN;
      snprintf (write_ptr, MAX_LINE_LEN, "'%s", read_ptr);
      write_ptr++;
      last_read = read_ptr;
    }

  int wanna_write = snprintf (line, MAX_LINE_LEN - 1,  "%s", modified_line);
  if (wanna_write > MAX_LINE_LEN - 1)
    fprintf (stderr, "replace_quotes(): Warning: line truncated.\n");
}

/*
 * Convert given line to plain text.
 */
void
process (const char line[MAX_LINE_LEN])
{
  if (strncmp (line, "<p", 2) != 0)
    return;

  char *ptr = (char *) line;
  ptr += strcspn (ptr, ">") + 1;
  size_t len = strcspn (ptr, "<") + 1;
  char output[MAX_LINE_LEN] = {0};
  snprintf (output, len, "%s", ptr);

  printf ("%s", output);

  if (ONE_LINER)
    putchar (' ');
  else
    putchar ('\n');
}

int
main (int argc, char **argv)
{
  int err = 0;
  FILE *file = NULL;
  char line[MAX_LINE_LEN] = {0};

  if (argc > 1 && strncmp (argv[1], "-1", 3) == 0)
    ONE_LINER = true;

  if (argc == 1 || (ONE_LINER && argc == 2))
    {
      fprintf (stderr, "No file provided.\n");
      usage (argv[0]);
      exit (1);
    }

  const char *filename = ONE_LINER ? argv[2] : argv[1];
  file = fopen (filename, "r");
  if (!file)
    {
      perror ("Can't open file");
      exit (1);
    }

  while (fgets (line, MAX_LINE_LEN, file))
    {
      replace_quotes (line);
      process (line);
    }

  if (file) fclose (file);
  return err;
}
