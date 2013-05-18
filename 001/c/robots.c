#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* purposely made BUFSIZE small so we get a chance to see the algorithm work */
#define BUFSIZE 10

int count_lasers(char* start, char* final, int parity) {
  int count = 0;
  if (final == NULL) {
    for (char *p = start; *p; p++) {
      if (parity && *p == '|')
        count++;
      parity = !parity;
    }
  } else {
    /* we need to go backwards */
    for (char *p = start; p >= final; p--) {
      if (parity && *p == '|')
        count++;
      parity = !parity;
    }
  }
  return count;
}

void process(char *upper, char *middle, char *lower) {
  char *p;
  /* this assumes that middle contains X */
  if ((p = strchr(middle, 'X')) == NULL) {
    printf("Something went wrong.  Missing X\n");
    return;
  }
  int x = p - middle;
  int west = count_lasers(upper + x, upper, 1) + count_lasers(lower + x, lower, 0);
  int east = count_lasers(upper + x, NULL, 1) + count_lasers(lower + x, NULL, 0);
  printf("GO %s\n", east < west ? "EAST" : "WEST");
}


int main(int argc, char *argv[]) {
  FILE *fp = NULL;
  char buf[BUFSIZE];
  char *line = NULL;
  int size = 0;
  char *lines[] = { NULL, NULL, NULL };
  int linenum = 0;

  if (argc != 2) {
    printf("Usage: %s FILENAME\n", argv[0]);
    exit(1);
  }

  char *filename = argv[1];
  if((fp = fopen(filename, "r")) == NULL) {
    perror(filename);
    exit(1);
  }
  while (fgets(buf, BUFSIZE, fp) != NULL) {
    /* ignore blank lines */
    if (line == NULL && strcmp(buf, "\n") == 0)
      continue;
    /* we use realloc here because we don't know if BUFSIZE is  bug enough
     * to hold the line so on next iteration we need to enlarge the array */
    line = realloc(line, sizeof(char) * (size + BUFSIZE));
    strncpy(line + size, buf, BUFSIZE);
    size += BUFSIZE - 1; /* need to be 1 less than BUFSIZE so replace \0 */
    /* store the line if the line is complete */
    if (strchr(buf, '\n') != NULL) {
      lines[linenum++] = line;
      line = NULL;
      size = 0;
    }
    /* we have enough lines so we can process this */
    if (linenum == 3) {
      process(lines[0], lines[1], lines[2]);
      /* do some cleanup */
      for (int i = 0; i < 3; i++) {
        free(lines[i]);
      }
      linenum=0;
      line = NULL;
    }
  }
  fclose(fp);
  return EXIT_SUCCESS;
}

