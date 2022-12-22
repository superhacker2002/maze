#ifndef SRC_MODEL_MAZE_MAZE_H_
#define SRC_MODEL_MAZE_MAZE_H_

#include "../helpers/data_structures.h"
#include "fstream"

namespace s21 {
constexpr int EMPTY = 0;
class Maze {
 public:
  using MazeMatrix = s21::Matrix<Walls>;

  explicit Maze(const std::string& file_path);
  explicit Maze(int rows, int cols);
  void outputMaze();
  int GetRows() const;
  int GetCols() const;
  Walls GetValue(int i, int j);

  friend std::ofstream& operator<<(std::ofstream& file, const Maze& maze);

 protected:
  bool m_reading_error_;
  MazeMatrix m_maze_;
  std::vector<int> m_side_line_;
  int m_counter_;

  Maze();
  void generateMaze();

  void fillEmptyValues();
  void assignUniqueSet();
  void addRightWalls(int row);
  void mergeSet(int index, int element);
  void addBottomWalls(int row);
  int calculateUniqueSet(int element);
  void checkBottomWall(int row);
  int calculateBottomWalls(int element, int row);
  void prepareNewLine(int row);
  void addEndLine();
  void checkEndLine();
  void writeMazeToFile();

  MazeMatrix getMazeFromFile(const std::string& file_path);

  std::pair<int, int> getMazeSize(std::fstream& file);
  MazeMatrix fillMazeMatrix(const std::string& file_path);
  void fillRightWall(std::fstream& file, std::vector<Walls>& maze);
  void fillBottomWall(std::fstream& file, std::vector<Walls>& maze);
  bool isWall(const int& state);
  void removePrevState(std::string& buffer);
  void getError() const;

};  // class Maze
}  // namespace s21

#endif  // SRC_MODEL_MAZE_MAZE_H_
