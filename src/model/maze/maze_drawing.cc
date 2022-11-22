#include "maze_drawing.h"

namespace s21 {
std::vector<QLineF> GetAnswerDrawData(s21::Maze maze, std::vector<int>& answer,
                                         Coordinates& start,  Coordinates& end) {
  std::vector<QLineF> lines;
  int x_size = 500 / maze.GetRows();
  int y_size = 500 / maze.GetCols();
  float x1 = start.x * 0.5;
  float y1 = start.y * 0.5;
  float x2 = end.x * 0.5;
  float y2 = end.y * 0.5;
  x1 *= x_size, y1 *= y_size;
  for (auto& direction : answer) {
    if (direction == LEFT) {
      x2 = x1 - x_size;
      y2 = y1;
    } else if (direction == RIGHT) {
      x2 = x1 + x_size;
      y2 = y1;
    } else if (direction == UP) {
      x2 = x1;
      y2 = y1 - y_size;
    } else if (direction == DOWN){
      x2 = x1;
      y2 = y1 + y_size;
    }
    lines.push_back(QLineF(x1, y1, x2, y2));
    x1 = x2, y1 = y2;
  }
  return lines;
}

std::vector<QLineF> GetMazeDrawData(s21::Maze& maze) {
  std::vector<QLineF> data;
  int rows = maze.GetRows();
  int cols = maze.GetCols();
  int x_size = 500 / rows, y_size = 500 / cols;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (maze.GetValue(i, j).bottom_wall) {
        int x1 = j * x_size == 0 ? 10 : j * x_size;
        int y1 = (i + 1) * y_size == 0 ? 10 : (i + 1) * y_size;
        int x2 = x1 + x_size == 0 ? 10 : x1 + x_size;
        int y2 = y1;
        data.push_back(QLineF(x1, y1, x2, y2));
      }
      if (maze.GetValue(i, j).right_wall) {
        int x1 = (j + 1) * x_size == 0 ? 10 : (j + 1) * x_size;
        int y1 = i * y_size == 0 ? 10 : i * y_size;
        int x2 = x1;
        int y2 = y1 + y_size == 0 ? 10 : y1 + y_size;
        data.push_back(QLineF(x1, y1, x2, y2));
      }
    }
  }
  return data;
}
}
