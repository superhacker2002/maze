#ifndef SRC_MODEL_HELPERS_DATA_STRUCTURES_H_
#define SRC_MODEL_HELPERS_DATA_STRUCTURES_H_
#include <queue>
#include <array>
#include "matrix.h"

namespace s21 {
    struct Limits {
        int birth_limit;
        int death_limit;
    };

    struct Walls {
        bool right_wall;
        bool bottom_wall;
    };

    struct Coordinates {
        int x;
        int y;
    };

    enum Directions {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    };
}
#endif  // SRC_MODEL_HELPERS_DATA_STRUCTURES_H_
