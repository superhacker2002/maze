#include "maze.h"
#include <fstream>

/**
 * Creates maze matrix of the size that was
 * provided in the first line in the file.
 * If no size was not received writes an error.
 * @param file_path Path to file we read from.
 * @return Matrix of the size received from file.
 */
s21::Maze::MazeMatrix s21::Maze::getMazeFromFile(const std::string& file_path) {
    std::fstream file;
    file.open(file_path);
    if (!file.is_open()) {
        m_reading_error_ = true;
        getError();
    }
    getMazeSize(file);
    s21::Maze::MazeMatrix maze_matrix(rows_, cols_);
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
void s21::Maze::getMazeSize(std::fstream& file) {
    std::string buffer;
    if (getline(file, buffer)) {
        try {
            rows_ = stoi(buffer);
            buffer.erase(0, buffer.find_first_of(' ') + 1);
            cols_ = stoi(buffer);
        } catch (...) {
            m_reading_error_ = true;
        }
    } else {
        m_reading_error_ = true;
    }
    getError();
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
s21::Maze::MazeMatrix s21::Maze::fillMazeMatrix(const std::string& file_path) {
    std::vector<walls> maze;
    std::string buffer;
    std::fstream file(file_path);

    getline(file, buffer);
    buffer = "";
    fillRightWall(file, maze);
    getError();

    getline(file, buffer);
    fillBottomWall(file, maze);
    getError();

    auto maze_matrix = s21::Matrix<s21::walls>::VectorToMatrix(maze);
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
void s21::Maze::fillRightWall(std::fstream& file, std::vector<s21::walls>& maze) {
    std::string buffer;
    for (int i = 0; i < rows_; ++i) {
        if (getline(file, buffer) && !buffer.empty()) {
            for (int j = 0; j < cols_; ++j) {
                int state = stoi(buffer);
                s21::walls cell_walls {};
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

bool s21::Maze::isWall(const int& state) {
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
void s21::Maze::removePrevState(std::string& buffer) {
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
void s21::Maze::fillBottomWall(std::fstream& file, std::vector<s21::walls>& maze) {
    std::string buffer;
    auto cell = maze.begin();
    for (int i = 0; i < rows_; ++i) {
        if (getline(file, buffer) && !buffer.empty()) {
            for (int j = 0; j < cols_; ++j) {
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