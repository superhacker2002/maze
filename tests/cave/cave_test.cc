#include <gtest/gtest.h>
#include "../../src/model/cave/cave.h"
#include "moc_generator.h"
#include <memory>

TEST(cave_generation_tests, random_generation) {
    s21::Cave cave(5, 5, {3, 4}, 50, std::make_unique<MocRandomGenerator>());
    int rows = cave.GetRows();
    int cols = cave.GetCols();
    int element_num = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool value = cave.GetValue(i, j);
            if (element_num % 2 == 0) {
                EXPECT_EQ(value, false);
            } else {
                EXPECT_EQ(value, true);
            }
            element_num++;
        }
    }
}

TEST(cave_generation_tests, random_generation_full) {
    s21::Cave cave(5, 5, {3, 4}, 40, std::make_unique<MocRandomGenerator>());
    int rows = cave.GetRows();
    int cols = cave.GetCols();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool value = cave.GetValue(i, j);
            EXPECT_EQ(value, false);
        }
    }
}

TEST(cave_generation_tests, random_generation_empty) {
    s21::Cave cave(5, 5, {3, 4}, 60, std::make_unique<MocRandomGenerator>());
    int rows = cave.GetRows();
    int cols = cave.GetCols();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool value = cave.GetValue(i, j);
            EXPECT_EQ(value, true);
        }
    }
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}