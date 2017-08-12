//  https://alvinalexander.com/scala/how-to-use-lists-nil-cons-scala-match-case-expressions
import scala.concurrent.Future
import scala.concurrent.ExecutionContext.Implicits.global
import scala.util.Failure
import scala.util.Success

object Main extends Application {
  val texto = "#art O #sub rato #verbo roeu #art a #sub roupa #pron do #sub rei #pron de #sub roma"
  val rotulos = List("#art", "#sub", "#verbo", "#pron")

  countRotulos(texto, rotulos).onComplete {
    case Success(map) => {
      println("MAP IS DONE:")
      println(map)
    }
    case Failure(ex) => println("Problems happens!")
  }

  def countRotulos(text: String, rotulos: List[String]): Future[Map[String, Int]] =  {
    def go(text: List[String]): Future[Map[String, Int]] = text match {
      // this is interesting, match an array and strips it
      case first :: tail => {
        first match {
          // match a rotulo
          case rotulo if rotulo.startsWith("#") => {
            val currentMap = Map(rotulo -> 1)

            go(tail).map { previousMap =>
              currentMap ++ previousMap.map { 
                case (key,value) => {
                  key -> (value + currentMap.getOrElse(key,0))
                }
              }
            }
          }
          // if not a rotulo, call recursion
          case _ => go(tail)
        }
      }
      // remember that recursion starts from the end to the beginning
      // so we create a new Map wheh the recursion reaches the end (Nil)
      // this time wrapping around a Future
      case Nil => Future { Map() }
    }

    val splittedText = text.split(" ").map(_.trim).toList
    // returns a Promise
    go(splittedText)
  }
}