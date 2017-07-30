#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// good to undestand -> http://www.geeksforgeeks.org/counting-inversions/

long int Intercala(int p, int q, int r, int v[]) {
    int i, j, k;
    int w[r-p+1];
    long int shifts = 0;
    
    i = p;
    j = q;
    k = 0;
    
    while (i<q && j<r) {
        if (v[i]<=v[j])
            w[k++] = v[i++];
        else {
          w[k++] = v[j++];
          shifts = shifts + (q - i);
        }
            
            
    }
    
    while(i<q)
        w[k++] = v[i++];
    
    while(j<r)
        w[k++] = v[j++];
        
    for (i=p; i<r; i++)
        v[i] = w[i-p];
       
    return shifts;
}

long int MergeSort (int p, int r, int v[]) {
  int q;
	long int shifts = 0;

    if (p<r-1) {
        q     = (p+r)/2;
        shifts = MergeSort(p, q, v);
        shifts += MergeSort(q, r, v);
        shifts += Intercala(p, q, r, v);
    }

	return shifts;
}

int main() {

    int i, t, n;
    scanf("%d", &t);
    for(i = 0; i < t; i++) {
        scanf("%d", &n);
        
        int v[n], e;
        for(e = 0; e < n; e++) {
            scanf("%d", &v[e]);
        }
        
        printf("%ld\n", MergeSort(0, n, v));
    }
    return 0;
}
