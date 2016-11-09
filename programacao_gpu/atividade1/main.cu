#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

int* m_malloc(int n) {
  return (int* )malloc(sizeof (int) * n * n);
}
void m_fill_random(int * mat, int n) {
  //srand((unsigned int)time(NULL));
  // int seed = rand();

  // use same seed to draw the same image again on every test
  srand(rand());
  int i;
  for (i = 0; i < n * n; i++) {
    mat[i] = rand() % 10;
  }
}

void mm_cpu(int * A, int * B, int * C, int n) {
  int i, j, k;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++) {
      C[i * n + j] = 0;
      for (k = 0; k < n; k++)
        C[i * n + j] += A[i * n + k] * B[k * n + j];
    }
}

void print_mat(int * A, int * B, int * C, int n) {
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", A[i * n + j]);
    printf("\n");
  }
  printf("\n\n");

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", B[i * n + j]);
    printf("\n");
  }
  printf("\n \n");

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++)
      printf("%d ", C[i * n + j]);
    printf("\n");
  }
}

// Matrices are stored in row-major order:
// M(row, col) = *(M.elements + row * M.width + col)
typedef struct {
  int width;
  int height;
  int stride; // necessario para o metodo com shared memory
  int* elements;
} Matrix;

// Thread block size
#define BLOCK_SIZE 16

// GET e SET elementos do device

__device__ float GetElement(const Matrix A, int row, int col) {  // Get a matrix element
    return A.elements[row * A.stride + col];
}

__device__ void SetElement(Matrix A, int row, int col, float value) {  // Set a matrix element
    A.elements[row * A.stride + col] = value;
}

// Get the BLOCK_SIZExBLOCK_SIZE sub-matrix Asub of A that is located col sub-matrices to the right and row 
 __device__ Matrix GetSubMatrix(Matrix A, int row, int col)    {        // sub-matrices down from the upper-left corner of A
    Matrix Asub;
    Asub.width    = BLOCK_SIZE;
    Asub.height   = BLOCK_SIZE;
    Asub.stride   = A.stride;
    Asub.elements = &A.elements[A.stride * BLOCK_SIZE * row + BLOCK_SIZE * col];
    return Asub;
}

// Forward declaration of the matrix multiplication kernel
__global__ void MatMulKernel_g(const Matrix, const Matrix, Matrix);
__global__ void MatMulKernel_s(const Matrix, const Matrix, Matrix);
void MatMul_g(const Matrix A, const Matrix B, Matrix C, int device);
void MatMul_s(const Matrix A, const Matrix B, Matrix C, int device);

int main() {

  clock_t t;
  float time;
  int co = 2;
  int size[7] = {256, 512, 1024, 2048, 4096, 8192, 16384}; // more sizes

	int n = size[co];

	printf("======= Matriz %dx%d =======\n", n, n);

	int* A = m_malloc(n);
	int* B = m_malloc(n);
	int* C = m_malloc(n);
	
	Matrix mA;
	mA.width = n;
	mA.height = n;
	mA.elements = A;

	Matrix mB;
	mB.width = n;
	mB.height = n;
	mB.elements = B;

	Matrix mC;
	mC.width = n;
	mC.height = n;
	mC.elements = C;

	m_fill_random(A, n);
	m_fill_random(B, n);

	  time = 0;
	  t = clock();
	  mm_cpu(A, B, C, n);
	  time = (float)(clock() - t);
	  time = time / CLOCKS_PER_SEC;
	  printf("CPU   = %10.1fms \n", time * 1000);

	  int count = 1;

	  cudaDeviceProp prop;
   	  cudaGetDeviceProperties(&prop, count);
	  cudaSetDevice(count);

	  t = clock();
	  MatMul_g(mA, mB, mC, count);
	  time = (float)(clock() - t);
	  time = time / CLOCKS_PER_SEC;
	  printf("GPU_GLOBAL - %s = %10.1fms \n", prop.name, time * 1000);

	  t = clock();
	  MatMul_s(mA, mB, mC, count);
	  time = (float)(clock() - t);
	  time = time / CLOCKS_PER_SEC;
	  printf("GPU_SHARED - %s = %10.1fms \n", prop.name, time * 1000);

	  free(A);
	  free(B);
	  free(C);
  return 0;
}



// Matrix multiplication - Host code
// Matrix dimensions are assumed to be multiples of BLOCK_SIZE
void MatMul_g(const Matrix A, const Matrix B, Matrix C, int device) {
  // Load A and B to device memory
  Matrix d_A;
  d_A.width = A.width;
  d_A.height = A.height;
  size_t size = A.width * A.height * sizeof(float);
  cudaSetDevice(device);
  cudaMalloc(&d_A.elements, size);
  cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);
  Matrix d_B;
  d_B.width = B.width;
  d_B.height = B.height;
  size = B.width * B.height * sizeof(float);
  cudaMalloc(&d_B.elements, size);
  cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);

  // Allocate C in device memory
  Matrix d_C;
  d_C.width = C.width;
  d_C.height = C.height;
  size = C.width * C.height * sizeof(float);
  cudaMalloc(&d_C.elements, size);

  // Invoke kernel
  dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
  dim3 dimGrid(B.width / dimBlock.x, A.height / dimBlock.y);
  MatMulKernel_g <<< dimGrid, dimBlock>>>(d_A, d_B, d_C);

  // Read C from device memory
  cudaMemcpy(C.elements, d_C.elements, size, cudaMemcpyDeviceToHost);

  // Free device memory
  cudaFree(d_A.elements);
  cudaFree(d_B.elements);
  cudaFree(d_C.elements);
}

