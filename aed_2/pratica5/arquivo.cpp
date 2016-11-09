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
} Key ;

// FOWARD DECLARATIONS
string readFile();
void writeFile();
void findPositions(char * keyword, Key * insert);
void showPositions(int * t, int n);
void buscaRemissivo(string test);
void insertWord(char * palavra);
bool my_predicate(char c);

const int m = 43;
const int n = 30;
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
char chave[100];

char alfabeto[NUM_CHILDREN] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int buscaBinRec(char vetor[],int ini,int fim,char pesq);
int length(char input[]);
NoTrie * buscaDigital(char chave [], NoTrie * pt, int l, int k);
int insereDigital(char x []);
int last_position;
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
			string sug = "";
			for(k = 0; k < depth; k++) {
				sug += sugestion[k];
			};
			buscaRemissivo(sug);
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
  	myfile.open ("input1.txt",ios::in);
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
				// str.erase(remove_if(str.begin(), str.end(), my_predicate), str.end());
				// convert string to char *
				char * palavra = strdup(str.c_str());
				insertWord(toLower(palavra));
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

void showPositions(int * t, int n) {
	int i;
	for(i = 0; i < n; i++){
		cout << t[i] << "| ";
	}
}


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
  	myfile.open ("input1.txt",ios::in);
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
				// remove all non word characters
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
// escreve arquivo de saída
void writeFile(){
	ofstream myfile; // abre arquivo e aponta para posição onde próximo elemento vai ser escrito
  	myfile.open("saida.txt",ios::app); // append the text at the final position of the file
	myfile << "Escrevendo no arquivo" << endl;
	myfile.close();
}

void insertWord(char * palavra) {

}

void buscaRemissivo(string test) { 
	// encontra a hash da string
	int i = 0;
	int posi = h(toLower(strdup(test.c_str())), test.size());
	cout << "A palavra " << test << " aparece na(s) linha(s): ";
	for (list<Key>::iterator it = hash[posi].begin(); it != hash[posi].end(); ++it){
		// if para lidar com colisoes -> teoricamente estaria na primeira posicao]
	  	if(it->palavra == stoLower(test)) {
	  		for(i = 0; i < it->numberPositions; i++) {
	  			cout << (int) it->positions[i] << " ";
	  		}
	  	}
	}
	cout << endl;
}

/* 
=============== MAIN
*/

main(){

	char * tmp;
	int position;

	// MY IMPLEMENTATION STARTS HERE

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
		// inserts word into trie
		strcpy(chave, toLower(tmp));
		insereDigital(chave);
		// calculate hash
		position = h(tmp, strlen(tmp));
		// this avoid collisions automatically
		Key * insert_key = new Key();
		insert_key->palavra = tmp;
		insert_key->n = strlen(tmp);
		// appends to insert_key the positions and the numberPositions
		findPositions(toLower(tmp), insert_key);
		// insert on hash table
		hash[position].push_back(*insert_key);
		// erase from the original string the splitted part
		keywords.erase(0, pos + delimiter.length());
		// this means we are at the last position
		if(keywords.find(delimiter) == string::npos) {
			last += 1;
		};
	}

	// dada uma palavra retorna
	string test = "Google";
	buscaRemissivo(test);

	// sugestao de palavras com suffixo
	strcpy(chave,"");
	// raiz da arvore, prefixo fornececido pelo usuario, numero maximo de palavras
	sugere(raiz, chave, 100);
}