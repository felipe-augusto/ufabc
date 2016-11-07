#include<stdio.h>
#define MAXHEIGHT 10001

void binarySearch(int o[], int value, int fim) {
	int mid;
	int inicio = 0;
	int found = 0;
	int tmp_value = 0;
	while (inicio < fim) {
		mid = (inicio + fim) / 2;
		if(o[mid] == value) {
			found = mid + 1;
			tmp_value = value;
			fim = mid;
		} else if (o[mid] < value) {
			inicio = mid + 1;
		} else {
			fim = mid;
		}

		if (inicio >= fim && !found) {
			printf("%d not found\n", value);
		} else if(inicio >= fim && found) {
			printf("%d found at %d\n", tmp_value, found);
		}
	}
}

void test(int arr [], int m) {
	printf("esse eh o maximo = %d", m);
	int i;
	for(i = 0; i < m; i++) {
		printf("%d, \n" ,arr[i]); 
    	}
}

int countingSort(int arr [], int order []) {
    int i, j;
    int k = 0;
    for(i = 0; i < MAXHEIGHT; i++) {
	if(arr[i] != 0) {
		for(j = 0; j < arr[i]; j++) {	
			order[k] = i;
			// printf("%d , k = %d | \n", order[k], k);
			k++;
		}
	} 
	arr[i] = 0;
	
	
    }
    return k;
}

int main() {
    int n, q, i, tmp, j, marbles_tmp;
    int arr[MAXHEIGHT] = {0};
    int ordered[MAXHEIGHT] = {10001};
    int finish = 1;
    int count = 1;
    
    while(finish) {
	    scanf("%d %d", &n, &q);
	    if(n == 0 && q == 0) {
		finish = 0;
		continue;
	    }

	    for(i = 0; i < n; i++) {
		scanf("%d", &marbles_tmp);
		arr[marbles_tmp] += 1;
	    }

	    int k = countingSort(arr, ordered);
	    printf("CASE# %d:\n", count);	

	    for(i = 0; i < q; i++) {
		scanf("%d", &marbles_tmp);
		//test(ordered, k);
		binarySearch(ordered, marbles_tmp, k);
	    }

	    count++;
	   
	    


    }
    return 0;
}