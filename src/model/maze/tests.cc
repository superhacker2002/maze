#include "maze.h"
#include "answer/maze_answer.h"

int main() {
    s21::Maze maze(4, 4);
    maze.outputMaze();
    s21::Coordinates start = {1, 0};
    s21::Coordinates end = {3, 3};
    s21::getMazeAnswer(maze, start, end);
}
