#ifndef Snake_h
#define Snake_h
#include <iostream>
#include <vector>
#include <utility>

#include "../include/Level.h"
#include "../include/Player.h"
#include "../include/SnakeGame.h"

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

        Snake(){
            lives = 5;
            score = 0;
            FoodEaten = 0;
        }


        void grow(pair<int, int> pos){
            snake_body.push_back(pos);
        }


        void eatFood(Snake snake, pair<int, int> pos){
            ++FoodEaten;
            score += 10; //<! temporário
            snake.grow(pos);
        }


        void clearSolution(){
            solution.clear();
        }


        void addToSolution(pair<int, int> position){
            solution.push_back(position);
        }

        void setSnakeCoordinate(pair<int, int> snake_coordinate){
            this->snake_coordinate = snake_coordinate;
        }


        pair<int, int> getSnakeCoordinates(){
            return snake_coordinate;
        }


        void putSnakeCoordinates(vector<string> &maze){
            for(int i=0; i < snake_body.size(); ++i){
                if(i == 0){
                    maze[snake_body[i].first][snake_body[i].second] = 'V';
                }
                else{
                    maze[snake_body[i].first][snake_body[i].second] = 'O';
                }
            }
        }
        //(a1, b1), (a2, b2), (a3, b3)
        //(x1, y1), (a1, b1), (a2, b2), ' ' 
        void updateSnakeCoordinates(vector<string> &maze, int cnt){
            vector<pair<int, int>> new_body;
            new_body.push_back(make_pair(solution[cnt].first, solution[cnt].second));

            maze[snake_body[snake_body.size()-1].first][snake_body[snake_body.size()-1].second] = ' '; 

            for(int i=0; i < snake_body.size()-1; ++i){
                new_body.push_back(snake_body[i]);
            }

            for(int i=0; i < snake_body.size(); ++i){
                snake_body[i].first = new_body[i].first;
                snake_body[i].second = new_body[i].second;
            }
        }


        pair<int, int> getPosition(int index){
            return solution[index];
        }


        int getSolutionSize(){
            return solution.size();
        }


        bool sucessSolution(){
            return solStatus;
        }


        void dead(){
            --lives;
        }
        

        int getLives(){
            return lives;
        }


        void setFoodEatean(int FoodEaten){
            this->FoodEaten = FoodEaten;
        }


        int getFoodEaten(){
            return FoodEaten;
        }

        void setSolStatus(bool status){
            solStatus = status;
        }


        void setAtualPosition(int atualPosition){
            this->atualPosition = atualPosition;
        }


        int getAtualPosition(){
            return atualPosition;
        }

        bool jaVisitado(pair<int, int> coordinate){
            for(int i=0; i < solution.size(); ++i){
                if(solution[i].first == coordinate.first && solution[i].second == coordinate.second)
                    return true;
            }
            return false;
        }

        void printSol(){
            for(int i=0; i < solution.size(); ++i){
                cout << solution[i].first << " " << solution[i].second << endl;
            }
        }
};

#endif //Snake_h