#include "file.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_straight(char *line, int index) {
  if (line[index] != 'X') {
    return 0;
  }
  if (line[index + 1] != 'M') {
    return 0;
  }
  if (line[index + 2] != 'A') {
    return 0;
  }
  if (line[index + 3] != 'S') {
    return 0;
  }
  return 1;
}

int check_backwards(char *line, int index) {
  if (line[index] != 'X') {
    return 0;
  }
  if (line[index - 1] != 'M') {
    return 0;
  }
  if (line[index - 2] != 'A') {
    return 0;
  }
  if (line[index - 3] != 'S') {
    return 0;
  }
  return 1;
}

int check_vertical(char **matrix, int row, int col, int line_count) {
  if (row + 3 >= line_count)
    return 0;
  if (matrix[row][col] != 'X') {
    return 0;
  }
  if (matrix[row + 1][col] != 'M') {
    return 0;
  }
  if (matrix[row + 2][col] != 'A') {
    return 0;
  }
  if (matrix[row + 3][col] != 'S') {
    return 0;
  }
  return 1;
}

int check_vertical_backwards(char **matrix, int row, int col, int line_count) {
  if (row - 3 < 0)
    return 0;
  if (matrix[row][col] != 'X') {
    return 0;
  }
  if (matrix[row - 1][col] != 'M') {
    return 0;
  }
  if (matrix[row - 2][col] != 'A') {
    return 0;
  }
  if (matrix[row - 3][col] != 'S') {
    return 0;
  }
  return 1;
}

int check_diagonals(char **matrix, int row, int col, int line_count) {
  if (row + 3 >= line_count)
    return 0;
  if (col + 3 >= strlen(matrix[row]))
    return 0;

  if (matrix[row][col] != 'X') {
    return 0;
  }
  if (matrix[row + 1][col + 1] != 'M') {
    return 0;
  }
  if (matrix[row + 2][col + 2] != 'A') {
    return 0;
  }
  if (matrix[row + 3][col + 3] != 'S') {
    return 0;
  }

  return 1;
}

int main(int argc, char *argv[]) {
  int line_count;
  char **lines = read_file_lines(argv[1], &line_count);

  int total = 0;

  for (int i = 0; i < line_count; i++) {
    printf("Line: %s\n", lines[i]);
    int temp = 0;
    for (int j = 0; j < strlen(lines[i]); j++) {
      // Check horizontal matches
      if (check_straight(lines[i], j) || check_backwards(lines[i], j)) {
        total++;
        temp++;
      }
      // Check vertical matches
      if (check_vertical(lines, i, j, line_count) ||
          check_vertical_backwards(lines, i, j, line_count)) {
        total++;
        temp++;
      }
      // Check diagonal matches
      if (check_diagonals(lines, i, j, line_count)) {
        total++;
        temp++;
      }
    }
    printf("Found %d matches in this line\n", temp);
  }

  printf("The result is: %d\n", total);

  free(lines);
  return 0;
}
