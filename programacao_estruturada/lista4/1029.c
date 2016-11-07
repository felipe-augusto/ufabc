#include<stdio.h>
#include<string.h>
#include<math.h>

int count = 0;

int fib(int n) {
	if(n == 0) return 0;
	if(n == 1) return 1;
	count++;
	return fib(n - 1) + fib(n - 2);
	
}

int main() {
	int number, tmp, i;
	scanf("%d", &number);

	for(i = 0 ; i < number; i++) {
		count = 0;
		scanf("%d", &tmp);
		printf("fib(%d) = %d calls = %d\n", tmp, count * 2, fib(tmp));
	}
	
	return 0;
}