#include<stdio.h>
#define MAXHEIGHT 231

void countingSort(int arr [], int max) {
    int i, j;
    for(i = 0; i < MAXHEIGHT; i++) {
        for(j = 0; j < arr[i]; j++) {
            if(i == max && j == arr[i] - 1) {
                printf("%d", i);
            } else {
                printf("%d ", i);
            }
        }
	arr[i] = 0;
    }
    printf("\n");
}

int main() {
    int n, i, tmp, j, max, people;
    max = 0;
    int arr[MAXHEIGHT] = {0};
    
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        scanf("%d", &people);
        for (j = 0; j < people; j++) {
            scanf("%d", &tmp);
            arr[tmp] += 1;
            if(tmp >= max) {
                max = tmp;
            }
        }
        countingSort(arr, max);
        
    }
    
    

    return 0;
}