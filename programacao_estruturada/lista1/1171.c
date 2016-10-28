#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, i, read;
	scanf("%d", &n);
	int v[2001] = {0};
	for(i = 0; i < n; i++){
		scanf("%d", &read);
		v[read] += 1;
	}

	for(i = 0; i < 2001; i ++) {
		if(v[i] != 0) {
			printf("%d aparece %d vez(es)\n", i, v[i]);
		}
	}
	

	return 0;
}