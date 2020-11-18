#include "Line.h"
//#include<math.h>
#include<qmath.h>
#include<QtGlobal>

using namespace std;
//parametraised constructor
Line::Line(Point *p1, Point *p2)
{
	m_startPoint =p1;
	m_endPoint = p2;
}
//defualt constructor
Line::Line()
{
}
//destructor
Line::~Line()
{
}
bool Line::operator==(const Line& secondLine)
{
	if(this->m_startPoint==secondLine.m_startPoint&&this->m_endPoint==secondLine.m_endPoint)
		return true;
	else
		return false;
}

bool Line::Reverse(const Line& secondLine)
{
	if(this->m_startPoint==secondLine.m_endPoint&&this->m_endPoint==secondLine.m_startPoint)
		return true;
	else
		return false;
}
Point* Line::GetStartPoint() const
{
	return m_startPoint;
}
Point* Line::GetEndPoint() const
{
	return m_endPoint;
}

void Line::SetStartPoint(Point* x)
{
	this->m_startPoint=x;
}
void Line::SetEndPoint(Point* y)
{
	this->m_endPoint=y;
}

double Line::Area()
{
	return 0.0;
}

double Line::Perimeter()
{
	return 0.0;
}
bool Line::IsParallel(Line* secondLine)
{
	double cos = this->cosAngle(secondLine);
    cos=qAbs(cos);

    if ((1 - cos) < 0.000001)
		return true;
	else
		return false;
}
double Line::cosAngle(Line* e2)
{
	Point p1(this->m_endPoint->GetXCoord()- this->m_startPoint->GetXCoord(), this->m_endPoint->GetYCoord() - this->m_startPoint->GetYCoord());
	Point p2(e2->m_endPoint->GetXCoord()- e2->m_startPoint->GetXCoord(), e2->m_endPoint->GetYCoord() - e2->m_startPoint->GetYCoord());

	double modp1 = mod(p1);
	double modp2 = mod(p2);

	double p12dot = dot(p1,p2);

	return p12dot / (modp1 * modp2);


}
double Line::dot(Point p1, Point p2)
{
	return p1.GetXCoord() * p2.GetXCoord() + p1.GetYCoord() * p2.GetYCoord();
}

double Line::mod(Point p)
{
    return qSqrt(p.GetXCoord() * p.GetXCoord() + p.GetYCoord() * p.GetYCoord());
}

bool Line::isLineContains(Point* point)
{
	Line *e2=new Line(this->GetEndPoint(),this->GetStartPoint());

	Line *e3=new Line(point,this->GetStartPoint());


	double cos = e2->cosAngle(e3);
    cos=qAbs(cos);
	if ((1 - cos) < 0.000001)
	{
		//case parallel
		double u = (point->GetXCoord() - this->GetStartPoint()->GetXCoord()) / ( this->GetEndPoint()->GetXCoord() -  this->GetStartPoint()->GetXCoord());
		double v = (point->GetYCoord() -  this->GetStartPoint()->GetYCoord()) / (this->GetEndPoint()->GetYCoord() - this->GetStartPoint()->GetYCoord());

		if ((u <= 1 && u >= 0) || (v <= 1 && v >= 0))
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;

}

int Line::getType()
{
	return 2;
}
void Line::GenerateData(Shape* secondShape)
{

}
Point* Line::LineLineIntersection(Line* secondLine,int& flag)
{

	if(this==secondLine)
	{
		flag=1;
		return nullptr;
	}
	if(this->Reverse(*secondLine)) {
		flag=1;
		return nullptr;
	}
	if(this->IsParallel(secondLine))
	{
		if( this->isLineContains(secondLine->GetStartPoint())) {
			flag=1;
			return nullptr;
		}		
		if( this->isLineContains(secondLine->GetEndPoint())) {
			flag=1;
			return nullptr;
		}
		if( secondLine->isLineContains(this->GetStartPoint())) {
			flag=1;
			return nullptr;
		}
		if( secondLine->isLineContains(this->GetEndPoint())) {
			flag=1;
			return nullptr;
		}
	}
	else
	{
		Point * resultPoint=nullptr;
		resultPoint=this->LLIntersectionNotParallel(secondLine);
		
		return resultPoint;
	}
	return nullptr;
}
Point* Line::LLIntersectionNotParallel(Line* secondLine)
{
	double u, v, d, dx, dy;
	d = determinant(this->GetStartPoint()->GetXCoord() - this->GetEndPoint()->GetXCoord(), secondLine->GetEndPoint()->GetXCoord() - secondLine->GetStartPoint()->GetXCoord(), this->GetStartPoint()->GetYCoord() - this->GetEndPoint()->GetYCoord(), secondLine->GetEndPoint()->GetYCoord() - secondLine->GetStartPoint()->GetYCoord());
	dx = determinant(this->GetStartPoint()->GetXCoord() - secondLine->GetStartPoint()->GetXCoord(), secondLine->GetEndPoint()->GetXCoord() - secondLine->GetStartPoint()->GetXCoord(), this->GetStartPoint()->GetYCoord() - secondLine->GetStartPoint()->GetYCoord(), secondLine->GetEndPoint()->GetYCoord() - secondLine->GetStartPoint()->GetYCoord());
	dy = determinant(this->GetStartPoint()->GetXCoord() - this->GetEndPoint()->GetXCoord(), this->GetStartPoint()->GetXCoord() - secondLine->GetStartPoint()->GetXCoord(), this->GetStartPoint()->GetYCoord() - this->GetEndPoint()->GetYCoord(), this->GetStartPoint()->GetYCoord() - secondLine->GetStartPoint()->GetYCoord());
	u = dx / d;
	v = dy / d;
	if ((0 <= u && u <= 1) && (0 <= v && v <= 1))
	{
		Point* p = new Point(this->GetStartPoint()->GetXCoord() + u * (this->GetEndPoint()->GetXCoord() - this->GetStartPoint()->GetXCoord()), this->GetStartPoint()->GetYCoord() + u * (this->GetEndPoint()->GetYCoord() - this->GetStartPoint()->GetYCoord()));


		return p;
	}
	else
		return nullptr;
}
double Line::determinant(double a1, double a2, double a3, double a4)
{
	return a1 * a4 - a2 * a3;

}

void Line::Setlposition(linePosition position)
{
	lPosition= position;
}

linePosition Line::Getlposition()
{
	return this->lPosition;
}

double Line::length()
{
	double a=GetEndPoint()->GetXCoord()-GetStartPoint()->GetXCoord();
	double b=GetEndPoint()->GetYCoord()-GetStartPoint()->GetYCoord();
    return qSqrt(a*a+b*b);
}
void Line::Draw()
{
	////each pair of vertices is drawn as a separate line.
    glBegin(GL_LINE);
    glColor3f(0.0,1.0,0.0);

    glVertex2d ( m_startPoint->GetXCoord(), m_startPoint->GetYCoord());
    glVertex2d ( m_endPoint->GetXCoord(), m_endPoint->GetYCoord());

    glEnd();
}
