#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

#define NUM_CHILDREN 26 //Numero de letras no alfabeto

typedef struct No {
	bool terminal;
	No *pont[26];
	} NoTrie;

int a = 0;
NoTrie *raiz = NULL;// raiz da árvore
char alfabeto[NUM_CHILDREN] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int buscaBinRec(char vetor[],int ini,int fim,char pesq);
int length(char input[]);
NoTrie * buscaDigital(char chave [], NoTrie * pt, int l, int k);
int insereDigital(char x []);
int last_position;
char tmp [100];
// para guardar os prefixos
char prefix[100];
int current = 0;

// funcao recursiva que imprime as palavras sugeridas por prefixos
void printPalavra(NoTrie * pt, char sugestion [], int max, char chave [], int depth = -1){
	int found = 0;
	int k;
	depth++; // profundidade da arvore
	if (pt != NULL) {
		for( k = 0; k < 25; k++) {
			if (pt->pont[k] != 0) {
				found = 1;
				sugestion[depth] = alfabeto[k];
				printPalavra(pt->pont[k], sugestion, max, chave, depth);
			}
		}
		// fim da arvore
		if (found == 0 && current < max) {
			cout << chave;
			for(k = 0; k < depth; k++) cout << sugestion[k];
			cout << endl;
			current++;
		}
	} else {
		return;
	}
}

// seta as variaveis globais e os vetores temporarios para a funcao recursiva
void sugere(NoTrie * pt, char chave [], int max) {
	int k;
	// guarda o prefixo que o usuario digitou
	for(k = 0; k < strlen(chave); k++) {
		int pos = buscaBinRec(alfabeto, 0, 25, chave[k]);
		pt = pt->pont[pos];
	}
	// variavel que guarda quantas palavras ja foram impresas (limitado por max)
	current = 0;
	printPalavra(pt, prefix, max, chave);
}

int stop;

// remove da trie
void remove(NoTrie * pt, char chave[], int k, int l = 0) {
	stop = 0;
	int j, f;
	if (l < k) {
		j = buscaBinRec(alfabeto, 0, 25, chave[l]);
		if (pt->pont[j] != NULL) {
			// checa quantos ponteiros ela tem
			int num_filhos = 0;
			for( f = 0; f < 25; f++) {
				if (pt->pont[f] != NULL) {
					num_filhos++;
				}
			}
			// pega os filhos e chama recursivo
			l = l + 1;
			remove(pt->pont[j], chave, k, l);
			
			// se tiver apenas um filho remove, senao para
			if (num_filhos == 1 && stop == 0) {
				for( f = 0; f < 25; f++) pt->pont[f] = NULL;
			} else if (stop == 0 && num_filhos != 1) {
				pt->pont[j] = NULL;
				stop = 1;
			} else {
				stop = 1;	
			}
		} 
	}
}

main(){
	raiz = new NoTrie;
	raiz->terminal = false;
	char chave[100];
	// insere palavras na trie
	strcpy(chave,"arara");
	insereDigital(chave);
	strcpy(chave,"aro");
	insereDigital(chave);
	strcpy(chave,"areia");
	insereDigital(chave);
	strcpy(chave,"arado");
	insereDigital(chave);

	// faz uma busca
	strcpy(chave, "aro");
	NoTrie * busca = buscaDigital(chave, raiz, 0, length(chave));
	cout << "Resultado da busca: " << a << endl; // a é a variabel global que nos diz se acho ou nao (struct please!?)

	// sugestao de palavras com suffixo
	strcpy(chave,"ar");
	// raiz da arvore, prefixo fornececido pelo usuario, numero maximo de palavras
	cout << "Sugestoes com o prefixo '" << chave << "':" <<endl;
	sugere(raiz, chave, 10);

	// remove
	strcpy(chave,"ara");
	cout << "Removendo a chave '" << chave << "'" << endl;
	remove(raiz, chave, length(chave));

	// remove
	strcpy(chave,"aro");
	cout << "Removendo a chave '" << chave << "'" << endl;
	remove(raiz, chave, length(chave));

	// verifica se a palavra realmente desapareceu
	strcpy(chave,"are");
	// raiz da arvore, prefixo fornececido pelo usuario, numero maximo de palavras
	cout << "Sugestoes com o prefixo '" << chave << "':" <<endl;
	sugere(raiz, chave, 10);
	
}

// busca uma palavra, retorna um ponteiro caso existe e um nulo caso não
// a variabel global 'a' possui o valor boleano que pode dizer se foi achado ou não
NoTrie * buscaDigital(char chave [], NoTrie * pt, int l, int k) {
	a = 0;
	int j;
	if (l < k) {
		j = buscaBinRec(alfabeto, 0, 25, chave[l]);
		if (pt->pont[j] != NULL) {;
			pt = pt->pont[j];
			l = l + 1;
			buscaDigital(chave, pt, l, k);
		} else {
			last_position = l;
			// significa que parou antes de achar, a = 1;
			if (last_position - 1 != strlen(chave)) {
				a = 1;
			}
			return pt;
		}
	}

}

// insere uma palavra na trie
int insereDigital(char chave []) {
	int h, j, i;
	NoTrie * pt = buscaDigital(chave, raiz, 0, length(chave));
	if(pt != NULL) {
		for(h = last_position + 1; h <= length(chave); h++) {
			j = buscaBinRec(alfabeto, 0, 25, chave[h - 1]);
			NoTrie * ptz = new NoTrie;
			for(i = 0; i < 25; i++) {
				ptz->pont[i] = NULL;
			}
			pt->pont[j] = ptz;
			pt = ptz;
		}
	}
}

// faz busca binária recursiva
int buscaBinRec(char vetor[],int ini,int fim,char pesq) {
	while(ini<=fim) {
		int meio;
		meio=(ini+fim)/2;
		if(vetor[meio]==pesq) return meio;
		else if (vetor[meio]<pesq) return buscaBinRec(vetor,meio+1,fim,pesq);
		else return buscaBinRec(vetor,ini,meio-1,pesq);
	}
	return -1;
}

// determina comprimento de uma string (somente caracteres válidos)
int length(char input[]){
    int length = 0;
    while(input[length]!='\0'){
        length++;
    }
	return length;
}
