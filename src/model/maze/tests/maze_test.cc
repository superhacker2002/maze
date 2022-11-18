#include "../maze.h"
#include "gtest/gtest.h"
#include "maze_test_class.h"
#include <iostream>

TEST(maze_tests, maze_generation) {
    MazeTest test_maze(5, 5);
    test_maze.testFillEmptyValues();
    std::vector<int> result = test_maze.getSideLine();
    std::cout << result[0] << result[1] << result[2] << result[3] << result[4];

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}