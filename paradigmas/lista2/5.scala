class Matriz(val contents: List[Linha]){
  // outro construtor da classe
  // que aceita uma matriz como argumento
  // e chama ela propria passando mat.contents que é List[Linha]
  // para nao dar pau quando fizer => new Matriz(new Matriz(new Linha()))
  def this(mat: Matriz) = this(mat.contents)

  // esse metodo retorna uma nova matriz
  // com a linha que foi passada por argumento
  // colocada no inicio da matriz
  def add(linha: Linha): Matriz = new Matriz(linha::this.contents)

  // adiciona a matriz that ao lado da matriz this
  // [A][B]
  def beside(that: Matriz): Matriz = {
    // println(that.contents(0))
    // println(that.contents zip this.contents)
    // println("wat")
    // for ((line1, line2) <- this.contents zip that.contents) {
    //   println((line1.contents, line2.contents))
    //   println(new Linha (line1.contents ::: line2.contents))
    // }
    // println("")

    new Matriz(
      // zip aggregates the contents of two lists into a single list of pairs.
      // List(1, 2, 3).zip(List("a", "b", "c")) = List((1,a), (2,b), (3,c))
      // ou seja, para cada linha de this
      // cria uma tupla com o valor de this.contents e that.contents
      // (line1, line2) <- (this.contents(0), that.contents(0))
      // (line1, line2) <- (this.contents(1), that.contents(1))
      for ((line1, line2) <- this.contents zip that.contents)
      // cria uma linha so com o que foi feito anteriormente
      // new Linha(this.contents(0) ::: that.contents(0))
      yield new Linha(line1.contents ::: line2.contents)
    )
  }

  // como contents tem uma lista de linhas
  // retorna cada objeto linha (pega o toString() da linha)
  // separado por "\n"
  override def toString = contents mkString "\n"
}

trait Trait1 extends Matriz {
  // chama o add original, porem com o valor somado com 1
  abstract override def add(linha: Linha)=
  super.add(new Linha(linha.contents.map(s=>s+1)))
}

trait Trait2 extends Matriz{
  // chama o add original, porem com o valor divido por 10
  abstract override def add(linha: Linha)=
  super.add(new Linha(linha.contents.map(s=>s/10)))
}

trait Trait3 extends Matriz{
  abstract override def beside(that: Matriz)= {
    // that -> matriz
    // that.contents -> linhas da matriz
    // that.contents.head -> primeira linha da matriz
    // that.add(that.contents.head) -> adiciona na primeira linha
    // a primeira linha da matriz
    super.beside(new Matriz(that.add(that.contents.head)))
  }
}

class Linha(val contents: List[Double]){
  // Returns a string representation of this iterable object.
  // The string representations of elements (w.r.t. the method toString())
  // are separated by the string sep

  // ou seja, retorna os elementos da lista separada por tabulacao "\t"
  override def toString = contents mkString "\t"
}

object Five extends Application {
  // cria uma linha a
  val a = new Linha(List(1,2))
  // cria uma matriz b
  val b = new Matriz(List(a, new Linha(List(3,4))))
  // println(b.contents)
  println("Matriz B:")
  println(b);println
  // [B]
  // 1.0  2.0
  // 3.0  4.0

  // Trait3 da override no "beside"
  // Trait2 e Trait1 dao override no "add" -> duas operacoes chamadas
  // primeiro voce soma um     (Trait1)
  // depois voce divide por 10 (Trait2)
  // traits sao executadas na ordem inversa que aparecem (??)

  val intermediate = (new Matriz(b) with Trait2 with Trait1 with Trait3)
  // val e = intermediate.add(a)
  // "add" com traits pertencem ao "intermediate" e nao a matriz "e"
  val e = (new Matriz(b) with Trait2 with Trait1 with Trait3).add(a)
  println("Matriz E:")
  println(e);println
  // [E]
  // 0.2  0.3
  // 1.0  2.0
  // 3.0  4.0

  val f = (new Matriz(e) with Trait3).beside(b)
  println("Matriz F:")
  println(f);println
  // [F] = [E] [B]
  // [0.2  0.3] [1.0  2.0]
  // [1.0  2.0] [1.0  2.0]
  // [3.0  4.0] [4.0  4.0]

  // por que o método "add" desta é normal?
  // nao é a matriz "e" quem tem o "add" com traits
  // mas sim a matriz "intermediate" que so foi criada
  // para gerar a matriz "e"
  val g = e.add(a)
  println("Matriz G:")
  println(g) 
  // 1.0  2.0
  // 0.2  0.3
  // 1.0  2.0
  // 3.0  4.0
}

