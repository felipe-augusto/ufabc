#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <ctime>
#include "ppm.h"
#include "td_cpu.h"
#include "td_gpu.h"
#include "utils.h"
#include <sys/time.h>
#include <math.h>       /* fmin */

int main() {
    // variables to measure time
    struct timeval inicio, final;
    int tmili;
    // input variables
    std::string fname = std::string("2048.ppm");
    ppm image(fname);

    // output image variables
    ppm image_cpu(image.width, image.height);
    ppm image_cpu_parallel(image.width, image.height);
    ppm image_gpu(image.width, image.height);

    // ppm image will be represented by this array
    int * image_array = (int *) malloc(sizeof(int) * image.height * image.width);

    // convert image from rgb to binary an put it into image_array
    int thre = 128;
    for(int i = 0; i < image.width * image.height; i++) {
        if(0.2989 * (unsigned int) image.r[i] + 0.5870 * (unsigned int) image.g[i] + 0.1140 * (unsigned int) image.b[i] > thre) {
            image_array[i] = 1;
        } else {
            image_array[i] = 0;
        }
    }

    // output matrix
    int * mtest = (int *) malloc(sizeof(int) * image.height * image.width);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++) {
            mtest[i * image.width + j] = 0;
        }
    }

    // .clock() does not seems reasonable -> http://stackoverflow.com/questions/5068697/pthreads-multicore-cpu-on-linux

    // TD CPU
    gettimeofday(&inicio, NULL);
    // call cpu TD method
    mtest = td_cpu(image_array, image.height, image.width, 0, image.height);
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo CPU: %dms\n", tmili);

    // find max level and normalize to fit RGB 255 limit
    image_cpu = normalize(image_cpu, find_max(image, mtest), mtest);
    // write to ppm file
    image_cpu.write("2048_td_cpu.ppm");
    // fill output with 0s to be sure that each rotine works separatelly
    zero(mtest, image.width, image.height);

    // TD CPU PARALLEL
    gettimeofday(&inicio, NULL);
    mtest = td_cpu_parallel(image_array, image.height, image.width); //, 0, image.height
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo CPU (Paralelo - 4 cores): %dms\n", tmili);

    image_cpu_parallel = normalize(image_cpu_parallel, find_max(image, mtest), mtest);
    image_cpu_parallel.write("2048_td_cpu_parallel.ppm");
    zero(mtest, image.width, image.height);

    int it = 15;
    // TD GPU GLOBAL MEMORY
    td_gpu(image_array, 0);
    gettimeofday(&inicio, NULL);
    for(int i = 0; i < it; i++) {
        mtest = td_gpu(image_array, 0);
    }
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo GPU Mem. Global: %dms\n", tmili / it);

    image_gpu = normalize(image_gpu, find_max(image, mtest), mtest);
    image_gpu.write("2048_td_gpu_global.ppm");
    zero(mtest, image.width, image.height);

    // TD GPU SHARED MEMORY
    td_gpu(image_array, 1);
    gettimeofday(&inicio, NULL);
    for(int i = 0; i < it; i++) {
        mtest = td_gpu(image_array, 1);
    };
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo GPU Mem. Compartilhada: %dms\n", tmili / it);

    image_gpu = normalize(image_gpu, find_max(image, mtest), mtest);
    image_gpu.write("2048_td_gpu_compartilhada.ppm");
    zero(mtest, image.width, image.height);

    return 0;
}
