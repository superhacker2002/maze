#include "view.h"
#include "ui_view.h"

s21::View::View(QWidget *parent)
    : QMainWindow(parent) , m_ui_(std::make_unique<s21::Ui::View>()),
    m_scene_(std::make_unique<QGraphicsScene>()), m_pen_(std::make_unique<QPen>(Qt::SolidPattern, 2)),
    m_controller_(std::make_unique<s21::Controller>()) {
  m_ui_->setupUi(this);
  StartSettings_();
}

void s21::View::onTabChanged_() {
  if (m_ui_->tabWidget->currentIndex() == 0) {
    PaintMaze_();
  } else {
    PaintCave_();
  }
}

void s21::View::ClearDrawArea_() {
  m_scene_->clear();
}

void s21::View::PaintBorders_() {
  m_scene_->addLine(10, 10, 10, 500, *m_pen_);
  m_scene_->addLine(10, 10, 500, 10, *m_pen_);
}

void s21::View::FlipCave_() {
  if (m_controller_->CaveExists()) {
    m_controller_->FlipCave();
    PaintCave_();
  }
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
    m_ui_->x2_spinbox->setMaximum(m_ui_->maze_cols->value() - 1);
    m_ui_->y2_spinbox->setMaximum(m_ui_->maze_rows->value() - 1);
    PaintMaze_();
}

void s21::View::TransformCave_() {
  if (m_controller_->CaveExists()) {
    m_controller_->TransformOnce();
    PaintCave_();
  }
}

void s21::View::PaintCave_() {
  ClearDrawArea_();
  if (m_controller_->CaveExists()) {
    auto data = m_controller_->GetCaveDrawData();
    for (auto it : data)
      m_scene_->addRect(it, *m_pen_, Qt::SolidPattern);  
  }
}

void s21::View::PaintMaze_() {
  ClearDrawArea_();
  if (m_controller_->MazeExists()) {
    PaintBorders_();
    auto data = m_controller_->GetMazeDrawData();
    for (auto it : data) {
      m_scene_->addLine(it, *m_pen_);
    }
  }
}

std::vector<QLineF> s21::View::GetAnswer_(std::pair<int, int> p1, std::pair<int, int> p2) {
  return m_controller_->GetAnswer(p1, p2);
}

void s21::View::PaintAnswer_() {

  if (m_controller_->MazeExists()) {
    m_pen_->setColor(QColor::fromRgbF(1.0, 0.0, 0.0));  // red
    auto lines_vec = GetAnswer_({
        m_ui_->x1_spinbox->value(),
        m_ui_->y1_spinbox->value()
      }, {
        m_ui_->x2_spinbox->value(),
        m_ui_->y2_spinbox->value()
      }
    );
    for (auto& line : lines_vec) {
      m_scene_->addLine(line, *m_pen_);
    }

    m_pen_->setColor(QColor::fromRgbF(0.0, 0.0, 0.0));  // back to black  
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
  connect(m_ui_->draw_answer_button, SIGNAL(clicked()), this, SLOT(PaintAnswer_()));
  connect(m_ui_->tabWidget, SIGNAL(currentChanged(int)), this, SLOT(onTabChanged_()));
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
