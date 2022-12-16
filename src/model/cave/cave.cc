#include "cave.h"

namespace s21 {
/**
 * Constructor for initializing random cave
 * of the specified by user size.
 * @param rows Rows of the cave.
 * @param cols Cols of the cave.
 * @param limit Struct with birth and death limits of the cells in cave.
 * @param birth_chance A chance of the cell to be "alive"
 * at the moment of initialization.
 */
Cave::Cave(size_t rows, size_t cols, Limits limit, int birth_chance)
    : m_cave_(Cave::CaveMatrix(rows, cols)),
      m_limits_(limit),
      m_birth_chance_(birth_chance) {
    InitializeCave_();
}

/**
 * Constructor for initialization of the cave
 * from file specified by user.
 * @param file_path Path to the file what we read from.
 * @param limit Struct with birth and death limits of the
 * cells in cave.
 */
Cave::Cave(const std::string &file_path, Limits limit)
    : m_cave_(Cave::CaveMatrix(GetCaveFromFile_(file_path))),
      m_limits_(limit) { ; }

void Cave::OutputCave() { m_cave_.OutputMatrix(); }

int Cave::GetRows() { return m_cave_.GetRows(); }

int Cave::GetCols() { return m_cave_.GetCols(); }

bool Cave::GetValue(int i, int j) { return m_cave_(i, j); }

void Cave::FlipCave() { m_cave_.Transpose(); }

/**
 * Filling the cave with cells states
 * according to the randomly generated numbers.
 * In the end the cell must be either
 * "alive" or "dead".
 */
void Cave::InitializeCave_() {
    int rows = m_cave_.GetRows();
    int cols = m_cave_.GetCols();
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            if (GetRandomNumber_() <= m_birth_chance_)
                m_cave_(i, j) = kALIVE;
            else
                m_cave_(i, j) = kDEAD;
        }
}


/**
 * Transforms current matrix according to the
 * cellular automation algorithm.
 * @return True - changes in matrix occurred,
 *         false - transformation is impossible.
 */
bool Cave::Transform() {
    bool changed = false;
    int rows = m_cave_.GetRows();
    int cols = m_cave_.GetCols();
    Cave::CaveMatrix tmp_cave(rows, cols);
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int alive_count = GetAliveNeighboursCount_(i, j);
            if (m_cave_(i, j) == kALIVE && alive_count < m_limits_.death_limit) {
                tmp_cave(i, j) = kDEAD;
                changed = true;
            } else if (m_cave_(i, j) == kDEAD && alive_count > m_limits_.birth_limit) {
                tmp_cave(i, j) = kALIVE;
                changed = true;
            } else {
                tmp_cave(i, j) = m_cave_(i, j);
            }
        }
    }
    m_cave_ = tmp_cave;
    return changed;
}

/**
 * Transforms current cave matrix
 * while the transformation is allowed.
 */
void Cave::TransformCycle(unsigned int sleep_time) {
    // пока поле меняется, запускаем трансформацию
    while (Transform()) {}
}

/**
 * Counts "alive" neighbours of the cell in order
 * to decide if cell must "die" or not.
 * @param i The row where the cell is.
 * @param j The column where the cell is.
 * @return The number of alive neighbours.
 */
int Cave::GetAliveNeighboursCount_(int i, int j) {
    int counter = 0;
    for (int buf_i = i - 1; buf_i < i + 2; ++buf_i) {
        for (int buf_j = j - 1; buf_j < j + 2; ++buf_j) {
            if (buf_i != i || buf_j != j) {
                try {
                    if (m_cave_(buf_i, buf_j) == kALIVE)
                        counter++;
                } catch (std::out_of_range &err) {  // если клетки нет, считаем ее живой
                    counter++;
                }
            }
        }
    }
    return counter;
}

/**
 * Filling cave matrix by receiving
 * information from user specified file.
 * @param file_path the file function reads from.
 * @return Cave matrix filled with data from file.
 */
Cave::CaveMatrix Cave::GetCaveFromFile_(const std::string &file_path) {
    std::string buffer;
    std::vector<bool> cave;
    std::fstream file;
    file.open(file_path);
    if (file.is_open()) {
        while (getline(file, buffer)) {
            while (buffer.size() > 0) {
                cave.push_back(stoi(buffer));
                buffer.erase(0, buffer.find_first_of(' ') + 1);
            }
        }
    }
    cave.erase(cave.begin());
    cave.erase(cave.begin());
    return Cave::CaveMatrix::VectorToMatrix(cave);
}

int Cave::GetRandomNumber_() {
    std::mt19937 engine;
    std::random_device device;
    engine.seed(device());
    int num = engine() % 100 - 0;
    return num;
}
}  // namespace s21