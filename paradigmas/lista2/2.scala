object Hi extends Application {
  // 2.a) Explique o que a função faz 
  // recebe uma f(x)
  // se a maior que b, retorna 0
  // senao, soma os resultados de f(a) de a até b
  // exemplo de (2, 4)
  // f(2) + f(3) + f(4) = 4 + 6 + 8 = 18

  def sum(f: Int => Int): (Int, Int) => Int = {
    def sumF(a: Int, b: Int): Int = {
      if (a > b) 0 else f(a) + sumF(a + 1, b)
    }
    // returns sumF
    sumF
  }

  // 2.b) Implemente-a de forma mais concisa utilizando currying.
  // currying the above example
  def currSum(f: Int => Int): Int => (Int => Int) = {
    def sumF(a:Int): (Int => Int) = (b:Int) =>
      if (a > b) 0 else f(a) + sumF(a + 1)(b)

    // returns sumF
    sumF
  }

  def test(a: Int): Int = a * 2
  def quadratic(a: Int) = a * a

  val fn = sum(test)
  println(fn(4,4))
  // 2. a) utilize-a para criar uma função que some os quadrados dos
  // valores dentro de uma determinada faixa.
  val fn2 = sum(quadratic)
  println(fn2(1,5)) // 1 + 4 + 9 + 16 + 25 = 55
  println(fn2(4,4)) // 16

  // tries with curry
  val fn3 = currSum(quadratic)
  println(fn3(1)(5)) // 1 + 4 + 9 + 16 + 25 = 55
}
