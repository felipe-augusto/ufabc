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

int main() {
    // MEDIR O TEMPO
    struct timeval inicio, final;
    int tmili;
    std::string fname = std::string("test.ppm");

    ppm image(fname);
    ppm image_cpu(image.width, image.height);
    ppm image_cpu_parallel(image.width, image.height);
    ppm image_gpu(image.width, image.height);

    // image ppm will be here
    int * image_array = (int *) malloc(sizeof(int) * image.height * image.width);

    // convert image from rgb to binary an put it into an input array
    int thre = 128;
    for(int i = 0; i < image.width * image.height; i++) {
        if(0.2989 * (unsigned int) image.r[i] + 0.5870 * (unsigned int) image.g[i] + 0.1140 * (unsigned int) image.b[i] > thre) {
            image_array[i] = 1;
        } else {
            image_array[i] = 0;
        }
    }

    // matrix de resposta que ira compor a imagem
    int * mtest = (int *) malloc(sizeof(int) * image.height * image.width);
    for(int i = 0; i < image.width; i++){
        for(int j = 0; j < image.height; j++) {
            mtest[i * image.width + j] = 0;
        }
    }

    // .clock() parace nao ser razoavel -> http://stackoverflow.com/questions/5068697/pthreads-multicore-cpu-on-linux

    // IMPLEMENTAÇAO DA TD EM CPU
    gettimeofday(&inicio, NULL);
    mtest = td_cpu(image_array, image.height, image.width, 0, image.height);
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo CPU: %dms\n", tmili);

    // find max level and normalize to fit RGB 255 limit
    image_cpu = normalize(image_cpu, find_max(image, mtest), mtest);
    image_cpu.write("td_cpu.ppm");

    // IMPLEMENTAÇAO DA TD EM CPU PARALELO
    gettimeofday(&inicio, NULL);
    mtest = td_cpu_parallel(image_array, image.height, image.width); //, 0, image.height
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo CPU (Paralelo): %dms\n", tmili);

    image_cpu_parallel = normalize(image_cpu_parallel, find_max(image, mtest), mtest);
    image_cpu_parallel.write("td_cpu_parallel.ppm");

    // IMPLEMENTAÇAO DA TD EM GPU GLOBAL
    gettimeofday(&inicio, NULL);
    mtest = td_gpu(image_array);
    gettimeofday(&final, NULL);
    tmili = (int) (1000 * (final.tv_sec - inicio.tv_sec) + (final.tv_usec - inicio.tv_usec) / 1000);
    printf("Tempo GPU: %dms\n", tmili);

    image_gpu = normalize(image_gpu, find_max(image, mtest), mtest);
    image_gpu.write("td_gpu.ppm");

    return 0;
}
