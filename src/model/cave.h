#ifndef SRC_MODEL_CAVE_H_
#define SRC_MODEL_CAVE_H_

#include "../helpers/matrix.h"
#include <fstream>
#include <ctime>
#include <random>

constexpr bool kALIVE = true;
constexpr bool kDEAD = false;

namespace s21 {
class Cave {
  public:
    s21::Matrix<bool> m_cave_;  // матрица представляющая пещеру
    int m_birth_limit_;  // лимит соседей для зарождения
    int m_death_limit_;  // лимит соседей для смерти
    int m_birth_chance_;  // шанс живой клетки при инициализации

  public:
    Cave() { ; }
    void SetSettings(size_t rows, size_t cols, int birth_limit, int death_limit, int birth_chance);
    bool Transform();
    void TransformCycle();

  public:
    void InitializeCave_();
    void GetInitializedCaveFromFile_(const std::string& file_path);
    int GetAliveNeighboursCount_(int i, int j);
    static int GetRandomNumber_(int min, int max);


};  // class Cave
}  // namespace s21
#endif  // SRC_MODEL_CAVE_H_
