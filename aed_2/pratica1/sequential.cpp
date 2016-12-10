#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <ctime>
#include <iostream>
#include <math.h>
using namespace std;

const int LENGTH = 100000000;
int v [LENGTH];

bool buscaSequencial (int key, int arr []) {
        int i;
	for (i = 0; i < LENGTH; i++) {
		if(arr[i] == key) {
			return true;
			break;
		}
	}
	return false;
}

bool buscaBinaria(int key, int arr[]) {
	int inf, half;
	long sup;
	inf = -1;
	sup = LENGTH;
	while (inf < (sup - 1)) {
		half = floor((inf + sup) / 2);
		if (key <= arr[half]) {
			sup = half;
		} else {
			inf = half;
		}
	}
	if (key == arr[sup]) {
		return true;
	} else {
		return false;
	}

}

void populate(int v[]) {
	for(int i = 0; i < LENGTH; i++) {
		v[i] = i;
	}
}

main(){
	// instacia o vetor e o popula
	populate(v);

	// verifica os casos: comeco, meio, fim, nao existe no vetor
	int positions [4]  = {v[0], v[LENGTH/2], v[LENGTH - 1], LENGTH + 1};

	for(int i = 0; i < 4; i++) {
		// time for buscaBinaria
		clock_t t1 = clock();
		bool respBin = buscaBinaria(positions[i], v);
		t1 = clock() - t1;
		float tempo1 = ((float)t1)/CLOCKS_PER_SEC;
	
		// time for buscaSequencial
		clock_t t2 = clock();
		bool respSeq = buscaSequencial(positions[i], v);
		t2 = clock() - t2;
		float tempo2 = ((float)t2)/CLOCKS_PER_SEC;
		cout << positions[i] << " | " << tempo1 << " | " << respBin << " | " << tempo2 <<  " | " << respSeq << endl;
	}

;
}
