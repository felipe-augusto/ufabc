#include <stdio.h>
#include <stdlib.h>

void sol_iterativa(int k, int *pai, int n) {
	int i;
	while(k != 0) {
		for(i = 0; i < n; i++) {
			if(i == k) {
				printf("%d ", k);
				k = pai[i];
				break;
			}
		}
	}
	printf("0\n");
};

void sol_recursiva(int k, int *	pai) {
	if(k == 0) {
		printf("%d\n", k);
	} else {
		printf("%d ", k);
		sol_recursiva(pai[k], pai);
	}
};

int main() {
  int n, *pai, k, i;
  scanf("%d", &n);
  pai = malloc(sizeof(n));
  for(i=0; i<n; i++) {
    scanf("%d", &pai[i]);
  }
  scanf("%d", &k);
  sol_recursiva(k, pai);
  // coloquei o tamanho para fazer a iterativa
  // nao consegui imaginar uma maneira de fazer sem
  sol_iterativa(k, pai, n);
}



