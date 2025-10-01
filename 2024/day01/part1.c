#define _GNU_SOURCE
#include "file.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void *a, const void *b) { return (*(int *)a - *(int *)b); }

int main(int argc, char *argv[]) {
  int line_count;
  char **lines = read_file_lines("input.txt", &line_count);

  int left[line_count];
  int right[line_count];
  size_t n;

  for (size_t i = 0; i < line_count; i++) {
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

  int n_1 = sizeof(right) / sizeof(right[0]);
  int n_2 = sizeof(left) / sizeof(left[0]);

  qsort(left, n_2, sizeof(int), comp);
  qsort(right, n_1, sizeof(int), comp);

  size_t sum = 0;

  for (size_t i = 0; i < line_count; i++) {
    sum += abs(left[i] - right[i]);
  }

  printf("The difference is: %lu\n", sum);

  return 0;
}
