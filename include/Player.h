#ifndef Player_h
#define Player_h
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

#include "../include/Level.h"
#include "../include/Snake.h"
#include "../include/SnakeGame.h"

using namespace std;


class Player{
    private:
        vector<pair<int, int>> solution;
    public:
        enum Directions{
            NORTH, 
            SOUTH,
            WEST,
            EAST
        };


       /**
        * @brief dada a localização atual da cobra dentro do labirinto e a localização da comida,
        *  ele retorna true se ele encontrou (e armazenou) uma sequência de direções que leva à 
        * comida, ou false caso contrário. No caso da solução ser encontrada, este método também
        *  armazena a solução internamente no objeto.
        * @param maze_ o mapa.
        * @param snake a cobra.
        * @param snake_coordinate coordenada inicial da cobra.
        * @param setAtualPos posição atual da cobra.
        * @return true caso seja encontrada uma solução para a comida; falso caso contrário.
        **/
        bool find_solution(const vector<string> &maze, Snake &snake, pair<int, int> snake_coordinate, int setAtualPos){
            //DIREITA(Y+1) == EAST, ESQUERDA(Y-1) == WEST, CIMA(X-1) == NORTH, BAIXO(X+1) == SOUTH  
            //NORTH
            //SOUTH
            //WEST
            //EAST
            if(snake.goal(maze, snake_coordinate) == true){
                snake.addToSolution(snake_coordinate);
                snake.setAtualPosition(setAtualPos);
                return true;
            }

            if((snake.validPath(maze, snake_coordinate) == true) && (snake.unvisited(snake_coordinate) == true)){
                snake.addToSolution(snake_coordinate);

                //NORTH
                if(find_solution(maze, snake, make_pair(snake_coordinate.first-1, snake_coordinate.second), 0) == true){
                    return true;
                }

                //SOUTH
                if(find_solution(maze, snake, make_pair(snake_coordinate.first+1, snake_coordinate.second), 1) == true){
                    return true;
                }

                //WEST
                if(find_solution(maze, snake, make_pair(snake_coordinate.first, snake_coordinate.second-1), 2) == true){
                    return true;
                }

                //EAST
                if(find_solution(maze, snake, make_pair(snake_coordinate.first, snake_coordinate.second+1), 3) == true){
                    return true;
                }
                
                snake.removeFromSolution(); //quando ele estiver desempilhando, remove os elementos da solução.

                return false;

            }
            return false;
        }
};


#endif //Player_h