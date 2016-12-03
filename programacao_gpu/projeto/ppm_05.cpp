#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include "ppm.h"
#include "td_cpu.h"
#include "utils.h"
#include <sys/time.h>
#include "td_gpu.h"
#include <math.h>       /* fmin */

//Split "mem" into "parts", e.g. if mem = 10 and parts = 4 you will have: 0,2,4,6,10
//if possible the function will split mem into equal chuncks, if not 
//the last chunck will be slightly larger

// std::vector<int> bounds(int parts, int mem) {
//     std::vector<int>bnd;
//     int delta = mem / parts;
//     int reminder = mem % parts;
//     int N1 = 0, N2 = 0;
//     bnd.push_back(N1);
//     for (int i = 0; i < parts; ++i) {
//         N2 = N1 + delta;
//         if (i == parts - 1)
//             N2 += reminder;
//         bnd.push_back(N2);
//         N1 = N2;
//     }
//     return bnd;
// }

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

int main() {
    // MEDIR O TEMPO
    struct timeval inicio, final;
    int tmili;
    std::string fname = std::string("test.ppm");

    ppm image(fname);
    ppm image_cpu(image.width, image.height);
    ppm image_cpu_parallel(image.width, image.height);
    ppm image_gpu(image.width, image.height);

    int * image_array = (int *) malloc(sizeof(int) * image.height * image.width);

    //Number of threads to use (the image will be divided between threads)
    int parts = 4;

    //std::vector<int>bnd = bounds(parts, image.size);


    // convert image from rgb to binary an put it into an input array
    int thre = 128;
    for(int i = 0; i < image.width * image.height; i++) {
        if(0.2989 * (unsigned int) image.r[i] + 0.5870 * (unsigned int) image.g[i] + 0.1140 * (unsigned int) image.b[i] > thre) {
            image_array[i] = 1;
        } else {
            image_array[i] = 0;
        }
    }


    // matrix de resposta que ira compor a image
    int * mtest = (int *) malloc(sizeof(int) * image.height * image.width);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++) {
            mtest[i * image.width + j] = 0;
        }
    }

    // .clock() parace nao ser razoavel
    // http://stackoverflow.com/questions/5068697/pthreads-multicore-cpu-on-linux

    // IMPLEMENTAÇAO DE FATO DA TD EM CPU
    gettimeofday(&inicio, NULL);
    mtest = td_cpu(image_array, image.height, image.width, 0, image.height); //, 
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo CPU: %dms\n", tmili);
    //td_cpu_parallel(image_array, image.height, image.width);

    // find max level and normaliza to fit RGB 255 limit
    image_cpu = normalize(image_cpu, find_max(image, mtest), mtest);

    // save td
    image_cpu.write("td_cpu.ppm");

    // IMPLEMENTAÇAO DE FATO DA TD EM CPU PARALLEL
    gettimeofday(&inicio, NULL);
    mtest = td_cpu_parallel(image_array, image.height, image.width); //, 0, image.height
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo CPU (Paralelo): %dms\n", tmili);
    //td_cpu_parallel(image_array, image.height, image.width);

    // find max level and normaliza to fit RGB 255 limit
    image_cpu_parallel = normalize(image_cpu_parallel, find_max(image, mtest), mtest);

    // save td
    image_cpu_parallel.write("td_cpu_parallel.ppm");

    //IMPLEMENTAÇAO DE FATO DA TD EM GPU GLOBAL
    
    gettimeofday(&inicio, NULL);
    mtest = td_gpu(image_array);
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo GPU: %dms\n", tmili);

    // find max level and normaliza to fit RGB 255 limit
    image_gpu = normalize(image_gpu, find_max(image, mtest), mtest);

    image_gpu.write("td_gpu.ppm");

    mtest = td_cpu_parallel(image_array, image.height, image.width);

    return 0;
}
