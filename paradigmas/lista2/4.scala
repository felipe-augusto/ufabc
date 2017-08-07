/*

No contexto de programação concorrente em Scala,
o que são Futures? Exemplifique sua utilização.

FONTE: https://alvinalexander.com/scala/differences-java-thread-vs-scala-future

Threads é uma abstracao de concorrência com própositos gerais (nao retorna nada)

Future é um objeto "segurando" um valor que
pode se tornar disponivel em determinado momento.

Uma Future representa o resultado de uma computacao assincrona
tem um tipo de retorno e aceita callbacks

Um exemplo de utilizacao que pode ser visto abaixo, onde queremos
chamar a mesma funçao para todos os elementos do vetor, mas queremos
que o calculo ocorra em paralelo e nao sequencialmente.

*/

// Parallel Collections: https://www.youtube.com/watch?v=GfZjsI4Xcyw
// Scala Futures:        https://www.youtube.com/watch?v=qdD-NuCRkzA
// Future Calculations:  https://www.youtube.com/watch?v=auQrWAKa3GA
// Awaiting Futures:     https://www.youtube.com/watch?v=qA_4bYw2wGo

import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.Failure
import scala.util.Success

import scala.concurrent.Await
import scala.concurrent.duration._

object FutureTest extends Application {
  // going to be execute in its own thread
  val f = Future {
    println("print in in the future")
  }

  // this is the same as above
  val f3: Future[Int] = Future {
      // your long-running task here that returns an Unit ...
      0
  }

  def fn(n: Int) = n * 2

  val f2 = Future {
    // something that can go bad
    for(i <- (1 to 20).par) yield fn(i)
  }

  f2.onComplete {
    case Success(n) => println(n)
    case Failure(ex) => println("something went wrong")
  }

  // println(Await.result(f2, 5 seconds))
  Thread.sleep(1)
}