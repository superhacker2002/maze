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
    using  __limits = std::pair<int, int>;
    #define __birth_limit first
    #define __death_limit second

  private:
    s21::Matrix<bool> m_cave_;  // матрица представляющая пещеру
    __limits m_limits_;  // {лимит соседей для зарождения, лимит соседей для смерти}
    int m_birth_chance_;  // шанс живой клетки при инициализации [0-100]%

  public:
    Cave() { ; }
    void SetSettings(size_t rows, size_t cols, __limits limit, int birth_chance);
    void GetCaveFromFile(const std::string& file_path);
    bool Transform();
    void TransformCycle();
    void OutputCave() { m_cave_.OutputMatrix(); }

  private:
    void InitializeCave_();
    int GetAliveNeighboursCount_(int i, int j);
    static int GetRandomNumber_();


};  // class Cave
}  // namespace s21
#endif  // SRC_MODEL_CAVE_H_
