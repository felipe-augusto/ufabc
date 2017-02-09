#include <stdio.h>
#include <stdlib.h>

void transforma(char *frase, int n) {
  int i = 0;
  for (i = 0; i < n; i++) {
    if(frase[i] == '\0') {
      break;
    } else if (frase[i] != ' ') {
      frase[i] = frase[i] + 32;
    } 
  }
}

int main() {
  char *frase;
  int n, i;
  scanf("%d", &n);
  frase = malloc(n+1); // pode isso porque char ocupa um byte
  scanf(" %c", &frase[0]);
  for(i=1; i<n; i++) {
    scanf("%c", &frase[i]);
  }
  frase[n]='\0';
  transforma(frase, n);
  printf("%s\n", frase);
  return 0;
}
