#include<iostream>
#include<string.h>
#include<stdlib.h>

// video que ajuda https://www.youtube.com/watch?v=xoU69C4lKlM

using namespace std;

typedef struct No *Apontador;

typedef struct No {
	int chave;
	Apontador dir,esq;
	} NoArvore;

NoArvore* insere(int chave, Apontador p);
NoArvore* busca(int chave, Apontador p);
// void lista(int caso);
void listaPaiFilhos(Apontador p);
void inorder(Apontador p);
void preordem(Apontador p);
void posordem(Apontador p);
int calculaAltura(Apontador p);

int main(){
	Apontador raiz=NULL;
	raiz = insere(7, raiz);
	insere(1, raiz);
	insere(9, raiz);
	insere(0, raiz);
	insere(3, raiz);
	insere(2, raiz);
	insere(5, raiz);
	insere(4, raiz);
	insere(6, raiz);
	insere(8, raiz);
	insere(10, raiz);
	cout << "\n ÁRVORE RESULTANTE: \n \n";
	listaPaiFilhos(raiz);
	cout << "Altura: " << calculaAltura(raiz) << endl;
	cout << "Busca (retorna o numero caso encontre):" << busca(10, raiz)->chave << endl; // segmentation fault caso NULL
	cout << "Simetrico: ";
	inorder(raiz);
	cout << endl;
	cout << "Pre-ordem: ";
	preordem(raiz);
	cout << endl;
	cout << "Pos-ordem: ";
	posordem(raiz);
	cout << endl;

	return(0);
}

// insere um nó na ABB
NoArvore* insere(int chave, Apontador p) {
	if (p == NULL) {
		cout << "INSERINDO: "<< chave << "\n";
		p = (Apontador) malloc(sizeof(NoArvore));
		p->chave=chave;
		p->esq = NULL;
		p->dir = NULL;
	} else if (chave < p->chave) {
		p->esq = insere(chave, p->esq);
	} else if (chave > p->chave) {
		p->dir = insere(chave, p->dir);
	} else cout << "Erro! Chave já existente!";
	return p; // devolve o proprio apontador para a raiz da arvore
}

// procura uma chave na ABB
NoArvore* busca(int chave, Apontador p) {
	if (p == NULL) {
		return NULL;
	} else if (chave < p->chave) {
		return busca(chave, p->esq);
	} else if (chave > p->chave) {
		return busca(chave, p->dir);
	} else return p;
}

void listaPaiFilhos(Apontador p) {
	if (p != NULL) {
		int esq = -1, dir = -1;
		if (p->esq != NULL) {
			esq = p->esq->chave;
		}
		if (p->dir != NULL) {
			dir = p->dir->chave;
		}
		cout << "Pai: " << p->chave << ", nó esq: " << esq << ", nó dir: " << dir << "\n";
		listaPaiFilhos(p->esq); // chama o método para imprimir a subárvore esquerda
		listaPaiFilhos(p->dir); // chama o método para imprimir a subárvore direita
	}
}

// lista todas as chaves da ABB em modo simétrico
void inorder(Apontador p) {
	if (p != NULL) {
		inorder(p->esq);
		cout << p->chave << ",";
		inorder(p->dir);
	}

}

// lista todas as chaves da ABB em modo pré-ordem
void preordem(Apontador p) {
	if(p != NULL) {
		cout << p->chave << ",";
		preordem(p->esq);
		preordem(p->dir);
	}

}

// lista todas as chaves da ABB em modo pós-ordem
void posordem(Apontador p) {
	if(p != NULL) {
		posordem(p->esq);
		posordem(p->dir);
		cout << p->chave << ",";
	}

}
	
// calcula a altura da ABB
int calculaAltura(Apontador p){	
	if (p==NULL){
		return 0;
	} else {
		int esq = calculaAltura(p->esq);
		int dir = calculaAltura(p->dir);
		if (esq>dir) return esq+1;
		else return dir+1;
	}
}
