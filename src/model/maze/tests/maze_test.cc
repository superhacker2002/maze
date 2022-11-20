#include "../maze.h"
#include "gtest/gtest.h"
#include "maze_test_class.h"
#include <iostream>

MazeTest test_maze(5, 5);

TEST(maze_tests, fill_empty_values) {
    test_maze.testFillEmptyValues();
    std::vector<int> result = test_maze.getSideLine();
    EXPECT_EQ(result.size(), 5);
    for (auto &val : result) {
        EXPECT_EQ(val, 0);
    }
}

TEST(maze_tests, assign_unique_set) {
    test_maze.testAssignUniqueSet();
    std::vector<int> result = test_maze.getSideLine();
    EXPECT_EQ(result.size(), 5);
    int unique_set_counter = 1;
    for (auto& val : result) {
        EXPECT_EQ(val, unique_set_counter++);
    }
}

TEST(maze_tests, add_right_walls) {
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

TEST(maze_tests, add_bottom_walls) {
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

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}