# -*- coding: utf-8 -*-
import proctexto

entrada = "./entrada.txt"
saida = "./saida.txt"

# A linha seguinte cria um arquivo do tipo file (isto é, um ponto de acesso
# para um arquivo em disco), aberto para *leitura* (o parâmetro 'r' 
# corresponde a opção reading -- leitura). O arquivo precisa existir, do 
# contrário a chamada gera um erro.
fonte = open(entrada, 'r') 

# A linha seguinte cria um arquivo do tipo file (isto é, um ponto de acesso
# para um arquivo em disco), aberto para *escrita* (o parâmetro 'w' 
# corresponde a opção writing -- escrita). O arquivo não precisa existir em
# disco no momento da chamada. Caso o arquivo exista, seu conteúdo anterior
# será sobrescrito. É preciso chamar o método close() ao fim das operações 
# de escrita, do contrário o conteúdo pode não ser escrito no arquivo 
# corretamente
destino = open(saida, 'w')

# Cria um filtro que deixará passar para a saída todas as linhas que começam
# com o string "Erro".
predicado = proctexto.ComecaCom("Erro")
filtro = proctexto.FiltroPredicado(predicado)

# Aplica o filtro no arquivo fonte e salva o resultado em destino
filtro.filtrar(fonte, destino)

# Fecha ambos os arquivos, garantindo a integridade do conteúdo do arquivo
# de saída.
fonte.close()
destino.close()
