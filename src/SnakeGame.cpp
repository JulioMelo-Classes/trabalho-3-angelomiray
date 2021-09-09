#include <iostream>
#include <fstream>
#include <sstream>

#include <chrono> //por causa do sleep
#include <thread> //por causa do sleep

#include "../include/SnakeGame.h"
#include "../include/Level.h"
#include "../include/Player.h"
#include "../include/Snake.h"

using namespace std;


SnakeGame::SnakeGame(){
    choice = "";
    frameCount = 0;
    atualLevel = 0;
    totalLevels = 0;
    initialize_game();
}


bool SnakeGame::setNewLevel(string line){
    stringstream ss;
    ss << line;
    int l, c, totalFood;
    ss >> l >> c >> totalFood;
    if(l > 100 || c > 100)
        return false;

    Level new_level(l, c, totalFood);

    Levels.push_back(new_level);

    ++totalLevels;

    return true;
}


bool SnakeGame::GoToNextLevel(vector<string> &maze, vector<Level> &Levels){
    ++atualLevel;
    maze.clear();
    maze = Levels[atualLevel].getMaze();

    if(maze.empty())
        return false;
    else
        return true;
}


bool SnakeGame::tryGetSnakeCoordinates(int lineCount, string line, Snake &snake){
    for(int i=0; i < line.size(); ++i){
        if(line[i] == '*'){
            snake.grow(make_pair(lineCount, i));
            snake.setSnakeCoordinate(make_pair(lineCount, i));
            return true;
        }
    }
    return false;
}


void SnakeGame::initialize_game(){
    //carrega o nivel ou os níveis
    ifstream levelFile("../data/maze1.txt"); //só dá certo se o jogo for executado dentro da raíz do diretório (vc vai resolver esse problema pegando o arquivo da linha de comando)
    
    int lineCount = 0;
    bool invalidFormat=false, getSnakeCoordinate=false;

    string line;
    
    if(levelFile.is_open()){
        while(getline(levelFile, line)){ //pega cada linha do arquivo
            if((line[0] != '.') && (line[0] != '#')){
                if(setNewLevel(line) == false){
                    invalidFormat = true; //caso tenha um número de linhas ou colunas superior à 100.
                    break;
                }
                else{
                    lineCount = 0; //como já foi inicializado o novo level no if, apenas iniciamos a contagem de linhas dessa nova fase.
                }       
            }
            else{
                Levels[totalLevels-1].addMazeLine(line);

                if(getSnakeCoordinate == false){
                    getSnakeCoordinate = tryGetSnakeCoordinates(lineCount, line, snake);
                }
                if(totalLevels == 1)
                    maze.push_back(line); //apenas inicializar o mapa da fase inicial. apenas para  evitar que o mapa inicial também receba todas as linha de todas as fases.
                ++lineCount;
            }
            
            if(lineCount > 100){
                invalidFormat = true;
                break;
            }

        }
    }

    if(invalidFormat == false){
        state = RUNNING;
    }
    else
        state = GAME_OVER;

}


void SnakeGame::process_actions(){
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch(state){
        case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
            cin>>std::ws>>choice;
            break;
        case GAME_OVER: //**
            game_over();
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}


void SnakeGame::update(){
    //atualiza o estado do jogo de acordo com o resultado da chamada de "process_input"
    switch(state){
        case RUNNING:
            if(frameCount == 0){ //inicio do nivel ou jogo
                Levels[atualLevel].generateNewFood(maze);
                bool b = test.find_solution(maze, snake, snake.getSnakeCoordinates(), snake.getAtualPosition());
            }
            else if(frameCount == snake.getSolutionSize()){ //final do nível ou jogo
                if((snake.sucessSolution() == true) && (snake.getFoodEaten()+1 < Levels[atualLevel].getTotalFood())){//caso a solução final seja encontrar a fruta e ainda não seja a última fruta do nível
                    snake.eatFood(snake, snake.getPosition(snake.getSolutionSize()-2));
                    //talvez snake coordinate?
                    snake.updateSnakeCoordinates(maze, frameCount);
                    snake.clearSolution();
                    frameCount = -1;//coloquei -1 pq com o incremento no render() ele já fica 0.
                }
                else if(snake.sucessSolution() == true && snake.getFoodEaten()+1 == Levels[atualLevel].getTotalFood()){ //caso a solução 
                    if(GoToNextLevel(maze, Levels) == false){ //não há um próximo level
                        state = GAME_OVER;
                        game_over();
                    }
                    else{
                        cout << "foi pro prox level " << endl;
                        frameCount = -1;
                    }
                }
                else{
                    if(snake.getLives()-1 == 0){
                        state = WAITING_USER;
                        //fim de jogo
                    }
                    else{
                        snake.dead();
                        snake.clearSolution();
                        Levels[atualLevel].generateNewFood(maze);
                        test.find_solution(maze, snake, snake.getPosition(snake.getSolutionSize()-1), snake.getAtualPosition()); //final pos
                        frameCount = 0;
                    }
                }
            }
            else{
                snake.updateSnakeCoordinates(maze, frameCount);
            }

            break;
        case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if(choice == "n"){
                state = GAME_OVER;
                game_over();
            }
            else{
                //pode fazer alguma coisa antes de fazer isso aqui
                state = RUNNING;
            }
            break;
        default:
            //nada pra fazer aqui
            break;
    }
}

/**
 * @brief função auxiliar para fazer o programa esperar por alguns milisegundos
 * @param ms a quantidade de segundos que o programa deve esperar
 */
void wait(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}

/**
 * @brief função auxiliar para limpar o terminal
    - ex-clear
 */
void SnakeGame::updateScreen(){
    //some C++ voodoo here ;D
    #if defined _WIN32
        system("cls");
    #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined (__APPLE__)
        system("clear");
    #endif
    
    if(frameCount == 0){ //e seja o primeiro level/primeira life
        cout << "---> Welcome to the classic Snake Game <--- " << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Levels loaded: X | Snake lives: " << snake.getLives() << " | Apples to eat: " << snake.getFoodEaten() << endl;
        cout << "Clear all levels to win the game. Good luck!!! " << endl;
        cout << "-----------------------------------------------------" << endl;
        cout << "Press <ENTER> to start the game! " << endl;
        cout << "Lives: "; for(int i=0; i < snake.getLives(); ++i) cout << "❤"; cout << " | Score: X     | Food eaten: " << snake.getFoodEaten() << " of " << Levels[atualLevel].getTotalFood() << endl;
        cout << "____________________________________________________________\n" << endl;
    }
    else{
        cout << "Lives: "; for(int i=0; i < snake.getLives(); ++i) cout << "❤"; cout << " | Score: X     | Food eaten: " << snake.getFoodEaten() << " of " << Levels[atualLevel].getTotalFood() << endl;
        cout << "____________________________________________________________\n" << endl;
    }

}


void SnakeGame::render(){
    updateScreen();
    switch(state){
        case RUNNING:
            //adiciona a cobra ao mapa
            snake.putSnakeCoordinates(maze); 

            for(int i=0; i < maze.size(); ++i)
                cout << maze[i] << endl;
            
            break;
        case WAITING_USER:
            cout<<"Você quer continuar com o jogo? (s/n)"<<endl;
            break;
        case GAME_OVER:
            cout<<"O jogo terminou!"<<endl;
            break;
    }
    frameCount++;
}


void SnakeGame::game_over(){
    //todo
}


void SnakeGame::loop(){
    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(100);// espera 1 segundo entre cada frame
    }
}
