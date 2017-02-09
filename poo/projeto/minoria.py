 # -*- coding: utf-8 -*-
from __future__ import division
import random


def create_random_history(length):
    """Cria uma lista de tamanho `length' com valores aleatórios sorteados
    do conjunto {-1, 1}.
    
    Parametros:
    length (int): comprimento da lista a ser criada.
    
    Devolve:
    Uma lista de tamanho length
    """
    result = [random.choice([-1, 1]) for i in range(length)]
    return result

class Game(object):
    """Implementa um novo jogo.
    
    Para utilizar esta classe na simulação de um jogo é preciso seguir os seguintes
    passos, na ordem em que são apresentados abaixo:
    (a) Criar um objeto do tipo Game, com um determinado tamanho de histórico t.
    (b) Usar o método add_agent do objeto recém criado para adicionar novos 
    agentes (devem ser instâncias de subclasses de Agent).
    (c) Chamar o método play_round repetidamente até completar o número 
    especificado de rodadas.
    Ao final desse processo, o atributo prices do objeto do tipo Game vai conter
    uma lista com o valor do preço da mercadoria ao final de cada rodada.
    Os métodos volatility e mean_price podem ser usados para recuperar o valor 
    da volatilidade do preço e o valor médio do preço ao final da simulação.
    """
    def __init__(self, history_length):
        """Inicialização do objeto.
        
        Parâmetros:
        history_length (int): Determina comprimento do histórico das ordens.
        """    
        self.history_length = history_length
        # histórico de preços, o preço inicial é determinado como zero.
        self.prices = [0]
        # lista interna de agentes, inicialmente vazia
        self.agents = []
        # no inicio não há historico para se armazenar, estamos criando um 
        # histórico aleatório fictício para preenchimento
        self.history = create_random_history(history_length)
        # numero de rodadas já executadas
        self.number_of_rounds = 0
        # objeto que acumula estatísticas do preço ao longo da simulação
        self.stat = RunningStat()
        
    def add_agent(self, new_agent):
        """Adiciona um novo agente.
        
        Parametros:
        new_agent (Agent): um agente do jogo de minoria.
        """
        if new_agent in self.agents:
            raise ValueError("Tentativa de adicionar um agente já existente ao jogo!")
        self.agents.append(new_agent)
        real_len = len(self.history)
        _len = min(real_len, self.history_length)
        # Fornece uma cópia do histórico mais recente para o agente.
        # Somente deve transmitir para o agente o histórico mais recente
        # de comprimento history_length (ou menor, caso não tenham ocorrido
        # ainda rodadas suficientes).       
        new_agent.set_history(self.history[real_len-_len:real_len][:])
        
    def play_round(self):
        """Executa uma rodada da simulação.
        Ao ser chamado, este método executa as seguintes ações:
        (1) Solicita o valor da ordem (compra ou venda) a todos os agentes 
            registrados no momento.
        (2) Calcula o valor agregado das ordens.
        (3) Calcula o novo preço da mercadoria e armazena no histórico.
        (4) Determina qual é a ordem (compra ou venda) vencedora da rodada.
        (5) Informa a todos os agentes registrados o valor agregado das ordens
            e qual foi a ordem vencedora na rodada (compra ou venda).
        (6) Atualiza o cálculo do preço médio e da volatilidade (variância do preço).
        """
        aggregate_bid = sum((ag.get_bid() for ag in self.agents))
        last_price = self.prices[-1]
        self.prices.append(last_price + aggregate_bid)
        if aggregate_bid > 0:
            winning_bid = -1
        else:
            winning_bid = 1
        # faz o update de todos os agentes registrados    
        for ag in self.agents:
            ag.update(aggregate_bid, winning_bid)
        self.stat.push(aggregate_bid)
        self.history.append(winning_bid)
        self.number_of_rounds += 1
        
    def volatility(self):
        """Devolve a volatilidade (variância) do preço até o momento.
        """
        return self.stat.variance()
        
    def mean_price(self):
        """Devolve o valor médio do preço até o momento.
        """
        return self.stat.mean()
        
