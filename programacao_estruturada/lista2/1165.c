#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, primo, k, i;

	scanf("%d", &n);

	for(i = 0; i < n; i++) {
		scanf("%d", &primo);
		k = 2;
		if(primo == 1) {
			printf("%d eh primo\n", primo);
			continue;
		}

		while(k <= primo) {
			

			if (primo % k == 0 && k != primo) {
				printf("%d nao eh primo\n", primo);
			   	break;
			}
			if(k == primo) {
				printf("%d eh primo\n", primo);
			}
			k++;
		}
	}

	return 0;
}