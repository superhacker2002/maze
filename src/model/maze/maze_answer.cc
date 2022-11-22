#include "maze_answer.h"

namespace s21 {
    void getMazeAnswer(s21::Maze maze, Coordinates start, Coordinates end) {
        int rows = maze.GetRows();
        int cols = maze.GetCols();
        s21::Matrix<int> distances(rows, cols);
        initializeMatrix<int> (distances, -1);

        s21::Matrix<bool> used_cells(rows, cols);
        initializeMatrix<bool> (used_cells, false);

        std::queue<Coordinates> plan;
        distances(start.x, start.y) = 0;
        used_cells(start.x, start.y) = true;
        plan.push(start);

        AnswerData data = {plan, maze, used_cells, distances};
        std::cout << distances(end.y, end.x) << std::endl;

        findPaths(data);
    }

    void findPaths(AnswerData& data) {
        while (!data.plan.empty()) {
            int x = data.plan.front().x;
            int y = data.plan.front().y;
            data.plan.pop();
            Coordinates current = {x, y};
            changeNeighboursCoordinates(data, current);
        }
    }

    void changeNeighboursCoordinates(AnswerData& data, Coordinates& current) {
        for (int shift = 0; shift < DELTA.size(); ++shift) {
            int nx = current.x + DELTA[shift].x;
            int ny = current.y + DELTA[shift].y;
            Coordinates neighbours = {nx, ny};
            if (correctCoordinates(data, current, neighbours, shift)) {
                data.distances(ny, nx) = data.distances(current.y, current.x) + 1;
                data.used_cells(ny, nx) = true;
                data.plan.push({nx, ny});
            }
        }
    }

    bool correctCoordinates(AnswerData& data, Coordinates& current, Coordinates& next, int shift) {
        int rows = data.maze_matrix.GetRows();
        int cols = data.maze_matrix.GetCols();
        bool is_correct = false;
        if (shift == DOWN) {
            is_correct = checkDownDirection(data, current, next, rows);
        } else if (shift == UP) {
            is_correct = checkUpDirection(data, current, next);
        } else if (shift == RIGHT) {
            is_correct = checkRightDirection(data, current, next, cols);
        } else if (shift == LEFT) {
            is_correct = checkLeftDirection(data, current, next);
        }
        if (is_correct && data.used_cells(next.y, next.x)) {
            is_correct = false;
        }

        return is_correct;
    }

    bool checkDownDirection(AnswerData& data, Coordinates& current, Coordinates& next, int rows) {
        return current.y < rows - 1 && !data.maze_matrix.GetValue(current.y, current.x).bottom_wall;
    }

    bool checkUpDirection(AnswerData& data, Coordinates& current, Coordinates& next) {
        return current.y > 0 && !data.maze_matrix.GetValue(next.y, next.x).bottom_wall;
    }

    bool checkRightDirection(AnswerData& data, Coordinates& current, Coordinates& next, int cols) {
        return current.x < cols - 1 && !data.maze_matrix.GetValue(current.y, current.x).right_wall;
    }

    bool checkLeftDirection(AnswerData& data, Coordinates& current, Coordinates& next) {
        return current.x > 0 && !data.maze_matrix.GetValue(next.y, next.x).right_wall;
    }






}
