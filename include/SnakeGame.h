#ifndef SnakeGame_h
#define SnakeGame_h
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "../include/Level.h"
#include "../include/Player.h"
#include "../include/Snake.h"

using namespace std;

class SnakeGame{
    public:
        /**
        * @brief descreve os possíveis estados do jogo, fique à vontade para adicionar outros se necessário
        **/
        enum GameStates{
            RUNNING, //<! quando o jogo está executando o estado é RUNNING
            GAME_OVER, //<! quando o jogo deve terminar o estado é GAME_OVER
            WAITING_USER //<! quando o jogo deve esperar por uma entrada do usuário o estado é WAITING_USER
        };

    private:
        //<! atributos adicione outros se quiser
        int gameMode; //guarda o modo de jogo.
        Player test; //<! testando o motor da IA
        Snake snake;
        std::vector<Level> Levels;
        std::vector<std::string> maze;
        int atualLevel, totalLevels;
        int frameCount; //<! contador de frames, usado apenas como exemplo
        std::string choice; //<! usado na função process_actions para guardar a escolha do usuário
        GameStates state; //<! guarda o estado do jogo

    public:
        /**
        * @brief construtor padrão, fique à vontade para adicionar parâmetros se desejar
        **/
        SnakeGame();

        /**
        * @brief chamado no main, este loop executa o jogo indefinidamente até que o usuário escolha terminar!
        */
        void loop();

        /**
        * @brief função auxiliar para limpar o terminal
        */
        void updateScreen();

    private:
        /**
        * @brief realiza a inicialização geral do jogo, fique à vontade para adicionar parâmetros se achar que deve
        **/
        void initialize_game();

        /**
        * @brief atualiza o estado do jogo, basicamente movendo os objetos, sorteando novas posições de comida
        **/
        void update();

        /**
        * @brief processa as entradas do jogador
        **/
        void process_actions();

        /**
        * @brief testa o estado do jogo e desenha a tela correspondente
        **/
        void render();

        /**
        * @brief é chamada quando o jogo termina a fim de destruir/resetar elementos do estado do jogo
        **/
        void game_over();

        /**
        * @brief é chamada ao ser  identificada, na entrada, um novo level(nova pos de linhas, colunas e número de comidas). Define características de tal level. 
        @param line linha contendo as informações do level linhas, colunas e número de comidas.
        @return true caso tenha um número válido de linhas e colunas. falso casao contrário.
        **/
        bool setNewLevel(string line);

        /**
        * @brief é chamada quando um novo nível é alcançado. 
        @param maze labirinto atual do nível.
        @param Levels vector que possui informações de todos os níveis.
        @return true caso haja um novo nível; falso caso não haja um próximo nível.
        **/
        bool GoToNextLevel(vector<string> &maze, vector<Level> &Levels);

        /**
        * @brief verifica se, dada uma linha, tal linha possui a coordenada de onde a cobra vai nascer(o char '*'), bem como armazena esta coordenada. 
        @param lineCount contador que possui o valor da linha atual.
        @param line linha que vai ser verificada
        @param snake a cobra do nível emm questão.
        @return true caso o char '*' esteja na linha; falso caso contrário.
        **/
        bool tryGetSnakeCoordinates(int lineCount, string line, Snake &snake);
};

#endif //SnakeGame_h