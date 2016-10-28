#include <stdio.h>
#include <math.h>

int main () {
	int amount;
	scanf("%d", &amount);
	printf("%d\n", amount);
	printf("%d nota(s) de R$ 100,00\n", amount / 100);
	amount = amount % 100;
	printf("%d nota(s) de R$ 50,00\n", amount / 50);
	amount = amount % 50;
	printf("%d nota(s) de R$ 20,00\n", amount / 20);
	amount = amount % 20;
	printf("%d nota(s) de R$ 10,00\n", amount / 10);
	amount = amount % 10;
	printf("%d nota(s) de R$ 5,00\n", amount / 5);
	amount = amount % 5;
	printf("%d nota(s) de R$ 2,00\n", amount / 2);
	amount = amount % 2;
	printf("%d nota(s) de R$ 1,00\n", amount / 1);
	return 0;
}