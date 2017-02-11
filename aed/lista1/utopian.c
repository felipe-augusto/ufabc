#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int t;
    scanf("%d",&t);
    for(int a0 = 0; a0 < t; a0++){
        int n, period; 
        scanf("%d",&n);
        long int height = 1;
        for(period = 0; period < n; period++) {
          !(period % 2) ? height *= 2 : height++;
        }
        printf("%ld\n", height);
   
    }
    return 0;
}
