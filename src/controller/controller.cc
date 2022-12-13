#include "controller.h"
#include "../model/maze/maze_answer.h"

// Cave
void s21::Controller::GetRandomCave(size_t rows, size_t cols,
          s21::Limits limit, int birth_chance) {
  m_cave_ = std::make_unique<s21::Cave>(rows, cols, limit, birth_chance);
}

void s21::Controller::GetCaveFromFile(const std::string& file_path, s21::Limits limit) {
  m_cave_ = std::make_unique<s21::Cave>(file_path, limit);
}

int s21::Controller::GetCaveRows() {
  return m_cave_->GetRows();
}

int s21::Controller::GetCaveCols() {
  return m_cave_->GetCols();
}

bool s21::Controller::GetPixel(int i, int j) {
  return m_cave_->GetValue(i, j);
}

bool s21::Controller::TransformOnce() {
  return m_cave_->Transform();
}

void s21::Controller::FlipCave() {
  m_cave_->FlipCave();
}

bool s21::Controller::CaveExists() {
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

s21::Walls s21::Controller::GetWall(int i, int j) {
  return m_maze_.get()->GetValue(i, j);
}

std::vector<QLineF> s21::Controller::GetAnswer(std::pair<int, int> p1, std::pair<int, int> p2) {
  s21::Coordinates start = {p1.second, p1.first};
  s21::Coordinates end = {p2.second, p2.first};
  auto answer = s21::getMazeAnswer(*m_maze_, start, end);
  return s21::GetAnswerDrawData(*m_maze_, answer, start, end);
}

bool s21::Controller::MazeExists() {
  return m_maze_ != nullptr; 
}

std::vector<QLineF> s21::Controller::GetMazeDrawData() {
  return s21::GetMazeDrawData(*m_maze_);
}

void s21::Controller::SaveMaze(const std::string& file_path) {
  std::ofstream file;
  file.open(file_path, std::ios_base::out);
  if (file.is_open() && MazeExists()) {
    file << *m_maze_.get();
  }
}
