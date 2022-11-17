#include "maze.h"
#include <fstream>

/**
 * Constructor for initializing maze from file.
 * @param file_path Path to file to read maze from.
 */
s21::Maze::Maze(const std::string& file_path)
    : m_reading_error_(false),
    m_maze_(getMazeFromFile(file_path)) {
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
s21::Maze::Maze(int rows, int cols)
    : m_reading_error_(false),
    m_maze_(s21::Maze::MazeMatrix(rows, cols)),
    m_rows_(rows),
    m_cols_(cols),
    m_counter_(1) {
    generateMaze();
}

int s21::Maze::GetRows() { return m_maze_.GetRows(); }

int s21::Maze::GetCols() { return m_maze_.GetCols(); }

s21::walls s21::Maze::GetValue(int i, int j) { return m_maze_(i, j); }

/**
 * Indicates if error occurred while program was running
 * and throw an exception.
 */
void s21::Maze::getError() const {
    if (m_reading_error_) {
        throw std::invalid_argument("Parsing failed.");
    }
}

void s21::Maze::outputMaze() {
    std::cout << " - - - - - - - - \n";

    for (int i = 0; i < m_rows_; ++i) {
        for (int j = 0; j < m_cols_; ++j) {
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




