//  https://alvinalexander.com/scala/how-to-use-lists-nil-cons-scala-match-case-expressions

object Main extends Application {
  val texto = "#art O #sub rato #verbo roeu #art a #sub roupa #pron do #sub rei #pron de #sub roma"
  val rotulos = List("#art", "#sub", "#verbo", "#pron")

  println(countRotulos(texto, rotulos))

  def countRotulos(text: String, rotulos: List[String]) =  {
    def go(text: List[String]): Map[String, Int] = text match {
      // this is interesting, match an array and strips it
      case first :: tail => {
        first match {
          // match a rotulo
          case rotulo if rotulo.startsWith("#") => {
            val currentMap = Map(rotulo -> 1)
            // ++ replaces any (k,v) from the map on the left side
            // by (k,v) from the right side map
            // for example : Map(1 -> 1) ++ Map(1 -> 2) results in Map(1 -> 2)
            currentMap ++ 
            go(tail)
              .map {
                // match a Map key, value pair
                case (key,value) => {
                  // get value from currentMap if exists, if not set to 0
                  val currentMapValue = currentMap.getOrElse(key,0)
                  key -> (value + currentMapValue)
                }
              }
          }
          // if not a rotulo, call recursion
          case _ => go(tail)
        }
      }
      // remember that recursion starts from the end to the beginning
      // so we create a new Map wheh the recursion reaches the end (Nil)
      case Nil => Map()
    }

    val splittedText = text.split(" ").map(_.trim).toList
    go(splittedText)
  }
}