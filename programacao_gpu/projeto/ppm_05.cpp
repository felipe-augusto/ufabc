#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include "ppm.h"
#include <math.h>       /* fmin */

//Split "mem" into "parts", e.g. if mem = 10 and parts = 4 you will have: 0,2,4,6,10
//if possible the function will split mem into equal chuncks, if not 
//the last chunck will be slightly larger

std::vector<int> bounds(int parts, int mem) {
    std::vector<int>bnd;
    int delta = mem / parts;
    int reminder = mem % parts;
    int N1 = 0, N2 = 0;
    bnd.push_back(N1);
    for (int i = 0; i < parts; ++i) {
        N2 = N1 + delta;
        if (i == parts - 1)
            N2 += reminder;
        bnd.push_back(N2);
        N1 = N2;
    }
    return bnd;
}

//Test if a given position (ii,jj) is "inside" the limits 0..nr_lines and 0..nr_columns

bool border(int ii, int jj, int nr_lines, int nr_columns) {
    if (ii >= 0 && ii < nr_lines && jj >= 0 && jj < nr_columns)
        return true;
    else
        return false;
}

//Blur the pixel at (i,j) using information from the neighbour pixels

void process(ppm &image, ppm &image2, int i, int j) {
    int ii, jj, nr_lines, nr_columns, indx;
    unsigned int r, g, b;
    float r_sum, g_sum, b_sum;
    //Filter used for bluring an image
    float filter[] = {
        0.10179640718562874, 0.11377245508982035, 0.10179640718562874,
        0.11377245508982035, 0.1377245508982036, 0.11377245508982035,
        0.10179640718562874, 0.11377245508982035, 0.10179640718562874
    };

    nr_lines = image.height;
    nr_columns = image.width;

    //Apply the filter:
    r_sum = 0;
    g_sum = 0;
    b_sum = 0;

    //check North-West
    ii = i - 1;
    jj = j - 1;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[0];
        g_sum += g * filter[0];
        b_sum += b * filter[0];
    }

    //check North
    ii = i - 1;
    jj = j;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[1];
        g_sum += g * filter[1];
        b_sum += b * filter[1];
    }

    //check North-East
    ii = i - 1;
    jj = j + 1;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[2];
        g_sum += g * filter[2];
        b_sum += b * filter[2];
    }

    //check West
    ii = i;
    jj = j - 1;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[3];
        g_sum += g * filter[3];
        b_sum += b * filter[3];
    }

    //center
    ii = i;
    jj = j;
    indx = ii * image.width + jj;

    r = (unsigned int) image.r[indx];
    g = (unsigned int) image.g[indx];
    b = (unsigned int) image.b[indx];

    r_sum += r * filter[4];
    g_sum += g * filter[4];
    b_sum += b * filter[4];


    //check East
    ii = i;
    jj = j + 1;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[5];
        g_sum += g * filter[5];
        b_sum += b * filter[5];
    }
    //check South-West
    ii = i + 1;
    jj = j - 1;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[6];
        g_sum += g * filter[6];
        b_sum += b * filter[6];
    }
    //check South
    ii = i + 1;
    jj = j;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[7];
        g_sum += g * filter[7];
        b_sum += b * filter[7];
    }
    //check South-East
    ii = i + 1;
    jj = j + 1;
    if (border(ii, jj, nr_lines, nr_columns)) {
        indx = ii * image.width + jj;

        r = (unsigned int) image.r[indx];
        g = (unsigned int) image.g[indx];
        b = (unsigned int) image.b[indx];

        r_sum += r * filter[8];
        g_sum += g * filter[8];
        b_sum += b * filter[8];
    }

    //Save the modifed pixel value in image2 
    indx = i * image.width + j;
    image2.r[indx] = (unsigned char) r_sum;
    image2.g[indx] = (unsigned char) g_sum;
    image2.b[indx] = (unsigned char) b_sum;
}

//Blur a chunck of an image

void tst(ppm &image, ppm &image2, int left, int right) {
    for (int i = left; i < right; ++i) {
        int ii = i / image.width;
        int jj = i - ii * image.width;
        process(image, image2, ii, jj);
    }
}

// copia o conteudo de uma matriz para outro
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

// imprime um matriz
void print(int * mat, int M, int N){
  int i, j;

  for(i = 0; i < M; i++) {
    for(j = 0; j < N; j++) {
        printf("%d ", mat[i * M + j]);
    }
    printf("\n");
  }
}

