// Traits sao usadas para compartilhar interfaces e parametros entre classes.
// Sao similares a interfaces no Java.

// A parte rica de uma trait sao os metodos concretos que ela implementa.
// A parte curta de uma trait sao os metodos abstratos.

// A parte curta deve ser implementada pelo usuário da classe.

// A vantagem é que você pode "misturar" (como é normalmente utilizado)
// uma trait em uma determinada classe e herdar automaticamente todos
// seus metodos concretos, sem ter que implementá-los
// Além disso traits sao mais flexiveis que herança, pois é possivel concatenar
// diversas traits em uma classe, mas nao é possível herdar de múltiplas classes.

// Por exemplo, tente implementar o caso abaixo usando herança ao inves de mixins

// dog = pooper + baker
// cat = pooper + meower
// cleaningRobot = driver + cleaner
// murderRobot = driver + killer
// murderRobotDog = driver + killer + barker

trait Poop {
  def poop() = println("I´m pooping")
}

trait Bark {
  def bark() = println("I´m barking")
}

trait Meow {
  def meow() = println("I´m meowing")
}

trait Driver {
  def drive() = println("I´m driving")
}

trait Cleaning {
  def clean() = println("I´m cleaning")
}

trait Killing {
  def kill() = println("I´m killing")
}

class Dog extends Poop with Bark;
class Cat extends Poop with Meow;
class cleaningRobot extends Driver with Cleaning;
class murderRobot extends Driver with Killing;
class murderRobotDog extends Driver with Killing with Bark;

object Main extends Application {
  val mrb = new murderRobotDog()
  mrb.bark()
  mrb.drive()
}