#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct lar_s {
  int area;
  char *tipo;
  char *cor;
} lar;

/*cria um lar*/
lar *cria_lar(char *tipo, char *cor, int area) {
  lar *l = malloc(sizeof(lar));
  l-> tipo = malloc(strlen(tipo)+1);
  strcpy(l->tipo, tipo);
  l-> cor = malloc(strlen(cor)+1);
  strcpy(l->cor, cor);
  l->area = area;
  return l;
}

/*muda a cor de um lar*/
void muda_cor(lar *l, char *cor) {
  if(l->cor) free(l->cor);
  l-> cor = malloc(strlen(cor)+1);
  strcpy(l->cor, cor);
}

/*muda a area de um lar*/
void muda_area(lar *l, int area){
  l->area = area;
}

/*muda o tipo area de um lar*/
void muda_tipo(lar *l, char *tipo) {
  if(l->tipo) free(l->tipo);
  l-> tipo = malloc(strlen(tipo)+1);
  strcpy(l->tipo, tipo);
}

/*recebe o tipo de l*/
char* get_tipo(lar *l) {
  char *copia = malloc(strlen(l->tipo)+1);
  strcpy(copia, l->tipo);
  return copia;
}

/*recebe a cor de l*/
char* get_cor(lar *l) {
  char *copia = malloc(strlen(l->cor)+1);
  strcpy(copia, l->cor);
  return copia;
}

/*recebe a area de l*/
int get_area(lar *l) {
  return l->area;
}

void imprime(lar *l) {
  printf("Tipo %s Cor %s Area %d\n",l->tipo,l->cor,l->area);
}
