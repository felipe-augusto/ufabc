# -*- coding: utf-8 -*-

import random

class Fila(object):
    """
    Implementa uma fila simples (o primeiro a entrar Ã© o primeiro a sair)  
    que pode receber qualquer tipo de objeto.
    
    """
    
    def __init__(self):
        self.data = []

    def insere(self, elemento):
        elemento.na_fila = True
        self.data.append(elemento)
        
    def retira(self):
        elem = self.data.pop(0)
        return elem
      
    def vazia(self):
        """Devolve True se fila vazia, False do contrÃ¡rio"""
        return len(self.data) == 0
        
    def tamanho(self):
        """Devolve a quantidade de objetos ainda guardados na fila. """
        return len(self.data)
        
        
class Caixa(object):
    """
    Implementa o comportamento de caixa para simulaÃ§ao de fila de banco.
    """
    def __init__(self):
        self.fim_atendimento = 0
    
    def livre(self, instante):
        """Devolve True se o caixa estÃ¡ livre para receber um novo cliente,
        False do contrÃ¡rio.
        """
        return instante > self.fim_atendimento
    
    def atende(self, cliente, instante):
        """Tenta atender um cliente em determinado instante de tempo.
        
        cliente: objeto do tipo cliente a ser atendido
        instante: instante de tempo em que o atendimento se inicia

        Devolve True caso o caixa consiga atender o cliente, False do contrÃ¡rio.

        """       
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
        duracao_atendimento: duraÃ§Ã£o do procedimento que o cliente deseja
        realizar no banco.
        """
        self.instante_chegada = instante_chegada
        self.duracao_atendimento = duracao_atendimento
        self.instante_atendimento = -1
        self.espera = -1 # contabiliza o tempo de espera do cliente
        self.atendido = False
        self.na_fila = False
        
    def atende(self, instante_atendimento):
        """
        Esse mÃ©todo deve ser chamado pelo objeto que coordena a simulaÃ§Ã£o.
        
        instante_atendimento: instante em que o caixa atende o cliente.
        
        Esse mÃ©todo calcula o valor da espera total do cliente.
        """
        self.atendido = True
        self.instante_atendimento = instante_atendimento
        self.espera = instante_atendimento - self.instante_chegada
        
class DistribuicaoClientes(object):
    """ResponsÃ¡vel por criar um sequÃªncia de clientes, de acordo com uma 
    distribuiÃ§Ã£o probabilistica.
    
    """
    def __init__(self, intervalo_medio, duracao_media):
        # intervalo medio entre um cliente e outro
        self.duracao_minima = 60 # duracao minima de um atendimento
        
        # intervalo medio entre chegadas de clientes consecutivos
        self.intervalo_medio = intervalo_medio 
        
        # duracao mÃ©dia do atendimento dos clientes
        self.duracao_media = duracao_media
        
    def cria_clientes(self, tempo_maximo):
        """
        Cria uma lista de clientes, ordenada por instante de chegada
        """
        clientes = []
        tempo = 0        
        while tempo < tempo_maximo:
            # distribuiÃ§Ã£o uniforme dos intervalos entre
            # chegada de clientes -- nÃ£o Ã© um modelo 
            # realista, escolhido por simplicidade
            delta_t = random.randint(0, 2*self.intervalo_medio)
            # distribuiÃ§Ã£o uniforme dos tempos de atendimento
            # dos clientes -- nÃ£o Ã© um modelo 
            # realista, escolhido por simplicidade
            duracao_max = 2*self.duracao_media - self.duracao_minima
            atendimento = random.randint(self.duracao_minima, duracao_max)
            # print tempo + delta_t
            cl = Cliente(tempo + delta_t, atendimento)
            tempo += delta_t
            clientes.append(cl)
        return clientes


def calcula_max(clientes):
    """Recebe uma sequÃªncia de clientes que jÃ¡ foram atendidos e calcula os
    valores mÃ¡ximos de espera e tempo de atendimento.
    
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
    """Recebe uma sequÃªncia de clientes que jÃ¡ foram atendidos e calcula os
    valores mÃ©dios de espera e tempo de atendimento.
    
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


class Simula():
    def __init__(self):
        # constroi
        self.intervalo_medio = int(raw_input("Digite o intervalo medio de chegada dos clientes:\n"))
        self.duracao_media = int(raw_input("Digite a duração média de atendimento dos clientes:\n"))
        self.tempo_maximo = int(raw_input("Digite o tempo maximo:\n"))
        # cria a lista de clientes
        self.clients = DistribuicaoClientes(self.intervalo_medio, self.duracao_media).cria_clientes(self.tempo_maximo)
        # cria caixas de atendimento
        self.num_caixas  = int(raw_input("Com quantos caixas você deseja simular:\n"))
        self.caixas = []
        for i in range (0, self.num_caixas):
            self.caixas.append(Caixa())
        # cria fila
        self.fila = Fila()

    def inicia (self):
        contador = 0
        # or not self.fila.vazia() -> pode causar erros caso o intervalo de chegada seja menor que a duracao media
        # cai num loop infinito
        while (contador < self.tempo_maximo):

            # verifica o tempo atual e o do cliente
            for client in self.clients:
                # insere todos os clientes com tempo de chegada menor que o contador
                # verifica se nao esta na fila e se ja nao foi atendido
                # nao posso remover porque os calculos de tempo dependem dos clientes
                if (client.instante_chegada <= contador) and not client.na_fila and not client.atendido:
                    self.fila.insere(client)

            # verifica se o caixa esta livre
            for caixa in self.caixas:
                # sabe se o caixa esta livre pelo contador (!?)
                if caixa.livre(contador):
                    # tenta pegar o primeiro da fila e o atende
                    # caso nao haja ninguem na fila passa direto
                    try:
                        primeiro_fila = self.fila.retira()
                        caixa.atende(primeiro_fila, contador)
                    except:
                        pass

            contador += 1

        return {"maximos" : calcula_max(self.clients), "medias": calcula_medias(self.clients)}
