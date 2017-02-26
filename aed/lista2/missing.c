#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define LENGHT 1000011
int vetor[LENGHT] = {0};

int main(void) {
  
  int numberA, numberB, i;
  
  scanf("%d", &numberA);
  for(i = 0; i < numberA; i++) {
    int tmp;
    scanf("%d", &tmp);
    vetor[tmp]++;
  }
  
  scanf("%d", &numberB);
  for(i = 0; i < numberB; i++) {
    int tmp;
    scanf("%d", &tmp);
    vetor[tmp]--;
  }
  
  for(i = 0; i < LENGHT; i++) {
    if(vetor[i] < 0) printf("%d ", i);
  }
  return 0;
}