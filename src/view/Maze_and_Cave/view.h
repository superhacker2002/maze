#ifndef SRC_VIEW_VIEW_H_
#define SRC_VIEW_VIEW_H_

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QFileDialog>

#include "../../controller/controller.h"

namespace s21 {
namespace Ui { class View; }

class View : public QMainWindow {
  Q_OBJECT

  public:
    View(QWidget *parent = nullptr);
    ~View();

  private:
    Ui::View* m_ui_;
    QGraphicsScene* m_scene_;
    QPen* m_pen_;
    s21::Controller* m_controller_;

    void StartSettings_();



    void ClearDrawArea_();
    void PaintCave_();
    void ConnectButtons_();
    
    void PaintMaze_();



  private slots:
    void TransformCave_();
    void CaveInit_();
    void FlipCave_();

    void MazeInit_();
};
} // namespace s21
#endif // SRC_VIEW_VIEW_H_
