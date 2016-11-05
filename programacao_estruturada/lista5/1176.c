#include <stdio.h>
 
unsigned long long int fibos[61] = {0};
 
unsigned long long int fib(n) {
	if(fibos[n] != 0) {
		return fibos[n];
	}
	if(n == 0) return 0;
	if(n == 1) {
		fibos[n] = 1;
		return 1;
	}
	fibos[n] = fib(n - 1) + fib(n - 2);
	return fibos[n];
}
 
int main(void) {
	int i, casos, tmp;
	scanf("%d", &casos);
	// calcula all fibonaccis
	fib(60);
	for(i = 0; i < casos; i++) {
		scanf("%d", &tmp);
		printf("Fib(%d) = %llu\n", tmp, fibos[tmp]);
	}
	return 0;
}