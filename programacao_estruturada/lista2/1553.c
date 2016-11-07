#include <stdio.h>
#include <stdlib.h>

int main() {
	while(1) {
		int n, k, i;
		scanf("%d %d", &n, &k);
		if (n == 0 && k== 0) {
			break;
		}
		int v[101] = {0};
		int question;

		for(i = 0; i < n; i++) {
			scanf("%d", &question);
			v[question] += 1;
		}
		int count = 0;

		for(i = 0; i < 101; i++) {
			if (v[i] >= k) {
				count++;
			}
		}

		printf("%d\n", count);
	}
	
	return 0;
}