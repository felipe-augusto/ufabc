# -*- coding: utf-8 -*-
from Tkinter import Canvas as Tkcanvas
import Tkinter as tk

class App(object):
    """Objeto que implementa uma janela onde podemos desenhar.
    """
    def __init__(self, width, height):
        """Inicialização
        
        Parametros:
        width (int): largura da área desenhável, em pixels.
        height (int): altura da área desenhável, em pixels.
        """
        self.width = width
        self.height = height
        self.root = tk.Tk()
        self.canvas = Tkcanvas(self.root, width=self.width, height=self.height, bg="white")
        
        
    def mainloop(self):
        """Arranja os elementos da janela e a torna visível.
        """
        self.canvas.pack()
        self.root.mainloop()        

class Shape(object):
    """Superclasse para objetos que implementam formas geométricas.
    """
    def __init__(self, xPos, yPos, colour, app):
        """
        Inicialização.
        Parâmetros:
        xPos (int): distância horizontal (em pixels) entre borda esquerda da janela e 
                    a forma geométrica.
        yPos (int): distância vertical (em pixels) entre borda superior da janela e 
                    a forma geométrica.
        colour (str): designa a cor de preenchimento da forma geométrica. Pode
                    ter valores como 'red', 'green', 'blue', etc.
        app (App): janela onde esta forma geométrica será desenhada.                    
                    
        """
        
        # O construtor da classe. Note que é preciso passar
        # um objeto do tipo Canvas ao criarmos um circulo.
        self.xPos = xPos
        self.yPos = yPos
        self.colour = colour
        self._app = app
        self.item = None

    def draw(self):
        """Desenha esta forma geométrica na tela.
        
        Este método deve ser implementado por todas as subclasses de Shape.
        """
        raise RuntimeError('Não implementado')

    def erase(self):
        """Apaga a forma geométrica da janela (caso esta já tenha sido desenhada).
        """
        if self.item is not None:
            self._canvas._canvas.delete(self.item)
        
    def change_colour(self, new_colour):
        """Muda a cor da forma geométrica.
        Parâmetros:
           new_colour (str): designa a nova cor de preenchimento da forma 
           geométrica. Pode ter valores como 'red', 'green', 'blue', etc.
        """
        # Altera a cor do circulo. Tente usar valores como
        # "red", "green", "blue" -- assim mesmo, entre aspas.
        self.colour = new_colour
        self.erase()
        self.draw()

class Circle(Shape):
    """Implementa a forma de círculo preenchido.
    """
    def __init__(self, diameter, xPos, yPos, colour, app):
        """
        Inicialização.
        Parâmetros:
        diameter (int): Diâmetro do círculo (em pixels).
        xPos (int): distância horizontal (em pixels) entre borda esquerda da janela e 
                    a forma geométrica.
        yPos (int): distância vertical (em pixels) entre borda superior da janela e 
                    a forma geométrica.
        colour (str): designa a cor de preenchimento da forma geométrica. Pode
                    ter valores como 'red', 'green', 'blue', etc.
        app (App): janela onde esta forma geométrica será desenhada.                    
                    
        """
        super(Circle, self).__init__(xPos, yPos, colour, app)
        self.diameter = diameter

    def draw(self):
        """Desenha este círculo.
        """ 
        self.erase()
        # Desenha o circulo em sua posição atual
        lowY = self.yPos + self.diameter
        leftX = self.xPos + self.diameter
        self.item = self._app.canvas.create_oval(self.xPos, self.yPos,
                                 leftX, lowY, outline=self.colour,
                                 fill=self.colour, width=1)

        

  
