#ifndef PLAYER_H
#define PLAYER_H
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


class Player{
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
        bool find_solution(const vector<string> &maze, Snake &snake, pair<int, int> snake_coordinate, int setAtualPos);
};


#endif //Player_h