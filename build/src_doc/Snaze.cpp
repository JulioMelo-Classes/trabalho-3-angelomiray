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

int main(int argc, char *argv[]){
    SnakeGame game(argc, argv);
    
    game.loop(); //bloqueia aqui e só saí quando o jogo termina

    return 0;
}