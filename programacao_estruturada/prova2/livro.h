typedef struct livro_s livro;

/* Cria um livro com os parametros dados */
livro *cria_livro(char *titulo, int ano, int paginas);

/* Cria uma lista de n ponteiros para livros. 
   Os ponteiros devem ser alocados, mas os livros em si nao precisam
   ser alocados*/
livro **cria_lista(int n);

/*Imprime o titulo, ano e paginas do livro*/
void imprime(livro *l);

/* devolve uma copia para o titulo do livro */
/* Ou seja, se a copia for alterada, o titulo de livro
 nao deve mudar!*/
char *get_titulo(livro *l);

/*re-ordena os livros por ano*/
/*Voce pode assumir que os anos vao de 1900 a 2016*/
void ordena(livro **l, int n);
