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
//#define right_wall first
//#define bottom_wall second

class Maze {
 public:
  using MatrixPtr = std::unique_ptr<s21::Matrix<std::pair<bool, bool>>>;
  using MazeMatrix = s21::Matrix<std::pair<bool, bool>>;
  explicit Maze(const std::string& file_path);
  MazeMatrix getMazeFromFile(const std::string& file_path);
  std::pair<int, int> getMazeSize(std::fstream& file);
  MazeMatrix fillMazeMatrix(const std::string &file_path);
  void fillRightWall(std::fstream& file, std::vector<std::pair<bool, bool>>& maze);
  void fillBottomWall(std::fstream& file, std::vector<std::pair<bool, bool>>& maze);
  void outputMaze();
  void getError() const;
 private:
  MatrixPtr m_maze_;  // указатель на матрицу, представляющую лабиринт
  bool reading_error_;


};  // class Maze
}  // namespace s21

#endif  // SRC_MODEL_MAZE_MAZE_H_