# Lista de Exercício - Prova

##### **1. Qual é a principal propriedade de uma árvore binária de busca?**

Para cada nó pertencente à uma árvore binária de busca (onde cada um armazena uma chave distinta), vale que nenhum nó da subárvore à esquerda possui chave com valor maior do que a chave do nó, nem que nenhum nó da subárvore à direita possua chave com valor menor que a chave do nó.

Definição formal:

* T possui n nós. Cada nó u armazena uma chave distinta;
* Para cada nó v de T: r(v1) < r(v) e r(v2) > r(v), onde v1 pertence à subárvore esquerda de v e v2 pertence à subárvore direita de v.

##### **2. Escreva os algoritmos recursivos para percorrer uma árvore binária de busca na forma: in-ordem, pré-ordem e pós-ordem.**

```c++
// lista todas as chaves da ABB em modo simétrico (in-order)
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
```

##### **3. Escreva um algoritmo recursivo para calcular a altura de uma árvore binária. Dica: utilize um dos algoritmos do exercício anterior.**

```c++
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
```

##### **4. Escreva um algoritmo recursivo que imprima as chaves de uma árvore binária de busca em ordem crescente.**

O algortimo in-order mostrado no exercício 2 imprime as chaves de uma árvore binária de busca em ordem crescente.

##### **5. Escreva um algoritmo recursivo que procura uma chave *x* em uma árvore binária de busca. No máximo quantas comparações o algoritmo fará se a árvore é degenerada? No máximo quantas comparações fará se a árvore for balancedada. Justifique.**

```c++
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
```

Lembrando que uma **árvore degenerada** é aquela em que cada nó possui apenas um filho, portanto sua altura é igual o número de nós (na prática uma lista ligada). **FALTA DEFINIÇÃO DE BALANCEADA AQUI.**

Para uma árvore degenerada fará **n** (número de nós) comparações, já para uma árvore balançeada fará **floor(log n + 1)**.

