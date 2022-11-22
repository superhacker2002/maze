#ifndef SRC_MODEL_MAZE_MAZE_ANSWER_H_
#define SRC_MODEL_MAZE_MAZE_ANSWER_H_

#include "maze.h"
#include <queue>
#include <array>

namespace s21 {
    struct Coordinates {
        int x;
        int y;
    };

    struct AnswerData {
        std::queue<Coordinates> plan;
        s21::Maze maze_matrix;
        Matrix<int> distances;
    };

    constexpr int UNUSED_CELL = -1;
    constexpr std::array<Coordinates, 4> DELTA = {{ {0, -1}, {0, 1}, {1, 0}, {-1, 0} }};
    enum Directions {
        UP = 0,
        DOWN,
        RIGHT,
        LEFT
    };

    void getMazeAnswer(s21::Maze maze, Coordinates start, Coordinates end);
    bool correctCoordinates(AnswerData& data, Coordinates& current, Coordinates& next, int shift);
    void findPaths(AnswerData& data);
    void changeNeighboursCoordinates(AnswerData& data, Coordinates& current);
    bool checkDownDirection(AnswerData& data, Coordinates& current, Coordinates& next, int rows);
    bool checkUpDirection(AnswerData& data, Coordinates& current, Coordinates& next);
    bool checkRightDirection(AnswerData& data, Coordinates& current, Coordinates& next, int cols);
    bool checkLeftDirection(AnswerData& data, Coordinates& current, Coordinates& next);

    template <class T>
    void initializeMatrix(s21::Matrix<T>& matrix, T value) {
        int rows = matrix.GetRows();
        int cols = matrix.GetCols();
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                matrix(row, col) = value;
            }
        }
    }

}

#endif  // SRC_MODEL_MAZE_MAZE_ANSWER_H_
