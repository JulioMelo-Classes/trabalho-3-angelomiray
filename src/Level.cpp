#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "../include/Player.h"
#include "../include/SnakeGame.h"
#include "../include/Snake.h"


Level::Level(int l, int c, int totFood){
    lines = l;
    columns = c;
    totalFood = totFood;
}


void Level::setLines(int lines){
    this->lines = lines;
}


void Level::setColumns(int columns){
    this->columns = columns;
}


void Level::setTotalFood(int totalFood){
    this->totalFood = totalFood;
}


int Level::getTotalFood(){
    return this->totalFood;
}


void Level::addMazeLine(string line){
    maze.push_back(line);
}


vector<string> Level::getMaze(){
    return maze;
}


void Level::setFreeCoordinates(){
    //cout << "setou free coordinates" << endl;
    for(int i=0; i < maze.size(); ++i){
        for(int j=0; j < maze[i].size(); ++j){
            if(maze[i][j] == ' '){
                freeCoordinates.push_back(make_pair(i, j));
            }
        }
    }
}


void Level::removeFreeCoordinate(pair<int, int> pos){
    for(int i=0; i < freeCoordinates.size(); ++i){
        if(freeCoordinates[i] == pos){
            freeCoordinates.erase(freeCoordinates.begin()+i);
            break;
        }
    }
}


void Level::generateNewFood(vector<string> &maze_, Snake &snake){
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


void Level::setInitialSnakeCoordinate(pair<int, int> coordinate){
    this->initial_snake_coordinate = coordinate;
}


pair<int, int> Level::getInitialSnakeCoordinate(){
    return this->initial_snake_coordinate;
}

pair<int, int> Level::getFoodCoordinate(){
    return this->foodCoordinate;
}

        
string Level::getLevelLine(int index){
    return maze[index];
}

pair<int, int> Level::randomStart(vector<string> &maze_, Snake &snake){
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
                maze_[t.first][t.second] == '*';
                removeFreeCoordinate(t);
                return t;
            }
            visited.push_back(t);
        }
    }

    return make_pair(-1, -1);

}


void Level::resetMaze(vector<string> &maze_, Snake &snake){
    maze_.clear();
    maze_ = maze;
}


void Level::loop(vector<string> &maze_, Snake &snake){
    resetMaze(maze, snake);
    snake.reset(snake, maze, initial_snake_coordinate);
    generateNewFood(maze, snake);
}