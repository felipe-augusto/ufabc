# -*- coding: utf-8 -*-

class Livro:
		def __init__ (self, nome, autor, num_pags):
			# parametros obrigatorios
			self.nome = nome
			self.autor = autor
			self.num_pags = num_pags
			# inicializa outros parametros
			# poderia ser todos None
			self.is_emprestado = False
			self.is_reservado = False
			self.codigo = None

		def setCodigo(self, codigo):
			self.codigo = codigo

		def setReserva(self, is_reservado):
			self.is_reservado = is_reservado

		def setEmprestado(self, is_emprestado):
			self.is_emprestado = is_emprestado

		def getCodigo(self):
			if self.codigo is None:
				return "Livro nao possui codigo cadastrado."
			else:
				return self.codigo

		def getLivro(self):
			if self.codigo is not None:
				return "Livro: " + self.nome + "; Autor: " + self.autor + "; Número de Páginas: " + str(self.num_pags) + "; Código: " + self.codigo
			else:
				return "Livro: " + self.nome + "; Autor: " + self.autor + "; Número de Páginas: " + str(self.num_pags)
		
		def reservar(self):
			if self.is_emprestado is True:
				self.is_reservado = True
				return "Livro reservado com sucesso!"
			else:
				return "Esse livro esta disponivel. Pegue-o emprestado!"

		def emprestar(self):
			if self.is_emprestado is False and self.is_reservado is False:
				self.is_emprestado = True
				return "Livro emprestado com sucesso!"
			elif self.is_emprestado is False:
				return "Este livro esta reservado."
			else:
				return "Este livro esta emprestado."

		# para nao lidar diretamente com o obj
		def __unicode__(self):
			return self.nome
		def __str__(self):        
			return unicode(self).encode('utf-8')

class TestaLivro:
	def testaCriacaoDeLivro (self):
		return Livro("Harry Potter e a pedra", "b", 50)

	def testaEmprestimoComReserva (self, livro):
		livro.setReserva(True);
		return livro.emprestar()

	def testaEmprestimoSemReserva(self, livro):
		livro.setReserva(False);
		return livro.emprestar()


livro = TestaLivro().testaCriacaoDeLivro()
print livro.getLivro()
print TestaLivro().testaEmprestimoComReserva(livro)
print TestaLivro().testaEmprestimoSemReserva(livro)