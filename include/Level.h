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
        vector<string> maze;
        pair<int, int> foodCoordinate;

    public:

        Level(int l, int c, int totFood){
            lines = l;
            columns = c;
            totalFood = totFood;
        }

        void setLines(int lines){
            this->lines = lines;
        }


        void setColumns(int columns){
            this->columns = columns;
        }


        void setTotalFood(int totalFood){
            this->totalFood = totalFood;
        }


        int getTotalFood(){
            return this->totalFood;
        }


        void addMazeLine(string line){
            maze.push_back(line);
        }


        vector<string> getMaze(){
            return maze;
        }


        //<! futuramente vou armazenar em um vetor as coordenadas que estão livres no mapa(que possuem ' '). aí vou sortear um número de acordo com o tam desse vetor e colocar a fruta em tal coordenada. talvez mais eficiente?
        void generateNewFood(vector<string> &maze_){
            srand(time(nullptr));
            
            while(true){
                int l_tmp = rand()%lines ; int c_tmp = rand()%columns;

                if(maze_[l_tmp][c_tmp] == ' '){
                    maze_[l_tmp][c_tmp] = '@';
                    cout << "COMIDA GErada NA COORDENADA (" << l_tmp << ',' << c_tmp << ") " << endl;
                    break;
                }
            }
        }


        pair<int, int> getFoodCoordinate(){
            return this->foodCoordinate;
        }
};



#endif //Level_h