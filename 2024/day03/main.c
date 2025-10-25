

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const char *pattern = "mul\\([0-9]+,[0-9]+\\)";
  const char *pattern_2 = "(do\\(\\))|(don't\\(\\))|(mul\\([0-9]+,[0-9]+\\))";

  regex_t regex;
  regcomp(&regex, pattern_2, REG_EXTENDED);

  FILE *fptr = fopen(argv[1], "r");

  int cr;
  size_t lines = 0;

  while ((cr = getc(fptr)) != EOF) {
    if (cr == '\n') {
      lines++;
    }
  }

  printf("Number of lines: %ld\n", lines);
  rewind(fptr);

  int total_1 = 0;
  int total_2 = 0;
  char *line = NULL;
  size_t n = 0;

  for (size_t i = 0; i < lines; i++) {
    size_t line_length = 0;

    getline(&line, &n, fptr);

    // End setup
    regmatch_t matches[4];

    char *cursor = line;

    int active = 1;

    while (regexec(&regex, cursor, 4, matches, 0) == 0) {
      int start = matches[0].rm_so;
      int end = matches[0].rm_eo;

      if (matches[1].rm_so != -1) {
        active = 1;
      } else if (matches[2].rm_so != -1) {
        active = 0;
      } else {

        int len = matches[3].rm_eo - matches[3].rm_so;
        char substr[8];
        strncpy(substr, cursor + matches[3].rm_so + 4, len - 5);
        substr[len - 5] = '\0';

        int a = atoi(strtok(substr, ","));
        int b = atoi(strtok(NULL, ","));

        if (active) {
          total_2 += a * b;
        }
        total_1 += a * b;
      }

      cursor += end;
    }

    printf("Part 1: %d\n", total_1);
    printf("Part 2: %d\n", total_2);
  }
  free(line);

  fclose(fptr);

  return 0;
}
