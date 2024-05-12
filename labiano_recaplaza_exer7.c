#include <stdio.h>
#include <stdlib.h>

int comp(const void *a, const void *b) {
  int *x, *y;
  x = (int *)a;
  y = (int *)b;
  return (*x - *y);
}

int main() {
  // initialize S, k, cell
  int S[] = {3, 7, 2, 9, 5};
  int k = 10;
  int cell, sLen;
  // cell = no (0) or yes (1)

  // row = length of s
  sLen = sizeof(S) / sizeof(S[0]);
  // sort subset S
  qsort(S, sLen, sizeof(int), comp);

  // column = k+1
  int col = k + 1;
  // initialize column 0 with 1s
  int mat[sLen][col];
  for (int i = 1; i < sLen + 1; i++) {
    for (int j = 0; j < col; j++) {
      if (j == 0)
        mat[i][j] = 1;
      else
        mat[i][j] = 0;
    }
  }

  // if sum of all elements in subset is less than column, assign 0
  // cell = max(cell above, cell above and S_i to the left)
  // if there is no S_i to the left, copy above cell
  // if the corner cell is 1, there's a solution

  // traceback where the 1s came from
  // go up until the highest 1, add the current S_i to the subset
  // go up and S_i cell to the left
  // repeat until we reach first column (not included in solution set), or uppermost row

  // checkers
  printf("Array length: %d\n\n", sLen);

  printf("Sorted array: ");
  for (int i = 0; i < sLen; i++) {
    printf("%d ", S[i]);
  }
  printf("\n\n");

  printf("Matrix:\n");
  for (int i = 0; i < sLen + 0; i++) {
    for (int j = 0; j < col; j++) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }

  return 0;
}