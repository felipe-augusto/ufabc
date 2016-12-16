#include<iostream>
#include<string.h>
#include<stdlib.h>

using namespace std;

// bal representa a diferença da altura das duas subárvores se = 0, a altura é igual
// se igual a 1, subárvore direita é maior (em um) do que a subárvore esquerda
// se igual a -1, subárvore esquerda é maior (em um) di qye a subárvore direita

typedef struct No {
  int chave;
  int bal;
  struct No *esq;
  struct No *dir;
} NoArvore;

NoArvore* insere(int chave, NoArvore *p); // modificar colocando os balanceamentos da AVL
NoArvore* busca(int chave, NoArvore *p);
NoArvore* caso1(NoArvore *p);
NoArvore* caso2(NoArvore *p);
void listaPaiFilhos(NoArvore *p);
void remove(int chave, NoArvore *p); // implementar com os balanceamentos da AVL



int main(){
	NoArvore *raiz=NULL;	

	raiz = insere(3, raiz);
	raiz = insere(12, raiz);
	raiz = insere(20, raiz); // ROTACAO SIMPLES
	raiz = insere(21, raiz);
	raiz = insere(18, raiz); // ROTACAO DUPLA

	cout << "\n ÁRVORE RESULTANTE: \n \n";
	listaPaiFilhos(raiz);

	return(0);
}

// insere um nó na AVL
NoArvore* insere(int chave, NoArvore *p) {
	if (p == NULL) {
		cout << "INSERINDO: "<< chave << "\n";
		p = new NoArvore;
		p->chave=chave;
		p->esq = NULL;
		p->dir = NULL;
		// implementacao
		p->bal = 0;	
	} else if (chave < p->chave) {
		p->esq = insere(chave, p->esq);
		// esquerda
		if (p->bal == 1) {
			p->bal = 0;
		} else if (p->bal == 0) {
			p->bal = -1;
		} else if (p->bal == -1) {
			cout << "REB ESQUERDA: " << p->chave << endl;
			p = caso1(p);
		}
	} else if (chave > p->chave) {
		p->dir = insere(chave, p->dir);
		// direita
		if (p->bal == -1) {
			p->bal = 0;
		} else if (p->bal == 0) {
			p->bal = 1;
		} else if (p->bal == 1) {
			p = caso2(p);
		}
	} else cout << "Erro! Chave já existente!";
	return p;
}

// procura uma chave na AVL
NoArvore* busca(int chave, NoArvore *p) {
	if (p == NULL) {
		return NULL;
	} else if (chave < p->chave) {
		return busca(chave, p->esq);
	} else if (chave > p->chave) {
		return busca(chave, p->dir);
	} else
	return p;
}

void listaPaiFilhos(NoArvore *p) {
	if (p != NULL) {
		int esq = -1, dir = -1;
		if (p->esq != NULL) {
			esq = p->esq->chave;
		}
		if (p->dir != NULL) {
			dir = p->dir->chave;
		}
		cout << "Pai: " << p->chave << ", nó esq: " << esq << ", nó dir: " << dir << " bal: " << p->bal <<"\n";
		listaPaiFilhos(p->esq); // chama o método para imprimir a subárvore esquerda
		listaPaiFilhos(p->dir); // chama o método para imprimir a subárvore direita
	}
}

NoArvore* caso1(NoArvore *p) {
	NoArvore *ptu = p->esq;
	if (ptu->bal == -1) {
		p->esq = ptu->dir;
		ptu->dir = p;
		p->bal = 0;
		p = ptu;
	} else {
		NoArvore *ptv = ptu->dir;
		ptu->dir = ptv->esq;
		ptv->esq = ptu;
		p->esq = ptv->dir;
		ptv->dir = p;
		if (ptv->bal == -1) {
			p->bal = 1;
		} else {
			p->bal = 0;
		}
		if (ptv->bal == 1) {
			ptu->bal = -1;
		} else {
			ptu->bal = 0;
		}
		p = ptv;
	}
	p->bal = 0;
	return p;
}

NoArvore* caso2(NoArvore *p) {
	NoArvore *ptu = p->dir;

	if (ptu->bal == 1) {
		p->dir = ptu->esq;
		ptu->esq = p;
		p->bal = 0;
		p = ptu;
	} else {
		NoArvore *ptv = ptu->esq;
		ptu->esq = ptv->dir;
		ptv->dir = ptu;
		p->dir = ptv->esq;
		ptv->esq = p;
		if (ptv->bal == 1) {
			p->bal = -1;
		} else {
			p->bal = 0;
		}
		if (ptv->bal == -1) {
			ptu->bal = 1;
		} else {
			ptu->bal = 0;
		}
		p = ptv;
	}
	p->bal = 0;
	return p;
}

// remove um nó na AVL
void remove(int chave, NoArvore *p) {
	
}
