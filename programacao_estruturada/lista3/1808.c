#include<stdio.h>
#include<string.h>

int main() {
	char v[100];
	float total = 0;
	float num = 0;
	scanf("%s",  v);
	// printf("A palavra eh %s\n", v);
	int i;

	for(i = 0; i < strlen(v); i++) {
		if(v[i] == '1' && v[i + 1] == '0') {
			total += 10;
			i++;
		} else {
			total += (float)v[i]- '0';
		}
		num++;
	}

	printf("%.2f\n", total/num);

	return 0;
}