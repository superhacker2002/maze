#include "maze.h"
#include "maze_answer.h"

int main() {
    s21::Maze maze("maze1.txt");
    maze.outputMaze();
    s21::Coordinates start = {0, 0};
    s21::Coordinates end = {4, 4};
    s21::getMazeAnswer(maze, start, end);
}
