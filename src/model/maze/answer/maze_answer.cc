#include "maze_answer.h"
#include <algorithm>

constexpr int UNUSED_CELL = -1;
constexpr int START_CELL = -2;
constexpr std::array<s21::Coordinates, 4> DELTA = {{ {0, -1}, {0, 1}, {1, 0}, {-1, 0} }};

namespace s21 {
/**
 * Gets maze and finds path from the first 
 * point to the second
 * @param maze Maze that was previously filled
 * @param start Coordinates from which we start 
 * finding path
 * @param end Coordinates the answer will be found to
*/
std::vector<int> getMazeAnswer(const s21::Maze& maze, Coordinates start, Coordinates end) {
    int rows = maze.GetRows();
    int cols = maze.GetCols();
    checkCoordinates(rows, cols, start);
    checkCoordinates(rows, cols, end);
    s21::Matrix<int> distances(rows, cols);
    initializeMatrix<int> (distances, UNUSED_CELL);

    s21::Matrix<Coordinates> answer_path(rows, cols);
    Coordinates undefined_cells = {UNUSED_CELL, UNUSED_CELL};
    initializeMatrix<Coordinates> (answer_path, undefined_cells);

    std::queue<Coordinates> plan;
    distances(start.x, start.y) = 0;
    plan.push(start);

    AnswerData data = {plan, maze, distances, answer_path};
    data.answer_path(start.y, start.x) = {START_CELL, START_CELL};
    findPaths(data);
    return reestablishPath(data.answer_path, end);
}

void checkCoordinates(int rows, int cols, Coordinates& coordinates) {
    if (coordinates.x < 0 || coordinates.y < 0 ||
         coordinates.x > cols || coordinates.y > rows) {
        throw std::invalid_argument("Invalid start or end coordinates.");
    }
}

/**
 * Fills matrix with distances to the
 * start point by checking all the 
 * neighbours of current cell.
*/

void findPaths(AnswerData& data) {
    while (!data.plan.empty()) {
        int x = data.plan.front().x;
        int y = data.plan.front().y;
        data.plan.pop();
        Coordinates current = {x, y};
        changeNeighboursCoordinates(data, current);
    }
}

/**
 * Additinonal function for checking if the 
 * neighbour cell can be reached, filling it 
 * with distance and remembering the path to
 * data.answer_path matrix.
*/
void changeNeighboursCoordinates(AnswerData& data, Coordinates& current) {
    for (size_t shift = 0; shift < DELTA.size(); ++shift) {
        int nx = current.x + DELTA[shift].x;
        int ny = current.y + DELTA[shift].y;
        Coordinates neighbours = {nx, ny};
        if (correctCoordinates(data, current, neighbours, shift) && 
                                data.answer_path(ny, nx).x != START_CELL) {
            data.distances(ny, nx) = data.distances(current.y, current.x) + 1;
            data.answer_path(ny, nx) = current;
            data.plan.push({nx, ny});
        }
    }
}

/**
 * Additinonal function for checking if neighbour
 * cell in a particular direction can be reached.
 * @param shift defines what number of direction
 * should be checked from.
*/
bool correctCoordinates(AnswerData& data, Coordinates& current, Coordinates& next, int shift) {
    int rows = data.maze_matrix.GetRows();
    int cols = data.maze_matrix.GetCols();
    bool is_correct = false;
    if (shift == DOWN) {
        is_correct = checkDownDirection(data, current, rows);
    } else if (shift == UP) {
        is_correct = checkUpDirection(data, current, next);
    } else if (shift == RIGHT) {
        is_correct = checkRightDirection(data, current, cols);
    } else if (shift == LEFT) {
        is_correct = checkLeftDirection(data, current, next);
    }
    if (is_correct && data.distances(next.y, next.x) != UNUSED_CELL) {
        is_correct = false;
    }

    return is_correct;
}

bool checkDownDirection(AnswerData& data, Coordinates& current, int rows) {
    return current.y < rows - 1 && !data.maze_matrix.GetValue(current.y, current.x).bottom_wall;
}

bool checkUpDirection(AnswerData& data, Coordinates& current, Coordinates& next) {
    return current.y > 0 && !data.maze_matrix.GetValue(next.y, next.x).bottom_wall;
}

bool checkRightDirection(AnswerData& data, Coordinates& current, int cols) {
    return current.x < cols - 1 && !data.maze_matrix.GetValue(current.y, current.x).right_wall;
}

bool checkLeftDirection(AnswerData& data, Coordinates& current, Coordinates& next) {
    return current.x > 0 && !data.maze_matrix.GetValue(next.y, next.x).right_wall;
}

/**
 * Function that returns vector with direction 
 * numbers reestablishing it with answer_path matrix
 * where needed coordinates were saved.
 * 
*/
std::vector<int> reestablishPath(s21::Matrix<Coordinates> answer_path, Coordinates& end) {
    Coordinates current = end;
    std::vector<Coordinates> path;
    while (current.x != START_CELL && current.x != UNUSED_CELL) {
        path.push_back(current);
        current = answer_path(current.y, current.x);
    }
    std::reverse(path.begin(), path.end());
    return normalizeAnswerPath(path);
}

/**
 * Makes conversion of vector with coordinates
 * to the vector with directions numbers.
*/
std::vector<int> normalizeAnswerPath(std::vector<Coordinates>& path) {
    std::vector<int> normalized_answer;
    Coordinates prev = path[0];
    for (size_t next = 1; next < path.size(); ++next) {
        if (path[next].y > prev.y) {
            normalized_answer.push_back(DOWN);
        } else if (path[next].y < prev.y) {
            normalized_answer.push_back(UP);
        } else if (path[next].x > prev.x) {
            normalized_answer.push_back(RIGHT);
        } else if (path[next].x < prev.x) {
            normalized_answer.push_back(LEFT);
        }
        prev = path[next];
    }
    return normalized_answer;
}
}
