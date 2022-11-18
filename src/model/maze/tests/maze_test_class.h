#include "../maze.h"

class MazeTest : public s21::Maze {
 public:
  MazeTest(int rows, int cols);
  
  void testFillEmptyValues();
  std::vector<int>& getSideLine() { return m_side_line_; }
};