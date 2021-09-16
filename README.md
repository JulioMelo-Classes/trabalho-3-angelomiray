# Compilação
Nesta sessão será abordada a forma de compilação do projeto.

## Dependências

- Compilador C++.

- cmake.

Entre no diretório `build`. 

    cd build

Execute o comando do cmake para compilar o projeto:

    cmake --build .


# Execução 
Para que o projeto seja executado, entre no diretório `build`(caso não esteja) e, posteriormente, no diretório `input_files`:

    cd build/input_files

Caso já esteja no diretório `build`:

    cd input_files

Crie um arquivo de texto com o labirinto que irá interagir com o motor da IA. Depois, execute o comando:

    ./snaze input_files/[nome_arquivo.txt] [Modo de Jogo] 

Há dois modos de jogo: snake com rabo e snake sem rabo. 

# Execução dos Arquivos de Teste
Nesta sessão serão arbodadas as execuções dos arquivos de teste.

## maze1.txt
Arquivo com dois níveis, mostrando a execução do motor da IA.

- Executando com modo de jogo snake com rabo: ./snaze input_files/maze1.txt 1

- output:
```
    Lives: ❤❤❤❤❤ | Score: X     | Food eaten: 2 of 3
    ____________________________________________________________

    ###############################
    #                             #
    # ######################### # #
    # #                       # # #
    # # ################### # # # #
    # # #                   # # # #
    # # #  ################## # # #
    # # #          OOX@       # # #
    # # ####################### # #
    #                             #
    ###############################
    ------------------------------------------------------------


                    WIN!!!

    ------------------------------------------------------------
    Lives: ❤❤❤❤❤ | Score: X     | Food eaten: 2 of 0
    ____________________________________________________________

    O jogo terminou!
```


# Avaliação CP2

## FindSolution.pacman

O método find soluiton ou similar deve ser capaz de encontrar o conjunto de comandos que levam da posição atual da cobrinha até a posição da comida no modo pacman.

**Avaiação**

Ok

## FindSolution.snake

O método find soluiton ou similar deve ser capaz de encontrar o conjunto de comandos que levam da posição atual da cobrinha até a posição da comida no modo snake.

**Avaliação**

25%, o algoritmo não leva em consideração a movimentação do corpo da cobrinha

## Random start

Deveria ser implementado na execução do programa um comando que permita que a posição inicial seja sorteada aleatoriamente. A posição inicial precisa ser válida e não deve causar a cobrinha/pacman iniciar em uma posição encurralada.

**Avaliação**

Ok

## Level Loop

Deveria se implementado na execução do programa um comando que permite que os níveis fiquem se repetindo infinitamente, com a transição de mapas indo do primeiro nível até o último nível e voltando para o primeiro, de forma que seja mantida a contagem de pontos bem como a contagem de nível.

**Avaliação**

Ok

## Organização / Compilação automatizada / Casos de Teste

Para a entrega final a organização do código em scr/data/include e compilação automatizada de alguma forma deve ser feita.

**Avaliação**

70% não foram feitos casos de teste

## Documentação do código / Readme / Documentação de Casos de Teste

**Avaliação**

70% não foram documentados os casos de teste
