1. variavéis passadas por argumentos o compilador irá criar um construtor
  
  class Algo(n: Int, d: Int)

2. se o método já existe na class é necessário usar override (vide exemplo toString, que existe em todos os objecto)

  class some(n: Int) {
    require(n > 5) // da throw caso nao seja (bom para valicao)
    override def toString = n // duvida, isto pode ser toString => n
  }

3. NUNCA MUDE UM ATRIBUTO DE UM OBJETO, CRIE OUTRO COM O VALOR DO ATRIBUTO NOVO E O RETORNE.

4. FUNCOES LOCAIS -> UMA FUNCAO DENTRO DE OUTRA FUNCAO (tem acesso ao escopo da funcao pai)

List(0.2  0.3, 1.0  2.0, 3.0  4.0)
List(1.0  2.0, 3.0  4.0)

List((0.2 0.3,1.0 2.0), (1.0  2.0,3.0 4.0))