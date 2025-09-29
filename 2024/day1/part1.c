#define _GNU_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main(int argc, char *argv[]) {
  FILE *fptr = fopen("input.txt", "r");

  int cr;
  size_t lines = -1;

  while ((cr = getc(fptr)) != EOF) {
    if (cr == '\n') {
      lines++;
    }
  }

  printf("Number of lines: %ld\n", lines);
  rewind(fptr);

  int left[lines];
  int right[lines];
  size_t n;

  for (size_t i = 0; i < lines; i++) {
    left[i] = 0;
    right[i] = 0;
    char *temp = NULL;
    size_t n = 0;
    size_t line_length = 0;

    line_length = getline(&temp, &n, fptr);

    if (line_length < 14)
      continue;

    char *token = strtok(temp, " ");

    for (size_t j = 0; j < 3; j++) {
      if (j > 0 && token) {
        int val = atoi(strdup(token));
        if (j == 1)
          left[i] = val;
        else if (j == 2)
          right[i] = val;
        token = strtok(NULL, " ");
      }
    }
    free(temp);
  }
  fclose(fptr);

  int n_1 = sizeof(right) / sizeof(right[0]);
  int n_2 = sizeof(left) / sizeof(left[0]);

  qsort(left, n_2, sizeof(int), comp);
  qsort(right, n_1, sizeof(int), comp);

  size_t sum = 0;

  for (size_t i = 0; i < lines; i++) {
    sum += abs(left[i] - right[i]);
  }

  printf("The difference is: %lu\n", sum);

  return 0;
}
