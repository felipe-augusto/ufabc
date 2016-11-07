#include <stdio.h>
#include <stdlib.h>

int mdc(int menor, int maior);
int mmc(int menor, int maior);
 
int mdc(int menor, int maior) {
    int copia;
    while(menor!=0) {
        copia = menor;
        menor = maior%menor;
        maior = copia;
    }
    return maior;
}
 
int mmc(int menor, int maior){
    return maior/mdc(menor,maior)*menor;
}

int main() {
	int buracos, i, tmp, begin;
	int arr[101];
	int count = 0;
	int result = 1;
	scanf("%d", &buracos);

	for (i = 0; i < buracos; i++) {
		scanf("%d", &tmp);
		arr[i] = tmp;
	}

	for (i = 0; i < buracos; i++) {
		count = 1;
		begin = arr[i] - 1;
		while(begin != i) {
			count++;
			begin = arr[begin] - 1;
		}
		result = mmc(result, count);
	}

	printf("%d\n", result);

	return 0;
}