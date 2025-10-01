#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **read_file_lines(const char *filename, int *lines) {
  FILE *fptr = fopen(filename, "r");

  int cr = 0;
  *lines = 0;

  while ((cr = getc(fptr)) != EOF) {
    if (cr == '\n')
      (*lines)++;
  }

  printf("Reading file '%s' with %d lines...\n", filename, *lines);

  rewind(fptr);

  char **contents = malloc(sizeof(char *) * (*lines + 1));
  size_t len = 0;
  for (int i = 0; i < *lines; i++) {
    contents[i] = NULL;
    len = 0;
    getline(&contents[i], &len, fptr);
    contents[i][strlen(contents[i]) - 1] = '\0';
  }

  fclose(fptr);
  return contents;
}
