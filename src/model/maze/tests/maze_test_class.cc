#include "maze_test_class.h"

MazeTest::MazeTest(int rows, int cols) 
    : s21::Maze() {
      m_maze_ = s21::Maze::MazeMatrix(rows, cols);
      m_rows_ = rows;
      m_cols_ = cols;
    }

void MazeTest::testFillEmptyValues() {
    s21::Maze::fillEmptyValues();
}

// std::vector<int> getSideLine() {
//     return ;
// }

