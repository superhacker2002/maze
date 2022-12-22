#include "cave.h"
#include "../helpers/randomizer/generator.h"
#include "../helpers/data_structures.h"
#include <memory>

int main() {
  RandomGenerator generator;
  // s21::Cave cave1(10, 10, {3, 5}, 70, std::make_unique<RandomGenerator>());
  s21::Limits limits = {3, 4};
  std::unique_ptr<s21::Cave> res = std::make_unique<s21::Cave>(10, 10, limits, 30, 
                                      std::make_unique<RandomGenerator>());
  res->OutputCave();

}