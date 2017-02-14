## Enunciado
 
Caro Aluno,

Faça os exercícios do Slide 36 da Aula 2, disponível no menu Repositório (bc1523_aula 02 e 03 - criptografia e confidencialidade).

Exercícios

1. Explique, com suas palavras, por que funciona substituir a cifra e a tabela de Vigenère pela expressão algébrica do slide 27 (Ci = Pi + Ki).

2. Codifique a cifra de Vigenère, usando alguma linguagem de programação que você conheça (ou funções de planilha eletrônica). Além disso, teste sua aplicação cifrando seu nome usando a chave "segurancadedados" e decifrea cifra de um colega seu.

Entregue o texto da resposta, o arquivo com o código de programação (ou planilha) e os resultados dos testes de execução com a senha "segurancadedados".

Você pode fazer com ajuda de colegas, mas sua solução e entrega deve ser individual.

Após a data limite, há uma tolerância para entrega em atraso até o domingo seguinte após o limite.

## Resposta

1) Por que se observarmos a tabela de substituição, caso a chave seja composta apenas de letras “aaaa”, teríamos uma mensagem cifrada identifica a mensagem original. Neste caso, teríamos Ci = Pi, e vale notar a importância do alfabeto ser convertido de 0 a 25 e não de 1 a 26, pois é necessário o elemento neutro para este primeiro caso (deslocamento zero da cifra de César). Entretanto, quando mudamos a chave, adicionamos um deslocamento que depende da posição da palavra no alfabeto, por isso faz sentido dizer Ci = Pi + Ki. Já a operação  modulo é necessária para voltar ao começo do alfabeto quando chegamos no final, daí temos: Ci = Pi + Ki (mod 26). A analogia se mantém para o inverso, entretanto, quando fazemos a diferença Pi = Ci – Ki, precisamos ter certeza que este é um número positivo (para obter mod 26), por isso somamos 26 (que seria uma rotação no alfabeto), e temos: Pi = Ci – Ki + 26 (mod 26).

2)
Teste

cifrada: xircge cujyvtr vgw mrngqs
decifrada : felipe augusto dos santos