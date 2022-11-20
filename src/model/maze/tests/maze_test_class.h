#include "../maze.h"

class MazeTest : public s21::Maze {
 public:
  MazeTest(int rows, int cols);
  void testFillEmptyValues();
  std::vector<int>& getSideLine();
  void testAssignUniqueSet();
  void testAddRightWalls(int row);
  s21::Maze::MazeMatrix getMazeMatrix();
};