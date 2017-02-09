#include <stdio.h>
#include "livro.h"

int main() {
  int i;
  livro **l;
  char *c;

  l = cria_lista(5);
  l[0] = cria_livro("ABC",1990, 120);
  l[1] = cria_livro("DEF",1995, 203);
  l[2] = cria_livro("FHI",1990, 123);
  l[3] = cria_livro("JKL",1984, 412);
  l[4] = cria_livro("MNO",1980, 1239);
  
  ordena(l, 5);

  for(i=0; i<5; i++) {
    imprime(l[i]);
  }
  
  printf("Titulo do primeiro livro %s\n", get_titulo(l[0]));
  c = get_titulo(l[0]);
  c[0] = 'Z';
  c[1] = 'Z';
  c[2] = 'Z';
  printf("Titulo do primeiro livro = %s e c = %s sao diferentes!\n",
         get_titulo(l[0]), c);
  
  return 0;
}
