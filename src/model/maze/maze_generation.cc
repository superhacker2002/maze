#include "maze.h"

bool randomBool() {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}

/**
 * Whole cycle for generating maze
 * with one input and one output.
 */
void s21::Maze::generateMaze() {
    fillEmptyValues();
    for (int i = 0; i < m_rows_ - 1; ++i) {
        assignUniqueSet();
        addRightWall(i);
        addBottomWall(i);
        checkBottomWall(i);
        prepareNewLine(i);
    }
    addEndLine();
}

/**
 * Initializes row with "empty" cells.
 */
void s21::Maze::fillEmptyValues() {
    for (int i = 0; i < m_cols_; i++) {
        m_side_line_.push_back(kEmpty);
    }
}

/**
 * Assigns unique value (number of unique set)
 * to each cell in a row.
 */
void s21::Maze::assignUniqueSet() {
    for (int i = 0; i < m_cols_; i++) {
        if (m_side_line_[i] == kEmpty) {
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
void s21::Maze::addRightWall(int row) {
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
void s21::Maze::mergeSet(int index, int element) {
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
void s21::Maze::addBottomWall(int row) {
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
int s21::Maze::calculateUniqueSet(int element) {
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
void s21::Maze::checkBottomWall(int row) {
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
int s21::Maze::calculateBottomWalls(int element, int row) {
    int count_bottom_walls = 0;
    for (int i = 0; i < m_cols_; i++) {
        if (m_side_line_[i] == element && !(m_maze_(row, i)).bottom_wall) {
            count_bottom_walls++;
        }
    }
    return count_bottom_walls;
}

/**`
 * Prepares new line of maze matrix.
 * @param row
 */
void s21::Maze::prepareNewLine(int row) {
    for (int i = 0; i < m_cols_; i++) {
        if ((m_maze_(row, i)).bottom_wall) {
            m_side_line_[i] = kEmpty;
        }
    }
}

void s21::Maze::addEndLine() {
    assignUniqueSet();
    addRightWall(m_rows_ - 1);
    checkEndLine();
}

/**
 * Checks all conditions for adding an and line
 * to maze matrix.
 */
void s21::Maze::checkEndLine() {
    for (int i = 0; i < m_cols_ - 1; i++) {
        if (m_side_line_[i] != m_side_line_[i + 1]) {
            (m_maze_(m_rows_ - 1, i)).right_wall = false;
            mergeSet(i, m_side_line_[i]);
        }
        (m_maze_(m_rows_ - 1, i)).bottom_wall = true;
    }
    (m_maze_(m_rows_ - 1, m_cols_ -1)).bottom_wall = true;
}
