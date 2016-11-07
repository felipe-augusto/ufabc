# Consulta para prova

Leitura:

```c
#include<stdio.h> /*biblioteca com entrada e saida*/
 
int main() {
  int x;
  scanf("%d", &x); /*leitura: atencao para o &*/
  printf("O numero e %d\n", x); /*saida: o \n eh para pular linha*/
  return 0; /*fim do programa*/
}
```

Ler e imprimir um double:
```c
#include<stdio.h> /*biblioteca com entrada e saida*/
 
int main() {
  double x;
  scanf("%lf", &x); /*leitura: atencao para o &*/
  printf("O numero e %.2f\n", x); /*saida com duas casas decimais depois da virgula*/
  return 0; /*fim do programa*/
}
```

Vetor e matriz (alocação estática):

```c
#include<stdio.h> /*biblioteca com entrada e saida*/
 
int main() {
  int x[5];
  int i; /* declare as variaveis no comeco */
  /* leitura: atencao para o & */
  for(i=0; i<5; i++) {
    scanf("%d", &x[i]);
  }
  /* impressao */
  for(i=0; i<5; i++) {
    printf("x[%d] = %d\n", i, x[i]);
  }
  return 0; /*fim do programa*/
}
```

Matriz com duas linhas e duas colunas:

```c
#include <stdio.h>
 
int main() {
  int x[2][3]; /*Uma matriz com 2 linhas e 3 colunas*/
  int i, j;
  for(i = 0; i<2; i++) { /* linhas */
    for(j = 0; j<3; j++) { /* colunas */
      scanf("%d", &x[i][j]);
    }
  }
  for(i = 0; i<2; i++) { /* linhas */
    for(j = 0; j<3; j++) { /* colunas */
      printf("x[%d][%d] = %d\n", i,j, x[i][j]);
    }
  }
  return 0;
}
```

Função:

```c
#include<stdio.h>
 
int main() {
    int x, y, z;
    scanf("%d %d", &x, &y);
    z = x+y;
    printf("soma = %d\n",z);
    return 0;
}
```

Usando função:
```c
#include<stdio.h>
 
int soma(int a, int b) {
    return a+b;
}
 
int main() {
    int x, y, z;
    scanf("%d %d", &x, &y);
    z = soma(x,y);
    printf("soma = %d\n",z);
    return 0;
}
```

Declarar função que será escrita depois:

```c
#include<stdio.h>
 
int soma(int a, int b);
 
int main() {
    int x, y, z;
    scanf("%d %d", &x, &y);
    z = soma(x,y);
    printf("soma = %d\n",z);
    return 0;
}
 
int soma(int a, int b) {
    return a+b;
}
```

Compor funções:

```c
#include<stdio.h>
 
int soma(int a, int b);
 
int main() {
    int x, y, z;
    scanf("%d %d", &x, &y);
    z = soma(x,soma(y,y));
    printf("soma = %d\n",z);
    return 0;
}
 
int soma(int a, int b) {
    return a+b;
}
```

No código a seguir o valor de x não muda. Como discutimos é porque passamos apenas o valor de x como parâmetro:

```c
#include<stdio.h>
 
void dobra(int x) {
    x = 2*x;
}
 
int main() {
    int x;
    scanf("%d", &x);
    printf("O valor de x eh %d\n", x);
    dobra(x);
    printf("O valor de x eh %d\n", x);
    return 0;
}

```

Mas se x for uma variável global, podemos mudar o valor de x em qualquer função.

```c
#include<stdio.h>
 
int x; //variavel global
 
int dobra() {
    x = 2*x;
}
 
int main() {
    scanf("%d", &x);
    printf("O valor de x eh %d\n", x);
    dobra();
    printf("O valor de x eh %d\n", x);
    return 0;
}

```

MDC e MMC. Note que a função MMC usa a função de MDC.

```c
#include<stdio.h>
 
int mdc(int menor, int maior);//assumindo menor<=maior
int mmc(int menor, int maior);
 
int main(){
    int x, y, menor, maior;
    scanf("%d %d", &x, &y);
    if(x<=y){
        menor = x;
        maior = y;
    } else {
        menor = y;
        maior = x;
    }
    printf("mdc de %d e %d eh %d\n",menor, maior, mdc(menor,maior));
    printf("mmc de %d e %d eh %d\n",menor, maior, mmc(menor,maior));
    return 0;
}
 
int mdc(int menor, int maior) {
    int copia;
    while(menor!=0) {
        copia = menor;
        menor = maior%menor;
        maior = copia;
    }
    return maior;
}
 
int mmc(int menor, int maior){
    return maior/mdc(menor,maior)*menor;
}

```

