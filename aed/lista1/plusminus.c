#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int n;
    int positive = 0;
    int negative = 0;
    int zero = 0;
    scanf("%d",&n);
    int arr[n];
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%d",&arr[arr_i]);
       if(arr[arr_i] > 0) positive++;
       if(arr[arr_i] == 0) zero++;
       if(arr[arr_i] < 0) negative++;
    }
    printf("%f\n%f\n%f\n", (double)positive/n, (double)negative/n, (double)zero/n);
    return 0;
}
