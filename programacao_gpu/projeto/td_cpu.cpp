#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> bounds(int process, int height) {
    std::vector<int>bnd;
    int size = 0;
    int increment = height / process;
    for(int i = 0; i < process + 1; i++) {
    	if(size < height) {
    		bnd.push_back(size);
    		size += increment;
    	} else {
    		bnd.push_back(height);
    	}
    	
    }
    return bnd;
}

// acumula o valor da segunda matrix na primeira
void soma(int * f, int * g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
    for(j = 0; j < N; j++) {
        f[i * M + j] = f[i * M + j] + g[i * M + j];
    }
  }
}

// copia o conteudo de uma matriz para outro
void copy(int * f, int  * g, int M, int N) {
  int i, j;
  for(i = 0; i < M; i++) {
    for(j = 0; j < N; j++) {
        f[i * M + j] = g[i * M + j];
    }
  }
}

int * td_core(int * in, int height, int width, int start, int end) {

}

int * td_cpu(int * in_, int height, int width, int start, int end) {
    float time_;
    clock_t t;
	int i, j, l, k;

    // faz uma copia local para nao modificar o in_
    int * in = (int *) malloc(sizeof(int) * height * width);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++) {
            in[i * width + j] = in_[i * width + j];
        }
    }

	// matrix temporaria para auxiliar nas operaçoes
    int * out = (int *) malloc(sizeof(int) * height * width);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++) {
            out[i * width + j] = 0;
        }
    }

    // matrix final que sera retornada
    int * mtest = (int *) malloc(sizeof(int) * height * width);
    for(int i = 0; i < width; i++){
        for(int j = 0; j < height; j++) {
            out[i * width + j] = 0;
        }
    }
    time_ = 0;
    t = clock();
	int flag = 1;
	soma(mtest, in, width, height);
	// TD - awkward way to do it (multiplas erosoes somando em uma nova matriz)
    while(flag) {
        flag = 0;
        // erosion
        for(i = start; i < end; i++) {
            for(j = 0; j < height; j++) {
                float mini = width * height;
                for(l = -1; l < 2; l++) {
                    for(k = -1; k < 2; k++) {
                        // tratamento de bordas
                        if(i + l >= 0 && i + l < width && j + k >= 0 && j + k < height) {
                            mini = fmin(in[(i + l) * width + (j + k)], mini);
                        }
                    }
                }
                if(mini != width * height) {
                    out[i * width + j] = mini;
                }
                if (mini != 0) {
                    flag = 1;
                }

            }
        }
        copy(in, out, width, height);
        soma(mtest, in, width, height);
    }
    time_ = (float)(clock() - t);
    time_ = time_ / CLOCKS_PER_SEC;
    printf("Tempo CPU (apenas TD): %5.1fms\n", time_ * 1000);
	return(mtest);
}

int * td_cpu_parallel(int * in, int height, int width) {
	// divide o height para quatro threads
	std::vector<int>bnd = bounds(4, height);
	//td_cpu(in, image.height, image.width, bnd[0], image.height);
	for(int i = 0; i < 4 + 1; i ++) {
		printf("%d ", bnd[i]);
	}
}