#include<stdio.h>
#include<string.h>

// norte

int main() {
	int i = 0;
	int comando = 2000;

	int count;
	char palavra[1001];

	while(comando != 0) {
		count = 0;
		scanf("%d", &comando);
		if (comando == 0) {
			break;
		}
		scanf("%s", palavra);
		for(i = 0; i < strlen(palavra); i++){
			if(palavra[i] == 'D') {
				count++;
			} else if(palavra[i] == 'E') {
				count--;
			}

			if(count == 4) {
				count = 0;
			} else if (count == -1) {
				count = 3;
			}
		}

		switch(count) {
			case 0:
				printf("%c\n", 'N');
				break;
			case 1:
				printf("%c\n", 'L');
				break;
			case 2:
				printf("%c\n", 'S');
				break;
			case 3:
				printf("%c\n", 'O');
				break;
		}
		
	}

	return 0;
}