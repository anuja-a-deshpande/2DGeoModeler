#ifndef POINT_H
#define POINT_H

#include "Two_d_shape.h"

#include <qmath.h>
#include<qopenglfunctions.h>


enum pointPosition
	{
		In,Out,On
	};

class Point : public Two_d_shape
{ 

public:
	//default constructor
	Point(); 
	//parameterized constructor
	Point(double x, double y);

	//destructor
	~Point();
	
	virtual void Draw();
    virtual void GenerateData(Shape* secondShape);
	virtual double Area();
	virtual double Perimeter();
	virtual int getType();
	

	//copy constructor
	Point(const Point &point);
	//operator overload "="
	const Point& operator=(const Point & secondPt);
	//operator overload "=="
    bool operator==(const Point secondpoint);
	
	//getters
	double GetXCoord() const;
	double GetYCoord() const;

	 void SetPposition(pointPosition position);
	
	 pointPosition GetPposition();
	 
	 
private:
	

	//setters
	 void SetXCoord(double x);
	 void SetYCoord(double y);
	
	 pointPosition pPosition;
	double m_XCoord;
	double m_YCoord;
};
#endif
