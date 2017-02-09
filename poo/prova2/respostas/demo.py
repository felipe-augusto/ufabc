# -*- coding: utf-8 -*-
import shapes
# Demonstração de uso das classes Circle, App

# cria a janela de tamanho 500x250 pixels (largura x altura)
app = shapes.App(500, 250)

# cria dois circulos para desenhar na janela
c1 = shapes.Circle(20, 30, 50, 'red', app)
c2 = shapes.Circle(12, 70, 25, 'green', app)

# cria o retangulo para desenhar na janela
r1 = shapes.Rectangle(60, 60, 150, 100, 'yellow', app)

# efetivamente desenha os circulos na janela
c1.draw()
c2.draw()
c1.erase()
c2.change_colour('blue')
c2.move(100, 200)

# desenha o retangulo
r1.draw()
# apaga o retangulo
r1.erase()

# cria um shape composto
cs = shapes.CompositeShape()
# adiciona shapes ao shape composto
cs.add(c1)
cs.add(r1)
# desenha o shape composto
cs.draw()
# move a parte composta como um todo
cs.move(150, 15)

# inicia a janela, a partir de agora 
app.mainloop()