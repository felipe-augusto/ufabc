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

int * td_gpu(int * in) {
  float time_;
  clock_t t;
  int *out, *end, * flag;     // host copies a,b
  int *d_in,*d_out, *d_end, * d_flag;  // device copies a,b
  int size = N * sizeof(int);

  // allocate outup space
  out = (int *)malloc(size);
  end = (int *)malloc(size);
  flag = (int *)malloc(sizeof(int));

  // Allocate space for device copies of in, out
  cudaMalloc((void **)&d_in, size);
  cudaMalloc((void **)&d_out, size);
  cudaMalloc((void **)&d_end, size);
  cudaMalloc((void **)&d_flag, sizeof(int));

  // copy input matrix an flag from host to device
  cudaMemcpy(d_in, in, size, cudaMemcpyHostToDevice);
  cudaMemcpy(d_flag, flag, sizeof(int), cudaMemcpyHostToDevice);

  time_ = 0;
  t = clock();

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
  time_ = (float)(clock() - t);
  time_ = time_ / CLOCKS_PER_SEC;
  printf("Tempo GPU (apenas TD): %5.1fms\n", time_ * 1000);
  return end;
  // Cleanup
  free(in); free(out);
  cudaFree(d_in); cudaFree(d_out); cudaFree(d_end);
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
  // flag para continuear ou nao
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