class Agent(object):
    """
    Classe base para implementação de agentes em uma simulação de
    jogo de minoria.
    
    Essa classe não deve ser usada diretamente. Em vez disso, as 
    classes concretas que implementam estratégias de jogo devem
    herdar da classe Agent e implementar seu próprio método de 
    realizar ordens (get_bid).
    """
    
    def __init__(self, history_length, agent_type="Null"):
        """
        Inicia os campos básicos do agente. Subclasses de Agent devem
        chamar este método em seu próprio método __init__ usando a 
        função super.
        
        Parametros:
        history_length (int): tamanho de histórico que este agente vai usar.
        agent_type (str): um nome para identificar este agente (opcional).
        """
        # Este atributo guarda a última ordem efetuada por este agente. 
        # É essencial que o método get_bid atualize o valor deste atributo
        # toda vez que uma ordem seja efetuada.
        self.last_bid = None 
        self.agent_type = agent_type
        self.history_length = history_length
        # O atributo seguinte armazena o histórico de recompensas (scores)
        # recebidos por este agente.
        self.scores = []
        self.history = []

    def total_score(self):
        """Calcula a recompensa total (isto é, a soma dos scores)
        recebida pelo agente desde o início até este ponto do jogo.
        
        Devolve:
            Soma dos scores (int).
        """         
        return sum(self.scores)

    def set_history(self, history):
        """Preenche o histórico do jogo.
        
        Parametros:
        history (sequência): Uma sequência com o histórico recente de ordens
            vencedoras. A ordem mais antiga (instante t-M) está na primeira
            posição da sequência. A ordem mais recente (instante t-1) fica na 
            última posição da sequência.
        Devolve:
            Nada.
        """        
        # makes a copy of input parameter so it will not be overwritten
        # by external users
        self.history = history[:]

    def update(self, aggregate_score, winning_bid):
        """Atualiza o histórico de jogo e as recompensas obtidas pelo agente.
        
        Parametros:
        aggregate_score (int): o valor de ordens agregadas obtido rodada mais
        recente da simulação.
        winning_bid (int): indica qual ordem foi vencedora na rodada mais 
        recente da simulação. Pode ser +1 ou -1.
        
        Devolve:
        Nada.
        """
        self.history.pop(0)
        self.history.append(winning_bid)
        self.scores.append(-1*self.last_bid*aggregate_score)
        

    def get_bid(self):
        """Este método deve ser sobreescrito pelas subclasses de Agent.
        A função do método é calcular ordem a ser realizada pelo agente
        na rodada atual.
        
        É importante que este método atualize o valor do parâmetro last_bid
        antes de retornar.
        
        Devolve:
            Ou +1 (ordem de compra) ou -1 (ordem de venda).
        """         
        raise NotImplemented("Should be properly implemented in subclasses.")

class RunningStat:
    """O propósito desta classe é calcular a média e a variância de
    uma determinada medida de maneira *corrida*. Isto é, novos valores
    da medida vão sendo acrescentados ao longo do tempo; em cada instante,
    este objeto será capaz de fornecer os valores de média e variância da medida,
    considerando os valores armazenados até o momento.
    
    Adaptado de:
    http://http://www.johndcook.com/standard_deviation.htm
    
    """
    def __init__(self):
        self.m_n = 0
        self.m_oldM = 0.0
        self.m_newM = 0.0
        self.m_oldS = 0.0
        self.m_newS = 0.0        

    def clear(self):
        self.m_n = 0

    def push(self, x):
        self.m_n += 1
        # See Knuth TAOCP vol 2, 3rd edition, page 232
        if (self.m_n == 1):     
            self.m_oldM = x
            self.m_newM = x
            self.m_oldS = 0.0    
        else:        
            self.m_newM = self.m_oldM + (x - self.m_oldM)/self.m_n
            self.m_newS = self.m_oldS + (x - self.m_oldM)*(x - self.m_newM)    
            # set up for next iteration
            self.m_oldM = self.m_newM 
            self.m_oldS = self.m_newS
           
    def num_data_values(self): 
        return self.m_n
        
    def mean(self):
        if self.m_n > 0:
            result = self.m_newM
        else:
            result = 0.0
        return result
    
    def variance(self):  
        if self.m_n > 1:
            result = self.m_newS/(self.m_n - 1)
        else:
            result = 0.0
        return result