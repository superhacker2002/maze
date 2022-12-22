#include "cave_drawing.h"

namespace s21 {
std::vector<QRectF> GetCaveDrawData(s21::Cave& cave) {
  std::vector<QRectF> data;
  int rows = cave.GetRows();
  int cols = cave.GetCols();
  int x_size = 500 / rows, y_size = 500 / cols;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (cave.GetValue(i, j)) {
        data.push_back(QRectF(i * x_size, j * y_size, x_size, y_size));
      }
    }
  }
  return data;
}
}  // namespace s21