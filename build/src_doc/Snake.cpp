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

Snake::Snake(){
    lives = 5;
    score = 0;
    FoodEaten = 0;
    atualPosition = 3;
    snake_coordinate = make_pair(-1, -1);
}


void Snake::grow(pair<int, int> pos){
    snake_body.push_back(pos);
}


void Snake::eatFood(){
    ++FoodEaten;
    score += 10; //<! temporário
}


void Snake::clearSolution(){
    solution.clear();
}


void Snake::addToSolution(pair<int, int> position){
    solution.push_back(position);
}


void Snake::removeFromSolution(){
    solution.erase(solution.end()-1);
}


void Snake::setSnakeCoordinate(pair<int, int> snake_coordinate){
    this->snake_coordinate = snake_coordinate;
}


pair<int, int> Snake::getSnakeCoordinates(){
    return snake_coordinate;
}


bool Snake::insideSnake(pair<int, int> pos){
    for(int i=0; i < snake_body.size(); ++i){
        if(pos == snake_body[i])
            return true;
    }
    return false;
}


void Snake::putSnakeCoordinates(vector<string> &maze){
    for(int i=0; i < snake_body.size(); ++i){
        if(i == 0){
            maze[snake_body[i].first][snake_body[i].second] = 'X';
        }
        else{
            maze[snake_body[i].first][snake_body[i].second] = 'O';
        }
    }
}

//(a1, b1), (a2, b2), (a3, b3)
//(x1, y1), (a1, b1), (a2, b2), ' ' 
void Snake::updateSnakeCoordinates(vector<string> &maze, int cnt){
    vector<pair<int, int>> new_body;
    new_body.push_back(make_pair(solution[cnt].first, solution[cnt].second));

    maze[snake_body[snake_body.size()-1].first][snake_body[snake_body.size()-1].second] = ' ';

    for(int i=0; i < snake_body.size()-1; ++i){
        new_body.push_back(snake_body[i]);
    }
    
    snake_body.clear();

    for(int i=0; i < new_body.size(); ++i){
        snake_body.push_back(new_body[i]);
    }
}


pair<int, int> Snake::getPosition(int index){
    return solution[index];
}


int Snake::getSolutionSize(){
    return solution.size();
}


void Snake::dead(){
    --lives;
}


int Snake::getLives(){
    return lives;
}


void Snake::setFoodEatean(int FoodEaten){
    this->FoodEaten = FoodEaten;
}


int Snake::getFoodEaten(){
    return FoodEaten;
}


void Snake::setAtualPosition(int atualPosition){
    this->atualPosition = atualPosition;
}


int Snake::getAtualPosition(){
    return atualPosition;
}


bool Snake::unvisited(pair<int, int> pos){
    for(int i=0; i < solution.size(); ++i){
        if(solution[i] == pos){
            return false;
        }
    }
    return true;
}


bool Snake::goal(vector<string> maze, pair<int, int> pos){
    return maze[pos.first][pos.second] == '@' ? true : false;
}


bool Snake::validPath(vector<string> maze, pair<int, int> pos){
    return (maze[pos.first][pos.second] == ' ' || maze[pos.first][pos.second] == '*') 
            || (maze[pos.first][pos.second] == 'X') ? true : false;
}


bool Snake::define_direction(vector<string> &maze, pair<int, int> pos){
    if(pos.first == -1){ //caso seja, de fato, um pedido de random start[não possui '*' no mapa].
        return false;
    }

    if(maze[pos.first-1][pos.second] == ' '){
        //cout << "t" << endl;
        atualPosition = 0;
        return true;
    }
    else if(maze[pos.first+1][pos.second] == ' '){
        //cout << "t" << endl;
        atualPosition = 1;
        return true;
    }
    else if(maze[pos.first][pos.second-1] == ' '){
        //cout << "t" << endl;
        atualPosition = 2;
        return true;
    }
    else if(maze[pos.first][pos.second+1] == ' '){
        //cout << "t" << endl;
        atualPosition = 3;
        return true;
    }
    else{
        return false;
    }
    //cout << "saiu find_Dir" << endl;
    return false;
}


void Snake::reset(Snake &snake, vector<string> &maze, pair<int, int> coordinate){
    snake_body.clear();
    solution.clear();
    FoodEaten = 0;
    snake.grow(coordinate);
    snake.setSnakeCoordinate(coordinate);
    define_direction(maze, coordinate);
}


void Snake::suicide(vector<string> &maze, Snake &snake){
    pair<int, int> t = snake.getSnakeCoordinates();

    while(maze[t.first][t.second] != '#'){
        if(atualPosition == 0){
            snake.addToSolution(t);
            --t.first; 
        }
        else if(atualPosition == 1){                    
            snake.addToSolution(t);
            ++t.first; 
            
        }
        else if(atualPosition == 2){                    
            snake.addToSolution(t);
            --t.second; 
        }
        else if(atualPosition == 3){                    
            snake.addToSolution(t);
            ++t.second; 
        }
    }
    
}