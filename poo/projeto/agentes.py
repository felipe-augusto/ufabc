# -*- coding: utf-8 -*-
"""
Created on Thu Aug 04 08:20:04 2016

@author: carlos.ssantos
"""
import minoria
import random


class AgentePeriodico(minoria.Agent):
    """Agente que joga periodicamente a mesma 
    sequencia.
    """
    def __init__(self, history_length):
        super(AgentePeriodico, self).__init__( history_length, "Periodico")
        self.sequencia = [-1, -1, 1, -1, 1]
        self.indice = 0
        
    def get_bid(self):
        """
        Calcula ordem a ser realizada pelo agentena rodada atual.
        
        Devolve: A ordem baseada na rodada da sequencia fixa estipulada previamente.
        """
        ind = self.indice
        bid = self.sequencia[ind]
        self.indice = (ind + 1) % len(self.sequencia)
        ### IMPORTANTE: é preciso atualizar o valor
        ### de self.last_bid antes de retornar
        self.last_bid = bid
        return bid


class AgenteAleatorio(minoria.Agent):
    """Agente que joga aleatoriamente
    """
    def __init__(self, history_length):
        super(AgenteAleatorio, self).__init__( history_length, "Aleatorio")
        
    def get_bid(self):
        """
        Calcula ordem a ser realizada pelo agentena rodada atual.
        
        Devolve: Uma ordem aleatoria
        """
        bid = random.randint(0,1) *2 -1
        self.last_bid = bid
        return bid


class AgenteHistorico(minoria.Agent):
    """Agente que utiliza do historico para tomar decisoes
    """
    def __init__(self, history_length):
        super(AgenteHistorico, self).__init__( history_length, "Historico")
        self.type = None;
        
    def get_bid(self):
        """Varia as estragerias, pois se todos os agentes utilizarem a mesma estrategia,
            todos no final acabariam perdendo.
        """
        estrategias = [self.aleatorio for i in range(0,2)]
        estrategias.append(self.majority)
        # chama uma estrategia aleatoriamente
        self.last_bid = random.choice(estrategias)()
        return self.last_bid

    def majority(self):
        """ Estrategia que verifica se houve mais compras ou vendas na historia,
        se houve mais vendas o agente compra e se houve mais vendes o agente compra.
        Se o numero for igual a decisao tomada e aleatoriamente
        """
        self.type = 'majority'
        tmp = 0
        for i in self.history:
            tmp += i
        if tmp > 0: # mais pessoas compraram, entao temos que vender
            bid = -1
        if tmp < 0: # mais pessoas venderam, entao temos que comprar
            bid = 1
        if tmp == 0: # igual o numero de compra e venda -> joga o inverso da ultima
            bid = self.history[-1] * -1
        return bid
    
    def latest_bid(self):
        self.type = 'latest_bid'
        """ Estrategia que verifica o ultimo bid da historia e faz exatamente a mesma coisa """
        if self.history[-1] == -1:
            return -1
        else:
            return 1
        
    def aleatorio(self):
        self.type = 'aleatorio'
        """ Estrategia aleatoria """
        return random.randint(0,1) *2 -1
