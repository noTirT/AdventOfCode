#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkSave(int arr[], int n) {
  int ascending = 1;
  int descending = 1;

  for (int i = 1; i < n; i++) {
    if (arr[i] > arr[i - 1]) {
      descending = 0;
    }
    if (arr[i] < arr[i - 1]) {
      ascending = 0;
    }
    int diff = abs(arr[i] - arr[i - 1]);
    if (diff < 1 || diff > 3) {
      return 0;
    }
  }
  return ascending || descending;
}

int main(int argc, char *argv[]) {
  FILE *fptr = fopen("input.txt", "r");

  int cr;
  size_t lines = 0;

  while ((cr = getc(fptr)) != EOF) {
    if (cr == '\n') {
      lines++;
    }
  }

  printf("Number of lines: %ld\n", lines);
  rewind(fptr);

  int result_1 = 0;
  int result_2 = 0;

  for (size_t i = 0; i < lines; i++) {
    char *temp = NULL;
    size_t n = 0;
    size_t line_length = 0;

    line_length = getline(&temp, &n, fptr);

    int count = 1;
    for (int j = 0; j < line_length; j++) {
      count += (temp[j] == ' ');
    }

    char *token = strtok(temp, " ");

    int level[count];

    int curr_ind = 0;
    while (token != NULL) {
      int val = atoi(strdup(token));
      level[curr_ind++] = val;
      token = strtok(NULL, " ");
    }

    // End setup

    // Check for part 1
    if (checkSave(level, count)) {
      result_1 += 1;
      result_2 += 1;
    } else {
      for (int skip_ind = 0; skip_ind < count; skip_ind++) {
        int temp_arr[count - 1];
        int curr_ind = 0;
        for (int j = 0; j < count; j++) {
          if (j == skip_ind)
            continue;
          temp_arr[curr_ind++] = level[j];
        }
        if (checkSave(temp_arr, count - 1)) {
          result_2 += 1;
          goto cont;
        }
      }
    }

  cont:;

    free(temp);
  }

  printf("There are %d safe reports for task 1\n", result_1);
  printf("There are %d safe reports for task 2\n", result_2);
  fclose(fptr);

  return 0;
}
