#include "maze.h"

namespace s21 {
/**
 * Constructor for initializing maze from file.
 * @param file_path Path to file to read maze from.
 */
Maze::Maze(const std::string &file_path)
    : m_reading_error_(false), m_maze_(getMazeFromFile(file_path)) {
  try {
    m_maze_ = fillMazeMatrix(file_path);
  } catch (...) {
    m_reading_error_ = true;
    getError();
  }
}

/**
 * Constructor for generating maze with single
 * input and single output using Eller's algorithm.
 * @param rows Number of rows in maze.
 * @param cols Number of cells in the row in maze.
 */
Maze::Maze(int rows, int cols)
    : m_reading_error_(false),
      m_maze_(Maze::MazeMatrix(rows, cols)),
      m_counter_(1) {
  generateMaze();
}

Maze::Maze()
    : m_reading_error_(false),
      m_maze_(s21::Maze::MazeMatrix(5, 5)),
      m_counter_(1) {}

int Maze::GetRows() const { return m_maze_.GetRows(); }

int Maze::GetCols() const { return m_maze_.GetCols(); }

Walls Maze::GetValue(int i, int j) { return m_maze_(i, j); }

/**
 * Indicates if error occurred while program was running
 * and throws an exception.
 */
void Maze::getError() const {
  if (m_reading_error_) {
    throw std::invalid_argument("Parsing failed.");
  }
}

void hasWall(bool is_wall, std::string &maze_str) {
  if (is_wall) {
    maze_str.append("1 ");
  } else {
    maze_str.append("0 ");
  }
}

/**
 * Operator that allows to write maze in file
 * that was defined by user in specific format.
 * @param file File stream where maze will be written.
 * @param maze Filled maze that will be written to the file.
 * @return ofstream with written maze.
 */
std::ofstream &operator<<(std::ofstream &file, const Maze &maze) {
  std::string maze_str;
  int rows = maze.m_maze_.GetRows();
  int cols = maze.m_maze_.GetCols();
  maze_str.append(std::to_string(rows) + " " + std::to_string(cols) + "\n");
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      hasWall(maze.m_maze_.at(i, j).right_wall, maze_str);
    }
    maze_str.append("\n");
  }
  maze_str.append("\n");
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      hasWall(maze.m_maze_.at(i, j).bottom_wall, maze_str);
    }
    maze_str.append("\n");
  }

  file << maze_str;
  return file;
}

void Maze::outputMaze() {
  std::cout << " - - - - - - - - \n";
  int rows = m_maze_.GetRows();
  int cols = m_maze_.GetCols();

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (j == 0) {
        std::cout << "|";
      }
      bool right_wall = (m_maze_(i, j)).right_wall;
      bool bottom_wall = (m_maze_(i, j)).bottom_wall;
      if (bottom_wall) {
        std::cout << "_";
      } else {
        std::cout << " ";
      }
      if (right_wall) {
        std::cout << " |";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << "\n";
  }
}

}  // namespace s21