Um algoritmo simples para primalidade:

```c
#include<stdio.h>
 
int checa_primo(int n);
 
int main() {
    int n;
    printf("Digite um num de 2 a 100 (Digite 0 para terminar)");
    scanf("%d", &n);
    while(n!=0) {
        if(checa_primo(n)==1) {
            printf("%d eh primo\n", n);
        } else {
            printf("%d eh composto\n", n);
        }
        scanf("%d", &n);
    }
}
 
int checa_primo(int n) {
    int i, primo=1;
    for(i = 2; i*i<=n; i++) {
        if(n%i==0) {
            primo=0;
            break;
        }
    }
    return primo;
}
```

Crivo de Aristótenes:

```c
#include <stdio.h>
#define MAX 100
 
int primo[MAX+1];
int num_primos[MAX+1];
int primos_qte;
 
int checa_primo(int n);
void crivo();
 
int main() {
    int n;
    crivo();
    printf("Digite um num de 2 a 100 (Digite 0 para terminar)");
    scanf("%d",&n);
    while(n!=0) {
        if(checa_primo(n)) {
            printf("%d eh primo\n", n);
        } else {
            printf("%d eh composto\n", n);
        }
        scanf("%d",&n);
    }
    return 0;
}
 
int checa_primo(int n){
    int i, primo=1;
    for(i = 0; i<primos_qte && num_primos[i]*num_primos[i]<=n; i++) {
        if(n%num_primos[i]==0) {
            primo=0;
            break;
        }
    }
    return primo;
}
 
void crivo() {
    int i, j;
    primos_qte = 0;
    for(i=2; i<=MAX; i++) {
        primo[i]=1; //nenhum numero comeca riscado!
    }
    for(i=2; i<=MAX; i++) {
        if(primo[i]==1) {//o numero i não foi riscado
        num_primos[primos_qte]=i;
        primos_qte++;
            for(j=2*i; j<=MAX; j = j+i) {
                primo[j] = 0; //riscando j
            }
        }
    }
    printf("Os nums primos até 100 são:\n");
    for(i=0;i<primos_qte; i++) {
        printf("%d\n", num_primos[i]);
    }
}
```

Cada caractere (char) é associado a um valor inteiro: 'a' é associado a 97, 'b' a 98, 'c' a 99, e assim por diante:

```c
#include<stdio.h>
 
int main() {
    char c;
    int n;
    scanf("%c", &c);
    n = c;
    printf("O valor numérico de '%c' é %d",c,n);
}

```

Para converter um char c que representa um dígito (digamos, c='9'), basta fazer int n = c - '0'. 

```c
#include<stdio.h>
 
int main() {
    char c;
    int n;
    scanf("%c", &c);
    n = c-'0';
    printf("O char '%c' convertido para int vale %d",c,n);
}

```

Uma palavra é simplesmente um vetor de char. Note que ao inicializar a palavra com char a posição 4 foi preenchida como o caractere '\0'. 

```c
#include<stdio.h>
#include<string.h>
 
int main(){
    int i, j;
    char palavra[20] = "prog";
    int n; 
 
    n = strlen(palavra);
    for(i=0; i<n; i++){
        printf("O char na posicao %d é %c\n",i,palavra[i]);
    }
    printf("O char na posicao %d tem codigo %d\n",n,palavra[n]);
}
```

No código a seguir, colocamos duas palavras em uma matriz: 

```c
#include<stdio.h>
#include<string.h>
 
int main(){
    int i, j;
    char palavra[2][20] = {"prog","comp"};
    int n; 
 
    for(j=0; j<2;j++) {
        n = strlen(palavra[j]);
        for(i=0; i<n; i++){
            printf("O char na posicao %d é %c\n",i,palavra[j][i]);
        }
    printf("O char na posicao %d tem codigo %d\n",n,palavra[j][n]);
    }
}
```

Usamos %s no scanf para ler palavras. Podemos usar a função strcmp para comparar palavras: 

