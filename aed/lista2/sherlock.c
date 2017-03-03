#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
  int tests, i;
  scanf("%d", &tests);
  for(i = 0; i < tests; i++) {
    int tamanho, j, k;
    scanf("%d", &tamanho);
    int * vetor = malloc(tamanho * sizeof(int));
    int * left = malloc(tamanho * sizeof(int));
    int * right = malloc(tamanho * sizeof(int));
    int acc = 0;
    // calculate left side sum
    for(j = 0; j < tamanho; j++) {
      scanf("%d", &vetor[j]);
      acc += vetor[j];
      left[j] = acc;
    }
    // right side sum
    acc = 0;
    for(j = tamanho -1; j >= 0; j--) {
      acc += vetor[j];
      right[j] = acc;
    }
    // find    
    int found = 0;
    j = 0;
    while(j < tamanho && !found) {
      int leftSum = left[j - 1];
      int rightSum = right[j + 1];
      if (j == 0) leftSum = 0;
      if (j ==  tamanho - 1) rightSum  =0;
      if(leftSum == rightSum) {
        found = 1;
        printf("YES\n");
      }
      j++;
    }
    
    if(!found) {
      printf("NO\n");
    }
  }
  return 0;
}
