#include "maze.h"
#include "answer/maze_answer.h"

int main() {
    s21::Maze maze("../../../datasets/maze_files/maze2.txt");
    maze.outputMaze();
    s21::Coordinates start = {0, 0};
    s21::Coordinates end = {9, 9};
    s21::getMazeAnswer(maze, start, end);
}
