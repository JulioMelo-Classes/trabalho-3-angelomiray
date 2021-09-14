cmake_minimum_required(VERSION 3.5)
project(LP1-Snaze VERSION 0.1 LANGUAGES CXX )


### Executável
# Diretório contendo os .hpp
include_directories( include )

# Cria um executável com nome "snaze", adiciona neste executável os arquivos
add_executable( snaze
                src/SnakeGame.cpp
                src/Snaze.cpp
                )

# The end



