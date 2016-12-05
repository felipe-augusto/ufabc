# Consulta para prova 2

Exemplo de criação e como acessar os dados dentro de uma struct:
```c
#include<stdio.h>
struct ponto {
    int x;
    int y;
};
 
int main() {
    struct ponto p;
    p.x = 2;
    p.y = 3;
    printf("x=%d y=%d\n",p.x,p.y);
    return 0;
}
```

Outras formas de inicializar a struct (só para a declaração):
```c
#include<stdio.h>
struct ponto {
    int x;
    int y;
};
 
int main() {
    struct ponto p = {2,3};
    printf("x=%d y=%d\n",p.x,p.y);
    return 0;
}
```
ou
```c
#include<stdio.h>
struct ponto {
    int x;
    int y;
};
 
int main() {
    struct ponto p = {.x=2,.y=3};
    printf("x=%d y=%d\n",p.x,p.y);
    return 0;
}
```

Usando o comando typedef: 
```c
#include<stdio.h>
 
typedef struct ponto_s {
    int x;
    int y;
} ponto;
 
int main() {
    ponto p = {2,3};
    printf("x=%d y=%d\n",p.x,p.y);
    return 0;
}
```

Podemos usar tipos diferentes dentro de uma struct: 
```c
#include<stdio.h>
typedef struct ponto_s {
    int x;
    int y;
    char* nome;
} ponto;
 
int main() {
    ponto p1 = {5,3,"casa"};
    ponto p2 = {5};
    printf("x=%d y=%d nome=%s\n",p1.x,p1.y,p1.nome);
    printf("x=%d y=%d nome=%s\n",p2.x,p2.y,p2.nome);
    return 0;
}
```

Podemos usar uma struct dentro de outra: 
```c
#include<stdio.h>
typedef struct ponto_s {
    int x;
    int y;
} ponto;
 
typedef struct circulo_s{
    ponto centro;
    double raio;
} circulo;
 
int main() {
    ponto p = {1,2};
    circulo c = {p,0.4};
    printf("Centro : " );
    printf("x=%d y=%d\n",c.centro.x,c.centro.y);
    printf("Raio: %lf\n", c.raio);
    return 0;
}
```

Um exemplo um pouco mais complexo: lista ligada
```c
#include<stdio.h>
#include<stdlib.h>
 
typedef struct node_s {
    int val;
    struct node_s *prox;
} node;
 
int imprime(node *lista) {
    for(;lista; lista = lista->prox) printf("%d\n", lista->val);
}
 
node * insere(node *lista, int val){
    node *novo = malloc(sizeof(node));
    printf("Inserindo %d\n",val);
    novo->val = val;
    novo->prox = lista;
    return novo;
}
 
int main() {
    node *first = NULL;
    int i;
    for(i=0; i<4; i++) {
        first = insere(first,i);
    }
    imprime(first);
}
```

Pilha:
```c
#include<stdlib.h>

typedef struct fp_s {
    int topo; 
    int n; //capacidade
    int *v;
} fp;

/*retorna 1 se f eh vazio e 0 caso contrario*/
int is_empty(fp *f) {
    if(f->topo==0) return 1;
    else return 0;
}

/*retorna 1 se f esta cheio e 0 caso contrario*/
int is_full(fp *f) {
    if(f->topo == f->n) return 1;
    return 0;
}

/*retorna um ponteiro para fp*/
fp *create_fp(int n) {
    fp *f = malloc(sizeof(fp));
    f -> n = n;
    f -> topo = 0;
    f -> v = malloc(sizeof(n));
    return f;
}

/*retira e retorna um elemento de f*/
/*devolve -1 se f estiver vazio*/
/*deve retirar o ultimo elemento a ser adicionado*/
int retira(fp *f) {
    int i = -1;
    if(!is_empty(f)) {
        i = f->v[f->topo-1];
        f->topo--;
    }
    return i;
}

/*insere val em f*/
/*retorna 1 se a insercao foi bem sucedida*/
/*0 caso contrario*/
int insere(int val, fp *f) {
    if(!is_full(f)) {
        f->v[f->topo++] = val;
    } else {
        return 0;
    }
}
```

Fila:
```c
#include<stdlib.h>

typedef struct fp_s {
    int primeiro;
    int ultimo;
    int n;
    int *v;
} fp;


/*retorna 1 se f eh vazio e 0 caso contrario*/
int is_empty(fp *f) {
    if(f->primeiro==f->ultimo) return 1;
    else return 0;
}

/*retorna 1 se f esta cheio e 0 caso contrario*/
int is_full(fp *f) {
    if(f->primeiro==f->ultimo+1 || f->primeiro==0 && f->ultimo==f->n-1) return 1;
    return 0;
}

/*retorna um ponteiro para fp*/
fp *create_fp(int n) {
    fp *f = malloc(sizeof(fp));
    f -> n = n+1;
    f -> primeiro = 0;
    f -> ultimo = 0;
    f -> v = malloc(sizeof(n+1));
    return f;
}

/*retira e retorna um elemento de f*/
/*devolve -1 se f estiver vazio*/
/*deve retirar o primeiro elemento a ser adicionado*/
int retira(fp *f) {
    int i = -1;
    if(!is_empty(f)) {
        i = f->v[f->primeiro];
        f->primeiro++;
        (f->primeiro) = (f->primeiro)%(f->n);
    }
    return i;
}

/*insere val em f*/
/*retorna 1 se a insercao foi bem sucedida*/
/*0 caso contrario*/
int insere(int val, fp *f) {
    if(!is_full(f)) {
        f->v[f->ultimo++] = val;
        (f->ultimo) = (f->ultimo)%(f->n);
    } else {
        return 0;
    }
}
```

