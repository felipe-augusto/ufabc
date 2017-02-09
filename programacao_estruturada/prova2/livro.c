#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro_s {
	char * titulo;
	int ano;
	int paginas;
} livro;

/* Cria um livro com os parametros dados */
livro * cria_livro(char * titulo, int ano, int paginas) {
	livro * l = malloc(sizeof(livro));
	l->titulo = titulo;
	l->ano = ano;
	l->paginas = paginas;
	return l;
};

/* Cria uma lista de n ponteiros para livros. 
   Os ponteiros devem ser alocados, mas os livros em si nao precisam
   ser alocados*/
livro **cria_lista(int n) {
	livro ** livros = malloc(sizeof(livro *) * n);
	int i;
	for(i = 0; i < n; i++) {
		livros[i] = malloc(sizeof(livro));
	}
	return livros;
};

/*Imprime o titulo, ano e paginas do livro*/
void imprime(livro *l) {
	printf("Titulo: %s - Ano: %d - Páginas: %d\n", l->titulo, l->ano, l->paginas);
};

/* devolve uma copia para o titulo do livro */
/* Ou seja, se a copia for alterada, o titulo de livro
 nao deve mudar!*/
char *get_titulo(livro *l) {
	int i;
	size_t tamanho = strlen(l->titulo);
	char * novo_titulo = malloc(tamanho);
	for(i = 0; i < tamanho; i++) {
		*(novo_titulo + i) = l->titulo[i];
	}
	
	return novo_titulo;
};

// compare pass to qsort
int comp(const void * a, const void * b) {
	livro ** aa = (livro **) a;
	livro ** bb = (livro **) b;
	return (*aa)->ano - (*bb)->ano;
}

/*re-ordena os livros por ano*/
/*Voce pode assumir que os anos vao de 1900 a 2016*/
void ordena(livro **l, int n) {
	qsort(l, n, sizeof(l), comp);
};

