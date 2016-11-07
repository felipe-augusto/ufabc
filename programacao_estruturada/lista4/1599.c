#include<stdio.h>
#include<string.h>

#define LENGTH 1000  // 1000 + bordas

int main() {
	int I, J, i, j, k, p, tmp, has;
	int init_i, init_j, final_i, final_j;
	int M[LENGTH][LENGTH];
	while(scanf("%d %d", &I, &J) != EOF) {	
		has = -1;
		for(i = 0; i < I; i++){
			for(j = 0; j < J; j++){
				scanf("%d", &M[i][j]);
			}
		}

		for(i = 0; i < I; i++){
			for(j = 0; j < J; j++){
				tmp = 1;
				// quando esta nas bordas
				init_i = -1; init_j = -1;
				final_i = 2; final_j = 2;
				if(i == 0) init_i = 0;
				if(j == 0) init_j = 0;	
				if(i + 1 == I) final_i = 1;
				if(j + 1 == J) final_j = 1;			
				for(k = init_i; k < final_i; k++) {
					for(p = init_j; p < final_j; p++) {
						if(k == 0 && p == 0) {
							continue;
						}
						//printf("%d", M[i][j] <= M[i + k][j + p]);
						if (M[i][j] <= M[i + k][j + p]) {
							tmp = 0;
						}
					}
				}
				if (tmp) {
					has = 1;
					printf("%d %d\n", i + 1, j + 1);
				}
			}
		}

		if(has == -1) {
			printf("%d\n", -1);
		}

		printf("\n");
	}

	return 0;
}