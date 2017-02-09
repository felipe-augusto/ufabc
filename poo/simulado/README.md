# Simulado de Prova Prática 14/07/2016
### Prof. Carlos da Silva dos Santos

## **Enunciado:**

Nesta prova você desenvolverá uma simulação de uma fila de banco a partir de algumas classes já fornecidas. O objetivo da simulação é avaliar os tempos de espera médio e máximo para uma sequência de clientes, em função do número de caixas disponíveis. Você deve implementar sua simulação utilizando o código fornecido.

A simulação deve funcionar da seguinte forma:

* Cria-se uma sequência de clientes para o banco. Os atributos principais de cada cliente são o instante de chegada ao banco e a duração do seu atendimento. Aqui não estamos modelando as operações (saque, depósito, etc) que o cliente faria, o único aspecto que importa é o tempo da operação.
* O banco dispõe de um número n de caixas. Cada caixa pode estar livre ou ocupado. Quando um caixa fica livre em um instante de tempo t, imediatamente ele deve passar a atender o próximo cliente, caso exista.
* Ao atender um cliente, o caixa passa a ficar ocupado por um tempo igual à duração do atendimento do cliente.
* No momento de chegada ao banco, os clientes são encaminhados para um fila única de atendimento. O cliente fica na fila até que todos os clientes anteriores a ele sejam atendidos (isto é, o cliente torna-se o primeiro da fila).
* Quando um cliente é atendido, seu tempo de espera é calculado como a diferença entre o tempo de atendimento e o tempo de chegada do cliente ao banco.
* Como resultado da simulação, todos os cliente têm seu valor de tempo de espera calculado.

O programa de simulação implementado deverá permitir a escolha do número de caixas disponíveis, sem que o código precise ser editado para isso. Ao final da simulação, o tempo de espera médio e o tempo de espera máximo devem ser impressos. O programa deve simular a chegada de novos clientes durante um certo período (p. ex. uma hora), a partir do momento de abertura do banco.

A seguir serão descritas as classes já fornecidas:

**Cliente:** representa um cliente do banco no programa de simulação. Cada cliente é criado com um atributo que representa seu instante de chegada (medido em segundos a partir do horário de abertura do banco) e outro atributo que representa a duração (também em segundos) que levará o atendimento do cliente. O instante de chegada não necessariamente será igual ao instante de início do atendimento pois podem haver clientes esperando na fila. No momento em que um cliente é atendido, calculamos o tempo final de atendimento, de acordo com a fórmla:

`t(fim do atendimento)= t(início do atendimento) + duração atendimento.`

A classe Cliente fornece o método atende(), que deve ser chamado no momento em que o cliente é atendido. Esse método faz com que o tempo de espera do objeto seja calculado:

`espera = t(início do atendimento) - t(chegada).`

**DistribuicaoCliente:** esta é uma classe de conveniência, que cria um sequência de clientes sucessivos (isto é, seus instantes de chegada são crescentes) e com tempos de atendimento escolhidos aleatoriamente.

**Fila:** representa a fila do banco. A classe Fila fornece métodos para inserir um cliente no fim da fila, retirar o cliente do começo da fila (o próximo a ser atendido) e para inspecionar o tamanho da fila.

**Caixa:** representa um caixa de atendimento do banco. Quando queremos que um caixa atenda um cliente, devemos chamar o método atende() de Caixa, que recebe como parâmetros um Cliente e um instante de atendimento. Esse método chamará, por tabela, o método atende() do Cliente, fazendo com que o tempo de espera do cliente seja atualizado. Quando um caixa realiza um atendimento, ele permanecerá ocupado por um intervalo igual ao tempo de atendimento do cliente. O método livre() desta classe deve ser usado para certificar que o cliente seja encaminhado para uma caixa livre.

O processo de simulação pode ser resumido pelo seguinte pseudo-código:
```
1:  Criar lista de clientes
2:  Criar caixas de atendimento
3:  Criar fila
4:  Iniciar contador de tempo = zero
5:  Enquanto (contador de tempo) < (tempo máximo) ou (fila não vazia):
6:      Inserir na fila todos clientes cujo tempo de chegada for menor
        ou igual ao tempo atual
7:      Para todas os caixas:
8:          Se caixa livre, atender próximo cliente da fila
9:      Fim Para
10:     Incrementar contador de tempo
11: Fim Enquanto
```
## Critérios de avaliação:

O conteúdo submetido será avaliado levando-se em conta os seguintes
aspectos:

- correção do código com relação às regras da simulação.
- uso adequado de conceitos de orientação a objetos.