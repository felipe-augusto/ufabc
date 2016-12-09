#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ROW 8
#define N (ROW*ROW) //2048*2048
#define THREADS_PER_BLOCK 1 //1024
#define RADIUS 3
#define BLOCK_SIZE (THREADS_PER_BLOCK-2*RADIUS)

// forward declaration
__global__ void td(int *in, int *out);


void random_ints(int * mat, int n) {
  srand(time(0));
  int i;
  for (i = 0; i < n; i++) {
    mat[i] = (rand() % 2) * 10;
  }
}

void printMatrix(int * mat, int n) {

  int i, j;
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < ROW; j++) {
      printf("%d ", mat[i * ROW + j]);
    }
    printf("\n");
  }

}


int main(void) {
  int *in, *out;     // host copies a,b
  int *d_in,*d_out;  // device copies a,b
  int size = N * sizeof(int);

  // Alloc space for host copies a,b and setup input
  in  = (int *)malloc(size);

  random_ints(in, N);
  out = (int *)malloc(size);

  printf("IN\n");
  printMatrix(in, N);

  // Allocate space for device copies of in, out
  cudaMalloc((void **)&d_in, size);
  cudaMalloc((void **)&d_out, size);

  cudaMemcpy(d_in, in, size, cudaMemcpyHostToDevice);

  td<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_in,d_out);


  // Copy result back to host
  cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);

  printf("OUT\n");
  printMatrix(out, N);

  // Cleanup
  free(in); free(out);
  cudaFree(d_in); cudaFree(d_out);
  return 0;
}



__global__ void td(int *in, int *out) {
  int first_index = 0;
  int current_index = threadIdx.x + blockIdx.x * blockDim.x;
  int last_index = (ROW * ROW); // dimensao do bloco * numero_de_blocos + threads por bloco

  int distancia_esq = 0;
  int distancia_dir = 0;
  // olha todas as casas à esquerda da posição original
  for(int offset = current_index; offset >= 0; offset--) {
	if((int)in[offset] == 0){
		// achou a distancia minima a esquerda
		out[current_index] = distancia_esq;
		break;
	}
	// nao achou incrementa e continua
	distancia_esq++;
  }
  __syncthreads(); // espera todos à esquerda terminar

  // olha todas as casas à direita da posição original
  for(int offset = current_index; offset < last_index; offset++){
	if((int)in[offset] == 0) {
		// ver se a distancia a direita eh menor que a esquerda ja calculada
		if(out[current_index] > distancia_dir) {
			out[current_index] = distancia_dir;
		}
		break; // achou a distancia minima a direita

	}
	distancia_dir++;
  }



  __syncthreads(); // espera todas à direita terminar
}
