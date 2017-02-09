# -*- coding: utf-8 -*-
"""
Created on Thu Aug 04 08:44:19 2016

@author: carlos.ssantos
"""

import minoria
import agentes
from matplotlib import pylab as pl
import matplotlib.pyplot as plt
import numpy as np

HISTORY_LENGTH = 7
NUM_AGENTS = 41
NUM_ROUNDS = 51

volatility = []

jogo = minoria.Game(HISTORY_LENGTH)
for i in range(NUM_AGENTS):
    jogo.add_agent(agentes.AgenteHistorico(HISTORY_LENGTH))
for i in range(NUM_ROUNDS):
    jogo.play_round()
    volatility.append(jogo.volatility()) # pega a volatilidade da rodadas

# Registrar no final da simulacao os valores
# minimo, medio e maximo da recompensa total sobre os agentes
agents = [agent.total_score() for agent in jogo.agents]
values = {'minimo': str(min(agents)), 'maximo': str(max(agents)), 'media': str(np.mean(agents))}


# Plota nos graficoss
pl.plot(jogo.prices)
pl.plot(volatility)
pl.legend(['preco', 'volatilidade'], loc='lower left')
pl.xlabel('tempo')
pl.title('tamanho historico : ' + str(HISTORY_LENGTH) + ' | minimo : ' + values['minimo'] + ' \n maximo: ' + values['maximo'] + ' | media: ' + values['media'])
pl.show()

