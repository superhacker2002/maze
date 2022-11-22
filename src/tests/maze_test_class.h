#include "model/maze/maze.h"

class MazeTest : public s21::Maze {
 public:
  MazeTest(int rows, int cols);
  void testFillEmptyValues();
  std::vector<int>& getSideLine();
  void testAssignUniqueSet();
  void testAddRightWalls(int row);
  void testAddBottomWalls(int row);
  int testCalculateUniqueSet(int element);
  void testPrepareNewLine(int row);
  void testCheckEndLine();
};