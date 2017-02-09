#include <stdio.h>
#include <stdlib.h>

typedef struct aluno_s {
	int idade;
	int nota;
} aluno;

// compare pass to qsort
int comp(const void * a, const void * b) {
	aluno * aa = (aluno *) a;
	aluno * bb = (aluno *) b;
	if(aa->idade == bb->idade){
		return aa->nota - bb->nota;
	}
	return aa->idade - bb->idade;
}

void ordena(aluno * a, int n) {
	qsort(a, n, sizeof(a), comp);
}

void imprime(aluno * a, int n) {
	int i;
	for(i = 0; i < n; i++) {
		printf("%d %d\n", a[i].idade, a[i].nota);
	}
}

void encontra(int idade, aluno * a, int n) {
	int i;
	int found = 0;
	// tenha certeza que eh ordenado
	// apesar da funcao assumir, preferi garantir
	ordena(a, n);
	for(i = 0; i < n; i++) {
		if (a[i].idade == idade) {
			int min = 100;
			int max = 0;
			int cont = 1;
			while(cont) {
				if(a[i + cont - 1].idade == idade) {
					if(a[i + cont - 1].nota < min) {
						min = a[i + cont - 1].nota;
					} else if(a[i + cont - 1].nota > max) {
						max = a[i + cont - 1].nota;
					}
					cont++;
				} else {
					cont = 0;
				}
			}
			found = 1;
			// teria que fazer o caso de um aluno so
			if(min != 100 && max != 0) {
				printf("PRESENTE %d %d\n", min, max);
			} else {
				printf("PRESENTE\n");
			}
			break;
		}
	}
	if(!found) {
		printf("AUSENTE\n");
	}
}

int main() {
	int n_alunos, i;
	scanf("%d", &n_alunos);
	// cria lista de alunos
	aluno * alunos = malloc(sizeof(aluno) * n_alunos);
	// preenche a lista de alunos
	for(i = 0; i < n_alunos; i++) {
		int idade, nota;
		scanf("%d", &idade);
		scanf("%d", &nota);
		alunos[i].idade = idade;
		alunos[i].nota = nota;
	}
	// ordena
	ordena(alunos, n_alunos);
	imprime(alunos, n_alunos);
	// busca alunos
	int busca;
	scanf("%d", &busca);
	encontra(busca, alunos, n_alunos);
}
