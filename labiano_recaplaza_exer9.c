#include <stdio.h>
#include <stdlib.h>
#define N 5

int main() {
  int start, move;
  int nopts[N + 2];         // array of top of stacks
  int option[N + 2][N + 2]; // array of stacks of options
  int i, candidate;

  move = start = 0;
  nopts[start] = 1;

  while (nopts[start] > 0) // while dummy stack is not empty
  {
    if (nopts[move] > 0) {
      move++;
      nopts[move] = 0; // initialize new move

      if (move == 1) {
        for (candidate = N; candidate >= 1; candidate--) {
          nopts[move]++;
          option[move][nopts[move]] = candidate;
        }
      } else {
        for (candidate = N; candidate >= 1; candidate--) {
          for (i = move - 1; i >= 1; i--)
            if (candidate <= option[i][nopts[i]])
              break;
          if (!(i >= 1))
            option[move][++nopts[move]] = candidate;
        }
      }
    } else {
      if (move == N + 1) // reached end of array
      {
        for (i = 1; i < move; i++)
          printf("%2i", option[i][nopts[i]]); // print the top of stacks
        printf("\n");

        move--; // go back to previous stack and pop tos
        nopts[move]--;
      }

      if (nopts[move] != 0) {                              // if stack is not empty
        for (candidate = N; candidate >= 1; candidate--) { // compare cand to current tos
          if (option[move][nopts[move]] <= candidate) {    // if tos <= cand
            move++;                                        // go to next stack and "push" cand
            nopts[move]++;
          }
        }
      }

      if (nopts[move] == 0) { // if stack is empty, simply print the tos
        for (i = 1; i < move; i++)
          printf("%2i", option[i][nopts[i]]);
        printf("\n");
        move--; // go back to previous stack and pop tos
        nopts[move]--;
      }
    }
  }
}