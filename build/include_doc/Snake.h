#ifndef SNAKE_H
#define SNAKE_H
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

//Representa a cobra e seus atributos.  A simulação do jogo deve possuir apenas uma cobra.

class Snake{
    private:
        int lives;
        int score;
        int FoodEaten;
        int atualPosition; //guarda a posição que a cobra está virada
        // atualPosition;
        int solStatus;
        vector<pair<int, int>> solution;
        vector<pair<int, int>> snake_body; //vector que possui as coordenadas de uma parte do corpo da cobra
        pair<int, int> snake_coordinate;
    public:
        /**
        * @brief construtor.
        **/
        Snake();

        /**
        * @brief adiciona uma coordenada ao corpo da cobra, fazendo ela "crescer".
        * @param pos coordenada que será adicionada.
        **/
        void grow(pair<int, int> pos);

        /**
        * @brief modifica alguns atributos, quando come uma comida.
        **/
        void eatFood();

        /**
        * @brief exclui todos as coorrdenadas do atributo solution.
        **/
        void clearSolution();

        /**
        * @brief adiciona uma coordenada à solução.
        * @param position coordenada que será adicionada.
        **/
        void addToSolution(pair<int, int> position);

        /**
        * @brief remove a última coordenada da solução.
        **/
        void removeFromSolution();

        /**
        * @brief define a coordenada de onde a "cabeça" da cobra está.
        **/
        void setSnakeCoordinate(pair<int, int> snake_coordinate);

        /**
        * @return coordenada de onde a "cabeça" da cobra está.
        **/
        pair<int, int> getSnakeCoordinates();

        /**
        * @brief verifica se uma coordenada se choca com o corpo da cobra.
        * @param pos posição que será verificada.
        * @return true caso se choca; falso caso contrário.
        **/
        bool insideSnake(pair<int, int> pos);

        /**
        * @brief adiciona as coordenadas do corpo da cobra ao labirinto
        * @param maze labirinto que será adicionado o corpo da cobra.
        **/
        void putSnakeCoordinates(vector<string> &maze);
        
        //(a1, b1), (a2, b2), (a3, b3)
        //(x1, y1), (a1, b1), (a2, b2), ' ' 
        /**
        * @brief atualiza as coordenadas do corpo da cobra, com base nas coordenadas armazenadas
        * na solução.
        * @param maze labirinto que será adicionado o corpo da cobra.
        * @param cnt índice da coordenada armazenada na solução
        **/
        void updateSnakeCoordinates(vector<string> &maze, int cnt);


        /**
        * @brief retorna uma coordenada específica da solução.
        * @param index índice específico da coordenada;
        * @return coordenada específica.
        **/
        pair<int, int> getPosition(int index);

        /**
        * @brief retorna o tamanho da solution.
        **/
        int getSolutionSize();

        
        void dead();
        
        /**
        * @brief retorna a quantidade atual de vidas da cobra.
        **/
        int getLives();

        /**
        * @brief define a quantidade de vezes que a cobra comeu uma fruta.
        **/
        void setFoodEatean(int FoodEaten);

        /**
        * @brief retorna a quantidade de vezes que a cobra comeu uma fruta.
        **/
        int getFoodEaten();

        /**
        * @brief define a direção atual da cobra. (0 == NORTH, 1 == SOUTH, 2 == WEST, 3 == EAST)
        **/
        void setAtualPosition(int atualPosition);

        /**
        * @brief retorna a direção atual da cobra. (0 == NORTH, 1 == SOUTH, 2 == WEST, 3 == EAST)
        **/
        int getAtualPosition();

        /**
        * @brief verifica se uma coordenada dada não foi visitada pela cobra.
        * @param pos coordenada que será verificada
        * @return true caso não tenha sido visitada; false caso contrário.
        **/
        bool unvisited(pair<int, int> pos);

        /**
        * @brief verifica se uma coordenada dada é uma fruta ('@').
        * @param pos coordenada que será verificada
        * @return true caso seja uma fruta; false caso contrário.
        **/
        bool goal(vector<string> maze, pair<int, int> pos);

        /**
        * @brief verifica se uma coordenada dada é um caminho válido para a cobra ir.
        * @param pos coordenada que será verificada
        * @return true caso seja uma coordenada válida; false caso contrário.
        **/
        bool validPath(vector<string> maze, pair<int, int> pos);

        /** 
        * @brief define a posição que a cobra ficará virada.
        * @param pos coordenada que será verificada
        * @return true caso alguma coordenada ao redor dela não seja 
        * uma parede; false caso contrário.
        **/
        bool define_direction(vector<string> &maze, pair<int, int> pos);

        /** 
        * @brief reseta todos os atributos da cobra. acontece quando ela morre.
        * @param snake a cobra.
        * @param maze o labirinto atual.
        * @param coordinate coordenada inicial da cobra.
        **/
        void reset(Snake &snake, vector<string> &maze, pair<int, int> coordinate);

        /**         
        * @brief gera um caminho ao suicidio para a cobra. é chamada quando não há solução.
        * @param maze o labirinto atual.
        * @param snake a cobra.
        **/
        void suicide(vector<string> &maze, Snake &snake);
};

#endif //Snake_h