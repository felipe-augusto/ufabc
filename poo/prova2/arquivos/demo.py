# -*- coding: utf-8 -*-
import shapes
# Demonstração de uso das classes Circle, App

# cria a janela de tamanho 500x250 pixels (largura x altura)
app = shapes.App(500, 250)

# cria dois circulos para desenhar na janela
c1 = shapes.Circle(20, 30, 50, 'red', app)
c2 = shapes.Circle(12, 70, 25, 'green', app)
# efetivamente desenha os circulos na janela
c1.draw()
c2.draw()

# inicia a janela, a partir de agora 
app.mainloop()
