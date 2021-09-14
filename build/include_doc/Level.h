#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep
#include <algorithm>
#include "../include/Level.h"
#include "../include/Player.h"
#include "../include/SnakeGame.h"
#include "../include/Snake.h"
using namespace std;

// Representa  um  nível  do  jogo. Possui  dimensões  e  personagens que representam elementos do jogo.  A simulação do jogo pode ter um ou mais níveis.
class Level{

    private:
        int totalFood, lines, columns;
        pair<int, int> initial_snake_coordinate; //<! coordenada inicial da cobra.
        vector<string> maze;
        pair<int, int> foodCoordinate;
        vector<pair<int, int>> freeCoordinates; //<! coordenadas vázias no mapa.

    public:
        /**
        * @brief construtor. Define a quantidade de linhas, colunas e comidas em tal level.
        * @param l linhas do labirinto.
        * @param c colunas do labirinto.
        * @param lineCount contador que possui o valor da linha atual.
        **/
        Level(int l, int c, int totFood);

        /**
        * @brief Define a quantidade de linhas do labirinto em tal level.
        * @param lines quantidade de linhas.
        **/
        void setLines(int lines);

        /**
        * @brief Define a quantidade de colunas do labirinto em tal level.
        * @param columns quantidade de colunas.
        **/
        void setColumns(int columns);

        /**
        * @brief Define a quantidade de comida em tal level.
        * @param totalFood Quantidade de comida.
        **/
        void setTotalFood(int totalFood);

        /**
        * @return o total de comida em tal level.
        **/
        int getTotalFood();

        /**
        * @brief adiciona uma linha ao mapa desse level.
        * @param line a linha que será adicionada.
        **/
        void addMazeLine(string line);

        /**
        * @return matriz com o mapa desse level.
        **/
        vector<string> getMaze();

        /**
        * @brief define as coordenadas que estão livres(' ') no mapa.
        **/
        void setFreeCoordinates();

        /**
        * @brief remove uma coordenada que não está mais livre no mapa.
        * @param pos a posição que não está mais livre.
        **/
        void removeFreeCoordinate(pair<int, int> pos);


        /**
        * @brief gera uma comida em um local livre e aleatório no mapa.
        * @param maze_ o mapa do level em questão.
        * @param snake a cobra. apenas para não gerar comida em um local que a cobra esteja.
        **/
        void generateNewFood(vector<string> &maze_, Snake &snake);


        /**
        * @brief define a coordenada de "nascimento" da cobra em tal level.
        * @param coordinate a coordenada de "nascimento" da cobra.
        **/
        void setInitialSnakeCoordinate(pair<int, int> coordinate);

        /**
        * @return a coordenada de nascimento da cobra.
        **/
        pair<int, int> getInitialSnakeCoordinate();

        /**
        * @return a coordenada em que a comida foi gerada nesse level.
        **/
        pair<int, int> getFoodCoordinate();

        
        /**
        * @param index índice dessa linha no mapa.
        * @return uma linha específica do mapa.
        **/
        string getLevelLine(int index);

        /**
        * @brief faz a cobra nascer em um local aleatório e válido no mapa.
        * @param maze_ o mapa.
        * @param snake a cobra.
        * @return coordenada da cobra, caso exista alguma coordenada válida. 
        * senão, coordenada (-1, -1).
        **/
        pair<int, int> randomStart(vector<string> &maze_, Snake &snake);

        /**
        * @brief reseta o mapa em questão. 
        * @param maze_ o mapa.
        * @param snake a cobra.
        **/
        void resetMaze(vector<string> &maze_, Snake &snake);

        /**
        * @brief recomeça o jogo do zero, para caso o usuário queira jogar em modo loop. 
        * @param maze_ o mapa.
        * @param snake a cobra.
        **/
        void loop(vector<string> &maze_, Snake &snake);
};



#endif //Level_h