Graph
```c
#include<stdio.h>
#include<stdlib.h>

typedef struct graph_s {
    int n;
    int **adj;
} graph;

int get_n(graph *g) {
    return g->n;
}

graph *create_graph(int n) {
    int i,j;
    graph *g = malloc(sizeof(graph));
    g->n = n;
    g->adj = malloc(n*sizeof(int *));
    for(i=0; i<g->n; i++) {
        g->adj[i] = malloc(n*sizeof(int));
    }
    for(i=0; i<g->n; i++)
        for(j=0; j<g->n; j++)
            g->adj[i][j]=0;
    return g;
}

int *neighbours(graph *g, int v) {
    int *lista;
    int s = 0;
    int i, j;
    for(i=0; i<get_n(g); i++) 
        if(g->adj[v][i]==1) s++;
    lista = malloc(sizeof(int)*-(s+1));
    j = 0;
    for(i=0; i<get_n(g);i++) {
        if(g->adj[v][i]==1) {
            lista[j++]=i;
        }
    }
    lista[j] = -1;
    return lista;
}

void add_edge(int u, int v, graph *g) {
    g->adj[u][v]=1;
    g->adj[v][u]=1;
}

void print_graph(graph *g) {
    int i, j;
    int *lista;
    printf("Grafo tem %d vertices\n", g->n);
    for(i=0; i<g->n; i++) {
        lista = neighbours(g, i);
        for(j=0; lista[j] != -1; j++) {
            if(lista[j]>i) printf("Aresta %d %d\n", i, lista[j]);
        }
        free(lista);
    }
}
```

Busca Graph:
```c
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "fp.h"

void busca (graph *g);

int main() {
    graph *g = create_graph(7);
    add_edge(0,1,g);
    add_edge(1,2,g);
    add_edge(0,2,g);
    add_edge(1,4,g);
    add_edge(3,5,g);
    add_edge(5,6,g);
    add_edge(4,6,g);
    print_graph(g);
    busca(g);
}

void busca(graph *g){
    fp *fila = create_fp(get_n(g));
    int *achei = malloc(sizeof(int)*get_n(g));
    int *pai = malloc(sizeof(int)*get_n(g));
    insere(0, fila);
    achei[0]=1;
    while(!is_empty(fila)){
        int u = retira(fila);
        int *lista = neighbours(g,u);
        for(int j=0; lista[j]!=-1; j++){
            int w = lista[j];
            if(!achei[w]){
                achei[w]=1;
                pai[w]=u;
                insere(w,fila);
            }
        }
    }
    for(int j = 1; j<get_n(g); j++)
        printf("%d",pai[j]);
}

```

Aluno:
```c
#include<stdio.h>
#include<stdlib.h>

typedef struct aluno_s {
  int ra;
  int ano;
  double nota;
} aluno;

/*cria um aluno com RA ra, ano de ingresso ano e nota na P1 nota*/
aluno *cria_aluno(int ra,  int ano, double nota) {
  aluno *a = malloc(sizeof(aluno));
  a->ra = ra;
  a->ano = ano;
  a->nota = nota;
  return a;
}

/*aloca um vetor de n alunos, as informacoes nao sao preenchidas*/
aluno **aloca_classe(int n) {
  int i;
  aluno **a = malloc(sizeof(aluno*)*n);
  for(i=0; i<n; i++) a[i]=malloc(sizeof(aluno));
  return a;
}

/*modifica os dados do aluno para RA ra, ano de ingresso ano e nota na P1 nota*/
void modifica_aluno(aluno *a, int ra,  int ano, double nota) {
  a->ra = ra;
  a->ano = ano;
  a->nota = nota;
}

/*imprime as informaÃ§Ãµes do aluno*/
void imprime_aluno(aluno *a) {
  printf("RA:%d Ano:%d Nota:%.2lf\n", a->ra, a->ano, a->nota);
}

/*Recebe um vetor de n alunos e calcula a mÃ©dia das notas*/
double media(aluno **alunos, int n) {
  int i;
  double resp = 0;
  for(i=0; i<n;i++) resp += alunos[i]->nota;
  return resp/n;
}

int comp_nota(const void *a, const void *b) {
  aluno **aa = (aluno **) a;
  aluno **bb = (aluno **) b;
  return (*aa)->nota - (*bb)->nota;
}

int comp_ano(const void *a, const void *b) {
  aluno **aa = (aluno **) a;
  aluno **bb = (aluno **) b;
  return (*aa)->ano - (*bb)->ano;
}

/*Recebe um vetor de n alunos e o ordena em ordem crescente por nota*/
void ordena_nota(aluno **alunos, int n) {
  qsort(alunos, n, sizeof(aluno *), comp_nota);
}

/*Recebe um vetor de n alunos e o ordena em ordem crescente por ano*/
void ordena_ano(aluno **alunos, int n) {
  qsort(alunos, n, sizeof(aluno *), comp_ano);
}
```