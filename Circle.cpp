#include "Circle.h"
#include "math.h"
#include<stdio.h>
#include "QOpenGLFunctions"
#include<vector>

//default constructor
Circle::Circle()
{

}
//parameterized constructor
Circle::Circle(double radi,Point* center)
{
    m_radius=radi;
    m_center=center;

}
Circle::~Circle()
{
    delete m_center;

}
Circle::Circle(const Circle &circle)
{
    m_radius=circle.m_radius;
    m_center = new Point((*circle.m_center));

}
const Circle &Circle:: operator=(const Circle & equal)
{
    m_radius=equal.m_radius;
    m_center=equal.m_center;
    return *this;
}
//getter
Point* Circle::GetCenter() const
 {
     return m_center;
 }
double Circle::GetRadius() const
 {
   return m_radius;
 }
//setter
void Circle::SetRadius(double r)
{
        m_radius = r;
}
double Circle::Area()
{
    return pi*GetRadius()*GetRadius();
}

double Circle::Perimeter()
{
    return 2*pi*GetRadius();
}
void Circle::GenerateData(Shape* secondShape)
{

}

void Circle::Draw()
{
    glColor3f(1.0,0.0,0.0);
      glBegin(GL_POINTS);
        for(double i=0;i<360;i+=0.5)
           {
               //(center+radius*cos(i+0.1),center+radius*sin(i+0.1));
               glVertex2d(m_center->GetXCoord()+m_radius*cos(i+0.1),m_center->GetYCoord()+m_radius*sin(i+0.1));
           }
        glEnd();
      glFlush();
}


