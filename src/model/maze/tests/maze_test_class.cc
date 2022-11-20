#include "maze_test_class.h"

MazeTest::MazeTest(int rows, int cols) 
    : s21::Maze() {
      m_maze_ = s21::Maze::MazeMatrix(rows, cols);
    }

void MazeTest::testFillEmptyValues() {
    s21::Maze::fillEmptyValues();
}

std::vector<int>& MazeTest::getSideLine() {
    return m_side_line_;
}

void MazeTest::testAssignUniqueSet() {
    s21::Maze::assignUniqueSet();
}

void MazeTest::testAddRightWalls(int row) {
    s21::Maze::addRightWalls(row);
}

s21::Maze::MazeMatrix MazeTest::getMazeMatrix() {
    return m_maze_;
}

