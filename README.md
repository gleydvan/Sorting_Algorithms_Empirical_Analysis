# Universidade Federal do Rio Grande do Norte
### Instituto Metrópole Digital - IMD
### Bacharelado em Tecnologia da Informação – BTI

## Análise Empírica de Algoritmos de Ordenação

- Aluno: Gleydvan Macedo
- Professor: Selan Rodrigues dos Santos

### Resumo

Este programa tem como objetivo determinar qual algoritmo de ordenação, dos algoritmos analisados, é a melhor opção para ordenar um vetor de inteiros positivos, e em qual situação cada algoritmo é recomendado.

## Como Compilar
Utilize o comando 'make dir' para criar os diretórios bin, build, doc e tempos (caso não estejam criados).
Depois utilize o comando 'make' no terminal do Linux.

## Como Executar
Por meio de linha de comando no terminal digite:

./bin/Sorting_Algorithms_Empirical_Analysis -f(número da função desejada) -r(quantidade de elementos) -q(quantidade de testes para medir o tempo)

##### Modo de usar
- '-f (numero da funcao)' - Indica quais tipos de funcoes de ordenacao deseja utilizar na analise.
- '-q (quantidade)' - indica a quantidade de testes realizados para cada amostra em cada Analise Empirica.
- '-r (quantidade)' - indica o tamanho do range a ser utilizado (ou seja, a quantidade de elementos).

##### Números de cada função
- 1 Insertion sort
- 2 Selection sort
- 3 Bubble sort
- 4 Merge sort
- 5 Quick sort
- 6 Shell sort
- 7 Radix sort
- 8 Todos os algoritmos

##### Exemplos de execução:
      
    ./bin/Sorting_Algorithms_Empirical_Analysis -f4567 -q10 -r10000
    
    ./bin/Sorting_Algorithms_Empirical_Analysis -f8 -r50000 -q30
        
### Introdução

  Neste programa serão feitas analises dos seguintes algoritmos de ordenação:

  - Insertion sort
  - Selection sort
  - Bubble sort
  - Shell sort
  - Quick sort
  - Merge sort
  - Radix sort

### Descrição de Atividades (Método Utilizado)

  Para a análise dos algoritmos foi utilizado o método de análise empiríca, ou seja, foi cronometrado o tempo de execução de cada algoritmo em três cenários diferentes:

- Um vector armazenando números inteiros em ordem não decrescente
- Um vector armazenando números inteiros em ordem não crescente
- Um vector armazenando números inteiros aleatórios, sem ordem aparente.

  Para conseguir medições mais precisas do tempo que cada algoritmo leva para realizar a ordenação, foi realizada a média progressiva dos tempos medidos em 30 execuções de cada algoritmo, em cada um dos cenários.

  Foram utilizados 26 amostras de tamanhos diferentes para a análise de cada algoritmo, em cada um dos cenários, e o tempo médio obtido de cada um foi utilizado para criar gráficos que representam uma relação entre o tempo gasto na ordenação dos elementos e a quantidade de elementos utilizados na ordenação.