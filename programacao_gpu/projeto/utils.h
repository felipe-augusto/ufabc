#include <vector>
#include <iostream>
#include <string>

ppm rgb2binary (ppm image, int * image_array, int thre);
int find_max (ppm image, int * mtest);
ppm normalize(ppm image, int max, int * mtest);