# -*- coding: utf-8 -*-

import random

class Fila(object):
    """
    Implementa uma fila simples (o primeiro a entrar é o primeiro a sair)
    que pode receber qualquer tipo de objeto.

    """

    def __init__(self):
        self.data = []

    def insere(self, elemento):
        self.data.append(elemento)

    def retira(self):
        elem = self.data.pop(0)
        return elem

    def vazia(self):
        """Devolve True se fila vazia, False do contrário"""
        return len(self.data) == 0

    def tamanho(self):
        """Devolve a quantidade de objetos ainda guardados na fila. """
        return len(self.data)


class Caixa(object):
    """
    Implementa o comportamento de caixa para simulaçao de fila de banco.
    """
    def __init__(self):
        self.fim_atendimento = 0

    def livre(self, instante):
        """Devolve True se o caixa está livre para receber um novo cliente,
        False do contrário.
        """
        return instante > self.fim_atendimento

    def atende(self, cliente, instante):
        """Tenta atender um cliente em determinado instante de tempo.

        cliente: objeto do tipo cliente a ser atendido
        instante: instante de tempo em que o atendimento se inicia

        Devolve True caso o caixa consiga atender o cliente, False do contrário.

        """
        atendido = False
        if self.livre(instante):
            cliente.atende(instante)
            self.fim_atendimento = instante + cliente.duracao_atendimento
            atendido = True
        return atendido


class Cliente(object):
    """Implementa o comportamento do cliente do banco.
    """
    def __init__(self, instante_chegada, duracao_atendimento):
        """Parametros:
        instante_chegada: momento em que o cliente chega no banco.
        duracao_atendimento: duração do procedimento que o cliente deseja
        realizar no banco.
        """
        self.instante_chegada = instante_chegada
        self.duracao_atendimento = duracao_atendimento
        self.instante_atendimento = -1
        self.espera = -1 # contabiliza o tempo de espera do cliente
        self.atendido = False

    def atende(self, instante_atendimento):
        """
        Esse método deve ser chamado pelo objeto que coordena a simulação.

        instante_atendimento: instante em que o caixa atende o cliente.

        Esse método calcula o valor da espera total do cliente.
        """
        self.atendido = True
        self.instante_atendimento = instante_atendimento
        self.espera = instante_atendimento - self.instante_chegada

class DistribuicaoClientes(object):
    """Responsável por criar um sequência de clientes, de acordo com uma
    distribuição probabilistica.

    """
    def __init__(self, intervalo_medio, duracao_media):
        # intervalo medio entre um cliente e outro
        self.duracao_minima = 60 # duracao minima de um atendimento

        # intervalo medio entre chegadas de clientes consecutivos
        self.intervalo_medio = intervalo_medio

        # duracao média do atendimento dos clientes
        self.duracao_media = duracao_media

    def cria_clientes(self, tempo_maximo):
        """
        Cria uma lista de clientes, ordenada por instante de chegada
        """
        clientes = []
        tempo = 0
        while tempo < tempo_maximo:
            # distribuição uniforme dos intervalos entre
            # chegada de clientes -- não é um modelo
            # realista, escolhido por simplicidade
            delta_t = random.randint(0, 2*self.intervalo_medio)
            # distribuição uniforme dos tempos de atendimento
            # dos clientes -- não é um modelo
            # realista, escolhido por simplicidade
            duracao_max = 2*self.duracao_media - self.duracao_minima
            atendimento = random.randint(self.duracao_minima, duracao_max)
            chegada_ = tempo + delta_t
            if chegada_ < tempo_maximo:
                cl = Cliente(chegada_, atendimento)
                clientes.append(cl)
            tempo += delta_t    
        return clientes


def calcula_max(clientes):
    """Recebe uma sequência de clientes que já foram atendidos e calcula os
    valores máximos de espera e tempo de atendimento.

    Devolve uma tupla (espera_max, tempo_de_atendimento_max)
    """
    espera_max = 0
    tempo_max = 0
    for cl in clientes:
        if cl.duracao_atendimento > tempo_max:
            tempo_max = cl.duracao_atendimento
        if cl.espera > espera_max:
            espera_max = cl.espera
    return (espera_max, tempo_max)

def calcula_medias(clientes):
    """Recebe uma sequência de clientes que já foram atendidos e calcula os
    valores médios de espera e tempo de atendimento.

    Devolve uma tupla (espera_media, tempo_de_atendimento_medio)
    """
    contador = 0
    espera_acumulada = 0
    tempo_acumulado = 0
    for cl in clientes:
        contador += 1
        tempo_acumulado += cl.duracao_atendimento
        espera_acumulada += cl.espera
    espera_media = espera_acumulada/contador
    tempo_de_atendimento_medio = tempo_acumulado/contador
    return (espera_media, tempo_de_atendimento_medio)

