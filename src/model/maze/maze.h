#ifndef SRC_MODEL_MAZE_MAZE_H_
#define SRC_MODEL_MAZE_MAZE_H_

#include <memory>

#include "../../helpers/matrix.h"

/*
первое значение из пары ячейки матрицы:
  true - справа от ячейки есть стенка
  false - справа от ячейки нет стенки

второе значение из пары ячейки матрицы:
  true - снизу от ячейки есть стенка
  false - снизу от ячейки нет стенки
*/

namespace s21 {
#define right_wall first
#define bottom_wall second

class Maze {
 public:
  using MatrixPtr = std::unique_ptr<s21::Matrix<std::pair<bool, bool>>>;
  using MazeMatrix = s21::Matrix<std::pair<bool, bool>>;
  Maze(const std::string& file_path);
  MazeMatrix getMazeFromFile(const std::string& file_path);

 private:
  MatrixPtr m_maze_;  // указатель на матрицу, представляющую лабиринт


};  // class Maze
}  // namespace s21

#endif  // SRC_MODEL_MAZE_MAZE_H_