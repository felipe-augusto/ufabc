# -*- coding: utf-8 -*-

"""
Este modulo contém algumas classes voltadas ao problema de processar arquivos
de registros (ou arquivos de log). Esses são arquivos textuais onde cada linha
contém um registro diferente.

As classes FiltroPredicado e PredicadoAbstrato são usadas para implementar a
função de filtrar linhas de um arquivo de entrada com base em um determinado
critério. Dado um arquivo de entrada, o objetivo aqui é gerar um arquivo de 
saída contendo o subconjunto das linhas do arquivo de entrada que atendem a
um determinado predicado. 

A classe FiltroPredicado implementa a funcão de percorrer o arquivo de entrada,
testar se cada linha atende ao predicado desejado e escrever no arquivo de 
saída somente as linhas em que o predicado é avaliado como verdadeiro.

O teste do predicado em si é implementado em uma classe diferente, que deve
herdar da classe mãe PredicadoAbstrato. A função dessa classe é apenas demarcar
a interface das classes que implementam predicados. Cada classe de predicado
concreta deve implementar o método verdadeiro(self, um_string) que recebe como
parâmetro um_string a ser testado e devolve os valores True ou False, 
dependendo se o string de entrada obecece ou não ao predicado desejado.

Como exemplo de predicado concreto, é fornecida a classe ComecaCom, que 
testa se o string de interesse começa ou não com um determinado padrão de 
caracteres determinado.

"""

class FiltroPredicado(object):
    """Filtro para conteúdo de arquivo com base em um predicado.
    """
    
    def __init__(self, predicado):
        """Parâmetros:
            predicado (descendente de PredicadoAbstrato): um objeto que 
            implementa um predicado, isto é, o objeto passado como parâmetro
            deve implementar o método verdadeiro(self, um_string)
        """
        self._predicado = predicado

    def filtrar(self, fonte, destino):
        """Lê o conteúdo de um arquivo fonte e escreve no arquivo destino as 
        linhas do arquivo fonte que obedecem ao predicado fornecido na 
        inicialização.
        
        Parâmetros:
            fonte (file): objeto do tipo arquivo, aberto para leitura, com o 
            conteúdo de entrada.
            destino (file): objeto do tipo arquivo, aberto para escrita, que 
            receberá o conteúdo de saída.
        """
        for linha in fonte:
            if self._predicado.verdadeiro(linha):
                destino.write(linha)


class PredicadoAbstrato(object):

    def __init__(self):
        """Método de inicialização vazio"""
        pass

    def verdadeiro(self, um_string):
        """Avalia se o predicado é válido para um determinado string.

        Este método deve ser implementado por todo as subclasses de
        PredicadoAbstrato

        Argumentos:
            um_string (str): String que será avaliado quanto ao predicado desejado.

        Devolve:
            True se o predicado é verdadeiro para umstring, False do contrário.
        """
        raise NotImplementedError("Método não implementado!")

class ComecaCom(object):
    """Predicado que avalia se um string começa com determinada sequência
    de caracteres.
    """
    def __init__(self, prefixo):
        """Inicialização
        
        Argumentos:
        prefixo (str): Sequência de caracteres que será usada para avaliar o predicado.
        """
        # Transforma parametro em string, caso não seja ainda;
        # essa ação visa evitar algum erro caso o tipo do argumento
        # prefixo seja diferente
        super(ComecaCom, self).__init__()
        self._prefixo = str(prefixo)

    def verdadeiro(self, um_string):
        """Avalia se um string se inicia com o prefixo passado no momento
        da inicialização desse objeto.
        
        Argumentos:
            umstring (string): String que será avaliado quando ao predicado.
            
        Devolve:
            True caso umstring comece com o prefixo passado na inicializaçao, 
            False caso contrário.
        """
        return um_string.startswith(self._prefixo)

