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

        
    

SnakeGame::SnakeGame(int argc, char* argv[]){
    choice = "";
    frameCount = 0;
    atualLevel = 0;
    totalLevels = 0;
    allFood = 0;
    initialize_game(argc, argv);
}


bool SnakeGame::setNewLevel(string line){
    stringstream ss;
    ss << line;
    int l, c, totalFood;
    ss >> l >> c >> totalFood;
    if(l > 100 || c > 100)
        return false;

    Level new_level(l, c, totalFood);
    allFood += totalFood;
    Levels.push_back(new_level);

    ++totalLevels;
    return true;
}


//vector<string> &maze, vector<Level> &Levels
bool SnakeGame::GoToNextLevel(){
    ++atualLevel;

    maze.clear();

    if(atualLevel == totalLevels && loopChoice == 'n'){
        return false;
    }

    else if(atualLevel == totalLevels && loopChoice == 's'){
        atualLevel = 0;
        maze = Levels[atualLevel].getMaze();
        Levels[atualLevel].setFreeCoordinates();
        snake.reset(snake, maze, Levels[atualLevel].getInitialSnakeCoordinate()); 
        Levels[atualLevel].generateNewFood(maze, snake);
        state = WAITING_USER;
    }

    else{
        maze = Levels[atualLevel].getMaze();
        Levels[atualLevel].setFreeCoordinates();
        snake.reset(snake, maze, Levels[atualLevel].getInitialSnakeCoordinate()); 
        Levels[atualLevel].generateNewFood(maze, snake);
    }

    return true;
    
}


bool SnakeGame::tryGetSnakeCoordinates(int lineCount, string line, Snake &snake, vector<Level> &Levels){
    for(int i=0; i < line.size(); ++i){
        if(line[i] == '*'){
            
            //
            if(totalLevels-1 == 0){ //apenas armazenas a coordenada do primeiro level.
                snake.grow(make_pair(lineCount, i));
                snake.setSnakeCoordinate(make_pair(lineCount, i));
            }   
            
            Levels[totalLevels-1].setInitialSnakeCoordinate(make_pair(lineCount, i));

            return true;
        }
    }

    return false;
}


