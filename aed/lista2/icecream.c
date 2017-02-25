#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// quick way to solve this is using hash tables -> O(n)
// refer to this: http://stackoverflow.com/questions/4720271/find-a-pair-of-elements-from-an-array-whose-sum-equals-a-given-number

int main() {
    int trips, i;
    scanf("%d", &trips);
    for(i = 0; i < trips; i++) {
      int money, flavorsNumber, prices, j;
      scanf("%d", &money);
      scanf("%d", &flavorsNumber);
      int flavorsPrices[flavorsNumber];
      for(j = 0; j < flavorsNumber; j++) {
        scanf("%d", &flavorsPrices[j]);
      }
      // search
      int k = 0;
      int found = 0;
      while(k < flavorsNumber && !found) {
        for(j = k + 1; j < flavorsNumber; j++) {
          if(flavorsPrices[k] + flavorsPrices[j] == money) {
            printf("%d %d", k + 1, j + 1);
            found = 1;
          };
        }
        k++;
      }
      printf("\n");
    }
    return 0;
}