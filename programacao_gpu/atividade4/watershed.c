#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


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

// copia o conteudo de uma matriz para outro
void copy(int ** f, int ** g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		f[i][j] = g[i][j];
	}
  }
}

// verifica se existe algum zero dentro de uma matriz
int zeros(int ** m, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		if(m[i][j] == 0) return 1;
	}
  }
  return 0;
}

// cria um objecto aleatorio
void createRandomBlock(int ** m, int M, int N) {
  int i, j, l, k;
  srand((unsigned int)time(0));
  srand(rand());
  int object = 1;
  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		if (m[i][j] == 0 && rand() % M < M/10) {
			int tamanho_x = rand() % 4;
			int tamanho_y = rand() % 4;
			object++;
			for(l = -tamanho_x; l < tamanho_y; l++) {
				for(k = -tamanho_y; k < tamanho_y; k++) {
					if(0 <= i + l && i + l < M && 0 <= j + k && j + k < N) {
						m[i + l][j + k] = object;
					}
				}
			}
		}
	}
  }
}

int main() {

	int i, j, k, l, w;
	float time_;
	clock_t t;
	int tamanhos[6] = {128, 256, 512, 1024, 2048, 4096};
	// benchmark imagens com tamanhos diferentes
	for (w = 0; w < 6; w++){
		int size = tamanhos[w];

		// aloca dinamicamente espaço para a matrix
		int ** m = malloc(size * sizeof(int * ));
		for(i = 0; i < size; i++){
			m[i] = malloc(size * sizeof(int));
			for(j = 0; j < size; j++) {
				m[i][j] = 0;
			}
		}
		// cria uma imagem para teste

		// m[0][0] = 1;
		// m[0][1] = 1;
		// m[0][2] = 1;
		// m[1][0] = 1;
		// m[1][1] = 1;
		// m[1][2] = 1;
		// m[3][5] = 2;
		// m[3][6] = 2;
		// m[3][7] = 2;
		// m[4][5] = 2;
		// m[4][6] = 2;
		// m[4][7] = 2;
		// m[9][0] = 3;
		// m[9][1] = 3;
		// m[9][2] = 3;
		// m[9][3] = 3;
		
		// funcao que tenta criar alguns blocos para simular alguns objetos
		createRandomBlock(m, size, size);
		
		// caso queira ver a matriz
		// print(m, size, size);

	 	// aloca a matriz de saida
		int ** out = malloc(size * sizeof(int * ));
		for(i = 0; i < size; i++){
			out[i] = malloc(size * sizeof(int));
			for(j = 0; j < size; j++) {
				out[i][j] = 0;
			}
		}

		// mede o tempo do watershed
		time_ = 0;
		t = clock();

		// watershed
		copy(out, m, size, size);
		
		while(zeros(m, size, size)) {
			for(i = 0; i < size; i++) {
				for (j = 0; j < size; j++) {
					if (m[i][j] == 0) {
						int max = 0;
						for(k = -1; k < 2; k++) {
							for (l = -1; l < 2; l++) {
								// condicoes de borda
								if(0 <= i + k && i + k < size && 0 <= j + l && j + l < size) {
									if(max < m[i + k][j + l]) {
										max = m[i + k][j + l];
									}
								}
							}
						}
						out[i][j] = max;
					}
				}
			}
			copy(m, out, size, size);
		}

		// medindo o tempo
		time_ = (float)(clock() - t);
		time_ = time_ / CLOCKS_PER_SEC;

		// caso queira ver a matriz de saida
		// print(out, size, size);

		// mostra o tempo que demorou
		printf("Imagem %dx%d: %5.1fms\n", size, size, time_ * 1000);
		
		free(m);
		free(out);
	}

}
