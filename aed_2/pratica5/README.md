# Roteiro da Aula Prática 5

Nossa atividade prática é baseada no exercício 16 (página 220) do livro do Ziviani. Vamos implementar algoritmos para a criação de um índice remissivo.

1. O programa deverá ler um arquivo texto contendo um texto e palavras-chave que compõem o vocabulário. Um modelo do arquivo texto está disponível na atividade da Prática 5;

2. O programa deverá construir uma tabela *hash* usando como chaves as palavras do vocabulário. Utilize na função *hash* o método da divisão (cuidado com a escolha de m). Escolha um método de tratamento de colisões dentre aqueles discutidos em sala de aula;

3.  O programa deverá construir uma árvore *trie* usando como chaves as palavras do vocabulário. Utilize, neste passo, a árvore trie já implementada
na disciplina. Para isso, restringimos o texto e as palavras-chave à língua inglesa, para utilizarmos somente as 26 letras do alfabeto sem acentuação;

4. A tabela hash deve armazenar em quais linhas cada palavra do vocabulário se encontra no texto;

5. O programa deve ter as seguintes funções:

	* **busca de uma palavra do índice remissivo:** dada uma palavra, o programa retorna as linhas onde a palavra se encontra no texto;

	* **impressão do índice remissivo em ordem lexicográfica:**  o programa imprime todas as palavras-chave em ordem lexicográfica, cada qual com as linhas em que a palavra ocorre no texto;
