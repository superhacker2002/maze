#include "maze.h"
#include <fstream>

s21::Maze::Maze(const std::string& file_path)
    : m_maze_(std::make_unique<s21::Maze::MazeMatrix>(getMazeFromFile(file_path))),
      reading_error_(false) {
    try {
        *(m_maze_.get()) = fillMazeMatrix(file_path);
    } catch (...) {
        reading_error_ = true;
        getError();
    }
}

void s21::Maze::getError() const {
    if (reading_error_) {
        throw std::invalid_argument("Parsing failed.");
    }
}

s21::Maze::MazeMatrix s21::Maze::getMazeFromFile(const std::string& file_path) {
    std::fstream file;
    file.open(file_path);
    if (!file.is_open()) {
        reading_error_ = true;
        getError();
    }
    getMazeSize(file);
    s21::Maze::MazeMatrix maze_matrix(rows_, cols_);
    file.close();
    return maze_matrix;
}

void s21::Maze::getMazeSize(std::fstream& file) {
    std::string buffer;
    if (getline(file, buffer)) {
        try {
            rows_ = stoi(buffer);
            buffer.erase(0, buffer.find_first_of(' ') + 1);
            cols_ = stoi(buffer);
        } catch (...) {
            reading_error_ = true;
        }
    } else {
        reading_error_ = true;
    }
    getError();
}

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
    return maze_matrix;
}

void s21::Maze::fillRightWall(std::fstream& file, std::vector<s21::walls>& maze) {
    std::string buffer;
    for (size_t i = 0; i < rows_; ++i) {
        if (getline(file, buffer) && !buffer.empty()) {
             for (size_t j = 0; j < cols_; ++j) {
                int state = stoi(buffer);
                s21::walls cell_walls {};
                cell_walls.right_wall = isWall(state);
                maze.emplace_back(cell_walls);
                removePrevState(buffer);
            }
        } else {
            reading_error_ = true;
        }
    }
    getError();
}

bool s21::Maze::isWall(const int& state) {
    if (!(state == 0 || state == 1)) {
        reading_error_ = true;
        getError();
    }
    return state == 1;
}

void s21::Maze::removePrevState(std::string& buffer) {
    if (buffer.size() == 1) {
        buffer.erase(0, 1);
    } else {
        buffer.erase(0, buffer.find_first_of(' ') + 1);
    }
}

void s21::Maze::fillBottomWall(std::fstream& file, std::vector<s21::walls>& maze) {
    std::string buffer;
    auto cell = maze.begin();
    for (size_t i = 0; i < rows_; ++i) {
        if (getline(file, buffer) && !buffer.empty()) {
            for (size_t j = 0; j < cols_; ++j) {
                int state = stoi(buffer);
                (*cell).bottom_wall = isWall(state);
                removePrevState(buffer);
                ++cell;
            }
        } else {
            reading_error_ = true;
        }
    }
    getError();
}

void s21::Maze::outputMaze() {
    std::cout << "- - - - - - -\n";

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (j == 0) {
                std::cout << "|";
            }
            bool right_wall = ((*(m_maze_.get()))(i, j)).right_wall;
            bool bottom_wall = ((*(m_maze_.get()))(i, j)).bottom_wall;
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




