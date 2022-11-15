#include "model/cave.h"

int main() {
  
  // s21::Cave cave1(500, 500, {2, 5}, 10);  // красиво копетс
  s21::Cave cave1(10, 10, {4, 3}, 20);
  cave1.GetCaveFromFile("cave2.txt");

  // cave1.m_cave_.OutputMatrix();
  // cave1.TransformCycle();
  // std::cout << "\n";
  // cave1.m_cave_.OutputMatrix();


  char button = 'a';
  while(button == 'a') {
    cave1.OutputCave();
    cave1.Transform();
    std::cin >> button;
  }
}