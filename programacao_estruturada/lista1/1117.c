#include <stdio.h>
#include <math.h>

int main () {
	float sum = 0;
	int controle = 0;
	while (controle < 2) {
		float le;
		scanf("%f", &le);
		if(le < 0.0 || le > 10.0){
			printf("%s\n", "nota invalida");
		} else {
			sum += le;
			controle++;
			if (controle == 2) {
				printf("media = %.2f\n", sum / 2);
			}

		}
	}

	return 0;
}