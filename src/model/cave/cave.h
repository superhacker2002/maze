#ifndef SRC_MODEL_CAVE_CAVE_H_
#define SRC_MODEL_CAVE_CAVE_H_

#include <ctime>
#include <fstream>
#include <memory>
#include "../helpers/data_structures.h"
#include "../helpers/matrix.h"
#include "../helpers/randomizer/interface.h"

namespace s21 {

constexpr bool ALIVE = true;
constexpr bool DEAD = false;

class Cave {
 public:
  using CaveMatrix = s21::Matrix<bool>;

  Cave(size_t rows, size_t cols, Limits limit, int birth_chance,
       std::unique_ptr<IRandomizer> generator);
  Cave(const std::string& file_path, Limits limit,
       std::unique_ptr<IRandomizer> generator);
  ~Cave() = default;
  bool Transform();
  void TransformCycle();
  void OutputCave();
  int GetRows();
  int GetCols();
  bool GetValue(int i, int j);
  void FlipCave();

 private:
  bool m_reading_error_;
  CaveMatrix m_cave_;  // матрица, представляющая пещеру
  Limits m_limits_;  // {зарождения, смерти}
  int m_birth_chance_;  // шанс живой клетки при инициализации [0-100]%
  std::unique_ptr<IRandomizer> m_random_generator_;

  int GetAliveNeighboursCount_(int i, int j);
  CaveMatrix GetCaveFromFile_(const std::string& file_path);
  void InitializeCave_();
  void GetError_() const;
  std::pair<int, int> GetCaveSize_(std::fstream &file);
  CaveMatrix FillCaveMatrix_(std::fstream &file);
  void RemovePrevState_(std::string &buffer);
  bool CorrectState_(const int &state);
};  // class Cave
}  // namespace s21
#endif  // SRC_MODEL_CAVE_CAVE_H_