```c
#include<stdio.h>
#include<string.h>
 
 
int main() {
    char palavra1[20];
    char palavra2[20];
    int i;
    int n;
 
    scanf("%s", palavra1); //note que o & nao aparece aqui
    scanf("%s", palavra2); //note que o & nao aparece aqui
 
    int comparacao = strcmp(palavra1, palavra2);
 
    printf("%d\n", comparacao);
 
    if(comparacao==0) {
        printf("%s = %s\n", palavra1,palavra2);
    } else if(comparacao<0){
        printf("%s < %s\n", palavra1,palavra2);
    } else {
        printf("%s > %s\n", palavra1,palavra2);
    }
}}
```

Aqui está uma função que calcula potências de 2 [recursao]:

```c
#include<stdio.h>
 
int pot(int n) {
    int i;
    int resp = 1;
    for(i=0; i<n; i++) resp = resp*2;
    return resp;
}
 
int main() {
    int n;
    scanf("%d",&n);
	printf("%d", pot(n));
}
```

E aqui está uma versão usando recursão [recursao]:

```c
#include<stdio.h>
 
int pot(int n) {
    if(n == 0) {
        return 1;
    } else {
        return pot(n-1)*2;
    }
}
 
int main() {
    int n;
    scanf("%d",&n);
	printf("%d", pot(n));
}
```

O seguinte código calcula o número de Fibonacci. Os números de Fibonacci são definidos pela seguinte recorrência: 

* F(0) = 0 
* F(1) = 1 
* F(n) = F(n-1)+F(n-2), se n>=2
```c
#include<stdio.h>
 
int fib(int n) {
    if(n==0) return 0;
    else if(n==1) return 1;
    else return fib(n-1)+fib(n-2);
}
 
 
int main() {
    int n;
    scanf("%d",&n);
	printf("%d", fib(n));
}
```

MDC com impressão para cada chamada de função [recursao]:
```c
int mdc(int menor, int maior);//assumindo menor<=maior
 
int main(){
    int menor, maior;
    scanf("%d %d", &menor, &maior);
    printf("mdc de %d e %d eh %d\n",menor, maior, mdc(menor,maior));
    return 0;
}
 
int mdc(int menor, int maior) {
    int r;
    printf("ABRE mdc(%d,%d) {\n",menor, maior);
    if (menor == 0) r = maior;
    else r = mdc(maior%menor, menor);
    printf("FECHA mdc(%d,%d) }\n", menor,maior);
    return r;
}
```

Potência de 2 com impressão para cada chamada de função [recursao]:
```c
#include<stdio.h>
#define MAX
 
int potencias[32];
 
int pot(int n) {
    int resp, r;
    printf("ABRE pot(%d) {\n",n);
    if(n == 0) {
        resp = 1;
    } else {
        r = pot(n/2);
        resp = r*r*(1+r%2);
    }
    printf("FECHA pot(%d) }\n",n);
    return resp;
}
 
int main() {
    int n;
    scanf("%d",&n);
    printf("%d\n", pot(n));
}
```

Fibonacci com impressão para cada chamada de função [recursao]:
```c
#include<stdio.h>
 
int fib(int n) {
    int r;
    printf("ABRE fib(%d)\n", n);
    if(n==0) r=0;
    else if(n==1) r=1;
    else return r=fib(n-1)+fib(n-2);
    printf("FECHA fib(%d)\n", n);
    return r;
}
 
```

A versão de Fibonacci acima tem o defeito de recalcular os mesmos números de Fibonacci várias vezes. Na versão abaixo, vamos guardando os valores calculados em um vetor para evitar esses recálculos. Isso é um exemplo do que chamamos de recursão memorizada.:
```c
#include<stdio.h>
#define MAX 50
 
int fibnum[MAX];
 
int fib(int n) {
    int r;    
    if(fibnum[n]!=-1) r=fibnum[n]; //já foi calculado
    else if(n==0) r = 0;
    else if(n==1) r = 1;
    else r = fib(n-1)+fib(n-2);
    fibnum[n]=r;
    printf("fib(%d) = %d\n", n, r);
    return r;
}
 
 
int main() {
    int n, i;
    scanf("%d",&n);
    for(i=0; i<=n; i++) fibnum[i]=-1;//para indicar que ainda não foi calculado
    printf("%d", fib(n));
}
 
```

