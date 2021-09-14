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
        /**
        * @brief construtor.
        **/
        Snake(){
            lives = 5;
            score = 0;
            FoodEaten = 0;
            atualPosition = 3;
            snake_coordinate = make_pair(-1, -1);
        }

        /**
        * @brief adiciona uma coordenada ao corpo da cobra, fazendo ela "crescer".
        * @param pos coordenada que será adicionada.
        **/
        void grow(pair<int, int> pos){
            snake_body.push_back(pos);
        }

        /**
        * @brief modifica alguns atributos, quando come uma comida.
        **/
        void eatFood(){
            ++FoodEaten;
            score += 10; //<! temporário
            
        }

        /**
        * @brief exclui todos as coorrdenadas do atributo solution.
        **/
        void clearSolution(){
            solution.clear();
        }

        /**
        * @brief adiciona uma coordenada à solução.
        * @param position coordenada que será adicionada.
        **/
        void addToSolution(pair<int, int> position){
            //snake_coordinate = position;
            solution.push_back(position);
        }

        /**
        * @brief remove a última coordenada da solução.
        **/
        void removeFromSolution(){
            solution.erase(solution.end()-1);
        }

        /**
        * @brief define a coordenada de onde a "cabeça" da cobra está.
        **/
        void setSnakeCoordinate(pair<int, int> snake_coordinate){
            this->snake_coordinate = snake_coordinate;
        }

        /**
        * @return coordenada de onde a "cabeça" da cobra está.
        **/
        pair<int, int> getSnakeCoordinates(){
            return snake_coordinate;
        }

        /**
        * @brief verifica se uma coordenada se choca com o corpo da cobra.
        * @param pos posição que será verificada.
        * @return true caso se choca; falso caso contrário.
        **/
        bool insideSnake(pair<int, int> pos){
            for(int i=0; i < snake_body.size(); ++i){
                if(pos == snake_body[i])
                    return true;
            }
            return false;
        }

        /**
        * @brief adiciona as coordenadas do corpo da cobra ao labirinto
        * @param maze labirinto que será adicionado o corpo da cobra.
        **/
        void putSnakeCoordinates(vector<string> &maze){
            //maze[snake_coordinate.first][snake_coordinate.second] = 'V';
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
        /**
        * @brief atualiza as coordenadas do corpo da cobra, com base nas coordenadas armazenadas
        * na solução.
        * @param maze labirinto que será adicionado o corpo da cobra.
        * @param cnt índice da coordenada armazenada na solução
        **/
        void updateSnakeCoordinates(vector<string> &maze, int cnt){
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


        /**
        * @brief retorna uma coordenada específica da solução.
        * @param index índice específico da coordenada;
        * @return coordenada específica.
        **/
        pair<int, int> getPosition(int index){
            return solution[index];
        }

        /**
        * @brief retorna o tamanho da solution.
        **/
        int getSolutionSize(){
            return solution.size();
        }


        void dead(){
            --lives;
        }
        
        /**
        * @brief retorna a quantidade atual de vidas da cobra.
        **/
        int getLives(){
            return lives;
        }

        /**
        * @brief define a quantidade de vezes que a cobra comeu uma fruta.
        **/
        void setFoodEatean(int FoodEaten){
            this->FoodEaten = FoodEaten;
        }

        /**
        * @brief retorna a quantidade de vezes que a cobra comeu uma fruta.
        **/
        int getFoodEaten(){
            return FoodEaten;
        }

        /**
        * @brief define a direção atual da cobra. (0 == NORTH, 1 == SOUTH, 2 == WEST, 3 == EAST)
        **/
        void setAtualPosition(int atualPosition){
            this->atualPosition = atualPosition;
        }

        /**
        * @brief retorna a direção atual da cobra. (0 == NORTH, 1 == SOUTH, 2 == WEST, 3 == EAST)
        **/
        int getAtualPosition(){
            return atualPosition;
        }

        /**
        * @brief verifica se uma coordenada dada não foi visitada pela cobra.
        * @param pos coordenada que será verificada
        * @return true caso não tenha sido visitada; false caso contrário.
        **/
        bool unvisited(pair<int, int> pos){
            for(int i=0; i < solution.size(); ++i){
                if(solution[i] == pos){
                    return false;
                }
            }
            return true;
        }

        /**
        * @brief verifica se uma coordenada dada é uma fruta ('@').
        * @param pos coordenada que será verificada
        * @return true caso seja uma fruta; false caso contrário.
        **/
        bool goal(vector<string> maze, pair<int, int> pos){
            return maze[pos.first][pos.second] == '@' ? true : false;
        }

        /**
        * @brief verifica se uma coordenada dada é um caminho válido para a cobra ir.
        * @param pos coordenada que será verificada
        * @return true caso seja uma coordenada válida; false caso contrário.
        **/
        bool validPath(vector<string> maze, pair<int, int> pos){
            //cout << "entrou valid path" << endl;
            //cout << "maze[pos]: " << maze[pos.first][pos.second] << endl;
            return (maze[pos.first][pos.second] == ' ' || maze[pos.first][pos.second] == '*') 
                    || (maze[pos.first][pos.second] == 'X') ? true : false;
        }

        /** 
        * @brief define a posição que a cobra ficará virada.
        * @param pos coordenada que será verificada
        * @return true caso alguma coordenada ao redor dela não seja 
        * uma parede; false caso contrário.
        **/
        bool define_direction(vector<string> &maze, pair<int, int> pos){
            //cout << "entrou find_dir " << pos.first << ' ' <<  pos.second << endl;
            //cout << maze[pos.first][pos.second] << endl;
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

        /** 
        * @brief reseta todos os atributos da cobra. acontece quando ela morre.
        * @param snake a cobra.
        * @param maze o labirinto atual.
        * @param coordinate coordenada inicial da cobra.
        **/
        void reset(Snake &snake, vector<string> &maze, pair<int, int> coordinate){

            snake_body.clear();
            solution.clear();
            FoodEaten = 0;
            // if(define_direction(maze, coordinate) == false){
            //     //pair<int, int> t = Levels[aL].randomStart(maze, snake);
            //     //algo aqui
            // }
            snake.grow(coordinate);
            snake.setSnakeCoordinate(coordinate);
            define_direction(maze, coordinate);
            //solution.push_back(coordinate); //<! temporário.  

        }

        /**         
        * @brief gera um caminho ao suicidio para a cobra. é chamada quando não há solução.
        * @param maze o labirinto atual.
        * @param snake a cobra.
        **/
        void suicide(vector<string> &maze, Snake &snake){
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
};

#endif //Snake_h