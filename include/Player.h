#ifndef Player_h
#define Player_h
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#include "../include/Level.h"
#include "../include/Snake.h"
#include "../include/SnakeGame.h"

using namespace std;


class Player{
    private:
        //vector<pair<int, int>> solution;
    public:
        enum Directions{
            WEST,
            EAST,
            SOUTH,
            NORTH
        };

        //retorna uma direção para a cobra com base na sequência de direções encontradas e armazenadas pelo motor de IA ou em uma política aleatória
        Directions next_move(){
            srand(time(nullptr));
            int nm = rand()%4;

            if(nm == WEST)
                return WEST;
            else if(nm == EAST)
                return EAST;
            else if(nm == SOUTH)
                return SOUTH;
            else
                return NORTH;
        }


        bool SnakeStuck(vector<string> maze, Directions position, pair<int,  int> snake_coordinate){
            if(position == NORTH){
                if(maze[snake_coordinate.first][snake_coordinate.second+1] != ' '
                && maze[snake_coordinate.first][snake_coordinate.second-1] != ' '
                && maze[snake_coordinate.first-1][snake_coordinate.second] != ' '){
                    return true;
                }
            }
            else if(position == SOUTH){
                if(maze[snake_coordinate.first][snake_coordinate.second-1] != ' '
                && maze[snake_coordinate.first][snake_coordinate.second+1] != ' '
                && maze[snake_coordinate.first+1][snake_coordinate.second] != ' '){
                    return true;
                }
            }
            else if(position == EAST){ //direita
                if(maze[snake_coordinate.first-1][snake_coordinate.second] != ' '
                && maze[snake_coordinate.first][snake_coordinate.second+1] != ' '
                && maze[snake_coordinate.first+1][snake_coordinate.second] != ' '){
                    return true;
                }
            }
            else if(position == EAST){ //esquerda
                if(maze[snake_coordinate.first-1][snake_coordinate.second] != ' '
                && maze[snake_coordinate.first][snake_coordinate.second-1] != ' '
                && maze[snake_coordinate.first+1][snake_coordinate.second] != ' '){
                    return true;
                }
            }

            return false;
        }

        //dada a localização atual da cobra dentro do labirinto e a localização da comida, ele retorna true se ele encontrou (e armazenou) uma sequência de direções que leva à comida, ou false caso contrário. No caso da solução ser encontrada, este método também armazena a solução internamente no objeto.
        bool find_solution(const vector<string> &maze, Snake &snake, pair<int, int> snake_coordinate){

            Directions atualPosition = NORTH;
            
            snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second));
            
            while(true){
                Directions nm = next_move(); //pegou a pos

                if((nm == NORTH) && (atualPosition != SOUTH)){ //se for pra norte, verifica se não há nada na frente e vai...
                    if(maze[snake_coordinate.first-1][snake_coordinate.second] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first-1, snake_coordinate.second);
                        atualPosition = nm;
                    }
                    else if(maze[snake_coordinate.first-1][snake_coordinate.second] == '@'){
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        break;
                    }
                }
                else if((nm == SOUTH) && (atualPosition != NORTH)){
                    if(maze[snake_coordinate.first+1][snake_coordinate.second] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first+1, snake_coordinate.second);                        
                        atualPosition = nm;
                    }
                    else if(maze[snake_coordinate.first+1][snake_coordinate.second] == '@'){
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second)); 
                        break;
                    }
                }
                else if((nm == WEST) && (atualPosition != EAST)){
                    if(maze[snake_coordinate.first][snake_coordinate.second-1] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second-1));                            
                        atualPosition = nm;
                    }
                    else if(maze[snake_coordinate.first][snake_coordinate.second-1] == '@'){
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second-1)); 
                        break;
                    }
                }
                else{
                    if(maze[snake_coordinate.first][snake_coordinate.second+1] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));  
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second+1);                                                  
                        atualPosition = nm;
                    }
                    else if(maze[snake_coordinate.first][snake_coordinate.second+1] == '@'){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));
                        break;
                    }
                }

                if(SnakeStuck(maze, atualPosition, snake_coordinate) == true){
                    snake.addToSolution(make_pair(-1,-1));
                    break;
                }
            }
            return true;
        }
};

#endif //Player_h