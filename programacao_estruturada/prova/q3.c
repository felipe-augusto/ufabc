#include <stdio.h>
#include <stdlib.h>

// coloquei grande deste tamanho porque se tiver muitos número primo
// vai subir muito e teria perigo de estourar
unsigned long long int mdc(long int menor, long int maior);
unsigned long long int mmc(long int menor, long int maior);
 
unsigned long long int mdc(long int menor, long int maior) {
    unsigned long long int tmp;
    while(menor!=0) {
        tmp = menor;
        menor = maior % menor;
        maior = tmp;
    }
    return maior;
}

unsigned long long int mmc(long int menor, long int maior){
    return maior/mdc(menor,maior)*menor;
}


int main() {
	int i, num_cucos, tmp;
	long int tempo = 1;
	scanf("%d", &num_cucos);

	for(i = 0; i < num_cucos; i++) {
		long int test;
		scanf("%d", &tmp);
		if(tmp < tempo) {
			test = mmc(tmp, tempo);
			if (test > tempo) tempo = test;
		} else {
			test = mmc(tempo, tmp);
			if (test > tempo) tempo = test;
		}
	}

	printf("%ld\n", tempo);
}