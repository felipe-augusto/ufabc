#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



// verifica se existe algum zero dentro de uma matriz
int zeros(float ** m, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		if(m[i][j] != 0) return 1;
	}
  }
  return 0;
}

// copia o conteudo de uma matriz para outro
void soma(float ** f, float ** g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		f[i][j] = f[i][j] + g[i][j];
	}
  }
}

// copia o conteudo de uma matriz para outro
void copy(float ** f, float  ** g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		f[i][j] = g[i][j];
	}
  }
}

// imprime um matriz
void print(float ** mat, int M, int N){
  int i, j;

  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		printf("%.2f ", mat[i][j]);
	}
	printf("\n");
  }
}


// gera numeros binarios aleatorios para a matrix
void completeRandom(float ** mat, int row, int col) {
	srand((unsigned int)time(0));
	srand(rand());
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			mat[i][j] = rand() % 2;
		}
	}
}


// gera numeros binarios aleatorios para a matrix
void generateRandom(float ** mat, int row, int col) {
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
	mat[row - 1][j - 2] = 1;
	mat[row - 2][j - 1] = 1;
}

int main() {
	int size = 20;
	int i, j, l, k;
	// aloca dinamicamente espaço para a matrix
	float ** m = malloc(size * sizeof(float * ));
	for(i = 0; i < size; i++){
		m[i] = malloc(size * sizeof(float));
		for(j = 0; j < size; j++) {
			m[i][j] = 0;
		}
	}

	// aloca dinamica espaço para a matrix de saida
	float ** out = malloc(size * sizeof(float * ));
	for(i = 0; i < size; i++){
		out[i] = malloc(size * sizeof(float));
		for(j = 0; j < size; j++) {
			out[i][j] = 0;
		}
	}

	// matrix com a soma
	float ** mtest = malloc(size * sizeof(float * ));
	for(i = 0; i < size; i++){
		mtest[i] = malloc(size * sizeof(float));
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
							mini = fmin(m[i + l][j + k], mini);
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

