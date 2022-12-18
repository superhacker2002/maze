#ifndef SRC_MODEL_MAZE_MAZE_ANSWER_H_
#define SRC_MODEL_MAZE_MAZE_ANSWER_H_

#include "../maze.h"

namespace s21 {
    struct AnswerData {
        std::queue<Coordinates> plan;
        Maze maze_matrix;
        Matrix<int> distances;
        Matrix<Coordinates> answer_path;
    };
    std::vector<int> getMazeAnswer(const s21::Maze& maze, Coordinates start, Coordinates end);
    void checkCoordinates(int rows, int cols, Coordinates& coordinates);
    bool correctCoordinates(AnswerData& data, Coordinates& current, Coordinates& next, int shift);
    void findPaths(AnswerData& data);
    void changeNeighboursCoordinates(AnswerData& data, Coordinates& current);
    bool checkDownDirection(AnswerData& data, Coordinates& current, int rows);
    bool checkUpDirection(AnswerData& data, Coordinates& current, Coordinates& next);
    bool checkRightDirection(AnswerData& data, Coordinates& current, int cols);
    bool checkLeftDirection(AnswerData& data, Coordinates& current, Coordinates& next);
    std::vector<int> reestablishPath(s21::Matrix<Coordinates> answer_path, Coordinates& end);
    std::vector<int> normalizeAnswerPath(std::vector<Coordinates>& path);

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