Aqui está um versão iterativa (com um laço ao invés de recursão). Note que neste caso, não precisamos inicializar o vetor com um valor indicando que ainda não foi calculado. 

```c
#include<stdio.h>
#define MAX 50
 
int fibnum[MAX];
 
int fib(int n) {
    int i;
    fibnum[0]=0;
    fibnum[1]=1;
    for(i = 2; i<=n; i++) fibnum[i]=fibnum[i-1]+fibnum[i-2];
    return fibnum[n];
}
 
 
int main() {
    int n, i;
    scanf("%d",&n);
    printf("%d", fib(n));
}
 
```

Note que para calcular um número de Fibonacci só precisamos guardar os dois anteriores. Então podemos economizar espaço como a seguir:  

```c
#include<stdio.h>
 
int fib(int n) {
    int ultimo, penultimo, atual;
    int i;
    if(n==0) {
        atual = 0;
    } else if(n==1) {
        atual = 1;
    } else {
        penultimo=0;
        ultimo=1;
        for(i = 2; i<=n; i++) {
            atual = ultimo+penultimo;
            penultimo = ultimo;
            ultimo = atual;
        }
    }
    return atual;
}
 
 
int main() {
    int n, i;
    scanf("%d",&n);
    printf("%d\n", fib(n));
}

 
```

Vimos em sala como representar um grafo (ou digrafo, se quisermos que as arestas tenham direção) através de uma matriz que chamamos de matriz de adjacência. Aqui está um exemplo de leitura.

```c
#include<stdio.h>
 
int fib(int n) {
    int ultimo, penultimo, atual;
    int i;
    if(n==0) {
        atual = 0;
    } else if(n==1) {
        atual = 1;
    } else {
        penultimo=0;
        ultimo=1;
        for(i = 2; i<=n; i++) {
            atual = ultimo+penultimo;
            penultimo = ultimo;
            ultimo = atual;
        }
    }
    return atual;
}
 
 
int main() {
    int n, i;
    scanf("%d",&n);
    printf("%d\n", fib(n));
}

 
```
 
 O algoritmo de busca em profundidade é um algoritmo recursivo que percorre os vértices de um grafo que podem ser alcançados a partir de um mesmo vértice. Usamos o vetor descoberto para marcar quais os vértices foram descobertos ou não.

```c
#include<stdio.h>
#define MAX 10
 
int n, m;
int adj[MAX][MAX] = {0};
int descoberto[MAX]={0};
 
void leitura();
void busca(int u);
 
int main(){
    int v;
    leitura();
    busca(0);
    for(v=0; v<n;v++){
        printf("%d foi visitado\n", v);
    }
    return 0;
}
 
void busca(int u){
    int v;
    printf("Começando a visitar %d\n", u);
    descoberto[u]=1;
    for(v=0; v<n; v++) {
        if(adj[u][v] && !descoberto[v]) 
            busca(v);
    }
    printf("Terminando de visitar %d\n", u);
}
 
void leitura(){
    int i, j, u, v;
    scanf("%d %d", &n, &m);
    for(i=0; i<n;i++)
        for(j=0; j<n;j++)
            adj[i][j]=0;
    for(i=0; i<n;i++) 
        descoberto[i]=0;
    for(i=0; i<m;i++) {
        scanf("%d %d", &u, &v);
        adj[u][v]=1;
        adj[v][u]=1;
    }
    printf("Matriz\n");
    for(i=0; i<n;i++) {
        for(j=0; j<n;j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}
 
```

Vimos uma modificação de busca em profundidade para o seguinte problema. Dado um conjunto de tarefas com dependências entre si, encontrar uma ordenação das tarefas de modo que se uma tarefa A depende de uma tarefa B, B aparece na ordenação antes de A.

Construímos um digrafo $G$ onde o conjunto de vértices são as tarefas e incluímos um arco $(A,B)$ se a tarefa $A$ depende de $B$. Para encontrar uma ordenação (assumindo que seja possível), basta considerar os vértices a medida que terminamos de visitá-los:



