#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int comp(const void *a, const void *b) {
  int *x, *y;
  x = (int *)a;
  y = (int *)b;
  return (*x - *y);
}

void subsetsum(int *arr, int sum, int arrLen) {
  // timer
  double t;
  clock_t t1, t2;
  t1 = clock();

  int start, move;
  int nopts[arrLen + 2];              // array of top of stacks
  int option[arrLen + 2][arrLen + 2]; // array of stacks of options
  int i, candidate, currentSum;
  int validSubsets = 0;

  move = start = 0;
  nopts[start] = 1;

  while (nopts[start] > 0) // while dummy stack is not empty
  {
    if (nopts[move] > 0) {
      move++;
      nopts[move] = 0; // initialize new move

      if (move == 1) {
        for (candidate = arrLen - 1; candidate >= 0; candidate--) {
          nopts[move]++;
          option[move][nopts[move]] = candidate;
        }
      } else {
        for (candidate = arrLen - 1; candidate >= 0; candidate--) {
          for (i = move - 1; i >= 1; i--)
            if (arr[candidate] <= arr[option[i][nopts[i]]])
              break;
          if (!(i >= 1))
            option[move][++nopts[move]] = candidate;
        }
      }
    } else {
      if (move == arrLen + 1) // reached end of array
      {
        int partialSum = 0;
        for (i = 1; i < move; i++) // get sum of the tos
          partialSum += arr[option[i][nopts[i]]];

        if (partialSum == sum) {
          printf("{ ");
          for (int j = 1; j < move; j++) {
            printf("%i", arr[option[j][nopts[j]]]); // print the top of stacks
            if (j != move - 1)
              printf(", ");
          }
          printf(" }");
          printf("\n");
          validSubsets++;
        }

        move--; // go back to previous stack and pop tos
        nopts[move]--;
      }

      if (nopts[move] != 0) {                                       // if stack is not empty
        for (candidate = arrLen - 1; candidate >= 0; candidate--) { // compare cand to current tos
          if (arr[option[move][nopts[move]]] <= arr[candidate]) {   // if tos <= cand
            move++;                                                 // go to next stack and "push" cand
            nopts[move]++;
          }
        }
      }

      if (nopts[move] == 0) { // if stack is empty, print the tos when partialSum == sum
        int partialSum = 0;
        for (i = 1; i < move; i++)
          partialSum += arr[option[i][nopts[i]]];

        if (partialSum == sum) {
          printf("{ ");
          for (i = 1; i < move; i++) {
            printf("%i", arr[option[i][nopts[i]]]);
            if (i != move - 1)
              printf(", ");
          }

          printf(" }");
          printf("\n");
          validSubsets++;
        }
        move--; // go back to previous stack and pop tos
        nopts[move]--;
      }
    }
  }
  if (validSubsets == 0)
    printf("There are no subsets that are equal to the sum.\n");
  else
    printf("Total number of valid subsets: %d\n", validSubsets);

  t2 = clock(); // clock_t
  t = (double)(t2 - t1) / (double)CLOCKS_PER_SEC;

  printf("\nTime elapsed: %f\n", t);
}

int main() {
  int sets, sum;
  char *str = (char *)malloc(sizeof(char) * 1000);

  FILE *fp = fopen("input.txt", "r");
  if (fp != NULL) {
    sets = atoi(fgets(str, sizeof(str), fp));
    printf("No of sets: %d\n\n", sets); // =======print for checking only=========

    for (int i = 0; i < sets; i++) {
      sum = atoi(fgets(str, sizeof(str), fp));
      printf("Sum: %d\n", sum); // =======print for checking only=========

      int *arr = (int *)malloc(sizeof(int));

      fscanf(fp, "%[^\n]\n", str);

      char *token = strtok(str, " ");
      int index = 0;
      while (token != NULL) {
        arr[index] = atoi(token); // convert token to integer and store in the array
        index++;

        token = strtok(NULL, " "); // get the next token
      }

      // sort the array
      qsort(arr, index, sizeof(int), comp);

      printf("Integers: "); // =======print for checking only=========
      for (int j = 0; j < index; j++) {
        printf("%d ", arr[j]);
      }
      printf("\n");

      printf("Subsets:\n");
      subsetsum(arr, sum, index);
      free(arr);

      printf("\n");
    }
  }
  free(str);
  fclose(fp);
  return 0;
}