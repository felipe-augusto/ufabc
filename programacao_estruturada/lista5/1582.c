#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int mdc(int menor, int maior) {
    int copia;
    while(menor!=0) {
        copia = menor;
        menor = maior%menor;
        maior = copia;
    }
    return maior;
}
 
int mmc(int menor, int maior){
    return maior/mdc(menor,maior)*menor;
}

int main() {
	int x, y, z;
	while(scanf("%d %d %d", &x, &y, &z) != EOF) {
		// primeiro precisa por em ordem
		int a, b, c;

		a = fmin(fmin(x, y), z);
		c = fmax(fmax(x, y), z);
		b = x + y + z - a - c; // clever -> http://stackoverflow.com/questions/4367745/simpler-way-of-sorting-three-numbers

		// verifica se eh pitagoras
		if ((int) pow(a,2) + (int) pow(b,2) != (int) pow(c,2)) {
			printf("tripla\n");
		} else {
			if (mdc(a, b) != 1 || mdc(a, c) != 1 || mdc(b, c) != 1) {
				printf("tripla pitagorica\n");
			} else {
				printf("tripla pitagorica primitiva\n");
			}
		}
	}
}