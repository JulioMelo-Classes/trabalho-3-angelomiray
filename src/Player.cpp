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

bool Player::find_solution(const vector<string> &maze, Snake &snake, pair<int, int> snake_coordinate, 
                  int setAtualPos){
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