#include <stdio.h>
#include <string.h>

//colocar funcao checa aqui
int checa(int posicao, char * palavra, int tamanho) {
  int i, j;
  for (i = posicao; i < tamanho; i++) {
    if(palavra[posicao - 1] == palavra[i]) {
      // se achar uma igual ainda tem que verificar se todas as posicoes
      // subsquentes dao match (problema com palavras repetidas)
      int first = posicao;
      int final = i;
      for (j = i + 1; j < tamanho; j++) {
        if(palavra[first] != palavra[j] || first == final) {
          return 0;
        }
        first++;
      }
      //printf("%d %d\n", first, j);
      return tamanho - first;
    }
  }
  return 0;
}

int main() {
  char p[35];
  int i, j, n;
  int achei;

  while(scanf("%s", p)==1) {
    achei = 0;
    n = strlen(p); //comprimento de p
    for(i=1; i<n; i++) {
      achei = checa(i,p,n);
      if(achei) break;
    }
    if(!achei) i=0; //nao houve repeticao
    for(j=0; j<strlen(p)-achei; j++) {//imprime sem a repeticao
      printf("%c",p[j]);
    }
    printf("\n");
  }
}