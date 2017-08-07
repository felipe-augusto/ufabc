object Hi extends Application {
  class Data (val dia: Int, val mes: Int, val ano: Int) extends Ordered[Data] {
    // raise error on dia
    require(dia > 0)
    require(dia < 32)
    // raise error on mes
    require(mes > 0)
    require(mes < 13)
    override def toString = dia + "/" + mes + "/" + ano

    // need to implement this method (trait)
    override def compare(that: Data): Int =
      (that.dia, that.mes, that.ano) match {
        case (a, b, c)
          if (c < this.ano) => 1
        case (a, b, c)
          if (c == this.ano && b < this.mes) => 1
        case (a, b, c)
          if (c == this.ano && b == this.mes && a < this.dia) => 1
        case _ => -1
    }

    // couldn't do it using only compare
    def ==(that: Data): Boolean = (that.dia, that.mes, that.ano) match {
        case (a, b, c)
          if (c == this.ano && b == this.mes && a == this.dia) => true
        case _  => false
    }
  }

  try {
    val c = new Data(32, 01, 2004) // erro no dia
  } catch {
    case ex: IllegalArgumentException => println("Failed to initialize class")
  } 

  val a = new Data(20, 01, 2004)
  val b = new Data(20, 01, 2004)
  // 
  val d = new Data(23, 06, 2015)
  val e = new Data(23, 05, 2015)
  val f = new Data(22, 06, 2015)

  println(a == b) // true
  println(a == d) // false
  println(b < d)  // true
  println(d < e)  // false -> por um mes
  println(d > f)  // true -> por um dia
}