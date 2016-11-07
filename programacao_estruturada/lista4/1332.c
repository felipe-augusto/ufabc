#include<stdio.h>
#include<string.h>

int main() {
	int n = 0;
	int i, tamanho, j, c_a, c_tw, c_th;
	scanf("%d", &n);

	char one[3] = {"one"};
	char two[3] = {"two"};
	char three[5] = {"three"};

	char palavra[5];

	for(i = 0; i < n; i++){
		c_a = 0;
		c_tw = 0;
		c_th = 0;

		scanf("%s", palavra);
		tamanho = (int)strlen(palavra);

		for(j = 0; j < strlen(palavra); j++) {
			if(one[j] != palavra[j]) c_a++;
			if(two[j] != palavra[j]) c_tw++;
			if(three[j] != palavra[j]) c_th++;
		}

		if(c_a == 1 || c_a == 0) {
			printf("%d\n", 1);
		} else if (c_tw == 1 || c_tw == 0) {
			printf("%d\n", 2);
		} else {
			printf("%d\n", 3);
		}
	}

	return 0;
}