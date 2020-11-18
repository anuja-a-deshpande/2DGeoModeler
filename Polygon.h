#ifndef POLYGON_H
#define POLYGON_H

#include "Shape.h"
#include "Line.h"
#include "Point.h"
#include<vector>
#include<map>
#include<math.h>

using namespace std;
class Polygon : public Two_d_shape
{
public:
	// default constructor
	Polygon();

	//parametraised constructor
	Polygon(vector<Point *> polypoint);

	//destructor
	~Polygon();

	virtual void Draw();
    virtual void GenerateData(Shape* secondShape);
	virtual double Area();
	virtual double Perimeter();
	virtual int getType();
	int getIndexOfLine(vector<Line *>,Line * l);
	
	void setPointPosition(Polygon *p);
    void splitByVertices(std::map<Line*,std::vector<Point*> > mydata);
    vector<Point *> sortPointsData(Point* p,vector<Point* > pv);
	vector<Line *> getEdges();
	 bool pointPositionOfPolygon(Point *p);
	 double Angle2D(Point* p1,Point* p2);
    vector<Shape *> Intersection(Polygon* pl2);
    vector<Shape *> Union(Polygon* pl2 );
    vector<Shape *> Difference(Polygon* pl2 );
    vector<Shape*> noIntersectionCaseForDifference(Polygon* pl1,Polygon* pl2);
    vector<Shape*> noIntersectionCaseForUnion(Polygon* pl1,Polygon* pl2);
    vector<Shape*> noIntersectionCaseForIntersection(Polygon* pl1,Polygon* pl2);

     void setEdgePosition(Polygon* pl2);
     void Drawintersection();
        bool EdgeInsidePolygon(Line * l);
		bool PolygonEdgeStatus();


	Line * getEdge1(Polygon *p,Line * lv);
	Line * getEdge2(Polygon *p,Line * lv);

	//copy constructor
	//Polygon(const Polygon &polygon);
	//const Polygon& operator=(const Polygon & equal);

protected:
	vector<Line*> m_Edges;
};
#endif
