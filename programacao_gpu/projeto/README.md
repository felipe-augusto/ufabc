# Transformada em Distância

Projeto final da disciplina de Processamento de Imagens Utilizando a GPU.
O objetivo foi implementar uma rotina de transformada em distância através de múltiplas erosões em CPU, CPU Paralelo, GPU com memória global e GPU com memória compartilhada.

O arquivo de teste que executa as rotinas (encapsuladas nos arquivos ```td_cpu.cpp``` e ```td_gpu.cpp```) é o arquivo ```td_test.cpp```.

Para compilar:

```sh
nvcc -x cu *.cpp *.cu -std=c++11
```

## Resultados

Testes foram realizados com imagens de 512x512 e 1024x1024.

### Imagem 512x512

Tempo CPU: 1663ms
Tempo CPU (Paralelo - 4 cores): 579ms
Tempo GPU Mem. Global: 6ms
Tempo GPU Mem. Compartilhada: 5ms

### Imagem 1024x1024

Tempo CPU: 13972ms
Tempo CPU (Paralelo - 4 cores): 4670ms
Tempo GPU Mem. Global: 25ms
Tempo GPU Mem. Compartilhada: 20ms