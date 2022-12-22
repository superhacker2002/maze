#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/cave/cave.h"
#include "../model/maze/maze.h"
#include "../model/drawing/maze_drawing.h"
#include "../model/drawing/cave_drawing.h"

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
    void GetRandomCave(size_t rows, size_t cols, std::pair<int, int> limit, int birth_chance);
    void GetCaveFromFile(const std::string& file_path, std::pair<int, int> limit);
    int GetCaveRows();
    int GetCaveCols();
    bool GetPixel(int i, int j);
    bool TransformOnce();
    void FlipCave();
    bool CaveExists();
    std::vector<QRectF> GetCaveDrawData();


    void GetMazeFromFile(const std::string& file_path);
    void GenerateMaze(int rows, int cols);
    int GetMazeRows();
    int GetMazeCols();
    Walls GetWall(int i, int j);
    std::vector<QLineF> GetAnswer(std::pair<int, int> p1, std::pair<int, int> p2);
    bool MazeExists();
    std::vector<QLineF> GetMazeDrawData();
    void SaveMaze(const std::string& file_path);

};  // class Controller
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
