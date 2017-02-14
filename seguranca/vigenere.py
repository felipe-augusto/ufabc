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