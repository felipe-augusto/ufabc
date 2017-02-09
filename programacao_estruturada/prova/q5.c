#include <stdio.h>
#include <stdlib.h>

int f (int i, int j){
	if(i <= 1 || j <= i) return 1;
	else return f(i-2, j) + f(i-1, j-1) + f(i, j - 2);
}

int main() {
	printf("%d\n", f(4,5));
}