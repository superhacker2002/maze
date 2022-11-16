#include "maze.h"
#include <fstream>

s21::Maze::Maze(const std::string& file_path)
    : m_maze_(std::make_unique<s21::Maze::MazeMatrix>(getMazeFromFile(file_path))),
      reading_error_(false) {
    *(m_maze_.get()) = std::move(fillMazeMatrix(file_path));
}

s21::Maze::MazeMatrix s21::Maze::getMazeFromFile(const std::string& file_path) {
    std::fstream file;
    file.open(file_path);
    std::pair<int, int> size;
    if (!file.is_open()) {
        reading_error_ = true;
    } else {
        size = getMazeSize(file);
    }
    try {
        getError();
    } catch (...) {
        std::cout << "Parsing failed";
    }

    s21::Maze::MazeMatrix maze_matrix(size.first, size.second);
    file.close();
    return maze_matrix;
}

void s21::Maze::getError() const {
    if (reading_error_) {
        throw std::invalid_argument("Parsing failed.");
    }
}

std::pair<int, int> s21::Maze::getMazeSize(std::fstream& file) {
    std::string buffer;
    int rows, cols;
    if (getline(file, buffer)) {
        try {
            rows = stoi(buffer);
            buffer.erase(0, buffer.find_first_of(' ') + 1);
            cols = stoi(buffer);
        } catch (...) {
            reading_error_ = true;
        }
    } else {
        reading_error_ = true;
    }
    getError();
    return std::make_pair(rows, cols);
}

s21::Maze::MazeMatrix s21::Maze::fillMazeMatrix(const std::string& file_path) {
    std::vector<std::pair<bool, bool>> maze;
    std::string buffer;
    std::fstream file(file_path);
    getline(file, buffer);
    buffer = "";
    fillRightWall(file, maze);
    getline(file, buffer);
    fillBottomWall(file, maze);
    auto maze_matrix = s21::Matrix<std::pair<bool, bool>>::VectorToMatrix(maze);
    return maze_matrix;
}

void s21::Maze::fillRightWall(std::fstream& file, std::vector<std::pair<bool, bool>>& maze) {
    std::string buffer;
    for (size_t i = 0; i < m_maze_->GetRows(); ++i) {
        if (getline(file, buffer)) {
            while (!buffer.empty()) {
                int state = stoi(buffer);
                if (state == 0) {
                    maze.emplace_back(std::make_pair(false, false));
                } else if (state == 1) {
                    maze.emplace_back(std::make_pair(true, false));
                } else {
                    reading_error_ = true;
                }
                if (state == 0 || state == 1) {
                    if (buffer.size() == 1) {
                        buffer.erase(0, 1);
                    } else {
                        buffer.erase(0, buffer.find_first_of(' ') + 1);
                    }
                }
            }
        } else {
            reading_error_ = true;
        }
    }
}

void s21::Maze::fillBottomWall(std::fstream& file, std::vector<std::pair<bool, bool>>& maze) {
    std::string buffer;
    auto cell = maze.begin();
    for (size_t i = 0; i < m_maze_->GetRows(); ++i) {
        getline(file, buffer);
        for (size_t j = 0; j < m_maze_->GetCols(); ++j) {
            if (!buffer.empty()) {
                int state = stoi(buffer);
                if (state == 1) {
                    (*cell).second = true;
                } else if (state != 0) {
                    reading_error_ = true;
                }
                if (state == 0 || state == 1) {
                    if (buffer.size() == 1) {
                        buffer.erase(0, 1);
                    } else {
                        buffer.erase(0, buffer.find_first_of(' ') + 1);
                    }
                }
            }
            ++cell;
        }
    }
}

void s21::Maze::outputMaze() {
    std::cout << "- - - - - - -\n";
    for (size_t i = 0; i < m_maze_->GetRows(); ++i) {
        for (size_t j = 0; j < m_maze_->GetCols(); ++j) {
            if (j == 0) std::cout << "|";
            bool right_wall = ((*(m_maze_.get()))(i, j)).first;
            bool bottom_wall = ((*(m_maze_.get()))(i, j)).second;
            if (bottom_wall) std::cout << "_";
            else std::cout << " ";
            if (right_wall) std::cout << " |";
            else if (bottom_wall && right_wall) std::cout << "|";
            else std::cout << "  ";
        }
        std::cout << "\n";

    }

}




