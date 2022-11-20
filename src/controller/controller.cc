#include "controller.h"

  // Cave
void s21::Controller::GetRandomCave(size_t rows, size_t cols,
          s21::Limits limit, int birth_chance) {
  m_cave_ = std::make_unique<s21::Cave>(rows, cols, limit, birth_chance);
}

int s21::Controller::GetCaveRows() {
  return m_cave_.get()->GetRows();
}

int s21::Controller::GetCaveCols() {
  return m_cave_.get()->GetCols();
}

bool s21::Controller::GetPixel(int i, int j) {
  return m_cave_.get()->GetValue(i, j);
}

void s21::Controller::TransformOnce() {
  m_cave_.get()->Transform();
}

void s21::Controller::TransformTillEnd() {
  m_cave_.get()->TransformCycle();
}

void s21::Controller::FlipCave() {
  m_cave_.get()->FlipCave();
}

bool s21::Controller::DoesCaveExist() {
  return m_cave_ != nullptr;
}

std::vector<QRectF> s21::Controller::GetCaveDrawData() {
  return m_cave_->GetDrawData();
}

  // Maze
void s21::Controller::GetMazeFromFile(const std::string& file_path) {
  m_maze_ = std::make_unique<s21::Maze>(file_path);
}

void s21::Controller::GenerateMaze(int rows, int cols) {
    m_maze_ = std::make_unique<s21::Maze>(rows, cols);
}

int s21::Controller::GetMazeRows() {
  return m_maze_.get()->GetRows();
}

int s21::Controller::GetMazeCols() {
  return  m_maze_.get()->GetCols();
}

s21::walls s21::Controller::GetWall(int i, int j) {
  return m_maze_.get()->GetValue(i, j);
}

std::vector<QLineF> s21::Controller::GetAnswer(std::pair<int, int> p1, std::pair<int, int> p2) {
  return m_maze_->GetAnswer(p1, p2);
}

bool s21::Controller::DoesMazeExist() {
  return m_maze_ != nullptr; 
}

std::vector<QLineF> s21::Controller::GetMazeDrawData() {
  return m_maze_->GetDrawData();
}