#include <stdio.h>
#include <stdlib.h>

int arredonda(int n) {
  int tmp = n % 10;
  if (tmp > 0 && tmp < 5) {
    return n - tmp + 5;
  } else if(tmp > 5 && tmp <= 9) {
    return n - tmp + 10;
  } else {
    return n;
  }
}

void histograma(int *notas, int n) {
  int i;
  int last_index[4] = {0}; // quatro ranges
  for(i = 0; i < n; i++) {
    if(notas[i] >= 0 && notas[i] < 30) {
      last_index[0] += 1;
    } else if (notas[i] >= 30 && notas[i] < 50) {
      last_index[1] += 1;
    } else if (notas[i] >= 50 && notas[i] < 85) {
      last_index[2] += 1;
    } else if (notas[i] >= 85 && notas[i] <= 100) { // poderia ser so um else (mas assim preve erros)
      last_index[3] += 1;
    }
  }
  printf("%d aluno(s) tiraram de  0 a 29\n", last_index[0]);
  printf("%d aluno(s) tiraram de 30 a 49\n", last_index[1]);
  printf("%d aluno(s) tiraram de 50 a 84\n", last_index[2]);
  printf("%d aluno(s) tiraram de 85 a 100\n", last_index[3]);

}

int main() {
  int *notas, n, i;
  scanf("%d", &n);
  notas = malloc(sizeof(int)*n);
  for(i=0; i<n; i++) {
    scanf("%d", &notas[i]);
    notas[i] = arredonda(notas[i]);
  }
  for(i=0; i<n; i++) {
    printf("%d ",notas[i]);
  }
  printf("\n");
  histograma(notas, n);
  return 0;
}
