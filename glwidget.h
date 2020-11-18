#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QObject>
#include<QGLWidget>
#include<QMouseEvent>
#include<QMessageBox>
#include<OpenGL/glu.h>
//#include<OpenGL/glut.h>
#include<OpenGL/gl.h>
#include<Point.h>
#include<Line.h>
#include<CModeler.h>
#include<Polygon.h>
#include<Circle.h>


using namespace std;
static int Counter;
class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    CModeler cmod;


    std::vector<Shape *> pintersection;
    std::vector <Point *> pointVector;
    std::vector<Polygon *> polygonvector;
    std::vector<Point *> temp;
    Point * p;
    Polygon *pl;
    explicit GLWidget(QWidget *parent = 0);


    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseTracking(QMouseEvent *e);
    bool  search(std::vector<Point *> pv,Point *p);
    static void setCounter(int C);


signals:

public slots:


private:

};

#endif // GLWIDGET_H
