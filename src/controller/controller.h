#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/cave/cave.h"

namespace s21 {
class Controller {
  public:
    using __cave_ptr = std::unique_ptr<Cave>;

  private:
    __cave_ptr m_cave_;

  public:
    Controller() {;}
    ~Controller() = default;
    void GetRandomCave(size_t rows, size_t cols, s21::Cave::__limits limit, int birth_chance);
    int GetRows() { return m_cave_.get()->GetRows(); }
    int GetCols() { return m_cave_.get()->GetCols(); }
    bool& GetValue(int i, int j) { return m_cave_.get()->GetValue(i, j); }
    void TransformOnce() { m_cave_.get()->Transform(); }
    void TransformTillEnd() { m_cave_.get()->TransformCycle(); }
    void FlipCave() { m_cave_.get()->FlipCave(); }
};  // class Controller
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_