#ifndef SRC_MODEL_CAVE_H_
#define SRC_MODEL_CAVE_H_

#include <ctime>
#include <fstream>
#include <memory>
#include <random>

#include "../../helpers/matrix.h"

constexpr bool kALIVE = true;
constexpr bool kDEAD = false;

namespace s21 {
class Cave {
 public:
  using __limits = std::pair<int, int>;
  using __mtrx_ptr = std::unique_ptr<s21::Matrix<bool>>;
#define __birth_limit first
#define __death_limit second
#define m_cave_ref_ (*m_cave_)

 private:
  __mtrx_ptr m_cave_;  // умный указатель на матрицу, представляющую пещеру
  __limits m_limits_;  // {зарождения, смерти}
  int m_birth_chance_;  // шанс живой клетки при инициализации [0-100]%

 public:
  Cave(size_t rows, size_t cols, __limits limit, int birth_chance);
  ~Cave() = default;
  void GetCaveFromFile(const std::string& file_path);
  bool Transform();
  void TransformCycle();
  void OutputCave() { m_cave_->OutputMatrix(); }
  void InitializeCave();

 private:
  int GetAliveNeighboursCount_(int i, int j);
  static int GetRandomNumber_();

};  // class Cave
}  // namespace s21
#endif  // SRC_MODEL_CAVE_H_
