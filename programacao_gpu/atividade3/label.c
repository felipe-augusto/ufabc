#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int M = 2048;
int N = 2048;

int cor = 0;

int matrix[2048][2048];
int labels[2048][2048];


struct cedula {
	int i;
	int j;
	int cor;
};

/// stack
// no minimo o dobro
int MAXSIZE = 4000000;       
struct cedula stack[4000000];     
int top = -1;            

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

struct cedula peek() {
   return stack[top];
}


struct cedula pop() {
   struct cedula data;
	
   if(!isempty()) {
      data = stack[top];
      top = top - 1;   
      return data;
   }else {
      printf("Could not retrieve data, Stack is empty.\n");
   }
}

int push(struct cedula data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top] = data;
   }else {
      printf("Could not insert data, Stack is full.\n");
   }
}

void m_fill_random(int mat[M][N]) {
  srand((unsigned int)time(0));
  // int seed = rand();

  // use same seed to draw the same image again on every test
  srand(rand());
  int i, j;

  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		mat[i][j] = rand() % 2;
	}
  }
}

void fill_negative(int mat[M][N]) {
  //srand((unsigned int)time(NULL));
  // int seed = rand();

  // use same seed to draw the same image again on every test
  srand(rand());
  int i, j;

  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		mat[i][j] = -1;
	}
  }
}

void print(int mat[M][N]){
  int i, j;

  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		printf("%d ", mat[i][j]);
	}
	printf("\n");
  }
}

void replace(int mat[M][N]){
  int i, j;

  for(i = 0; i < M; i++) {
	for(j = 0; j < N; j++) {
		if(mat[i][j] == -1) {
			mat[i][j] = 0;
		};
	}
  }
}

int main() {

	int i, j, k, l;
	float time;
	clock_t t;
	struct cedula cedula_tmp;
	//printf("ORIGINAL: \n");
	m_fill_random(matrix); // gera imagem binaria na memoria
	fill_negative(labels); // inicializa vetor de labels com -1
	//print(matrix);
	int round = 0;

	//printf("LABEL: \n");

	// medindo o tempo
	time = 0;
	t = clock();
	// comeca
	for(i = 0; i < M; i++) {
		for(j = 0; j < N; j++) {
			// achei um pixel que esteja pintado (semente)
			if(matrix[i][j] > 0 && labels[i][j] == -1) {
				// posicao que foi encontrada
				cedula_tmp.i = i;
				cedula_tmp.j = j;
				push(cedula_tmp);
				//printf("%d %d \n", cedula_tmp.i, cedula_tmp.j);
				// todos com cor um
				cor++;
				while (!isempty()) {
					cedula_tmp = pop();
					//pinta no label
					labels[cedula_tmp.i][cedula_tmp.j] = cor;
					//vizinhanca
					for(k = -1; k < 2; k++){
						for(l = -1; l < 2; l++){
							if(matrix[cedula_tmp.i + k][cedula_tmp.j + l] > 0 && (0 <= cedula_tmp.i + k) && (cedula_tmp.i + k < M) && (0 <= cedula_tmp.j + l) && (cedula_tmp.j + l < N) && labels[cedula_tmp.i + k][cedula_tmp.j + l] == -1) {
								// achei um vizinho que satisfaz
								struct cedula * new_tmp = malloc(sizeof (struct cedula));
								new_tmp->i = cedula_tmp.i + k;
								new_tmp->j = cedula_tmp.j + l;
								//printf("empilhei: %d %d %p\n", new_tmp->i, new_tmp->j, new_tmp);
								push(* new_tmp);
							}
						}
					}
				}
			}
		}
	}

	// limpa a stack inteira

	time = (float)(clock() - t);
	time = time / CLOCKS_PER_SEC;

	printf("Imagem %dx%d: %5.1fms\n", M, N, time * 1000);

	replace(labels); // troca o -1 que estava de referencia por 0
	//print(labels);

}
