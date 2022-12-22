#include <gtest/gtest.h>
#include "maze_test_class.h"
#include "../../src/model/maze/answer/maze_answer.h"

MazeTest test_maze(5, 5);
s21::Maze test_answer_maze("datasets/maze_files/maze1.txt");

TEST(maze_generation_tests, fill_empty_values) {
    test_maze.testFillEmptyValues();
    std::vector<int> result = test_maze.getSideLine();
    EXPECT_EQ(result.size(), 5);
    for (auto &val : result) {
        EXPECT_EQ(val, s21::EMPTY);
    }
}

TEST(maze_generation_tests, assign_unique_set) {
    test_maze.testAssignUniqueSet();
    std::vector<int> result = test_maze.getSideLine();
    EXPECT_EQ(result.size(), 5);
    int unique_set_counter = 1;
    for (auto& val : result) {
        EXPECT_EQ(val, unique_set_counter++);
    }
}

TEST(maze_generation_tests, add_right_walls) {
    test_maze.testAddRightWalls(0);
    std::vector<int> result = test_maze.getSideLine();
    EXPECT_EQ(result.size(), 5);
    int row = 0;
    int cols = test_maze.GetCols();
    for (int col = 0; col < cols; ++col) {
        if (test_maze.GetValue(row, col).right_wall) {
            EXPECT_FALSE(result[col] == result[col + 1]);
        } else {
            EXPECT_EQ(result[col], result[col + 1]);
        }
    }
}

TEST(maze_generation_tests, add_bottom_walls) {
    test_maze.testAddBottomWalls(0);
    std::vector<int> result = test_maze.getSideLine();
    EXPECT_EQ(result.size(), 5);
    int row = 0;
    int cols = test_maze.GetCols();
    int cells_without_bottom = 0;
    int prev_set_number = result[0];
    for (int col = 0; col < cols; ++col) {
        if (result[col] != prev_set_number || col == cols - 1) {
            EXPECT_TRUE(cells_without_bottom >= 1);
            cells_without_bottom = 0;
            prev_set_number = result[col];
        }
        if (!test_maze.GetValue(row, col).bottom_wall) {
            ++cells_without_bottom;
        }
    }
}

TEST(maze_generation_tests, prepare_new_line) {
    std::vector<bool> prev_line;
    int cols = test_maze.GetCols();
    for (int col = 0; col < cols; ++col) {
        prev_line.push_back(test_maze.GetValue(0, col).bottom_wall);
    }

    test_maze.testPrepareNewLine(0);
    std::vector<int> result = test_maze.getSideLine();
    auto prev_cell = prev_line.begin();
    for (auto& res_cell : result) {
        if (*prev_cell) {
            EXPECT_EQ(res_cell, s21::EMPTY);
        } else {
            EXPECT_TRUE(res_cell != s21::EMPTY);
        }
        ++prev_cell;
    }
}

TEST(maze_generation_tests, check_end_line) {
    test_maze.testCheckEndLine();
    int row = test_maze.GetRows() - 1;
    int cols = test_maze.GetCols();
    for (int col = 0; col < cols; ++col) {
        EXPECT_TRUE(test_maze.GetValue(row, col).bottom_wall);
    }
}

TEST(maze_answer_tests, get_answer_invalid) {
    s21::Maze test_answer_maze("datasets/maze_files/maze1.txt");
    EXPECT_ANY_THROW(s21::getMazeAnswer(test_answer_maze, {0, 0}, {10, 10}));
    EXPECT_ANY_THROW(s21::getMazeAnswer(test_answer_maze, {10, 10}, {0, 0}));
    EXPECT_ANY_THROW(s21::getMazeAnswer(test_answer_maze, {0, 0}, {-1, -1}));
    EXPECT_ANY_THROW(s21::getMazeAnswer(test_answer_maze, {-1, -1}, {0, 0}));
}

TEST(maze_answer_tests, get_answer_usual_1) {
    std::vector<int> correct_answer = {s21::RIGHT, s21::RIGHT, s21::RIGHT, 
                                        s21::DOWN, s21::DOWN, s21::LEFT,
                                        s21::DOWN, s21::RIGHT};
    auto it = correct_answer.begin();
    std::vector<int> result = s21::getMazeAnswer(test_answer_maze, {0, 0}, {3, 3});
    for (auto& cell : result) {
        EXPECT_EQ(cell, *it);
        it++;
    }
}

TEST(maze_answer_tests, get_answer_usual_2) {
    std::vector<int> correct_answer = {s21::RIGHT, s21::UP, s21::UP, 
                                        s21::RIGHT, s21::RIGHT, s21::DOWN,
                                        s21::DOWN, s21::LEFT, s21::DOWN,
                                        s21::LEFT, s21::LEFT};
    auto it = correct_answer.begin();
    
    std::vector<int> result = s21::getMazeAnswer(test_answer_maze, {0, 2}, {0, 3});
    for (auto& cell : result) {
        EXPECT_EQ(cell, *it);
        it++;
    }
}

TEST(maze_answer_tests, get_answer_usual_3) {
    std::vector<int> correct_answer = {s21::RIGHT, s21::UP, s21::UP, 
                                        s21::LEFT, s21::LEFT, s21::DOWN,
                                        s21::DOWN, s21::LEFT, s21::UP};
    auto it = correct_answer.begin();
    
    std::vector<int> result = s21::getMazeAnswer(test_answer_maze, {2, 2}, {0, 1});
    for (auto& cell : result) {
        EXPECT_EQ(cell, *it);
        it++;
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}