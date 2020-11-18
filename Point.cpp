#include "Point.h"
#include "Polygon.h"
#include<qmath.h>
#include<QtGlobal>
#include<iostream>
using namespace std;
//default constructor
Point::Point()
{	
}

Point::Point(double x, double y)
{
	m_XCoord = x;
	m_YCoord = y;
}

//destructor
Point::~Point()
{
}
//copy constructor
Point::Point(const Point& point)
{
    m_XCoord = point.GetXCoord();
	m_YCoord = point.GetYCoord();
}

const Point& Point::operator=(const Point& secondPt)
{
    m_XCoord = secondPt.GetXCoord();
    m_YCoord = secondPt.GetYCoord();

	return *this;
}
bool Point::operator==(const Point secondpoint)
{
    bool result;
    double x=(this->GetXCoord()-secondpoint.GetXCoord())*(this->GetXCoord()-secondpoint.GetXCoord());
    double y=(this->GetYCoord()-secondpoint.GetYCoord())*(this->GetYCoord()-secondpoint.GetYCoord());
    double diff=qSqrt(x+y);
    if(qAbs(diff)<0.000001)
        result= true;
	else
        result=false;

    return result;
}

//getters
double Point::GetXCoord() const
{
    return m_XCoord;
}

double Point::GetYCoord()const
{
    return m_YCoord;
}

//setters
void Point::SetXCoord( double x )
{
     m_XCoord= x;
}

void Point::SetYCoord( double y )
{
     m_YCoord= y;
}


double Point::Area()
{
	return 0.0;
}

double Point::Perimeter()
{
	return 0.0;
}

void Point::GenerateData(Shape* secondShape)
{

}

int Point::getType()
{
	return 1;
}

void Point::SetPposition(pointPosition position)
{
	pPosition= position;
}
pointPosition Point::GetPposition()
{
	return this->pPosition;
}

void Point::Draw()
{
    glColor3f(1.0,0.0,0.0);
   // glPointSize(4);
    glBegin(GL_POINT);
    glVertex2d(this->GetXCoord(),this->GetYCoord());
    glEnd();
}







