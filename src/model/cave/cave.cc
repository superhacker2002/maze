#include "cave.h"

s21::Cave::Cave(size_t rows, size_t cols, Limits limit, int birth_chance)
    : m_cave_(s21::Cave::CaveMatrix(rows, cols)),
    m_rows_(rows),
    m_cols_(cols),
    m_limits_(limit),
    m_birth_chance_(birth_chance) {
  InitializeCave_();
}

s21::Cave::Cave(const std::string& file_path, Limits limit)
    : m_cave_(s21::Cave::CaveMatrix(GetCaveFromFile_(file_path))),
    m_rows_(m_cave_.GetRows()),
    m_cols_(m_cave_.GetCols()),
    m_limits_(limit) { ; }

void s21::Cave::InitializeCave_() {
  for (int i = 0; i < m_rows_; ++i)
    for (int j = 0; j < m_cols_; ++j) {
      if (GetRandomNumber_() <= m_birth_chance_)
        m_cave_(i, j) = kALIVE;
      else
        m_cave_(i, j) = kDEAD;
    }
}

bool s21::Cave::Transform() {
  bool changed = false;
  s21::Matrix<bool> tmp_cave(m_rows_, m_cols_);
  for (int i = 0; i < m_rows_; ++i) {
    for (int j = 0; j < m_cols_; ++j) {
      int alive_count = GetAliveNeighboursCount_(i, j);
      if (m_cave_(i, j) == kALIVE && alive_count < m_limits_.__death_limit) {
        tmp_cave(i, j) = kDEAD;
        changed = true;
      } else if (m_cave_(i, j) == kDEAD && alive_count > m_limits_.__birth_limit) {
        tmp_cave(i, j) = kALIVE;
        changed = true;
      } else {
        tmp_cave(i, j) = m_cave_(i, j);
      }
    }
  }
  m_cave_ = tmp_cave;
  return changed;
}

void s21::Cave::TransformCycle() {
  // пока поле меняется, запускаем трансформацию
  while (Transform()) {}
}

int s21::Cave::GetAliveNeighboursCount_(int i, int j) {
  int counter = 0;
  for (int buf_i = i - 1; buf_i < i + 2; ++buf_i) {
    for (int buf_j = j - 1; buf_j < j + 2; ++buf_j) {
      if (buf_i != i || buf_j != j) {
        try {
          if (m_cave_(buf_i, buf_j) == kALIVE)
            counter++;
        } catch (std::out_of_range& err) {  // если клетки нет, считаем ее живой
          counter++;
        }
      }
    }
  }
  return counter;
}

s21::Matrix<bool> s21::Cave::GetCaveFromFile_(const std::string& file_path) {
  std::string buffer;
  std::vector<bool> cave;
  std::fstream file;
  file.open(file_path);
  if (file.is_open()) {
    while (getline(file, buffer)) {
      while (buffer.size() > 0) {
        cave.push_back(stoi(buffer));
        buffer.erase(0, buffer.find_first_of(' ') + 1);
      }
    }
  }
  cave.erase(cave.begin());
  cave.erase(cave.begin());
  return s21::Matrix<bool>::VectorToMatrix(cave);
}

int s21::Cave::GetRandomNumber_() {
  std::mt19937 engine;
  std::random_device device;
  engine.seed(device());
  int num = engine() % 100 - 0;
  return num;
}