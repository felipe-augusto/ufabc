#include<stdio.h>
#include<string.h>
#include <math.h>

int main() {
	int n, i, tmp;
	scanf("%d", &n);


	for(i = 0; i < n; i++) { // 12 graos -> 1 grama
		scanf("%d", &tmp);
		printf("%llu kg\n", (unsigned long long int)(pow(2, tmp) / (12 * 1000)));	
	}

	return 0;
}