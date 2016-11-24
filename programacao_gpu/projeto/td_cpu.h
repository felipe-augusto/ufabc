#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> bounds(int parts, int mem);
void soma(int * f, int * g, int M, int N);
void copy(int * f, int  * g, int M, int N);
int * td_core(int * in, int height, int width, int start, int end);
int * td_cpu(int * in, int height, int width, int start, int end);
int * td_cpu_parallel(int * in, int height, int width);
