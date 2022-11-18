#include "maze.h"

int main() {
    s21::Maze maze("generated_maze.txt");
    maze.outputMaze();
//    std::ofstream file("generated_maze.txt");
//    file << maze;
//    file.close();
}
