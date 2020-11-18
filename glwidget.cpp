#include "glwidget.h"
#include<QToolTip>
#include<qopenglfunctions.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent)
{
    setMouseTracking(true);
}

void GLWidget::initializeGL()
{

    glClearColor(1,1,1,1);

    //gluOrtho2D(0,800,0,750);

}



void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    for(size_t i=0;i<this->pointVector.size();i++){
        if(this->pointVector.size()%2==0)
        {
            Line *l=new Line(pointVector[i],pointVector[i+1]);
            cmod.m_allShapes.push_back(l);
            i++;
        }
    }

    for(size_t i=0; i<this->cmod.m_allShapes.size();i++)
    {
        this->cmod.m_allShapes[i]->Draw();
    }

    if(Counter==1)
    {
        for(size_t i=0;i<temp.size();i++)
        {
            temp[i]->Draw();
            //Circle *c = new Circle(2.0,temp[i]);
            //c->Draw();
        }
    }else if(Counter==3)
    {
        for(size_t i=0; i < temp.size(); i++)
        {
            //Circle *c=new Circle(2.0,temp[i]);
            //c->Draw();
        }
        for(size_t i=0; i < polygonvector.size(); i++)
            polygonvector[i]->Draw();

    }else if((Counter==4) || (Counter==5) || (Counter==6))
    {
        //         for(int i=0;i<temp.size();i++)
        //         {
        //         //Circle *c=new Circle(2.0,temp[i]);
        //         //c->Draw();
        //         }
        for(size_t i = 0; i < polygonvector.size(); i++)
            polygonvector[i]->Draw();

        for(size_t i=0; i < pintersection.size(); i++)
        {
            pl=dynamic_cast<Polygon*>(pintersection[i]);
            pl->Drawintersection();
        }
    }
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,(GLsizei) w,(GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
void GLWidget::mouseTracking(QMouseEvent *e)
{
    cursor().setPos(e->pos());

}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    QToolTip::showText(event->globalPos(),
                       //  In most scenarios you will have to change these for
                       //  the coordinate system you are working in.
                       QString::number( event->pos().x() ) + ", " +
                       QString::number(750- event->pos().y() )+" ,"+QString::number(temp.size()),
                       this,rect());
    // QWidget::mouseMoveEvent(event);  // Or whatever the base class is.

}
void GLWidget::mousePressEvent(QMouseEvent *e)
{
    if(Counter==1)
    {
        // QMessageBox::information(this, "Polygon is created","Counter="+QString::number(Counter));
        p=new Point((double)(e->x()),750-(double)(e->y()));
        temp.push_back(p);

        //  cmod.AddShape(p);
        updateGL();
    }else if (Counter==2) {
        //QMessageBox::information(this, "Polygon is created","Counter="+QString::number(Counter));
        p=new Point((double)(e->x()),750-(double)(e->y()));
        temp.push_back(p);
        updateGL();
    }else if (Counter==3) {
        //  QMessageBox::information(this, "Polygon is created","Counter="+QString::number(Counter));
        p=new Point((double)(e->x()),750-(double)(e->y()));

        if(!search(temp,p))
        {
            temp.push_back(p);
            updateGL();
        }
        else
        {
            polygonvector.push_back(new Polygon(temp));
            updateGL();
            temp.clear();
        }

    }else if(Counter==4)
    {
        pintersection.clear();
        QMessageBox::information(this, "Intersection is ","Counter="+QString::number(Counter));
        polygonvector[0]->GenerateData(polygonvector[1]);
        pintersection= polygonvector[0]->Intersection(polygonvector[1]);

        updateGL();

    }else if(Counter==5)
    {

        QMessageBox::information(this, "Union is ","Counter="+QString::number(Counter));
        polygonvector[0]->GenerateData(polygonvector[1]);
        pintersection= polygonvector[0]->Union(polygonvector[1]);

        updateGL();

    }else if(Counter==6)
    {

        QMessageBox::information(this, "Difference is ","Counter="+QString::number(Counter));
        polygonvector[0]->GenerateData(polygonvector[1]);
        pintersection= polygonvector[0]->Difference(polygonvector[1]);

        updateGL();
    }else if(Counter==7)
    {
        pintersection.clear();
        pointVector.clear();
        polygonvector.clear();
        temp.clear();
        updateGL();
    }

    //    else if(Counter==4)
    //        {
    //          cmod.clearAllshapes();

    //          updateGL();
    //       }
}
bool GLWidget::search(std::vector<Point *> pv,Point *p)
{
    for(size_t i=0;i<temp.size();i++)
    {
        double x=(pv[i]->GetXCoord()-p->GetXCoord())*(pv[i]->GetXCoord()-p->GetXCoord());
        double y=(pv[i]->GetYCoord()-p->GetYCoord())*(pv[i]->GetYCoord()-p->GetYCoord());
        if(qSqrt(x+y)<10)
            return true;

    }
    return false;

}
void GLWidget::setCounter(int C)
{
    Counter=C;
}

