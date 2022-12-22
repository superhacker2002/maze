#include <fstream>
#include "../maze.h"

namespace s21 {
/**
 * Creates maze matrix of the size that was
 * provided in the first line in the file.
 * If no size was not received writes an error.
 * @param file_path Path to file we read from.
 * @return Matrix of the size received from file.
 */
Maze::MazeMatrix Maze::getMazeFromFile(const std::string &file_path) {
  std::fstream file;
  file.open(file_path);
  if (!file.is_open()) {
    m_reading_error_ = true;
    getError();
  }
  auto size = getMazeSize(file);
  Maze::MazeMatrix maze_matrix(size.first, size.second);
  file.close();
  return maze_matrix;
}

/**
 * Reads first line from file and writes
 * maze matrix rows and columns in private
 * fields of the Maze class. If reading failed
 * writes an error.
 * @param file File stream from what we read.
 */
std::pair<int, int> Maze::getMazeSize(std::fstream &file) {
  std::string buffer;
  std::pair<int, int> size;
  if (getline(file, buffer)) {
    try {
      size.first = stoi(buffer);
      buffer.erase(0, buffer.find_first_of(' ') + 1);
      size.second = stoi(buffer);
    } catch (...) {
      m_reading_error_ = true;
    }
  } else {
    m_reading_error_ = true;
  }
  getError();
  return size;
}

/**
 * Fills maze matrix cells according to
 * the digit that was received from file.
 * 1 - wall exists (true).
 * 0 - wall does not exist (false).
 * If information was not received writes an error.
 * @param file_path File name from what we read.
 * @return Filled with values maze matrix.
 */
Maze::MazeMatrix Maze::fillMazeMatrix(const std::string &file_path) {
  std::vector<Walls> maze;
  std::string buffer;
  std::fstream file(file_path);

  getline(file, buffer);
  buffer = "";
  fillRightWall(file, maze);
  getError();

  getline(file, buffer);
  fillBottomWall(file, maze);
  getError();

  auto maze_matrix = Matrix<Walls>::VectorToMatrix(maze);
  file.close();
  return maze_matrix;
}

/**
 * Reads first part of the file and fills in each cell
 * of the maze matrix if it has right wall.
 * @param file File stream from what we read.
 * @param maze Vector where we temporarily store the
 * information about right wall existence.
 */
void Maze::fillRightWall(std::fstream &file, std::vector<Walls> &maze) {
  std::string buffer;
  int rows = m_maze_.GetRows();
  int cols = m_maze_.GetCols();
  for (int i = 0; i < rows; ++i) {
    if (getline(file, buffer) && !buffer.empty()) {
      for (int j = 0; j < cols; ++j) {
        int state = stoi(buffer);
        Walls cell_walls{};
        cell_walls.right_wall = isWall(state);
        maze.emplace_back(cell_walls);
        removePrevState(buffer);
      }
    } else {
      m_reading_error_ = true;
    }
  }
  getError();
}

bool Maze::isWall(const int &state) {
  if (!(state == 0 || state == 1)) {
    m_reading_error_ = true;
    getError();
  }
  return state == 1;
}

/**
 * Removes previous digit from line in order
 * to continue getting next values.
 * @param buffer
 */
void Maze::removePrevState(std::string &buffer) {
  if (buffer.size() == 1) {
    buffer.erase(0, 1);
  } else {
    buffer.erase(0, buffer.find_first_of(' ') + 1);
  }
}

/**
 * Reads first part of the file and fills in each cell
 * of the maze matrix if it has bottom wall.
 * @param file File stream from what we read.
 * @param maze Vector where we temporarily store the
 * information about bottom wall existence.
 */
void Maze::fillBottomWall(std::fstream &file, std::vector<Walls> &maze) {
  std::string buffer;
  auto cell = maze.begin();
  int rows = m_maze_.GetRows();
  int cols = m_maze_.GetCols();
  for (int i = 0; i < rows; ++i) {
    if (getline(file, buffer) && !buffer.empty()) {
      for (int j = 0; j < cols; ++j) {
        int state = stoi(buffer);
        (*cell).bottom_wall = isWall(state);
        removePrevState(buffer);
        ++cell;
      }
    } else {
      m_reading_error_ = true;
    }
  }
  getError();
}
}  // namespace s21