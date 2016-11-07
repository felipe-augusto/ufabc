#include<stdio.h>
#include<string.h>
#include <math.h>

int mdc(int menor, int maior) {
	int tmp;
	while(menor != 0) {
		tmp = menor;
		menor = maior % menor;
		maior = tmp;
	}
	return maior;
}

int main() {
	int n, i, n1, n2;
	scanf("%d", &n);


	for(i = 0; i < n; i++) {
		scanf("%d %d", &n1, &n2);
		if(n1 > n2) {
			printf("%d\n", mdc(n2, n1));
		} else {
			printf("%d\n", mdc(n1, n2));
		}
	}

	return 0;
}