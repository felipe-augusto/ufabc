#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

__global__ void td(int *in, int *out, int * d_flag);
__global__ void soma(int *in, int *out, int * end);
__global__ void copy(int *in, int *out, int * end);
__global__ void fill(int *in, int * end);
int * td_gpu(int * in);