// PRATICAMENTE IGUAL AO ANTERIOR, COM A DIFERENCA
// QUE O KERNEL INVOCADO AQUI EH O DE SHARED AO INVES DO GLOBAL
void MatMul_s(const Matrix A, const Matrix B, Matrix C, int device) {
  // Load A and B to device memory
  Matrix d_A;
  d_A.width = A.width;
  d_A.height = A.height;
  size_t size = A.width * A.height * sizeof(float);
  cudaSetDevice(device);
  cudaMalloc(&d_A.elements, size);
  cudaMemcpy(d_A.elements, A.elements, size, cudaMemcpyHostToDevice);
  Matrix d_B;
  d_B.width = B.width;
  d_B.height = B.height;
  size = B.width * B.height * sizeof(float);
  cudaMalloc(&d_B.elements, size);
  cudaMemcpy(d_B.elements, B.elements, size, cudaMemcpyHostToDevice);

  // Allocate C in device memory
  Matrix d_C;
  d_C.width = C.width;
  d_C.height = C.height;
  size = C.width * C.height * sizeof(float);
  cudaMalloc(&d_C.elements, size);

  // Invoke kernel
  dim3 dimBlock(BLOCK_SIZE, BLOCK_SIZE);
  dim3 dimGrid(B.width / dimBlock.x, A.height / dimBlock.y);
  MatMulKernel_s <<< dimGrid, dimBlock>>>(d_A, d_B, d_C);

  // Read C from device memory
  cudaMemcpy(C.elements, d_C.elements, size, cudaMemcpyDeviceToHost);

  // Free device memory
  cudaFree(d_A.elements);
  cudaFree(d_B.elements);
  cudaFree(d_C.elements);
}

// MULTIPLICACAO DE MATRIZES UTILIZANDO MEMORIA GLOBAL
__global__ void MatMulKernel_g(Matrix A, Matrix B, Matrix C) {
  // Each thread computes one element of C by accumulating results into Cvalue
  float Cvalue = 0;
  int row = blockIdx.y * blockDim.y + threadIdx.y;
  int col = blockIdx.x * blockDim.x + threadIdx.x;
  for (int e = 0; e < A.width; ++e)
    Cvalue += A.elements[row * A.width + e] * B.elements[e * B.width + col];
  C.elements[row * C.width + col] = Cvalue;
}

// MULTIPLICACAO DE MATRIZES UTILIZANDO MEMORIA COMPARTILHADA
__global__ void MatMulKernel_s(Matrix A, Matrix B, Matrix C)
{
    // Block row and column
    int blockRow = blockIdx.y;
    int blockCol = blockIdx.x;

    // Each thread block computes one sub-matrix Csub of C
    Matrix Csub = GetSubMatrix(C, blockRow, blockCol);

    // Each thread computes one element of Csub
    // by accumulating results into Cvalue
    float Cvalue = 0;

    // Thread row and column within Csub
    int row = threadIdx.y;
    int col = threadIdx.x;


    // Loop over all the sub-matrices of A and B that are
    // required to compute Csub
    // Multiply each pair of sub-matrices together
    // and accumulate the results
	for (int m = 0; m < (A.width / BLOCK_SIZE); ++m) {
		// Get sub-matrix Asub of A
		Matrix Asub = GetSubMatrix(A, blockRow, m);
		// Get sub-matrix Bsub of B
		Matrix Bsub = GetSubMatrix(B, m, blockCol);
		// Shared memory used to store Asub and Bsub respectively
		__shared__ float As[BLOCK_SIZE][BLOCK_SIZE];
		__shared__ float Bs[BLOCK_SIZE][BLOCK_SIZE];
		// Load Asub and Bsub from device memory to shared memory
		// Each thread loads one element of each sub-matrix
		As[row][col] = GetElement(Asub, row, col);
		Bs[row][col] = GetElement(Bsub, row, col);
		// Synchronize to make sure the sub-matrices are loaded
		// before starting the computation
		__syncthreads();
	       // Multiply Asub and Bsub together
		for (int e = 0; e < BLOCK_SIZE; ++e)
		    Cvalue += As[row][e] * Bs[e][col];
		// Synchronize to make sure that the preceding
		// computation is done before loading two new
		// sub-matrices of A and B in the next iteration
		__syncthreads();
	    }
	    // Write Csub to device memory Each thread writes one element
	    SetElement(Csub, row, col, Cvalue);
}
