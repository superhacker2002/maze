#include "maze.h"
#include "maze_answer.h"

int main() {
    s21::Maze maze(6, 6);
    maze.outputMaze();
    s21::Coordinates start = {0, 0};
    s21::Coordinates end = {5, 5};
    s21::getMazeAnswer(maze, start, end);
}
