#include "view.h"
#include "ui_view.h"

s21::View::View(QWidget *parent)
    : QMainWindow(parent) , m_ui_(std::make_unique<s21::Ui::View>()),
    m_scene_(std::make_unique<QGraphicsScene>()), m_pen_(std::make_unique<QPen>(Qt::SolidPattern, 2)),
    m_controller_(std::make_unique<s21::Controller>()) {
  m_ui_->setupUi(this);
  StartSettings_();  
}

void s21::View::ClearDrawArea_() {
  m_scene_->clear();
}

void s21::View::PaintBorders_() {
  m_scene_->addLine(10, 10, 10, 500, *m_pen_);
  m_scene_->addLine(10, 10, 500, 10, *m_pen_);
}

void s21::View::FlipCave_() {
  m_controller_->FlipCave();
  PaintCave_();
}

void s21::View::CaveInit_() {
  m_controller_->GetRandomCave(
    m_ui_->rows_spinbox->value(), 
    m_ui_->cols_spinbox->value(),
    {
      m_ui_->birth_spinbox->value(),
      m_ui_->death_spinbox->value(),
    },
    m_ui_->birth_chance_spinbox->value()
    );
  PaintCave_();
}

void s21::View::MazeInit_() {
  QString filepath = QFileDialog::getOpenFileName(0, "Выбрать файл", "", "*.txt");
  if (filepath != "") {
    m_controller_->GetMazeFromFile(filepath.toStdString());
    PaintMaze_();
  } else {
    ClearDrawArea_();
  }
}

void s21::View::RandomMaze_() {
    m_controller_->GenerateMaze(m_ui_->maze_rows->value(), m_ui_->maze_cols->value());
    PaintMaze_();
}

void s21::View::TransformCave_() {
  m_controller_->TransformOnce();
  PaintCave_();
}

void s21::View::PaintCave_() {
  ClearDrawArea_();
  int rows = m_controller_->GetCaveRows();
  int cols = m_controller_->GetCaveCols();
  int x_size = 500 / rows, y_size = 500 / cols;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (m_controller_->GetPixel(i, j))
        m_scene_->addRect(i * x_size, j * y_size, x_size, y_size, *m_pen_, Qt::SolidPattern);
    }
  }
}

void s21::View::PaintMaze_() {
  ClearDrawArea_();
  PaintBorders_();
  int rows = m_controller_->GetMazeRows();
  int cols = m_controller_->GetMazeCols();
  int x_size = 500 / rows, y_size = 500 / cols;
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (m_controller_->GetWall(i, j).bottom_wall) {
        int x1 = j * x_size == 0 ? 10 : j * x_size;
        int y1 = (i + 1) * y_size == 0 ? 10 : (i + 1) * y_size;
        int x2 = x1 + x_size == 0 ? 10 : x1 + x_size;
        int y2 = y1;
        m_scene_->addLine(x1, y1, x2, y2, *m_pen_);  
      }
      if (m_controller_->GetWall(i, j).right_wall) {
        int x1 = (j + 1) * x_size == 0 ? 10 : (j + 1) * x_size;
        int y1 = i * y_size == 0 ? 10 : i * y_size;
        int x2 = x1;
        int y2 = y1 + y_size == 0 ? 10 : y1 + y_size;
        m_scene_->addLine(x1, y1, x2, y2, *m_pen_);
      }
    }
  }
}

s21::View::~View() {
  ;
}

void s21::View::ConnectButtons_() {
  connect(m_ui_->transform_cave_button, SIGNAL(clicked()), this, SLOT(TransformCave_()));
  connect(m_ui_->create_cave_button, SIGNAL(clicked()), this, SLOT(CaveInit_()));
  connect(m_ui_->flip_cave_button, SIGNAL(clicked()), this, SLOT(FlipCave_()));
  connect(m_ui_->maze_file_button, SIGNAL(clicked()), this, SLOT(MazeInit_()));
  connect(m_ui_->random_maze_button, SIGNAL(clicked()), this, SLOT(RandomMaze_()));
}

void s21::View::StartSettings_() {
  m_ui_->draw_area->setScene(m_scene_.get());
  m_ui_->draw_area->centerOn(0, 0);
  m_scene_->setSceneRect(0, 0, 510, 510);
  m_ui_->draw_area->setStyleSheet("background-color:white;");
  m_ui_->draw_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_ui_->draw_area->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_ui_->draw_area->setAlignment(Qt::AlignTop | Qt::AlignLeft);
  ConnectButtons_();
}
