#ifndef S21_VIEW_H
#define S21_VIEW_H

#include <QMainWindow>

namespace s21 {

namespace Ui { class View; }

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();

private:
    Ui::View *ui;
};

} // namespace s21
#endif // S21_VIEW_H
