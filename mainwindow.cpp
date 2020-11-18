#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPoint_triggered()
{
    GLWidget::setCounter(1);
}

void MainWindow::on_actionLine_triggered()
{
    GLWidget::setCounter(2);
}

void MainWindow::on_actionPolygon_triggered()
{
    GLWidget::setCounter(3);
}

void MainWindow::on_actionIntersection_triggered()
{
    GLWidget::setCounter(4);
}

void MainWindow::on_actionUnion_triggered()
{
    GLWidget::setCounter(5);
}

void MainWindow::on_actionDiffernce_triggered()
{
    GLWidget::setCounter(6);
}

void MainWindow::on_actionClear_triggered()
{
    GLWidget::setCounter(7);
}