```c
#include<stdio.h>
#define MAX 10
 
int n, m;
int adj[MAX][MAX];
int descoberto[MAX];
 
void leitura();
void busca(int u, int c);
 
int main(){
    int v, c;
    leitura();
    for(v=0; v<n; v++) {
        if(!descoberto[v]) {
            c++;
            busca(v,c);
        }
    }
    return 0;
}
 
void busca(int u, int c){
    int v;
    descoberto[u]=c;
    for(v=0; v<n; v++) {
        if(adj[u][v] && !descoberto[v])//v tem que ser feito antes de u 
            busca(v, c);
    }
    printf("Faça %d\n", u);
}
 
void leitura(){
    int i, j, u, v;
    scanf("%d %d", &n, &m);
    for(i=0; i<n;i++)
        for(j=0; j<n;j++)
            adj[i][j]=0;
    for(i=0; i<n;i++) 
        descoberto[i]=0;
    for(i=0; i<m;i++) {
        scanf("%d %d", &u, &v);
        adj[u][v]=1;//aqui estamos colocando so a direcao de u a v
    }
    printf("Matriz\n");
    for(i=0; i<n;i++) {
        for(j=0; j<n;j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}
 
```
Mas e se existirem dependências circulares (por exemplo, A depende de B, que depende de C, que depende de A)? Para detectar esse tipo de ocorrência, não basta considerar se um vértice já foi ou não descoberto. Precisamos considerar os seguintes estados para os vértices: não descoberto (codificado com 0), em processo de visita (codificado com 1), com visita terminada (codificado com 2).
```c
#include<stdio.h>
#define MAX 10
 
int n, m;
int adj[MAX][MAX];
int descoberto[MAX];
int ordenacao[MAX];
int prox = 0;
 
void leitura();
int busca(int u);
 
int main(){
    int v, sucesso;
    leitura();
    sucesso=1;
    for(v=0; v<n && sucesso; v++) {
        if(!descoberto[v]) {
            sucesso = busca(v);
        }
    }
    if(sucesso) {
        for(v=0; v<n;v++) {
            printf("Faça %d\n", ordenacao[v]);
        }
    } else {
        printf("Houve conflito!\n");
    }
    return 0;
}
 
int busca(int u){
    int v, sucesso;
    sucesso = 1;
    descoberto[u]=1;//comecando a visita
    for(v=0; v<n && sucesso; v++) {
        if(adj[u][v] && !descoberto[v]){ //v tem que ser feito antes de u 
                sucesso = busca(v);
            } else if (adj[u][v] && descoberto[v]==1) {//CONFLITO!
                sucesso = 0; //para indicar conflito
        }
    }
    descoberto[u]=2;//terminando a visita
    ordenacao[prox]=u;
    prox++;
    return sucesso; 
}
 
 
void leitura(){
    int i, j, u, v;
    scanf("%d %d", &n, &m);
    for(i=0; i<n;i++)
        for(j=0; j<n;j++)
            adj[i][j]=0;
    for(i=0; i<n;i++) 
        descoberto[i]=0;
    for(i=0; i<m;i++) {
        scanf("%d %d", &u, &v);
        adj[u][v]=1;
    }
    printf("Matriz\n");
    for(i=0; i<n;i++) {
        for(j=0; j<n;j++) {
            printf("%d ", adj[i][j]);
        }
        printf("\n");
    }
}
 
```

[Ponteiros] Criando uma variável char e vendo seu endereço em hexadecimal:
```c
#include<stdio.h>
 
int main() {
    char x = 'a';
    printf("Endereço de x: %p\n", &x);
    printf("Valor de x: %c\n", x);
    return 0;
}
 
```
[Ponteiros] Podemos imprimir como um unsigned long long também: 

```c
#include<stdio.h>
 
int main() {
    char x = 'a';
    printf("Endereco de x: %llu\n", (unsigned long long)&x);
    printf("Valor de x: %c\n", x);
    return 0;
}
 
```

[Ponteiros] Criando um ponteiro y e operador *:
```c
 #include<stdio.h>
 
int main() {
    char x = 'a';
    char *y = &x;
    printf("Valor de y: %p\n", y);
    printf("Valor guardado no endereço: %c\n", *y);
    return 0;
}
```
[Ponteiros] O código a seguir não tem nenhum efeito na variável x:
```c
#include<stdio.h>
 
int f(int x) {
    x = 2;
}
 
int main() {
    int x = 3;
    printf("x = %d\n", x);
    f(x);
    printf("x = %d\n", x);
    return 0;
}
 
```
[Ponteiros] Para mudar o valor da variável passamos um ponteiro como parâmetro:

