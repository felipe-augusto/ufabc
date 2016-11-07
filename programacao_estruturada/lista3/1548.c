#include<stdio.h>
#include<string.h>

#define MAXHEIGHT 1001

int countingSort(int arr [], int order []) {
    int i, j;
    int k = 0;
    for(i = MAXHEIGHT-1; i >= 0; i--) {
		if(arr[i] != 0) {
			for(j = 0; j < arr[i]; j++) {	
				order[k] = i;
				k++;
		}
	} 
	arr[i] = 0;
    }
    return k;
}

int main() {
	int buracos, i, alunos, j, tmp, k;
	int arr[MAXHEIGHT] = {0};
	int ordered[MAXHEIGHT] = {-1};
	int unordered[MAXHEIGHT] = {0};
	int count;

	scanf("%d", &buracos);

	for(i = 0; i < buracos; i++) {
		scanf("%d", &alunos);
		for(j = 0; j < alunos; j++) {
			scanf("%d", &tmp);
			arr[tmp] += 1;
			unordered[j] = tmp;
		}

		countingSort(arr, ordered);
		count = 0;

		for(k = 0; k < alunos; k++) {
			if(ordered[k] == unordered[k]) {
				count++;
			}
		}

		printf("%d\n", count);

	}

	return 0;
}