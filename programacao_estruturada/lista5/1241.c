#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char numero[1000];
char compare[1000];

int main() {
	int casos, i, j, k, status;
	scanf("%d", &casos);
	for (i = 0; i < casos; ++i){
			status = 1;
			scanf("%s", numero);
			scanf("%s", compare);
			// sub maior que original
			if(strlen(numero) < strlen(compare)) {
				status = 0;
			}
			k = strlen(numero) - 1;
			for(j = strlen(compare) - 1; j >= 0; j--){
				if (numero[k] != compare[j]) {
					status = 0;
					break;
				}
				k--;
			}
			if(status) {
				printf("encaixa\n");
			} else {
				printf("nao encaixa\n");
			}
	}
	return 0;
}