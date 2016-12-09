#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define ROW 6
#define N (6*6) //2048*2048
#define THREADS_PER_BLOCK (ROW/2) //1024
#define RADIUS 3
#define BLOCK_SIZE (THREADS_PER_BLOCK-2*RADIUS)

// forward declaration
__global__ void dila(int *in, int *out);


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


  dila<<< (N/THREADS_PER_BLOCK), THREADS_PER_BLOCK>>>(d_in,d_out);

  // Copy result back to host
  cudaMemcpy(out, d_out, size, cudaMemcpyDeviceToHost);

  printf("OUTZ\n");
  printMatrix(out, N);

  // Cleanup
  free(in); free(out);
  cudaFree(d_in); cudaFree(d_out);
  return 0;
}



__global__ void dila(int *in, int *out) {
  __shared__ float temp[BLOCK_SIZE + 2 * RADIUS];
  int gindex = threadIdx.x + blockIdx.x * blockDim.x;
  int lindex = threadIdx.x + RADIUS;
  // 1. Read input elements into shared memory
  temp[lindex] = in[gindex];
  if (threadIdx.x < RADIUS) {
    temp[lindex - RADIUS]     = in[gindex - RADIUS];
    temp[lindex + BLOCK_SIZE] = in[gindex + BLOCK_SIZE];
  }
  __syncthreads();
  // 2. Apply the dilatation
  float result = 0.0; // low number
  for (int offset = -RADIUS ; offset <= RADIUS ; offset++){
	   result = fmaxf(result, temp[lindex + offset]);

  }
  // 3. Copy the result
  out[gindex] = result;
}
