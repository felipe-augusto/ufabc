#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ROW 512
#define N (ROW*ROW) //2048*2048
#define THREADS_PER_BLOCK (ROW) //1024


// forward declaration
__global__ void td(int *in, int *out, int * d_flag);
__global__ void soma(int *in, int *out, int * end);
__global__ void copy(int *in, int *out, int * end);
__global__ void fill(int *in, int * end);

void random_ints(int * mat, int n) {
  srand(time(0));
  int i;
  for (i = 0; i < n; i++) {
    mat[i] = rand() % 2;
  }
}

void prandom_ints(int * mat, int n) {
  int i, j;
  for (i = 0; i < ROW; i++) {
    for (j = 0; j < ROW; j++) {
      if(i == 0 || j == 0 || j + 1 == ROW || i + 1 == ROW) {
        mat[i * ROW + j] = 0;
      } else {
        mat[i * ROW + j] = 1;
      }
      
    }
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
  mat[row - 1][j - 2] = 1;
  mat[row - 2][j - 1] = 1;
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
  int *in, *out, *end, * flag;     // host copies a,b
  int *d_in,*d_out, *d_end, * d_flag;  // device copies a,b
  int size = N * sizeof(int);

  // Alloc space for host copies a,b and setup input
  in  = (int *)malloc(size);
  // fill input matrix (as an example)
  prandom_ints(in, N);
  out = (int *)malloc(size);
  end = (int *)malloc(size);
  flag = (int *)malloc(sizeof(int));

  printf("IN\n");
  //printMatrix(in, N);

  // Allocate space for device copies of in, out
  cudaMalloc((void **)&d_in, size);
  cudaMalloc((void **)&d_out, size);
  cudaMalloc((void **)&d_end, size);
  cudaMalloc((void **)&d_flag, sizeof(int));

  // copy input matrix an flag from host to device
  cudaMemcpy(d_in, in, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_flag, flag, sizeof(int), cudaMemcpyHostToDevice);

  // set as true
  flag[0] = 1;
  // copy input to end
  fill<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_in,d_end);

  // enquanto tiver
  while(flag[0]) {
    td<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_in,d_out, d_flag);
    copy<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_in, d_out, d_end);
    soma<<<N/THREADS_PER_BLOCK,THREADS_PER_BLOCK>>>(d_in, d_out, d_end);
    cudaMemcpy(flag, d_flag, sizeof(int), cudaMemcpyDeviceToHost);
  }

  // Copy result back to host
  cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);
  cudaMemcpy(end, d_end, size, cudaMemcpyDeviceToHost);

  printf("flag: %d\n", flag[0]);

  printf("END\n");
  //printMatrix(end, N);

  // Cleanup
  free(in); free(out);
  cudaFree(d_in); cudaFree(d_out); cudaFree(d_end);
  return 0;
}

__global__ void td(int *in, int *out, int * d_flag) {
  d_flag[0] = 0;
  int current_index = threadIdx.x + blockIdx.x * blockDim.x;
  int * local_in  = (int *)malloc(ROW * ROW);

  int l, m;
  float mini = ROW * ROW;
  for(l = -1; l <= 1; l++) {
    for(m = -1; m <= 1; m++) {
      // borda
      if(((int) blockIdx.x + l) >= 0 && ((int) blockIdx.x + l) < ROW && ((int) threadIdx.x + m) >= 0 && ((int) threadIdx.x + m) < ROW) {
        mini = fmin(in[(blockIdx.x + l) * blockDim.x + (threadIdx.x + m)], mini);
      }
    }
  }

  if(mini != ROW * ROW) {
    out[current_index] = mini;
  }

  if(mini != 0) {
    d_flag[0] = 1;
  }
  
}

__global__ void copy(int *in, int *out, int * end) {
  int current_index = threadIdx.x + blockIdx.x * blockDim.x;
  in[current_index] = out[current_index];
}

__global__ void soma(int *in, int *out, int * end) {
  int current_index = threadIdx.x + blockIdx.x * blockDim.x;
  end[current_index] += out[current_index];
}

__global__ void fill(int *in, int * end) {
  int current_index = threadIdx.x + blockIdx.x * blockDim.x;
  end[current_index] = in[current_index];
}
