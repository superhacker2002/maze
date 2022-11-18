#ifndef SRC_MODEL_MAZE_MAZE_H_
#define SRC_MODEL_MAZE_MAZE_H_

#include "../../helpers/matrix.h"
#include "fstream"

namespace s21 {
struct  walls {
  bool right_wall;  // стенка справа от ячейки
  bool bottom_wall;  // стенка снизу от ячейки
};
enum directions {
  kLEFT,
  kRIGHT,
  kTOP,
  kBOTTOM
};
constexpr int kEMPTY = 0;

class Maze {
 public:
  using MazeMatrix = s21::Matrix<walls>;
  using AnswerData = std::vector<float>;

  Maze() = default;
  explicit Maze(const std::string& file_path);
  explicit Maze(int rows, int cols);
  void outputMaze();
  int GetRows();
  int GetCols();
  walls GetValue(int i, int j);
  AnswerData GetAnswer(std::pair<int, int> point1, std::pair<int, int> point2);

  friend std::ofstream& operator<<(std::ofstream& file, const Maze& maze);

 protected:
  bool m_reading_error_;
  MazeMatrix m_maze_;
  std::vector<int> m_side_line_;
  int m_counter_;

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

  std::pair<int, int>& getMazeSize(std::fstream& file);
  MazeMatrix fillMazeMatrix(const std::string &file_path);
  void fillRightWall(std::fstream& file, std::vector<walls>& maze);
  void fillBottomWall(std::fstream& file, std::vector<walls>& maze);
  bool isWall(const int& state);
  void removePrevState(std::string& buffer);
  void getError() const;
};  // class Maze
}  // namespace s21

#endif  // SRC_MODEL_MAZE_MAZE_H_