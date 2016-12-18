#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



// verifica se existe algum zero dentro de uma matriz
int zeros(int ** m, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		if(m[i][j] != 0) return 1;
	}
  }
  return 0;
}

// copia o conteudo de uma matriz para outro
void soma(int ** f, int ** g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		f[i][j] = f[i][j] + g[i][j];
	}
  }
}

// copia o conteudo de uma matriz para outro
void copy(int ** f, int ** g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		f[i][j] = g[i][j];
	}
  }
}

// imprime um matriz
void print(int ** mat, int M, int N){
  int i, j;

  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		printf("%d ", mat[i][j]);
	}
	printf("\n");
  }
}


// gera numeros binarios aleatorios para a matrix
void generateRandom(int ** mat, int row, int col) {
	srand((unsigned int)time(0));
	srand(rand());
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			if(i == 0 || j == 0 || j + 1 == col || i + 1 == row) {
				mat[i][j] = 0;
			} else {
				mat[i][j] = 1;
			}
		}
	}
}

int main() {
	int size = 20;
	int i, j, l, k;
	// aloca dinamicamente espaço para a matrix
	int ** m = malloc(size * sizeof(int * ));
	for(i = 0; i < size; i++){
		m[i] = malloc(size * sizeof(int));
		for(j = 0; j < size; j++) {
			m[i][j] = 0;
		}
	}

	// aloca dinamica espaço para a matrix de saida
	int ** out = malloc(size * sizeof(int * ));
	for(i = 0; i < size; i++){
		out[i] = malloc(size * sizeof(int));
		for(j = 0; j < size; j++) {
			out[i][j] = 0;
		}
	}

	// matrix com a soma
	int ** mtest = malloc(size * sizeof(int * ));
	for(i = 0; i < size; i++){
		mtest[i] = malloc(size * sizeof(int));
		for(j = 0; j < size; j++) {
			mtest[i][j] = 0;
		}
	}


	generateRandom(m, size, size);
	print(m, size, size);

	soma(mtest, m, size, size);
	// TD - awkward way to do it (multiplas erosoes somando em uma nova matriz)
	while(zeros(m, size, size)) {
		// erosion
		for(i = 0; i < size; i++) {
			for(j = 0; j < size; j++) {
				float mini = size * size;
				for(l = -1; l < 2; l++) {
					for(k = -1; k < 2; k++) {
						// tratamento de bordas
						if(i + l >= 0 && i + l < size && j + k >= 0 && j + k < size) {
							if(abs(l) + abs(k) == 2) {
								mini = fmin(sqrt(m[i + l][j + k]), mini);
							} else {
								mini = fmin(m[i + l][j + k], mini);
							}
							
						}
					}
				}
				if(mini != size * size) {
					out[i][j] = mini;
				}
			}
		}
		copy(m, out, size, size);
		soma(mtest, m, size, size);
	}

	printf("\n");

	print(mtest, size, size);
}

