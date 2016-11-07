#include<stdio.h>
#define MAXHEIGHT 10100

int binarySearch(int o[], int value, int fim, int min) {
	int mid;
	int inicio = 0;
	int found =  -1;
	int tmp_value = 0;
	while (inicio < fim) {
		mid = (inicio + fim) / 2;
		if(o[mid] == value) {
			found = mid;
			tmp_value = value;
			// maior ou menor
			if (min) {
				fim = mid;
			} else {
				inicio = mid + 1;
			}
			
		} else if (o[mid] < value) {
			inicio = mid + 1;
		} else {
			fim = mid;
		}

		if(inicio >= fim && found != -1) {
			return found;
		}
	}

	return -1;
}

void test(int arr [], int m) {
	int i;
	for(i = 0; i < m; i++) {
		printf("%d, pos: %d\n" ,arr[i], i); 
    	}
}

int countingSort(int arr [], int order []) {
    int i, j;
    int k = 0;
    for(i = 0; i < MAXHEIGHT; i++) {
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
    int n, q, i, j, range_min, range_max, trial;
    int arr[MAXHEIGHT] = {0};
    int ordered[MAXHEIGHT] = {10100};
    int finish = 1;
    int count = 1;
    
    while(scanf("%d", &n) != EOF) {
	    
	    for(i = 0; i < n; i++) {
		scanf("%d %d", &range_min, &range_max);
		for(j = range_min; j <= range_max; j++) {
			arr[j] += 1;
		}
	    }

	    int k = countingSort(arr, ordered);
	    scanf("%d", &trial);
            int min = binarySearch(ordered, trial, k, 1);
	    int max = binarySearch(ordered, trial, k, 0);
	    if (min != -1 && max != -1) {
		printf("%d found from %d to %d\n", trial, min, max);
	    } else {
		printf("%d not found\n", trial);
            }
    }
    return 0;
}