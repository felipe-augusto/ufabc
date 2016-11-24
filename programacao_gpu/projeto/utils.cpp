#include <vector>
#include <iostream>
#include <string>
#include "ppm.h"


// converts ppm image from rgb to binary
ppm rgb2binary (ppm image, int * image_array, int thre) {

	for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            int r = (unsigned int) image.r[i * image.width + j];
        }    
    }

	return image;
}

int find_max (ppm image, int * mtest) {
    int max = 0;
    for(int i = 0; i < image.width * image.height; i++) {
            if(mtest[i] > max) {
                max = mtest[i];
            }; 
    }
    return max;	
}

// normalize max level to interval 0 to 255
ppm normalize(ppm image, int max, int * mtest) {
    float normalized = 255.0 / find_max(image, mtest);
    for(int i = 0; i < image.width; i++) {
        for(int j = 0; j < image.height; j++) {
            image.r[i * image.width + j] = (unsigned char) (mtest[i * image.width + j] * normalized);
            image.g[i * image.width + j] = (unsigned char) (mtest[i * image.width + j] * normalized);
            image.b[i * image.width + j] = (unsigned char) (mtest[i * image.width + j] * normalized);
        }    
    }
    return image;
}