int main() {
    std::string fname = std::string("test.ppm");

    ppm image(fname);
    ppm image2(image.width, image.height);
    ppm image3(image.width, image.height);

    int * image_array = (int *) malloc(sizeof(int) * image.height * image.width);

    //Number of threads to use (the image will be divided between threads)
    int parts = 4;

    std::vector<int>bnd = bounds(parts, image.size);
    int thre = 128;
    float black = 255;
    float white = 0;

    // convert imagem from rgb to binary
    for(int i = 0; i < image.width * image.height; i++) {
        if(0.2989 * (unsigned int) image.r[i] + 0.5870 * (unsigned int) image.g[i] + 0.1140 * (unsigned int) image.b[i] > thre) {
            image2.r[i] = (unsigned char) black;
            image2.g[i] = (unsigned char) black;
            image2.b[i] = (unsigned char) black;
            image_array[i] = black;
        } else {
            image2.r[i] = (unsigned char) white;
            image2.g[i] = (unsigned char) white;
            image2.b[i] = (unsigned char) white;
            image_array[i] = white;
        }
    }

    // print(image_array, image.width, image.height);

    // prepare to do td

    // aloca dinamica espaço para a matrix de saida
    int * out = (int *) malloc(sizeof(int) * image.height * image.width);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++) {
            out[i * image.width + j] = 0;
        }
    }

    // matrix com a soma
    int * mtest = (int *) malloc(sizeof(int) * image.height * image.width);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++) {
            out[i * image.width + j] = 0;
        }
    }

    int i, j, l, k;
    int flag = 1;
    soma(mtest, image_array, image.width, image.height);
    // TD - awkward way to do it (multiplas erosoes somando em uma nova matriz)
    while(flag) {
        flag = 0;
        // erosion
        for(i = 0; i < image.width; i++) {
            for(j = 0; j < image.height; j++) {
                float mini = image.width * image.height;
                for(l = -1; l < 2; l++) {
                    for(k = -1; k < 2; k++) {
                        // tratamento de bordas
                        if(i + l >= 0 && i + l < image.width && j + k >= 0 && j + k < image.height) {
                            mini = fmin(image_array[(i + l) * image.width + (j + k)], mini);
                        }
                    }
                }
                if(mini != image.width * image.height) {
                    out[i * image.width + j] = mini;
                }
                if (mini != 0) {
                    flag = 1;
                }

            }
        }
        copy(image_array, out, image.width, image.height);
        soma(mtest, image_array, image.width, image.height);
    }

    // find max level
    int max = 0;
    for(int i = 0; i < image.width * image.height; i++) {
            if(mtest[i] > max) {
                max = mtest[i];
            }; 
    }

    float normalized = 255.0 / max;
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            image3.r[i * image.width + j] = (unsigned char) (mtest[i * image.width + j] * normalized);
            image3.g[i * image.width + j] = (unsigned char) (mtest[i * image.width + j] * normalized);
            image3.b[i * image.width + j] = (unsigned char) (mtest[i * image.width + j] * normalized);
        }
            
    }

    
    // // apply distance transform on the image
    // for(int i = 0; i < image2.width * image2.height; i++) {
    //     int distancia_esq = 0;
    //     int distancia_dir = 0;
    //     // olha a esquerda
    //     for(int j = i; j >= 0; j--) {
    //         if((unsigned int) image2.r[i] == 0) {
    //             image3.r[j] = (unsigned char) distancia_esq;
    //             image3.g[j] = (unsigned char) distancia_esq;
    //             image3.b[j] = (unsigned char) distancia_esq;
    //             break;
    //         }
    //         distancia_esq++;
    //     }
    //     // olha a direita
    //     for(int j = i; j < image2.width * image2.height; j++) {
    //         if((unsigned int) image2.r[i] == 0) {
    //             if((unsigned int) image3.r[j] > distancia_dir) {
    //                 image3.r[j] = (unsigned char) distancia_dir;
    //                 image3.g[j] = (unsigned char) distancia_dir;
    //                 image3.b[j] = (unsigned char) distancia_dir;
    //             }
    //             break;
    //         }
    //         distancia_dir++;
    //     }
    // }

    image3.write("test3.ppm");

    // //std::vector<std::thread> tt(parts-1);
    // std::vector<std::thread> tt;

    // time_t start, end;
    // time(&start);
    // //Lauch parts-1 threads
    // for (int i = 0; i < parts - 1; ++i) {
    //     tt.push_back(std::thread(tst, std::ref(image), std::ref(image2), bnd[i], bnd[i + 1]));
    //     //tt[i] = std::thread(tst, std::ref(image), std::ref(image2), bnd[i], bnd[i + 1]);
    // }

    // //Use the main thread to do part of the work !!!
    // for (int i = parts - 1; i < parts; ++i) {
    //     tst(image, image2, bnd[i], bnd[i + 1]);
    // }

    // //Join parts-1 threads
    // for(auto &e : tt){
    //     e.join();
    // }
    // //for(int i = 0; i < parts - 1; ++i){
    // //    tt[i].join();
    // //}

    // time(&end);
    // std::cout << difftime(end, start) << " seconds" << std::endl;

    // //Save the result
    // image2.write("test.ppm");

    return 0;
}
