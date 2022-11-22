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
    int rows = m_maze_.GetRows();
    for (int i = 0; i < rows - 1; ++i) {
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
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
        m_side_line_.push_back(EMPTY);
    }
}

/**
 * Assigns unique value (number of unique set)
 * to each cell in a row.
 */
void Maze::assignUniqueSet() {
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
        if (m_side_line_[i] == EMPTY) {
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
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols - 1; i++) {
        bool choice = randomBool();
        // либо рандомно, либо если ячейки принадлежат к одному множеству ставим правую стенку
        if (choice || m_side_line_[i] == m_side_line_[i + 1]) {
            (m_maze_(row, i)).right_wall = true;
        } else {
            mergeSet(i, m_side_line_[i]);
        }
    }
    // Добавление правой стенки в последнюю ячейку
    (m_maze_(row, cols - 1)).right_wall = true;
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
    int cols = m_maze_.GetCols();
    for (int j = 0; j < cols; j++) {
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
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
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
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
        if (m_side_line_[i] == element) {
            count_unique_set++;
        }
    }
    return count_unique_set;
}

/**
 * Checks if the cell does not have any cells
 * without bottom walls.
 * if so, removes bottom wall from one cell
 * in the set.
 * @param row Row number where we count cells.
 */
void Maze::checkBottomWall(int row) {
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
        if (calculateBottomWalls(m_side_line_[i], row) == 0) {
            (m_maze_(row, i)).bottom_wall = false;
        }
    }
}

/**
 * Counts bottom walls of the cells in the unique set.
 * @param element The number of set.
 * @param row The row of maze where we count walls.
 * @return The number of right walls in set.
 */
int Maze::calculateBottomWalls(int element, int row) {
    int count_bottom_walls = 0;
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
        if (m_side_line_[i] == element && !(m_maze_(row, i)).bottom_wall) {
            count_bottom_walls++;
        }
    }
    return count_bottom_walls;
}

/**
 * Prepares new line of maze matrix.
 * @param row Matrix row that should be prepared
 * for inserting new walls.
 */
void Maze::prepareNewLine(int row) {
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols; i++) {
        if ((m_maze_(row, i)).bottom_wall) {
            m_side_line_[i] = EMPTY;
        }
    }
}

void Maze::addEndLine() {
    assignUniqueSet();
    int rows = m_maze_.GetRows();
    addRightWalls(rows - 1);
    checkEndLine();
}

/**
 * Checks all conditions for adding an end line
 * to maze matrix.
 */
void Maze::checkEndLine() {
    int rows = m_maze_.GetRows();
    int cols = m_maze_.GetCols();
    for (int i = 0; i < cols - 1; i++) {
        if (m_side_line_[i] != m_side_line_[i + 1]) {
            (m_maze_(rows - 1, i)).right_wall = false;
            mergeSet(i, m_side_line_[i]);
        }
        (m_maze_(rows - 1, i)).bottom_wall = true;
    }
    (m_maze_(rows - 1, cols - 1)).bottom_wall = true;
}

} // namespace s21
