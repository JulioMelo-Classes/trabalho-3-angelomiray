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


