

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  const char *pattern = "mul\\([0-9]+,[0-9]+\\)";
  regex_t regex;
  regmatch_t matches[1];
  regcomp(&regex, pattern, REG_EXTENDED);

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

  for (size_t i = 0; i < lines; i++) {
    char *line = NULL;
    size_t n = 0;
    size_t line_length = 0;

    getline(&line, &n, fptr);

    // End setup

    while (regexec(&regex, line, 1, matches, 0) == 0) {
      int start = matches[0].rm_so;
      int end = matches[0].rm_eo;
      int len = end - start;

      char substr[8];
      strncpy(substr, line + start + 4, len - 4);
      substr[len] = '\0';

      printf("%s\n", substr);

      int a = atoi(strtok(substr, ","));
      int b = atoi(strtok(NULL, ","));
    }

    printf("%d\n", total_1);

    free(line);
  }

  fclose(fptr);

  return 0;
}