```c
#include<stdio.h>
 
int f(int *x) {
    *x = 2;
}
 
int main() {
    int x = 3;
    printf("x = %d\n", x);
    f(&x);
    printf("x = %d\n", x);
    return 0;
 
```
[Ponteiros] Incrementando e decrementando um ponteiro:
```c
#include<stdio.h>
 
int main() {
    char x = 'a';
    char y = 'b';
    char *z;
    printf("Endereco de x: %u\n", (unsigned long long)&x);
    printf("Endereco de y: %u\n", (unsigned long long)&y);
    z = &x;
    printf("%c\n", *z);
    z++;
    printf("%c\n", *z);
    z--;
    printf("%c\n", *z);
    return 0;
}
 
```

[Ponteiros] O quanto é incrementado/decrementado depende do tipo de ponteiro:
```c
#include<stdio.h>
 
int main() {
    int x = 123;
    int y = 456;
    int *z;
    printf("Endereco de x: %llu\n", (unsigned long long)&x);
    printf("Endereco de y: %llu\n", (unsigned long long)&y);
    z = &x;
    printf("%d\n", *z);
    z++;
    printf("%d\n", *z);
    z--;
    printf("%d\n", *z);
    return 0;
}
 
```
Vetores e ponteiros são semelhantes: 
```c
#include<stdio.h>
 
int main() {
    int v[3];
    int *x;
    v[0]=123;
    v[1]=456;
    v[2]=789;
    x = v;
    printf("x[0]=%d\n",x[0]);
    printf("x[1]=%d\n",x[1]);
    printf("x[2]=%d\n",x[2]);
    return 0;
}
```

```c
#include<stdio.h>
 
int main() {
    int v[3];
    int *x;
    v[0]=123;
    v[1]=456;
    v[2]=789;
    x = v;
    printf("*x=%d\n",*x);
    x++;
    printf("*x=%d\n",*x);
    x++;
    printf("*x=%d\n",*x);
    x++;
    return 0;
}
```

[Ponteiros] Para passar um vetor como parâmetro, basta passar um ponteiro para a primeira posição: 
```c
#include<stdio.h>
 
void muda(int *x) {
    x[0]=111;
    x[1]=222;
}
 
int main() {
    int a = 1;
    int b = 2;
    printf("%d %d\n", a, b);
    muda(&a);
    printf("%d %d\n", a, b);
    return 0;
}
```

[Ponteiros] Usando ponteiros, é fácil criar um vetor com coordenadas negativas: 
```c
#include<stdio.h>
 
int main() {
    int v[3] = {12,34,56};
    int *x;
    x = v;
    x++;
    printf("x[-1]=%d\n", x[-1]);
    printf("x[0]=%d\n", x[0]);
    printf("x[1]=%d\n", x[1]);
    return 1;
}
```
O seguinte código é válido no C99, mas não no C90 (mas o gcc aceita como uma extensão:

```c
#include<stdio.h>
 
int main() {
    int n;
    scanf("%d", &n);
    char v[n];
    return 0;
}
```

Em C90, usamos o malloc (incluir stdlib.h):
```c
#include<stdio.h>
 
int main() {
    int n;
    char *v;
    scanf("%d", &n);
    v = (char *)malloc(n);
    return 0;
}
```
O malloc devolve um ponteiro do tipo "void *", assim nós fazemos um cast para o nosso tipo de ponteiro (char *). O parâmetro passado para o malloc é o número de bytes que queremos alocar. Mas quando não sabemos quantos bytes precisamos para um tipo podemos usar a função sizeof(tipo):

```c
#include<stdio.h>
#include<stdlib.h>
 
int main() {
    int n;
    int *v;
    scanf("%d", &n);
    v = (int *) malloc(sizeof(int)*n);
    return 0;
}
```

A função free(x) libera o espaço alocado para x: 
```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
 
int main() {
    int n, i;
    int *x;
    scanf("%d", &n);
    x = (int *) malloc(sizeof(int)*n);
    for(i=0; i<n; i++) x[i]=i*i;
    for(i=0; i<n; i++) printf("%d\n", x[i]);
    free(x);
    scanf("%d", &n);
    x = (int *) malloc(sizeof(int)*n);
    for(i=0; i<n; i++) x[i]=i*i*i;
    for(i=0; i<n; i++) printf("%d\n", x[i]);
    free(x);
    return 0;
}
```