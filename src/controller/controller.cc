#include "controller.h"

void s21::Controller::GetRandomCave(size_t rows, size_t cols,
          s21::Cave::__limits limit, int birth_chance) {
  m_cave_ = std::make_unique<s21::Cave>(rows, cols, limit, birth_chance);
}

