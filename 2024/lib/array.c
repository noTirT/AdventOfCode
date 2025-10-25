#include "array.h"
#include <stdlib.h>
#include <string.h>

char **rotate_matrix_clockwise(char **matrix, int rows) {

  char **rotated = malloc(sizeof(char *) * (strlen(matrix[0]) + 1));

  for (int i = 0; i < rows; i++) {
    for (int j = 0; i < strlen(matrix[i]); j++) {
      rotated[j][rows - i - 1] = matrix[i][j];
    }
  }

  return rotated;
}
