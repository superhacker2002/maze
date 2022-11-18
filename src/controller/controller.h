#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/cave/cave.h"
#include "../model/maze/maze.h"

namespace s21 {
class Controller {
  public:
    using CavePtr = std::unique_ptr<Cave>;
    using MazePtr = std::unique_ptr<Maze>;

  private:
    CavePtr m_cave_;
    MazePtr m_maze_;

  public:
    Controller() {;}
    ~Controller() = default;
    void GetRandomCave(size_t rows, size_t cols, s21::Limits limit, int birth_chance);
    int GetCaveRows() { return m_cave_.get()->GetRows(); }
    int GetCaveCols() { return m_cave_.get()->GetCols(); }
    bool GetPixel(int i, int j) { return m_cave_.get()->GetValue(i, j); }
    void TransformOnce() { m_cave_.get()->Transform(); }
    void TransformTillEnd() { m_cave_.get()->TransformCycle(); }
    void FlipCave() { m_cave_.get()->FlipCave(); }
    bool DoesCaveExist() { return m_cave_ != nullptr; }


    void GetMazeFromFile(const std::string& file_path);
    void GenerateMaze(int rows, int cols);
    int GetMazeRows() { return m_maze_.get()->GetRows(); }
    int GetMazeCols() { return  m_maze_.get()->GetCols(); }
    walls GetWall(int i, int j) { return m_maze_.get()->GetValue(i, j); }
    s21::Maze::AnswerData GetAnswer(std::pair<int, int> p1, std::pair<int, int> p2) { return m_maze_->GetAnswer(p1, p2); }
    bool DoesMazeExist() { return m_maze_ != nullptr; }

};  // class Controller
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
