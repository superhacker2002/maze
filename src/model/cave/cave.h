#ifndef SRC_MODEL_CAVE_CAVE_H_
#define SRC_MODEL_CAVE_CAVE_H_

#include <ctime>
#include <fstream>
#include <memory>
#include <random>

#include "../../helpers/matrix.h"

constexpr bool kALIVE = true;
constexpr bool kDEAD = false;

namespace s21 {

struct Limits {
    int birth_limit;
    int death_limit;
};

class Cave {
 public:
  using CaveMatrix = s21::Matrix<bool>;

 private:
  CaveMatrix m_cave_;  // матрица, представляющая пещеру
  Limits m_limits_;  // {зарождения, смерти}
  int m_birth_chance_;  // шанс живой клетки при инициализации [0-100]%
  int m_rows_;
  int m_cols_;

 public:
  Cave(size_t rows, size_t cols, Limits limit, int birth_chance);
  Cave(const std::string& file_path, Limits limit);
  ~Cave() = default;
  bool Transform();
  void TransformCycle();
  void OutputCave();
  int GetRows();
  int GetCols();
  bool GetValue(int i, int j);
  void FlipCave();

 private:
  int GetAliveNeighboursCount_(int i, int j);
  CaveMatrix GetCaveFromFile_(const std::string& file_path);
  static int GetRandomNumber_();
  void InitializeCave_();

};  // class Cave
}  // namespace s21
#endif  // SRC_MODEL_CAVE_CAVE_H_
