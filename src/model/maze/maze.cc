#include "maze.h"
#include <fstream>

s21::Maze::Maze(const std::string& file_path) {

}

s21::Maze::MazeMatrix s21::Maze::getMazeFromFile(const std::string& file_path) {
    std::fstream file;
    file.open(file_path);
    bool reading_error = false;
    if (file.is_open()) {
        std::pair<int, int> size = getMazeSize(file, reading_error);
        if (!reading_error) {
            s21::Maze::MazeMatrix maze_matrix(size.first, size.second);
        }
    } else {
        reading_error = true;
    }
    if (reading_error) {
        throw std::exception("Parsing failed");
    }
    return maze_matrix;
}

std::pair<int, int> s21::Maze::getMazeSize(std::fstream& file, bool& reading error) {
    std::string buffer;
    int rows, cols;
    if (getline(file, buffer)) {
        try {
            rows = stoi(buffer);
            buffer.erase(0, buffer.find_first_of(' ') + 1);
            cols = stoi(buffer);
        } catch (...) {
            reading_error = true;
        }
    } else {
        reading_error = true;
    }
    return std::make_pair<int, int>(rows, cols);
}

s21::Maze::fillMazeMatrix(std::fstream& file) {
    std::string buffer;
    bool reading_error = false;
    for (size_t line = 0; line < GetRows(); ++line) {
        if (getline(file, buffer)) {
            int j = 0;
            while (buffer.size() > 0) {

            }
        }
    }
}




