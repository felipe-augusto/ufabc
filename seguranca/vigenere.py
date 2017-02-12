# -*- coding: utf-8 -*-

cifra = 'segurancadedados'
message = 'felipe augusto dos santos'

def cypher (message, cifra):
	cyphred = ""
	for index, letter in enumerate(message):
		nmessage = ord(letter) - 97
		if nmessage == -65: # blank space
			cyphred += " "
		else:
			ncifra = ord(cifra[index % len(cifra)]) - 97
			cyphred += chr(((nmessage + ncifra) % 26) + 97)
	return cyphred

def decypher (message, cifra):
	decyphred = ""
	for index, letter in enumerate(message):
		nmessage = ord(letter) - 97
		if nmessage == -65:
			decyphred += " "
		else:
			ncifra = ord(cifra[index % len(cifra)]) - 97
			decyphred += chr(((nmessage - ncifra + 26) % 26) + 97)
	return decyphred

cifrado = cypher(message, cifra)
print cifrado
print decypher(cifrado, cifra)

# porque na tabela de substituicao olhando-se as linhas, o primeiro elemento
# de cada linha deve ser exatamente a mesma letra da mensagem
# ou seja se a cifra apenas 'aaaaa'
# a cifragem deve dar a resposta identifica a propria mensagem
# neste caso, teriamos que Ci = Pi
# eh importante que seja de 0 a 25, isso garante que no caso acima, o zero
# se some e nada aconteça
# as colunas na tabela polifisica indicam quanto temos que avancar no alfabeto
# com relacao a cifra entao temos originalmente Ci = Pi + Ki
# entretanto o modulo de 26 é necessario para adicionar limites no alfabeto