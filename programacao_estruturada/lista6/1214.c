#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//coloque a funcao calcula aqui
double calcula(int *notas, int n) {
  int i;
  float total = 0;
  int acima = 0;
  for(i = 0; i < n; i++){
    total += notas[i];
  }
  total = total / n;
  for(i = 0; i < n; i++){
    if(notas[i] > total) {
      acima++;
    }
  }
  return ((double) acima / (double) n) * 100.0;
}

int main() {
  int c, n, i, j;
  int *notas;
  double resp;
  scanf("%d", &c);
  for(i=0; i<c; i++) {
    scanf("%d",&n);
    notas = (int *) malloc(sizeof(int)*n);
    for(j=0; j<n; j++) 
      scanf("%d", &notas[j]);
    resp = calcula(notas, n);
    free(notas);
    printf("%.3lf%%\n", resp);
  }
}