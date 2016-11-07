#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, tmp, x, y, i, j;
	
	scanf("%d", &n);
	int v[201][201] = {0};
	int species[1001] = {0};
	int count = 0;
	int tmp_species;

	for(i = 1; i <= n; i++) {
		for(j = 1; j <=  n; j++) {
			scanf("%d", &tmp);
			v[i][j] = tmp;
		}
	}

	for(i = 0; i < (2 * n); i++) {
		scanf("%d %d", &x, &y);
		tmp_species = v[x][y];
		species[tmp_species] = 1;
	}

	for(i = 0; i < 1001; i++) {
		if(species[i] == 1) {
			count++;
		}
	}

	printf("%d\n", count);

	return 0;
}