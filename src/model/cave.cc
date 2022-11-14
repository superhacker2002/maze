#include "cave.h"


void s21::Cave::SetSettings(size_t rows, size_t cols, int birth_limit,
                              int death_limit, int birth_chance) {
  m_cave_.SetSize(rows, cols);
  m_birth_limit_ = birth_limit;
  m_death_limit_ = death_limit;
  m_birth_chance_ = birth_chance;
  InitializeCave_();
//   m_cave_ = s21::Matrix<bool>::VectorToMatrix({

//   });
}

// void s21::Cave::GetInitializedCaveFromFile_(const std::string& file_path) {
//   std::fstream file;
//   file.open(file_path);
//   std::string buffer;
//   if (file.is_open()) {
//     getline(file, buffer);

//   }
// }



void s21::Cave::InitializeCave_() {
  for (size_t i = 0; i < m_cave_.GetRows(); ++i)
    for (size_t j = 0; j < m_cave_.GetCols(); ++j) {
      int random = GetRandomNumber_(0, 100);
      if (random <= m_birth_chance_)
        m_cave_(i, j) = kALIVE;
      else
        m_cave_(i, j) = kDEAD;
    }
}

int s21::Cave::GetRandomNumber_(int min, int max) {
  std::mt19937 engine;
  std::random_device device;
  engine.seed(device());
  int num = engine() % max - min;
  return num;
}

bool s21::Cave::Transform() {
  bool changed = false;
  s21::Matrix<bool> tmp_cave(m_cave_.GetRows(), m_cave_.GetCols());
  for (int i = 0; i < m_cave_.GetRows(); ++i) {
    for (int j = 0; j < m_cave_.GetCols(); ++j) {
      int alive_count = GetAliveNeighboursCount_(i, j);
      if (m_cave_(i, j) == kALIVE && alive_count < m_death_limit_) {
        tmp_cave(i, j) = kDEAD;
        changed = true;
      } else if (m_cave_(i, j) == kDEAD && alive_count > m_birth_limit_) {
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
  while (Transform()) {
    // s21::Matrix<bool> prev_cave = m_cave_;
    // Transform();
    // if (prev_cave == m_cave_) break;
  }
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