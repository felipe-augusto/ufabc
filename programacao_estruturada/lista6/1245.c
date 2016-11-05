#include <stdio.h>
#include <math.h>

int direitos[61] = {0};
int esquerdos[61] = {0};

int main() {
	int num_botas, i, num;
	char pe;
	while(scanf("%d", &num_botas) != EOF) {
		int total = 0;
		for(i = 0; i <  num_botas; i++) {
			scanf("%d ", &num);
			scanf("%c", &pe);
			if(pe == 'D') {
				direitos[num] += 1;
			} else if (pe == 'E') {
				esquerdos[num] += 1;
			}
		}

		for(i = 30; i <= 60; i++) {
			if("%d", esquerdos[i] != 0 && direitos[i] != 0) {
				total += fmin(esquerdos[i], direitos[i]);
			};
			esquerdos[i] = 0;
			direitos[i] = 0;
		}
		printf("%d\n", total);
	}
}