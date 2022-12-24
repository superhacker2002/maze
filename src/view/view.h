#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QFileDialog>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QPen>
#include <QTimer>
#include <QErrorMessage>

#include "../controller/controller.h"

namespace s21 {
namespace Ui {
class View;
}

class View : public QMainWindow {
  Q_OBJECT

 public:
  View(QWidget *parent = nullptr);
  ~View();

 private:
  std::unique_ptr<Ui::View> m_ui_;
  std::unique_ptr<QGraphicsScene> m_scene_;
  std::unique_ptr<QPen> m_pen_;
  std::unique_ptr<s21::Controller> m_controller_;
  std::unique_ptr<QTimer> m_timer_;

  // common
  void StartSettings_();
  void ClearDrawArea_();
  void ConnectButtons_();
  // cave
  void PaintCave_();

  // maze
  void PaintMaze_();
  void PaintBorders_();
  std::vector<QLineF> GetAnswer_(std::pair<int, int> p1,
                                 std::pair<int, int> p2);

 private slots:
  void TransformCave_();
  void GetCaveFromFile_();
  void CaveInit_();
  void FlipCave_();
  void TransformCycling_();
  void StopTransformCycle_();

  void MazeInit_();
  void RandomMaze_();
  void PaintAnswer_();
  void SaveMaze_();
  void SetCoordinatesLimits_();

  void onTabChanged_();
};
}  // namespace s21
#endif  // SRC_VIEW_VIEW_H_
