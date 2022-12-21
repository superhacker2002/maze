#include "cave.h"
#include "../helpers/randomizer/generator.h"
#include <memory>

int main() {
  RandomGenerator generator;
  s21::Cave cave1(10, 10, {3, 5}, 70, std::make_unique<RandomGenerator>());
  // cave1.GetCaveFromFile("../../../datasets/cave2.txt");
  // cave1.InitializeCave();

  std::cout << "\n";
  cave1.OutputCave();

  // char button = 'a';
  // while (button == 'a') {
  //   cave1.OutputCave();
  //   cave1.Transform();
  //   std::cin >> button;
  // }
}