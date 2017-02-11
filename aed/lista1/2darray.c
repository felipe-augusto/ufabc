#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>


int main(){
    int arr[6][6];
    // worse case can be negative -> 7 * -9 = -63
    int hoursum = -64;
    for(int arr_i = 0; arr_i < 6; arr_i++){
       for(int arr_j = 0; arr_j < 6; arr_j++){ 
          scanf("%d",&arr[arr_i][arr_j]);
       }
    }
    // matrix is ready
    // since we know its 6x6 we can set limits
    for(int arr_i = 0; arr_i < 4; arr_i++){
      for(int arr_j = 0; arr_j < 4; arr_j++){
        int k, l;
        int hourTempSum = 0;
        for(k = 0; k < 3; k++) {
          for(l = 0; l < 3; l++) {
            if(k != 1 || (k == 1 && l == 1)) hourTempSum += arr[arr_i + k][arr_j + l];
          }
        }
        if(hourTempSum > hoursum) hoursum = hourTempSum;
      }
    }
    
    printf("%d", hoursum);
    
    return 0;
}
