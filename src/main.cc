#include "view/view.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::View window;
  window.show();
  return a.exec();
}
