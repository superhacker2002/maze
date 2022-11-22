#ifndef SRC_MODEL_HELPERS_DATA_STRUCTURES_H_
#define SRC_MODEL_HELPERS_DATA_STRUCTURES_H_
#include <queue>
#include <array>
#include "matrix.h"

namespace s21 {
    constexpr int EMPTY = 0;
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

    constexpr int UNUSED_CELL = -1;

    constexpr std::array<Coordinates, 4> DELTA = {{ {0, -1}, {0, 1}, {1, 0}, {-1, 0} }};

    enum Directions {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    };
}
#endif  // SRC_MODEL_HELPERS_DATA_STRUCTURES_H_
