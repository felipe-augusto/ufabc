object Hi {
  // convert int to rational whener its necessary
  implicit def intToRational(x: Int) = new Rational(x)

  def main(args: Array[String]) = {
    val loucura = new Rational(5)
    println(loucura)

    val first = new Rational(2, 4)
    val second = new Rational(2, 4)
    val result = first + second
    
    println(1 + result) // implicit conversion
    println(result + 2)
  }
}



// val n -> define como um atributo
class Rational(val n: Int, val d: Int) {
  require(d != 0)
  override def toString = n + "/" + d

  // famoso gato, pode instanciar com um parametro só
  def this(n: Int) = this(n, 1)

  // fazendo sobrecarga do metodo +
  // tanto para racional quanto para inteiro
  def + (that: Rational): Rational = 
    new Rational(this.n * that.d + that.n * this.d, this.d * that.d)

  def + (i: Int): Rational =
    new Rational(this.n + i * this.d, this.d)

  private val g = gcd(this.n, this.d)
  def getG = g

  private def gcd(a: Int, b: Int): Int =
    if (b == 0) a else gcd(b, a % b)
}