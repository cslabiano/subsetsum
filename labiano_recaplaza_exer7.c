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

  int col = k + 1;
  int mat[sLen + 1][col];

  // Initialize the matrix
  for (int i = 0; i <= sLen; i++) {
    for (int j = 0; j <= k; j++) {
      if (j == 0) {
        mat[i][j] = 1; // Sum of 0 can always be made with the empty subset
      } else {
        mat[i][j] = 0; // Initial assumption: no sum can be made
      }
    }
  }

  // if sum of all elements in subset is less than column, assign 0
  // cell = maximum or the logical operator or of the cell above and the cell one step up and S sub i cells to the left
  // if there is no S_i to the left, copy above cell
  // Fill the matrix using dynamic programming approach
  for (int i = 1; i <= sLen; i++) {
    for (int j = 1; j <= k; j++) {
      if (S[i - 1] > j) {
        mat[i][j] = mat[i - 1][j];
      } else {
        mat[i][j] = mat[i - 1][j] || mat[i - 1][j - S[i - 1]];
      }
    }
  }

  printf("Matrix:\n");
  for (int i = 1; i <= sLen; i++) {
    for (int j = 0; j <= k; j++) {
      printf("%d ", mat[i][j]);
    }
    printf("\n");
  }

  printf("\n");

  // if the corner cell is 1, there's a solution
  if (mat[sLen][k]) {
    printf("A subset with sum %d exists.\n", k);
  } else {
    printf("No subset with sum %d exists.\n", k);
    return 0;
  }

  // traceback where the 1s came from
  // from the bottom right cell, go up until the highest cell with a 1
  // add the current S_i to the subset
  // go one cell up and S_i cell to the left
  // add the current S_i to the subset
  // repeat until we reach the first column or row
  // dont't include column 0 to our solution set
  printf("Subset with sum %d: ", k);
  int i = sLen;
  int j = k;
  while (i > 0 && j > 0) {
    if (mat[i][j] && !mat[i - 1][j]) { // current cell is part of the subset
      printf("%d ", S[i - 1]);         // print the corresponding element
      j -= S[i - 1];                   // move left by S[i-1] cells
    }
    i--; // move up one cell
  }
  printf("\n");

  return 0;
}