/* Para tratamento de strings, veja: http://www.cprogramming.com/tutorial/string.html e http://www.cplusplus.com/reference/string/string/
Para leitura e escrita de arquivos, veja: http://www.cplusplus.com/doc/tutorial/files/ */
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

/* 
=============== HASH SPECIFIC IMPLEMENTATION
*/

// temporary key struct to hold items to be pushed to hash
typedef struct estrutura {
	char * palavra;
	int * positions;
	int n;
	int numberPositions;
	bool keyword;
} Key ;

// FOWARD DECLARATIONS
string readFile();
void findPositions(char * keyword, Key * insert);
void buscaRemissivo(string test, bool keywords);
void insertWord(char * palavra, bool is_keyword);
bool my_predicate(char c);

// melhor se fosse alocado dinamicamente, mas beleza (!)
const int m = 43;
const int n = 300;
int pesos[n];

// hash array with lists
list<Key> hash[m];


// evita somas diferentes -> geras os pessos
void geraPesos() {
	int i;
	for(i = 0; i < n; i++) {
		pesos[i] = rand() % m + 1;
	}
}


// funcao hashing
int h (char * chave, int k) {
	int soma = 0;
	for(int i = 0; i < k; i++) {
		soma += (unsigned int) chave[i] * pesos [i];
	}
	return soma % m;	
}

char * toLower(char * teste) {
	for (int i = 0; i < strlen(teste); i++)
    	teste[i] = tolower(teste[i]);
    return teste;
}

string stoLower(string teste) {
	for (int i = 0; i < teste.size(); i++)
    	teste[i] = tolower(teste[i]);
    return teste;
}

/* 
=============== TRIE SPEFICIC IMPLEMENTATION
*/


#define NUM_CHILDREN 26 //Numero de letras no alfabeto

typedef struct No {
	bool terminal;
	No *pont[26];
} NoTrie;

int a = 0;
NoTrie * raiz = new NoTrie;// raiz da árvore

// CRIE TRIE
char chave[200];

char alfabeto[NUM_CHILDREN] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int buscaBinRec(char vetor[],int ini,int fim,char pesq);
int length(char input[]);
NoTrie * buscaDigital(char chave [], NoTrie * pt, int l, int k);
int insereDigital(char x []);
int last_position;
// para guardar os prefixos
char prefix[100];
int current = 0;

void buscaRemissivo(string test, bool keywords = false) { 
	// encontra a hash da string
	int i = 0;
	int posi = h(toLower(strdup(test.c_str())), test.size());
	for (list<Key>::iterator it = hash[posi].begin(); it != hash[posi].end(); ++it){
		// if para lidar com colisoes -> teoricamente estaria na primeira posicao]
	  	if(it->palavra == stoLower(test) && it->keyword == keywords) {
	  		cout << test << ": ";
	  		for(i = 0; i < it->numberPositions; i++) {
	  			if(i + 1 >= it->numberPositions) {
	  				cout << (int) it->positions[i];
	  			} else {
	  				cout << (int) it->positions[i] << ", ";
	  			}
	  			
	  		}
	  		cout << endl;
	  	}

	}
}

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
			string sug = "";
			for(k = 0; k < depth; k++) {
				sug += sugestion[k];
				buscaRemissivo(sug, true);
			};
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

//lê arquivo de entrada
string readFile(){
	string line;
	string str; 
	int i,temp;
	ifstream myfile; // abre arquivo e aponta para próximo elemento a ser lido
  	myfile.open ("input2.txt",ios::in);
	if (myfile.is_open()){
		i = 0;
		// encontra todas as keywords
		while (myfile.good()){
			i++;
			getline(myfile,line);
			while (line.length()>1){
				temp = line.find_first_of(" ");
				if (temp!=-1){
					str = line.substr(0,temp);
					line = line.substr(temp+1);
				} else {
					str = line;
					line = line.substr(line.length());
				}
				string temp = str;
				temp.erase(remove_if(temp.begin(), temp.end(), my_predicate), temp.end());
				char * palavra = strdup(temp.c_str());
				insertWord(toLower(palavra), false);
			}
		}
		return str;
		myfile.close();
	} else cout << "Unable to open file";
}

// http://stackoverflow.com/questions/6319872/how-to-strip-all-non-alphanumeric-characters-from-a-string-in-c
bool my_predicate(char c) {
	return !isalpha(c);
};

