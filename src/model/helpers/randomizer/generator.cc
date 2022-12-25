#include "generator.h"

#include <random>

int RandomGenerator::GetRandomPercent() {
  std::mt19937 engine;
  std::random_device device;
  engine.seed(device());
  int num = engine() % 100 - 0;
  return num;
}