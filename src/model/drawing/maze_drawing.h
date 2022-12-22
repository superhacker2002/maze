#include <QLineF>
#include "../maze/maze.h"

namespace s21 {
std::vector<QLineF> GetAnswerDrawData(s21::Maze maze, std::vector<int>& answer,
                                      Coordinates& start, Coordinates& end);

std::vector<QLineF> GetMazeDrawData(s21::Maze& maze);
};  // namespace s21
