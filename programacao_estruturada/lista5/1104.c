#include <stdio.h>
#include <stdlib.h>

int array_alice[1001];
int array_beatriz[1001];

int buscaBinariaRec(int array [], int value, int start, int end) {
	int middle = (start + end) / 2;
	if (end < start){
		 return -1;
	}
	if(array[middle] == value) {
		return value;
	} else if(array[middle] < value) {
		buscaBinariaRec(array, value, middle + 1, end);
	} else {
		buscaBinariaRec(array, value, start, middle - 1);
	}
}

int main() {
	int num_alice, num_beatriz, i;

	scanf("%d %d", &num_alice, &num_beatriz);
	while(num_alice != 0 && num_beatriz != 0) {
		int dif_alice = 0;
		int dif_beatriz = 0;
		// para encontrar duplicados
		int decre_alice = 0;
		int decre_beatriz = 0;
		// preenche as arrays
		for(i = 0; i < num_alice; i++) {
			scanf("%d", &array_alice[i - decre_alice]);
			if(array_alice[i] == array_alice[i -1]) decre_alice++;
		}
		for(i = 0; i < num_beatriz; i++) {
			scanf("%d", &array_beatriz[i]);
			if(array_beatriz[i] == array_beatriz[i -1]) decre_beatriz++;
			int exists = buscaBinariaRec(array_alice, array_beatriz[i], 0, num_alice - 1 - decre_alice);
			if (exists == -1) dif_beatriz++;
		}
		for(i = 0; i < num_alice; i++) {
			int exists = buscaBinariaRec(array_beatriz, array_alice[i], 0, num_beatriz - 1 - decre_beatriz);
			if (exists == -1) dif_alice++;
		}
		printf("%d %d\n", dif_alice, dif_beatriz);
		scanf("%d %d", &num_alice, &num_beatriz);
	}
}
