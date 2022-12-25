#include "controller.h"
#include "../model/maze/answer/maze_answer.h"
#include "../model/helpers/randomizer/generator.h"
#include "../model/helpers/matrix.h"
#include <iostream>
#include <memory>

// Cave
void s21::Controller::GetRandomCave(size_t rows, size_t cols,
          std::pair<int, int> limit, int birth_chance) {
  s21::Limits limits = {limit.first, limit.second};
  m_cave_ = std::make_unique<s21::Cave>(rows, cols, limits, birth_chance, 
                                      std::make_unique<RandomGenerator>());
}

bool s21::Controller::GetCaveFromFile(const std::string& file_path, std::pair<int, int> limit) {
  bool result = true;
  s21::Limits limits = {limit.first, limit.second};
  try {
    m_cave_ = std::make_unique<s21::Cave>(file_path, limits, std::make_unique<RandomGenerator>());  
  } catch (...) {
    result = false;
  }
  return result;
}

int s21::Controller::GetCaveRows() {
  return m_cave_->GetRows();
}

int s21::Controller::GetCaveCols() {
  return m_cave_->GetCols();
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
  return s21::GetCaveDrawData(*m_cave_);
}

// Maze
bool s21::Controller::GetMazeFromFile(const std::string& file_path) {
  bool result = true;
  try {
    m_maze_ = std::make_unique<s21::Maze>(file_path);
  } catch (...) {
    result = false;
  }
  return result;
}

void s21::Controller::GenerateMaze(int rows, int cols) {
  m_maze_ = std::make_unique<s21::Maze>(rows, cols);
}

int s21::Controller::GetMazeRows() {
  return m_maze_->GetRows();
}

int s21::Controller::GetMazeCols() {
  return  m_maze_->GetCols();
}

s21::Walls s21::Controller::GetWall(int i, int j) {
  return m_maze_->GetValue(i, j);
}

std::vector<QLineF> s21::Controller::GetAnswer(std::pair<int, int> p1, std::pair<int, int> p2) {
  s21::Coordinates start = {p1.first, p1.second};
  s21::Coordinates end = {p2.first, p2.second};
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
