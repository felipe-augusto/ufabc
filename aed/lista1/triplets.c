#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

int main(){
    int alice = 0;
    int bob = 0;
    int a0; 
    int a1; 
    int a2; 
    scanf("%d %d %d",&a0,&a1,&a2);
    int b0; 
    int b1; 
    int b2; 
    scanf("%d %d %d",&b0,&b1,&b2);

    if (a0 > b0) {
        alice++;
    }
    if (a0 < b0) {
        bob++;
    }
    if (a1 > b1) {
        alice++;
    }
    if (a1 < b1) {
        bob++;
    }
    if (a2 > b2) {
        alice++;
    }
    if (a2 < b2) {
        bob++;
    }
    printf("%d %d", alice, bob);
    return 0;
}
