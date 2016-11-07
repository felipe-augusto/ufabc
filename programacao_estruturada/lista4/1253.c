#include<stdio.h>
#include<string.h>
#include<math.h>

int main() {
	int tests, positions, i, tamanho, j, value, low, high;
	char string[50];
	scanf("%d", &tests);

	for(i = 0 ; i < tests; i++) {
		scanf("%s", string);
		scanf("%d", &positions);
		tamanho = strlen(string);
		for(j = 0; j < tamanho; j++) {
			if (string[j] - positions < 65) {
				printf("%c", string[j] - positions + 26);
			} else {
				printf("%c", string[j] - positions);
			}
			
		}
		printf("\n");
	};


	return 0;
}