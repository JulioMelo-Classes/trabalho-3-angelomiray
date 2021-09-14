#ifndef Level_h
#define Level_h
#include <iostream>
#include <vector>
#include <string>
#include <utility>

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
        Level(int l, int c, int totFood){
            lines = l;
            columns = c;
            totalFood = totFood;
        }

        /**
        * @brief Define a quantidade de linhas do labirinto em tal level.
        * @param lines quantidade de linhas.
        **/
        void setLines(int lines){
            this->lines = lines;
        }

        /**
        * @brief Define a quantidade de colunas do labirinto em tal level.
        * @param columns quantidade de colunas.
        **/
        void setColumns(int columns){
            this->columns = columns;
        }

        /**
        * @brief Define a quantidade de comida em tal level.
        * @param totalFood Quantidade de comida.
        **/
        void setTotalFood(int totalFood){
            this->totalFood = totalFood;
        }

        /**
        * @return o total de comida em tal level.
        **/
        int getTotalFood(){
            return this->totalFood;
        }

        /**
        * @brief adiciona uma linha ao mapa desse level.
        * @param line a linha que será adicionada.
        **/
        void addMazeLine(string line){
            maze.push_back(line);
        }

        /**
        * @return matriz com o mapa desse level.
        **/
        vector<string> getMaze(){
            return maze;
        }

        /**
        * @brief define as coordenadas que estão livres(' ') no mapa.
        **/
        void setFreeCoordinates(){
            //cout << "setou free coordinates" << endl;
            for(int i=0; i < maze.size(); ++i){
                for(int j=0; j < maze[i].size(); ++j){
                    if(maze[i][j] == ' '){
                        freeCoordinates.push_back(make_pair(i, j));
                    }
                }
            }
        }

        /**
        * @brief remove uma coordenada que não está mais livre no mapa.
        * @param pos a posição que não está mais livre.
        **/
        void removeFreeCoordinate(pair<int, int> pos){
            for(int i=0; i < freeCoordinates.size(); ++i){
                if(freeCoordinates[i] == pos){
                    freeCoordinates.erase(freeCoordinates.begin()+i);
                    break;
                }
            }
        }


        /**
        * @brief gera uma comida em um local livre e aleatório no mapa.
        * @param maze_ o mapa do level em questão.
        * @param snake a cobra. apenas para não gerar comida em um local que a cobra esteja.
        **/
        void generateNewFood(vector<string> &maze_, Snake &snake){
            srand(time(nullptr));
            vector<pair<int, int>> visited; bool check = false;

            while(visited.size() < freeCoordinates.size()){
                pair<int, int> t = freeCoordinates[rand()%freeCoordinates.size()];

                for(int i=0; i < visited.size(); ++i){ //se essa pos ja foi visitada
                    if(t == visited[i]){
                        check = true;
                        break;
                    }
                }

                
                if(snake.insideSnake(t) == true){ //se essa pos se choca com a cobra.
                    check = false;
                }
                
                if(check == false){
                    maze_[t.first][t.second] = '@';
                    foodCoordinate = t;
                    removeFreeCoordinate(t);
                    break;
                }
            }
        }


        /**
        * @brief define a coordenada de "nascimento" da cobra em tal level.
        * @param coordinate a coordenada de "nascimento" da cobra.
        **/
        void setInitialSnakeCoordinate(pair<int, int> coordinate){
            this->initial_snake_coordinate = coordinate;
        }

        /**
        * @return a coordenada de nascimento da cobra.
        **/
        pair<int, int> getInitialSnakeCoordinate(){
            return this->initial_snake_coordinate;
        }

        /**
        * @return a coordenada em que a comida foi gerada nesse level.
        **/
        pair<int, int> getFoodCoordinate(){
            return this->foodCoordinate;
        }

        
        /**
        * @param index índice dessa linha no mapa.
        * @return uma linha específica do mapa.
        **/
        string getLevelLine(int index){
            return maze[index];
        }

        /**
        * @brief faz a cobra nascer em um local aleatório e válido no mapa.
        * @param maze_ o mapa.
        * @param snake a cobra.
        * @return coordenada da cobra, caso exista alguma coordenada válida. 
        * senão, coordenada (-1, -1).
        **/
        pair<int, int> randomStart(vector<string> &maze_, Snake &snake){
            srand(time(nullptr));
            vector<pair<int, int>> visited; bool check;

            while(visited.size() < freeCoordinates.size()){
                pair<int, int> t = freeCoordinates[rand()%freeCoordinates.size()];

                for(int i=0; i < visited.size(); ++i){
                    if(t == visited[i]){
                        check = true;
                        break;
                    }
                }

                if(check == false){
                    if(snake.define_direction(maze_, t) == true){
                        maze_[t.first][t.second] = '*';
                        removeFreeCoordinate(t);
                        return t;
                    }
                    visited.push_back(t);
                }
            }

            return make_pair(-1, -1);

        }

        /**
        * @brief reseta o mapa em questão. 
        * @param maze_ o mapa.
        * @param snake a cobra.
        **/
        void resetMaze(vector<string> &maze_, Snake &snake){
            maze_.clear();
            maze_ = maze;
        }

        /**
        * @brief recomeça o jogo do zero, para caso o usuário queira jogar em modo loop. 
        * @param maze_ o mapa.
        * @param snake a cobra.
        **/
        void loop(vector<string> &maze_, Snake &snake){
            resetMaze(maze, snake);
            snake.reset(snake, maze, initial_snake_coordinate);
            generateNewFood(maze, snake);
        }
};



#endif //Level_h