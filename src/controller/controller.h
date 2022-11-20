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
    int GetCaveRows();
    int GetCaveCols();
    bool GetPixel(int i, int j);
    void TransformOnce();
    void TransformTillEnd();
    void FlipCave();
    bool DoesCaveExist();
    std::vector<QRectF> GetCaveDrawData();


    void GetMazeFromFile(const std::string& file_path);
    void GenerateMaze(int rows, int cols);
    int GetMazeRows();
    int GetMazeCols();
    walls GetWall(int i, int j);
    std::vector<QLineF> GetAnswer(std::pair<int, int> p1, std::pair<int, int> p2);
    bool DoesMazeExist();
    std::vector<QLineF> GetMazeDrawData();

};  // class Controller
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
