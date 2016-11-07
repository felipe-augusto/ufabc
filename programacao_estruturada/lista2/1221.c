#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 2147483648

void erastofenes(unsigned long int tmp) {
	unsigned long int i, j;
	int primo = 1;
	for(i = 2; i < (unsigned long int)sqrt(tmp) + 1; i++) {
		for(j = 1; j * i <= (unsigned long int)sqrt(tmp) + 1; j++) {
			if(tmp % (i * j) == 0) {
				primo = 0;
				break;
			};
		}
		if (primo == 0) break;
	}
	if (primo == 1) {
		printf("%s\n", "Prime");	
	} else {
		printf("%s\n", "Not Prime");
	}
}

int main() {
	
	int n, i;
	unsigned long int tmp;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%lu", &tmp);
		// nao consegui guardar na memoria, 2^31 estourava
		erastofenes(tmp);
	}

	return 0;
}