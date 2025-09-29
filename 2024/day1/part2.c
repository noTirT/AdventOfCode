#define _GNU_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000

int size = 0;
int keys[MAX_SIZE];
int values[MAX_SIZE];

int getIndex(int key) {
  for (int i = 0; i < size; i++) {
    if (keys[i] == key)
      return i;
  }
  return -1;
}

void insert(int key, int value) {
  int index = getIndex(key);
  if (index == -1) {
    keys[size] = key;
    values[size] = value;
    size++;
  } else {
    values[index] = value;
  }
}

int get(int key) {
  int index = getIndex(key);
  if (index == -1)
    return 0;
  return values[index];
}

void increment(int key) {
  int index = getIndex(key);
  if (index == -1) {
    insert(key, 1);
  } else {
    int curr = get(key);
    curr += 1;
    insert(key, curr);
  }
}

void printMap() {
  for (int i = 0; i < size; i++) {
    printf("%d: %d\n", keys[i], values[i]);
  }
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
        else if (j == 2) {
          printf("Got the current value: %d\n", get(val));
          right[i] = val;
          increment(val);
          printf("And now Got the current value: %d\n\n", get(val));
        }

        token = strtok(NULL, " ");
      }
    }
    free(temp);
  }

  size_t sum = 0;

  for (size_t i = 0; i < lines; i++) {
    int mult = get(left[i]);
    sum += mult * left[i];
    printf("For key %d and value %d we calculate an addition of %d and as a "
           "result the sum %lu\n",
           right[i], left[i], mult * left[i], sum);
  }

  printMap();

  printf("The sum is: %lu\n", sum);

  fclose(fptr);

  return 0;
}
