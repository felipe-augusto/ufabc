#include <stdio.h>
#include <stdlib.h>

int main() {
	int n, i;
	scanf( "%d", &n);

	for(i = 0; i < n; i++) {
		long long a, b;
		scanf("%lli %lli", &a, &b);
		while(b) {
			if (b % 10 == a % 10) {
				b /= 10;
				a /= 10;				
			} else {
				printf("%s\n", "nao encaixa");
				break;
			}
		}
		if(b == 0) {
			printf("%s\n", "encaixa");
		} 
	}
	
	return 0;
}