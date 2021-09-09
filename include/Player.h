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
            NORTH, 
            SOUTH,
            WEST,
            EAST
        };

        //retorna uma direção para a cobra com base na sequência de direções encontradas e armazenadas pelo motor de IA ou em uma política aleatória
        Directions next_move(){
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
        bool find_solution(const vector<string> &maze, Snake &snake, pair<int, int> snake_coordinate, int setAtualPos){
            
            cout << "entrou find solution " << endl;
            Directions atualPosition = NORTH;

            if(setAtualPos == 0){
                Directions atualPosition = NORTH;
            }
            else if(setAtualPos == 1){
                Directions atualPosition = SOUTH;
            }
            else if(setAtualPos == 2){
                Directions atualPosition = WEST;
            }
            else{
                Directions atualPosition = EAST;
            }

            cout << "atual pos " << atualPosition << endl; 

            snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second));
            
            cout << "pos " << snake_coordinate.first <<' ' <<  snake_coordinate.second << endl;

            srand(time(nullptr)); //quando vc usa srand dentro do while é possível que o programa fique em loop
            
            while(true){
                Directions nm = next_move(); //pegou a pos
                //cout << "nm: " << nm << endl;
                if((nm == NORTH) && (atualPosition != SOUTH)){ //se for pra norte, verifica se não há nada na frente e vai...
                    if(maze[snake_coordinate.first-1][snake_coordinate.second] == '@'){
                        
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        
                        snake_coordinate = make_pair(snake_coordinate.first-1, snake_coordinate.second);
                        snake.setAtualPosition(0); //armazenando a 'posicao atual' como a posicao final da solucao, uma vez
                        //que ela ficará virada para tal lado ao fim da execucao da solucao.
    
                        break;
                    }
                    else if((maze[snake_coordinate.first-1][snake_coordinate.second] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first-1, snake_coordinate.second)) == false)){ //dar pref à lugares nao visitados
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first-1, snake_coordinate.second);
                        atualPosition = nm;
                    }
                    //se ele ja visitou o local norte e nao visitou leste ou oeste
                    else if((maze[snake_coordinate.first][snake_coordinate.second+1] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first, snake_coordinate.second+1)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second+1);
                        atualPosition = EAST;
                    }
                    
                    else if((maze[snake_coordinate.first][snake_coordinate.second-1] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first, snake_coordinate.second-1)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second-1));
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second-1);
                        atualPosition = WEST;
                    }
                    //
                    else if(maze[snake_coordinate.first-1][snake_coordinate.second] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first-1, snake_coordinate.second);
                        atualPosition = nm;
                    }
                }
                else if((nm == SOUTH) && (atualPosition != NORTH)){
                    if(maze[snake_coordinate.first+1][snake_coordinate.second] == '@'){
                        
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second)); 
                        
                        snake_coordinate = make_pair(snake_coordinate.first+1, snake_coordinate.second);
                        snake.setAtualPosition(1);
    
                        break;
                    }

                    else if((maze[snake_coordinate.first+1][snake_coordinate.second] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first+1, snake_coordinate.second)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first+1, snake_coordinate.second);                        
                        atualPosition = nm;
                    }

                    else if((maze[snake_coordinate.first][snake_coordinate.second+1] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first, snake_coordinate.second+1)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second+1);
                        atualPosition = EAST;
                    }
                    
                    else if((maze[snake_coordinate.first][snake_coordinate.second-1] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first, snake_coordinate.second-1)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second-1));
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second-1);
                        atualPosition = WEST;
                    }

                    else if(maze[snake_coordinate.first+1][snake_coordinate.second] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first+1, snake_coordinate.second);                        
                        atualPosition = nm;
                    }
                    
                }
                else if((nm == WEST) && (atualPosition != EAST)){
                    if(maze[snake_coordinate.first][snake_coordinate.second-1] == '@'){
                        
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second-1)); 
                        cout << "add sosl " << endl;
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second-1);  
                        snake.setAtualPosition(2);
    
                        break;
                    }
                    else if((maze[snake_coordinate.first][snake_coordinate.second-1] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first, snake_coordinate.second-1)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second-1));   
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second-1);                           
                        atualPosition = nm;
                    }
                    else if((maze[snake_coordinate.first+1][snake_coordinate.second] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first+1, snake_coordinate.second)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first+1, snake_coordinate.second);
                        atualPosition = SOUTH;
                    }
                    
                    else if((maze[snake_coordinate.first-1][snake_coordinate.second] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first-1, snake_coordinate.second)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first-1, snake_coordinate.second);
                        atualPosition = NORTH;
                    }
                    
                    else if(maze[snake_coordinate.first][snake_coordinate.second-1] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second-1));   
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second-1);                           
                        atualPosition = nm;
                    }
                    
                }
                else if((nm == EAST) && (atualPosition != WEST)){
                    if(maze[snake_coordinate.first][snake_coordinate.second+1] == '@'){
                        
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second+1); 
                        snake.setAtualPosition(3);
    
                        break;
                    }
                    else if((maze[snake_coordinate.first][snake_coordinate.second+1] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first, snake_coordinate.second+1)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));  
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second+1);     
                        atualPosition = nm;
                    }
                    else if((maze[snake_coordinate.first+1][snake_coordinate.second] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first+1, snake_coordinate.second)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first+1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first+1, snake_coordinate.second);
                        atualPosition = SOUTH;
                    }
                    
                    else if((maze[snake_coordinate.first-1][snake_coordinate.second] == ' ') && (snake.jaVisitado(make_pair(snake_coordinate.first-1, snake_coordinate.second)) == false)){
                        snake.addToSolution(make_pair(snake_coordinate.first-1, snake_coordinate.second));
                        snake_coordinate = make_pair(snake_coordinate.first-1, snake_coordinate.second);
                        atualPosition = NORTH;
                    }
                    else if(maze[snake_coordinate.first][snake_coordinate.second+1] == ' '){
                        snake.addToSolution(make_pair(snake_coordinate.first, snake_coordinate.second+1));  
                        snake_coordinate = make_pair(snake_coordinate.first, snake_coordinate.second+1);     
                        atualPosition = nm;
                    }
                    
                }

                if(SnakeStuck(maze, atualPosition, snake_coordinate) == true){
                    snake.setSnakeCoordinate(snake_coordinate);
                    snake.setSolStatus(false);
                    break;
                }
                else{
                    snake.setSnakeCoordinate(snake_coordinate);
                    snake.setSolStatus(true);
                }
            }

            return true;
        }
};

#endif //Player_h