#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int n;
    int rot;
    scanf("%d",&n);
    scanf("%d",&rot);
    int arr[n];
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%d",&arr[((n - rot) + arr_i) % n]);
    }
    
    for(int arr_i = 0; arr_i < n; arr_i++){
        if (arr_i == n - 1) printf("%d",arr[arr_i]);
        else printf("%d ",arr[arr_i]);
    }
   
    return 0;
}
