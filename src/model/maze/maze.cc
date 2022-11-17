#include "maze.h"
#include <fstream>

/**
 * Constructor for initializing maze from file.
 * @param file_path Path to file to read maze from.
 */
s21::Maze::Maze(const std::string& file_path)
    : m_reading_error_(false),
    m_maze_(std::make_unique<s21::Maze::MazeMatrix>(getMazeFromFile(file_path))) {
    try {
        *(m_maze_.get()) = fillMazeMatrix(file_path);
    } catch (...) {
        m_reading_error_ = true;
        getError();
    }
}

/**
 * Constructor for generating maze with single
 * input and single output using Eller's algorithm.
 * @param rows Number of rows in maze.
 * @param cols Number of cells in the row in maze.
 */
s21::Maze::Maze(int rows, int cols)
    : m_maze_(std::make_unique<s21::Maze::MazeMatrix>(rows, cols)),
    rows_(rows),
    cols_(cols),
    counter_(1),
    m_reading_error_(false) {
    generateMaze();
}

bool randomBool() {
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}

/**
 * Whole cycle for generating maze
 * with one input and one output.
 */
void s21::Maze::generateMaze() {
    fillEmptyValues();
    for (int i = 0; i < rows_ - 1; ++i) {
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
    for (int i = 0; i < cols_; i++) {
        side_line_.push_back(kEmpty);
    }
}

/**
 * Assigns unique value (number of unique set)
 * to each cell in a row.
 */
void s21::Maze::assignUniqueSet() {
    for (int i = 0; i < cols_; i++) {
        if (side_line_[i] == kEmpty) {
            side_line_[i] = counter_;
            ++counter_;
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
    for (int i = 0; i < cols_ - 1; i++) {
        bool choice = randomBool();
        // либо рандомно, либо если ячейки принадлежат к одному множеству ставим правую стенку
        if (choice || side_line_[i] == side_line_[i + 1]) {
            ((*(m_maze_.get()))(row, i)).right_wall = true;
        } else {
            mergeSet(i, side_line_[i]);
        }
    }
    // Добавление правой стенки в последнюю ячейку
    ((*(m_maze_.get()))(row, cols_ - 1)).right_wall = true;
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
    int mutableSet = side_line_[index + 1];
    for (int j = 0; j < cols_; j++) {
        if (side_line_[j] == mutableSet) {
            side_line_[j] = element;
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
    for (int i = 0; i < cols_; i++) {
        bool choice = randomBool();
        // множество должно иметь более одной ячейки для предотвращения замкнутости
        if (calculateUniqueSet(side_line_[i]) != 1 && choice) {
            ((*(m_maze_.get()))(row, i)).bottom_wall = true;
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
    for (int i = 0; i < cols_; i++) {
        if (side_line_[i] == element) {
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
    for (int i = 0; i < cols_; i++) {
        if (calculateBottomWalls(side_line_[i], row) == 0) {
            ((*(m_maze_.get()))(row, i)).bottom_wall = false;
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
    for (int i = 0; i < cols_; i++) {
        if (side_line_[i] == element && !((*(m_maze_.get()))(row, i)).bottom_wall) {
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
    for (int i = 0; i < cols_; i++) {
        if (((*(m_maze_.get()))(row, i)).bottom_wall) {
            side_line_[i] = kEmpty;
        }
    }
}

void s21::Maze::addEndLine() {
    assignUniqueSet();
    addRightWall(rows_ - 1);
    checkEndLine();
}

/**
 * Checks all conditions for adding an and line
 * to maze matrix.
 */
void s21::Maze::checkEndLine() {
    for (int i = 0; i < cols_ - 1; i++) {
        if (side_line_[i] != side_line_[i + 1]) {
            ((*(m_maze_.get()))(rows_ - 1, i)).right_wall = false;
            mergeSet(i, side_line_[i]);
        }
        ((*(m_maze_.get()))(rows_ - 1, i)).bottom_wall = true;
    }
    ((*(m_maze_.get()))(rows_ - 1, cols_ - 1)).bottom_wall = true;
}

/**
 * Indicates if error occurred while program was running
 * and throw an exception.
 */
void s21::Maze::getError() const {
    if (m_reading_error_) {
        throw std::invalid_argument("Parsing failed.");
    }
}

/**
 * Creates maze matrix of the size that was
 * provided in the first line in the file.
 * If no size was not received writes an error.
 * @param file_path Path to file we read from.
 * @return Matrix of the size received from file.
 */
s21::Maze::MazeMatrix s21::Maze::getMazeFromFile(const std::string& file_path) {
    std::fstream file;
    file.open(file_path);
    if (!file.is_open()) {
        m_reading_error_ = true;
        getError();
    }
    getMazeSize(file);
    s21::Maze::MazeMatrix maze_matrix(rows_, cols_);
    file.close();
    return maze_matrix;
}


/**
 * Reads first line from file and writes
 * maze matrix rows and columns in private
 * fields of the Maze class. If reading failed
 * writes an error.
 * @param file File stream from what we read.
 */
void s21::Maze::getMazeSize(std::fstream& file) {
    std::string buffer;
    if (getline(file, buffer)) {
        try {
            rows_ = stoi(buffer);
            buffer.erase(0, buffer.find_first_of(' ') + 1);
            cols_ = stoi(buffer);
        } catch (...) {
            m_reading_error_ = true;
        }
    } else {
        m_reading_error_ = true;
    }
    getError();
}

/**
 * Fills maze matrix cells according to
 * the digit that was received from file.
 * 1 - wall exists (true).
 * 0 - wall does not exist (false).
 * If information was not received writes an error.
 * @param file_path File name from what we read.
 * @return Filled with values maze matrix.
 */
s21::Maze::MazeMatrix s21::Maze::fillMazeMatrix(const std::string& file_path) {
    std::vector<walls> maze;
    std::string buffer;
    std::fstream file(file_path);

    getline(file, buffer);
    buffer = "";
    fillRightWall(file, maze);
    getError();

    getline(file, buffer);
    fillBottomWall(file, maze);
    getError();

    auto maze_matrix = s21::Matrix<s21::walls>::VectorToMatrix(maze);
    file.close();
    return maze_matrix;
}

/**
 * Reads first part of the file and fills in each cell
 * of the maze matrix if it has right wall.
 * @param file File stream from what we read.
 * @param maze Vector where we temporarily store the
 * information about right wall existence.
 */
void s21::Maze::fillRightWall(std::fstream& file, std::vector<s21::walls>& maze) {
    std::string buffer;
    for (int i = 0; i < rows_; ++i) {
        if (getline(file, buffer) && !buffer.empty()) {
             for (int j = 0; j < cols_; ++j) {
                int state = stoi(buffer);
                s21::walls cell_walls {};
                cell_walls.right_wall = isWall(state);
                maze.emplace_back(cell_walls);
                removePrevState(buffer);
            }
        } else {
            m_reading_error_ = true;
        }
    }
    getError();
}

bool s21::Maze::isWall(const int& state) {
    if (!(state == 0 || state == 1)) {
        m_reading_error_ = true;
        getError();
    }
    return state == 1;
}

/**
 * Removes previous digit from line in order
 * to continue getting next values.
 * @param buffer
 */
void s21::Maze::removePrevState(std::string& buffer) {
    if (buffer.size() == 1) {
        buffer.erase(0, 1);
    } else {
        buffer.erase(0, buffer.find_first_of(' ') + 1);
    }
}

/**
 * Reads first part of the file and fills in each cell
 * of the maze matrix if it has bottom wall.
 * @param file File stream from what we read.
 * @param maze Vector where we temporarily store the
 * information about bottom wall existence.
 */
void s21::Maze::fillBottomWall(std::fstream& file, std::vector<s21::walls>& maze) {
    std::string buffer;
    auto cell = maze.begin();
    for (int i = 0; i < rows_; ++i) {
        if (getline(file, buffer) && !buffer.empty()) {
            for (int j = 0; j < cols_; ++j) {
                int state = stoi(buffer);
                (*cell).bottom_wall = isWall(state);
                removePrevState(buffer);
                ++cell;
            }
        } else {
            m_reading_error_ = true;
        }
    }
    getError();
}

void s21::Maze::outputMaze() {
    std::cout << "- - - - - - - - \n";

    for (int i = 0; i < rows_; ++i) {
        for (int j = 0; j < cols_; ++j) {
            if (j == 0) {
                std::cout << "|";
            }
            bool right_wall = ((*(m_maze_.get()))(i, j)).right_wall;
            bool bottom_wall = ((*(m_maze_.get()))(i, j)).bottom_wall;
            if (bottom_wall) {
                std::cout << "_";
            } else {
                std::cout << " ";
            }
            if (right_wall) {
                std::cout << " |";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << "\n";
    }
}




