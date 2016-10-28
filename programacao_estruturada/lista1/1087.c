#include <stdio.h>
#include <math.h>

int main () {
	int x1, y1, x2, y2, found;
	// inicializa para sair do valor 0
	x1 = 9;
	y1 = 9;
	x2 = 9;
	y2 = 9;

	while(x1 != 0 && y1 != 0 && x2 != 0 && y2 != 0) {
		found = 0;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		// caso para parar
		if(x1 == 0 && y1 == 0 && x2 == 0 && y2 == 0) {
			break;
		}
		// caso fim igual comeco
		if(x1 == x2 && y1 == y2) {
			printf("%d\n", 0);
			found = 1;
			continue;
		}

		// gera todas as possibilidades
		signed int down_x, down_y, high, i, j;
		down_x = -1;
		down_y = -1;
		int inc = 1;
		while (inc < 9) {
			for(i = down_x; i <= (-down_x); i += inc) {
				for(j = down_x; j <= (-down_x); j += inc) {
					if (j == 0 && i == 0) {
						continue;
					}
					else if (i + x1 > 8 || i + x1 < 1 || j + y1 > 8 || j + y1 < 1) {
						continue;
					} else {
						if (x2 == i + x1 && y2 == j + y1) {
							found = 1;
							printf("%d\n", 1);
							break;
						};
					}
				}
			}
			down_x -= 1;
			inc++;
		}

		// caso nao tenha achado
		if (found == 0) {
			printf("%d\n", 2);
		}
	}
	return 0;
}