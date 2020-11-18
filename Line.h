#ifndef LINE_H
#define LINE_H

#include "Two_d_shape.h"
#include "Point.h"


enum linePosition
	{
		in,out,on
	};
class Line : public Two_d_shape
{ 
public:
	//parametraised constructor
	Line(Point *p1, Point *p2);
	//defualt constructor
	Line();
	//destructor
	~Line();

	virtual void Draw();
    virtual void GenerateData(Shape* secondShape);
	virtual double Area();
	virtual double Perimeter();
	virtual int getType();

    //Equals operetor
	bool operator==(const Line& secondLine);
	//for checking lines are reverse
	bool Reverse(const Line& secondLine);

	//setters
	void SetStartPoint(Point *p1);
	 void SetEndPoint(Point *p2);

	//getters
	Point* GetStartPoint() const;
	Point* GetEndPoint() const;

	//for Line Line intersection
	Point* LineLineIntersection(Line* secondLine,int& flag);
	Point* LLIntersectionNotParallel(Line* secondLine);
	//helper for intersection
	bool IsParallel(Line* secondLine);
	double cosAngle(Line* e2);
    double mod(Point p);
    double dot(Point p1, Point p2);
	double determinant(double a1, double a2, double a3, double a4);
	bool isLineContains(Point* point);
	double length();

	 void Setlposition(linePosition position);
    //void display();
	 linePosition Getlposition();
private:

	Point *m_startPoint;
	Point *m_endPoint;
	 linePosition lPosition;
};

#endif