void SnakeGame::initialize_game(int argc, char* argv[]){
    //carrega o nivel ou os níveis
    fstream levelFile; //só dá certo se o jogo for executado dentro da raíz do diretório (vc vai resolver esse problema pegando o arquivo da linha de comando)

    levelFile.open(argv[1], ios::in);

    stringstream ss; ss << argv[2]; ss >> gameMode;

    cout << "Deseja jogar em modo loop? [s/n]" << endl;
    cin >> std::ws >> loopChoice;

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
                    getSnakeCoordinate = false;
                }       
            }
            else{
                Levels[totalLevels-1].addMazeLine(line);

                if(getSnakeCoordinate == false){
                    getSnakeCoordinate = tryGetSnakeCoordinates(lineCount, line, snake, Levels);
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
    else{
        cout << "nao foi " << endl;
    }

    Levels[0].setFreeCoordinates(); //<! setar as coordenadas livres apenas para o primeiro 
    //<! level para os outros levels, é possível fazer no GoToNextLevel();


    if(snake.define_direction(maze, snake.getSnakeCoordinates()) == false){
        
        pair<int, int> tmp = Levels[totalLevels-1].randomStart(maze, snake);
        if(tmp.first == -1){ // não há nenhum local para a cobra no mapa
            game_over(gameResult);
        }
        else{
            if(gameMode != 2)
                snake.grow(tmp);
            snake.setSnakeCoordinate(tmp);
            Levels[totalLevels-1].setInitialSnakeCoordinate(tmp);
        }//talvez implementar o caso em que não há local para a cobra;
    }

    if(invalidFormat == false){
        Levels[atualLevel].generateNewFood(maze, snake);
        state = RUNNING;
    }
    else
        state = GAME_OVER;
    //this_thread::sleep_for(chrono::milliseconds(5000));
}


void SnakeGame::process_actions(){
    //processa as entradas do jogador de acordo com o estado do jogo
    //nesse exemplo o jogo tem 3 estados, WAITING_USER, RUNNING e GAME_OVER.
    //no caso deste trabalho temos 2 tipos de entrada, uma que vem da classe Player, como resultado do processamento da IA
    //outra vem do próprio usuário na forma de uma entrada do teclado.
    switch(state){
        case WAITING_USER: //o jogo bloqueia aqui esperando o usuário digitar a escolha dele
            cin>>std::ws>>choice;
            if(choice == "s"){
                Levels[atualLevel].loop(maze, snake);
            }
            else{
                game_over(gameResult);
            }
            break;
        case GAME_OVER: //**
            game_over(gameResult);
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
            //início do jogo ou fase.
            if(frameCount == 0){
                //há solução
                if(motor.find_solution(maze, snake, snake.getSnakeCoordinates(), snake.getAtualPosition()) == true){ 
                    cout << "true" << endl;
                    gameResult = WIN;
                }
                else{
                    cout << "false" << endl;
                    cout << snake.getAtualPosition() << endl;
                    gameResult = LOSE;
                    snake.suicide(maze, snake);
                    this_thread::sleep_for(chrono::milliseconds(5000));
                }
            }
            // último movimento da cobra
            else if(frameCount == snake.getSolutionSize()-1){
                //caso a fruta seja encontrada e ainda não seja a última fruta do nível
                if((gameResult == WIN) && (snake.getFoodEaten()+1 < Levels[atualLevel].getTotalFood())){
                    snake.eatFood();
                    if(gameMode != 2) snake.grow(snake.getPosition(snake.getSolutionSize()-2));
                    snake.setSnakeCoordinate(snake.getPosition(snake.getSolutionSize()-1));
                    snake.updateSnakeCoordinates(maze, frameCount); //talvez -1                    
                    Levels[atualLevel].generateNewFood(maze, snake);
                    frameCount = -1;//coloquei -1 pq com o incremento no render() ele já fica 0.
                    snake.clearSolution();
                }
                //caso seja a última fruta do level
                else if((gameResult == WIN) && (snake.getFoodEaten()+1 == Levels[atualLevel].getTotalFood())){
                    //vai para o próximo level
                    if(GoToNextLevel() == true){
                        frameCount = -1;
                    }
                    //fim de jogo. imprimirá uma mensagem apropriada de acordo com o "@gameresult"
                    else{
                        game_over(gameResult);
                    }
                }

                else if((gameResult == LOSE) && (snake.getLives() > 0)){
                    snake.dead();
                    Levels[atualLevel].resetMaze(maze, snake);
                    snake.reset(snake, maze, Levels[atualLevel].getInitialSnakeCoordinate());
                    Levels[atualLevel].generateNewFood(maze, snake);
                    frameCount = -1;
                }
                else{ // perdeu o jogo.
                    snake.dead();
                    if(loopChoice == 's')
                        state = WAITING_USER;
                    else
                        game_over(gameResult);
                }
            }
            
            else{
                snake.updateSnakeCoordinates(maze, frameCount);
            }

            break;
        case WAITING_USER: //se o jogo estava esperando pelo usuário então ele testa qual a escolha que foi feita
            if(choice == "n"){
                state = GAME_OVER;
                game_over(gameResult); //alterar talvez o game result
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
void SnakeGame::updateScreen(GameStates stt){
    
    //if(stt != GAME_OVER){
        //some C++ voodoo here ;D
        #if defined _WIN32
            system("cls");
        #elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
            system("clear");
        #elif defined (__APPLE__)
            system("clear");
        #endif
    //}
    
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
    updateScreen(state);
    switch(state){
        case RUNNING:
            //adiciona a cobra ao mapa
            snake.putSnakeCoordinates(maze); 

            for(int i=0; i < maze.size(); ++i)
                cout << maze[i] << endl;
            
            break;
        case WAITING_USER:
            cout<<"Você quer continuar com o jogo? (s/n)"<<endl;
            cin >> choice;
            break;
        case GAME_OVER:
            cout<<"O jogo terminou!"<<endl;
            break;
    }
    frameCount++;
}


void SnakeGame::game_over(Result gameResult_){ //msg diferente para win, lose e caso ele queirar parar mesmo.
    if(gameResult_ == WIN){
        cout << "------------------------------------------------------------" << endl;
        cout << "\n\n\t\t\t WIN!!!\t\t\n\n";
        cout << "------------------------------------------------------------" << endl;

    }
    else{
        cout << "------------------------------------------------------------" << endl;
        cout << "\n\n\t\t\t LOSE...\t\t\n\n";
        cout << "------------------------------------------------------------" << endl;
    }
    if(loopChoice == 's') 
        state = WAITING_USER;
    else 
        state = GAME_OVER;
}


void SnakeGame::loop(){
    while(state != GAME_OVER){
        process_actions();
        update();
        render();
        wait(300);// espera 1 segundo entre cada frame
    }
}
