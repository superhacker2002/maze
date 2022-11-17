#include "controller.h"

void s21::Controller::GetRandomCave(size_t rows, size_t cols,
          s21::Cave::Limits limit, int birth_chance) {
  m_cave_ = std::make_unique<s21::Cave>(rows, cols, limit, birth_chance);
}

void s21::Controller::GetMazeFromFile(const std::string& file_path) {
  m_maze_ = std::make_unique<s21::Maze>(file_path);
}

void s21::Controller::GenerateMaze(int rows, int cols) {
    m_maze_ = std::make_unique<s21::Maze>(rows, cols);
}

