object Hi extends Application {

  def repeatLoop(body: => Unit) = new Until(body)
  
  var x = 0;

  repeatLoop {
    x += 1;
    println(x)
  } until (x < 10)

  // more step-by-step solution
  // var Until = repeatLoop {
  //   x += 1;
  //   println(x)
  // }

  // Until.until(x < 10)
}

class Until(body: => Unit) {
  def until(cond: => Boolean) {
    body // isso eh porque eh um do-while
    // nao te recursao infinita por o body tem alguma coisa
    // que modifica a cond, senao a recursao abaixo falharia
    if(cond) until (cond)
  }
}