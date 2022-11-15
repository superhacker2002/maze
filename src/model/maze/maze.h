#ifndef SRC_MODEL_MAZE_MAZE_H_
#define SRC_MODEL_MAZE_MAZE_H_

#include <memory>

#include "../../helpers/matrix.h"

/*
первое значенине из пары ячейки матрицы : 
  true - справа от ячейки есть стенка
  false - справа от ячейки нет стенки

второе значенине из пары ячейки матрицы:
  true - снизу от ячейки есть стенка
  false - снизу от ячейки нет стенки
*/

namespace s21 {
class Maze {
 public:
  using __mtrx_ptr = std::unique_ptr<s21::Matrix<std::pair<bool, bool>>>;
#define right_wall first
#define bottom_wall second


 private:
  __mtrx_ptr m_maze_;  // указатель на матрицу, представляющую лабиринт




};  // class Maze
}  // namespace s21

#endif  // SRC_MODEL_MAZE_MAZE_H_