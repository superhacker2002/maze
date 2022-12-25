#ifndef SRC_MODEL_DRAWING_CAVE_DRAWING_H_
#define SRC_MODEL_DRAWING_CAVE_DRAWING_H_

#include <QRectF>
#include <vector>

#include "../cave/cave.h"

namespace s21 {
std::vector<QRectF> GetCaveDrawData(s21::Cave& cave);
}
#endif  // SRC_MODEL_DRAWING_CAVE_DRAWING_H_