// faz um push em um array
// so de pensar como isso eh facil de fazer em outras linguages, me faz querer chorar :(
int * pushElement(int * array, int n, int element) {
	if (n == 1) {
		array[0] = element;
		return array; 
	} else if (n > 1){
		int i = 0;
		// declara um vetor com uma posiçao a mais
		int * tmp = (int *) malloc((n + 1) * sizeof(int));
		// copia tudo que estava no vetor velho para o novo
		for(i = 0; i < n; i++) {
			tmp[i] = array[i];
		}
		// adiciona o novo elemento
		tmp[n - 1] = element;
		// retorna o ponteiro
		return tmp;
	}
}


// encontra as posiçoes do arquivo de entrada
void findPositions(char *  keyword, Key * insert) {
	string line;
	string str; 
	int i,temp;
	ifstream myfile; // abre arquivo e aponta para próximo elemento a ser lido
  	myfile.open ("input2.txt",ios::in);
  	int size = 1;
	int * positions = (int *) malloc(size * sizeof(int));
	if (myfile.is_open()){
		int position = 0;
		i = 0;
		// vetor que sera retornado
		while (myfile.good()){
			i++;
			getline(myfile,line);
			// position += line.length();
			position += 1;
			int last = line.length();
			int walked = 0;
			while (line.length()>1){
				temp = line.find_first_of(" ");
				walked += temp;
				if (temp!=-1){
					str = line.substr(0,temp);
					line = line.substr(temp+1);
				} else {
					str = line;
					line = line.substr(line.length());
				}
				str.erase(remove_if(str.begin(), str.end(), my_predicate), str.end());
				if (stoLower(str) == toLower(keyword)) {
					// calculates the positions
					// int pos = position - last + walked - strlen(keyword) + 1;
					int pos = position;
					// push to positions array
					positions = pushElement(positions, size, pos);
					size++;
				}
			}
		}
		// o ultimo nao conta
		size--;
		myfile.close();
		insert->positions = positions;
		insert->numberPositions = size;
	} else cout << "Unable to open file";

}

void insertWord(char * palavra, bool is_keyword) {
	palavra = toLower(palavra);
	// ter certeza que a palavra nao existe na trie
	// se existir da SEGMENTATION FAULT
	buscaDigital(palavra, raiz, 0, length(palavra));
	if(a) {
		insereDigital(palavra);
		// calculate hash
		int position = h(palavra, strlen(palavra));
		// this avoid collisions automatically
		Key * insert_key = new Key();
		insert_key->palavra = palavra;
		insert_key->n = strlen(palavra);
		insert_key->keyword = is_keyword;
		// appends to insert_key the positions and the numberPositions
		findPositions(toLower(palavra), insert_key);
		// insert on hash table
		hash[position].push_back(*insert_key);
	} else {
		if(is_keyword) {
			int posi = h(palavra, strlen(palavra));
			for (list<Key>::iterator it = hash[posi].begin(); it != hash[posi].end(); ++it){
				// if para lidar com colisoes -> teoricamente estaria na primeira posicao]
			  	if(toLower(it->palavra) == stoLower(palavra)) {
			  		it->keyword = true;
				}
			}
		}

	}
}


/* 
=============== MAIN
*/

main(){

	char * tmp;
	int position;

	// MY IMPLEMENTATION STARTS HERE
	cout << "==== ATIVIDADE PRATICA 5 ====" << endl;
	// create weight array
	geraPesos();
    // read the keywords
	string keywords = readFile();
	// split the keywords by , (comma)
	string delimiter = ",";
	string key;
	size_t pos = 0;
	// the delimiters does not get the last keyword
	int last = 0;
	while ((pos = keywords.find(delimiter)) != string::npos || last == 1) {
		key = keywords.substr(0, pos);
		// convert key to char *
		tmp = strdup(key.c_str());
		insertWord(tmp, true);
		// erase from the original string the splitted part
		keywords.erase(0, pos + delimiter.length());
		// this means we are at the last position
		if(keywords.find(delimiter) == string::npos) {
			last += 1;
		};
	}

	// dada uma palavra retorna
	cout << "(a) busca de uma palavra do indice remissivo" << endl;
	string test = "as";
	buscaRemissivo(test);
	test = "since";
	buscaRemissivo(test);
	
	// indice remissivo em ordem lexicografica
	cout << "(b) impressao do indice remissivo em ordem lexicografica" << endl;
	strcpy(chave, "");
	sugere(raiz, chave, 120); // raiz trie, chave fazia, maximo 120 resultados
}