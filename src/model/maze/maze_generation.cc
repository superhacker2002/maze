#include "maze.h"
#include <fstream>

namespace s21 {
    bool randomBool() {
        return 0 + (rand() % (1 - 0 + 1)) == 1;
    }

/**
 * Whole cycle for generating maze
 * with one input and one output.
 */
    void Maze::generateMaze() {
        fillEmptyValues();
        for (int i = 0; i < m_rows_ - 1; ++i) {
            assignUniqueSet();
            addRightWalls(i);
            addBottomWalls(i);
            checkBottomWall(i);
            prepareNewLine(i);
        }
        addEndLine();
    }

/**
 * Initializes row with "empty" cells.
 */
    void Maze::fillEmptyValues() {
        for (int i = 0; i < m_cols_; i++) {
            m_side_line_.push_back(kEMPTY);
        }
    }

/**
 * Assigns unique value (number of unique set)
 * to each cell in a row.
 */
    void Maze::assignUniqueSet() {
        for (int i = 0; i < m_cols_; i++) {
            if (m_side_line_[i] == kEMPTY) {
                m_side_line_[i] = m_counter_;
                ++m_counter_;
            }
        }
    }

/**
 * Adds right wall for a cell in the row
 * randomly or specially (if there are
 * cells from one unique set).
 * @param row Specifies what row should be processed.
 */
    void Maze::addRightWalls(int row) {
        for (int i = 0; i < m_cols_ - 1; i++) {
            bool choice = randomBool();
            // либо рандомно, либо если ячейки принадлежат к одному множеству ставим правую стенку
            if (choice || m_side_line_[i] == m_side_line_[i + 1]) {
                (m_maze_(row, i)).right_wall = true;
            } else {
                mergeSet(i, m_side_line_[i]);
            }
        }
        // Добавление правой стенки в последнюю ячейку
        (m_maze_(row, m_cols_ - 1)).right_wall = true;
    }

/**
 * Merges two sets into one by assigning the
 * set number to cells.
 * @param index Index of an element
 * (with set number to which cells will be added)
 * @param element (set number that will be assigned
 * to cells that will be merged into required set)
 */
    void Maze::mergeSet(int index, int element) {
        int mutableSet = m_side_line_[index + 1];
        for (int j = 0; j < m_cols_; j++) {
            if (m_side_line_[j] == mutableSet) {
                m_side_line_[j] = element;
            }
        }
    }

/**
 * Adds bottom wall for a cell in the row
 * randomly (only of it is not the only one
 * cell in the set).
 * @param row Specifies what row of the
 * maze should be processed.
 */
    void Maze::addBottomWalls(int row) {
        for (int i = 0; i < m_cols_; i++) {
            bool choice = randomBool();
            // множество должно иметь более одной ячейки для предотвращения замкнутости
            if (calculateUniqueSet(m_side_line_[i]) != 1 && choice) {
                (m_maze_(row, i)).bottom_wall = true;
            }
        }
    }

/**
 * Calculates the number of cells in the set.
 * @param element Specifies the number of set
 * which cells we are looking for.
 * @return The number of cells in set.
 */
    int Maze::calculateUniqueSet(int element) {
        int count_unique_set = 0;
        for (int i = 0; i < m_cols_; i++) {
            if (m_side_line_[i] == element) {
                count_unique_set++;
            }
        }
        return count_unique_set;
    }

/**
 * Checks if the cell is the only one in
 * its set. if so, removes bottom wall from
 * the cell.
 * @param row Row number where we count cells.
 */
    void Maze::checkBottomWall(int row) {
        for (int i = 0; i < m_cols_; i++) {
            if (calculateBottomWalls(m_side_line_[i], row) == 0) {
                (m_maze_(row, i)).bottom_wall = false;
            }
        }
    }

/**
 * Counts right walls of the cells in the unique set.
 * @param element The number of set.
 * @param row The row of maze where we count walls.
 * @return The number of right walls in set.
 */
    int Maze::calculateBottomWalls(int element, int row) {
        int count_bottom_walls = 0;
        for (int i = 0; i < m_cols_; i++) {
            if (m_side_line_[i] == element && !(m_maze_(row, i)).bottom_wall) {
                count_bottom_walls++;
            }
        }
        return count_bottom_walls;
    }

/**
 * Prepares new line of maze matrix.
 * @param row
 */
    void Maze::prepareNewLine(int row) {
        for (int i = 0; i < m_cols_; i++) {
            if ((m_maze_(row, i)).bottom_wall) {
                m_side_line_[i] = kEMPTY;
            }
        }
    }

    void Maze::addEndLine() {
        assignUniqueSet();
        addRightWalls(m_rows_ - 1);
        checkEndLine();
    }

/**
 * Checks all conditions for adding an end line
 * to maze matrix.
 */
    void Maze::checkEndLine() {
        for (int i = 0; i < m_cols_ - 1; i++) {
            if (m_side_line_[i] != m_side_line_[i + 1]) {
                (m_maze_(m_rows_ - 1, i)).right_wall = false;
                mergeSet(i, m_side_line_[i]);
            }
            (m_maze_(m_rows_ - 1, i)).bottom_wall = true;
        }
        (m_maze_(m_rows_ - 1, m_cols_ - 1)).bottom_wall = true;
    }


    void hasWall(bool is_wall, std::string& maze_str) {
        if (is_wall) {
            maze_str.append("1 ");
        } else {
            maze_str.append("0 ");
        }
    }

    std::ofstream &operator<<(std::ofstream &file, const Maze &maze) {
        std::string maze_str;
        maze_str.append(std::to_string(maze.m_rows_) + " "
                        + std::to_string(maze.m_cols_) + "\n");
        for (int i = 0; i < maze.m_rows_; ++i) {
            for (int j = 0; j < maze.m_cols_; ++ j) {
                hasWall(maze.m_maze_.at(i, j).right_wall, maze_str);
            }
            maze_str.append("\n");
        }
        maze_str.append("\n");
        for (int i = 0; i < maze.m_rows_; ++i) {
            for (int j = 0; j < maze.m_cols_; ++ j) {
                hasWall(maze.m_maze_.at(i, j).bottom_wall, maze_str);
            }
            maze_str.append("\n");
        }

        file << maze_str;
        return file;
    }
} // namespace s21
