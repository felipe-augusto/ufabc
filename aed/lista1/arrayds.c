#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

void inverso(int * p, int * ini) {
    printf("%d ", *p);
    if (p == ini) return;
    else inverso(p - 1, ini);
}

int main(){
    int n; 
    scanf("%d",&n);
    int *arr = malloc(sizeof(int) * n);
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%d",&arr[arr_i]);
    }
    inverso(arr + n - 1, arr);
    return 0;
}
