#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionPoint_triggered();

    void on_actionLine_triggered();

    void on_actionPolygon_triggered();

    void on_actionIntersection_triggered();

    void on_actionUnion_triggered();

    void on_actionDiffernce_triggered();

    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
