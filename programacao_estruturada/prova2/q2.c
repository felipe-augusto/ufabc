#include <stdio.h>
#include "lar.h"

int main() {
	// 1 item
	lar * lar_um = cria_lar("casa", "verde", 200);
	lar * lar_dois = cria_lar("apartamento", "azul", 50);
	lar * lar_tres = cria_lar("chale", "marrom", 20);
	// 2 item
	imprime(lar_um);
	imprime(lar_dois);
	imprime(lar_tres);
	// 3 item
	muda_cor(lar_um, "vermelho");
	// 4 item
	if(get_area(lar_dois) > get_area(lar_tres)) {
		printf("%s é maior que o %s\n", get_tipo(lar_dois), get_tipo(lar_tres));
	} else if(get_area(lar_dois) == get_area(lar_tres)) {
		printf("%s tem o mesmo tamanho que o %s\n", get_tipo(lar_tres), get_tipo(lar_dois));
	} else {
		printf("%s é maior que o %s\n", get_tipo(lar_tres), get_tipo(lar_dois));
	}
	return 0;
}