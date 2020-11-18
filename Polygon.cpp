#include "Polygon.h"
#include<iostream>
#include<list>

using namespace std;


//default constructor
Polygon::Polygon()
{

}
//parametraised constructor
Polygon::Polygon(vector<Point *> polypoint)
{
	for(int i=0;i<polypoint.size(); i++)
	{
		if(i==(polypoint.size()-1))
		{
			Line* L1=new Line(polypoint[i],polypoint[0]);
			m_Edges.push_back(L1);
		}
		else
		{
			Line* L1=new Line(polypoint[i],polypoint[i+1]);
			m_Edges.push_back(L1);
		}
    }
}

//destructor
Polygon::~Polygon()
{
}

//copy constructor

double Polygon::Area()
{
	return 0.0;
}

double Polygon::Perimeter()
{
	return 0.0;
}

void Polygon::GenerateData(Shape* secondShape)
{
    int flag=0;
	int type=	secondShape->getType();
	Polygon *polygonParameter;
	Point *p;


    std::map<Line*,std::vector<Point* > > mydata1;
    std::map<Line*,std::vector<Point* > > mydata2;

	switch (type)
	{
	case 1:
		cout << "intersection with point"<<endl;
		break;
	case 2:
		cout << "intersection with line"<<endl;
		break;
	case 3:
		cout << "intersection with polygon"<<endl;

		polygonParameter=dynamic_cast<Polygon *> (secondShape);

		for(int i=0;i<m_Edges.size();i++)
		{
			for(int j=0;j<polygonParameter->m_Edges.size();j++)
			{

				p=	m_Edges[i]->LineLineIntersection(polygonParameter->m_Edges[j],flag);

                if(p!=NULL && flag!=1)
				{

					p->SetPposition(On);

					mydata1[m_Edges[i]].push_back(p);
					mydata2[polygonParameter->m_Edges[j]].push_back(p);

				}
				if(flag==1)
					break;
			}
			if(flag==1)
				break;
		}

		if(flag!=1)
		{
			//split both polygons.
			this->splitByVertices(mydata1);
			polygonParameter->splitByVertices(mydata2);
			//sets positions of points of both polygons.
			this->setPointPosition(polygonParameter);
			polygonParameter->setPointPosition(this);


		}

		break;
	default:
		break;
	}

}

bool Polygon::PolygonEdgeStatus()
{

	bool insideflag = true;
	bool outsideflag = true;

	for(int i=0;i<this->getEdges().size();i++)
	{
		if (this->getEdges()[i]->Getlposition()==in)
		{
			outsideflag = false;
		}
		else if (this->getEdges()[i]->Getlposition()==out)
		{
			insideflag = false;
		}


	}

	if (insideflag || outsideflag)
		return true;
	else
		return false;
}

vector<Shape*> Polygon::noIntersectionCaseForIntersection(Polygon* pl1,Polygon* pl2)
{
     vector<Shape *> booleanPolygonlist ;
     if (pl1->getEdges()[0]->Getlposition()==out && pl2->getEdges()[0]->Getlposition()==out)
     {
             //intersection is null;
     }
     else if (pl1->getEdges()[0]->Getlposition()==out && pl2->getEdges()[0]->Getlposition()==in)
     {

         booleanPolygonlist.push_back(pl2);

     }
     else if (pl1->getEdges()[0]->Getlposition()==in && pl2->getEdges()[0]->Getlposition()==out)
     {
         booleanPolygonlist.push_back(pl1);

     }
     return booleanPolygonlist;

}
vector<Shape*> Polygon::noIntersectionCaseForUnion(Polygon* pl1,Polygon* pl2)
{
     vector<Shape *> booleanPolygonlist ;
     if (pl1->getEdges()[0]->Getlposition()==out && pl2->getEdges()[0]->Getlposition()==out)
     {
         booleanPolygonlist.push_back(pl1);
         booleanPolygonlist.push_back(pl2);


     }
     else if (pl1->getEdges()[0]->Getlposition()==out && pl2->getEdges()[0]->Getlposition()==in)
     {

         booleanPolygonlist.push_back(pl1);
     }
     else if (pl1->getEdges()[0]->Getlposition()==in && pl2->getEdges()[0]->Getlposition()==out)
     {
     booleanPolygonlist.push_back(pl2);
     }
     return booleanPolygonlist;

}
vector<Shape*> Polygon::noIntersectionCaseForDifference(Polygon* pl1,Polygon* pl2)
{
     vector<Shape *> booleanPolygonlist ;
     if (pl1->getEdges()[0]->Getlposition()==out && pl2->getEdges()[0]->Getlposition()==out)
     {
         booleanPolygonlist.push_back(pl1);
     }
     else if (pl1->getEdges()[0]->Getlposition()==out && pl2->getEdges()[0]->Getlposition()==in)
     {
         booleanPolygonlist.push_back(pl1);
         booleanPolygonlist.push_back(pl2);

     }
     else if (pl1->getEdges()[0]->Getlposition()==in && pl2->getEdges()[0]->Getlposition()==out)
     {
         //difference is null;
     }
     return booleanPolygonlist;

}


Line * Polygon::getEdge1(Polygon *p,Line * lv)
{
	Line *l;
	for(int j=0;j<p->getEdges().size();j++)
	{
		if(p->getEdges()[j]->GetStartPoint()==lv->GetEndPoint())
		{
			l=p->getEdges()[j];
		}
	}
	return l;
}
Line * Polygon::getEdge2(Polygon *p,Line * lv)
{
	Line *l;
	for(int j=0;j<p->getEdges().size();j++)
	{
		if(p->getEdges()[j]->GetStartPoint()==lv->GetStartPoint())
		{
			l=p->getEdges()[j];
		}
	}
	return l;
}



vector<Shape *>Polygon::Intersection(Polygon* pl2)
{

       vector<Shape *> outputPolygonlist ;

       this->setEdgePosition(pl2);
       pl2->setEdgePosition(this);

       bool checkPolygon1EdgesStatus = this->PolygonEdgeStatus();
       bool checkPolygon2EdgesStatus = pl2->PolygonEdgeStatus();

       if (checkPolygon1EdgesStatus && checkPolygon2EdgesStatus)
       {
           //all edges of both polygons are inside or outside
           //intersection list is empty.

           outputPolygonlist=noIntersectionCaseForIntersection(this, pl2);


           return outputPolygonlist;

       }
       else
       {
           //not all edges of both polygons are inside or outside

           vector<Line*> innerEdge;



               //for intersection
               for (int i=0;i<this->getEdges().size();i++)
               {
                   if (this->getEdges()[i]->Getlposition()==in)
                       innerEdge.push_back(this->getEdges()[i]);
               }



           Polygon *current, *nonCurrent;

           vector<Line *> Elist;
           vector<Point*> Vlist;
           Line* edge;


           //intersection list not empty

           for (int i = 0; i < innerEdge.size(); i++)
           {
               current = this;
               nonCurrent = pl2;
               Vlist.clear();
               Elist.clear();
               Elist.push_back(innerEdge[i]);
               edge=getEdge1(current,Elist[0]);

               //edge = current.Edges.Single(s => s.V1.Equals(outEdgeList[i].V2));
               //outEdgeList.Remove(outEdgeList[i]);

               innerEdge.erase(innerEdge.begin()+i);

               do
               {

                       //intersection
                       if (current == this)
                       {
                           if ( edge->Getlposition()==in)
                           {
                               Elist.push_back(edge);

                               innerEdge.erase(innerEdge.begin()+getIndexOfLine(innerEdge,edge));
                               // outEdgeList.Remove(edge);
                               edge =getEdge1(current,edge);
                               //pl1.Edges.Single(s => s.V1.Equals(edge.V2));

                           }
                           else
                           {
                               current = pl2;
                               edge=getEdge2(current,edge);
                               //edge = pl2.Edges.Single(s => s.V1.Equals(edge.V1));
                           }
                       }
                       else
                       {
                           if (edge->Getlposition()==in)
                           {
                               Elist.push_back(edge);
                               //outerEdge.erase(outerEdge.begin()+getIndexOfLine(outerEdge,edge));
                               edge=pl2->getEdge1(current,edge);


                               //  Elist.Add(edge);
                               // outEdgeList.Remove(edge);
                               //edge = pl2.Edges.Single(s => s.V1.Equals(edge.V2));
                           }
                           else
                           {
                               current = this;
                               edge=this->getEdge2(current,edge);

                           }
                       }




               } while (Elist[0] != edge);


               for(int j=0;j<Elist.size();j++)
                   Vlist.push_back(Elist[j]->GetStartPoint());

               //Vlist = Elist.Select(s => s.V1).ToList();

               Polygon *p=new Polygon(Vlist);
               outputPolygonlist.push_back(p);

               i = 0;
           }


       }

       return outputPolygonlist;
}
vector<Shape *>Polygon::Union(Polygon* pl2)
{

       vector<Shape *> outputPolygonlist ;

       this->setEdgePosition(pl2);
       pl2->setEdgePosition(this);

       bool checkPolygon1EdgesStatus = this->PolygonEdgeStatus();
       bool checkPolygon2EdgesStatus = pl2->PolygonEdgeStatus();

       if (checkPolygon1EdgesStatus && checkPolygon2EdgesStatus)
       {
           //all edges of both polygons are inside or outside
           //intersection list is empty.

           outputPolygonlist=noIntersectionCaseForUnion(this, pl2);


           return outputPolygonlist;

       }
       else
       {
           //not all edges of both polygons are inside or outside

           vector<Line*> outerEdge;




               for (int i=0;i<this->getEdges().size();i++)
               {
                   if (this->getEdges()[i]->Getlposition()==out)
                       outerEdge.push_back(this->getEdges()[i]);
               }



           Polygon *current, *nonCurrent;

           vector<Line *> Elist;
           vector<Point*> Vlist;
           Line* edge;




           for (int i = 0; i < outerEdge.size(); i++)
           {
               current = this;
               nonCurrent = pl2;
               Vlist.clear();
               Elist.clear();
               Elist.push_back(outerEdge[i]);
               edge=getEdge1(current,Elist[0]);

               //edge = current.Edges.Single(s => s.V1.Equals(outEdgeList[i].V2));
               //outEdgeList.Remove(outEdgeList[i]);

               outerEdge.erase(outerEdge.begin()+i);

               do
               {
                   if (current == this)
                   {
                       if ( edge->Getlposition()!=in)
                       {
                           Elist.push_back(edge);

                           outerEdge.erase(outerEdge.begin()+getIndexOfLine(outerEdge,edge));
                           // outEdgeList.Remove(edge);
                           edge =getEdge1(current,edge);
                           //pl1.Edges.Single(s => s.V1.Equals(edge.V2));

                       }
                       else
                       {
                           current = pl2;
                           edge=getEdge2(current,edge);
                           //edge = pl2.Edges.Single(s => s.V1.Equals(edge.V1));
                       }
                   }
                   else
                   {
                       if (edge->Getlposition()!=in)
                       {
                           Elist.push_back(edge);
                           //outerEdge.erase(outerEdge.begin()+getIndexOfLine(outerEdge,edge));
                           edge=pl2->getEdge1(current,edge);


                           //  Elist.Add(edge);
                           // outEdgeList.Remove(edge);
                           //edge = pl2.Edges.Single(s => s.V1.Equals(edge.V2));
                       }
                       else
                       {
                           current = this;
                           edge=this->getEdge2(current,edge);

                       }
                   }


               } while (Elist[0] != edge);


               for(int j=0;j<Elist.size();j++)
                   Vlist.push_back(Elist[j]->GetStartPoint());

               //Vlist = Elist.Select(s => s.V1).ToList();

               Polygon *p=new Polygon(Vlist);
               outputPolygonlist.push_back(p);

               i = 0;
           }


       }

       return outputPolygonlist;
}
vector<Shape *>Polygon::Difference(Polygon* pl2)
{

       vector<Shape *> outputPolygonlist ;


       vector<Point *> newList ;

           for (int i=pl2->getEdges().size()-1;i>=0;i--)
           {

               newList.push_back(pl2->getEdges()[i]->GetStartPoint());
           }

           Polygon* p3 = new Polygon(newList);
           pl2 = p3;


       this->setEdgePosition(pl2);
       pl2->setEdgePosition(this);

       bool checkPolygon1EdgesStatus = this->PolygonEdgeStatus();
       bool checkPolygon2EdgesStatus = pl2->PolygonEdgeStatus();

       if (checkPolygon1EdgesStatus && checkPolygon2EdgesStatus)
       {
           //all edges of both polygons are inside or outside
           //intersection list is empty.

           outputPolygonlist=noIntersectionCaseForDifference(this, pl2);


           return outputPolygonlist;

       }
       else
       {
           //not all edges of both polygons are inside or outside

           vector<Line*> outerEdge;



               //for intersection
               for (int i=0;i<this->getEdges().size();i++)
               {
                   if (this->getEdges()[i]->Getlposition()==out)
                       outerEdge.push_back(this->getEdges()[i]);
               }



           Polygon *current, *nonCurrent;

           vector<Line *> Elist;
           vector<Point*> Vlist;
           Line* edge;


           //intersection list not empty

           for (int i = 0; i < outerEdge.size(); i++)
           {
               current = this;
               nonCurrent = pl2;
               Vlist.clear();
               Elist.clear();
               Elist.push_back(outerEdge[i]);
               edge=getEdge1(current,Elist[0]);

               //edge = current.Edges.Single(s => s.V1.Equals(outEdgeList[i].V2));
               //outEdgeList.Remove(outEdgeList[i]);

               outerEdge.erase(outerEdge.begin()+i);

               do
               {
                   if (current == this)
                   {
                       if ( edge->Getlposition()!=in)
                       {
                           Elist.push_back(edge);

                           outerEdge.erase(outerEdge.begin()+getIndexOfLine(outerEdge,edge));
                           // outEdgeList.Remove(edge);
                           edge =getEdge1(current,edge);
                           //pl1.Edges.Single(s => s.V1.Equals(edge.V2));

                       }
                       else
                       {
                           current = pl2;
                           edge=getEdge2(current,edge);
                           //edge = pl2.Edges.Single(s => s.V1.Equals(edge.V1));
                       }
                   }
                   else
                   {
                       if (edge->Getlposition()==in)
                       {
                           Elist.push_back(edge);
                           //outerEdge.erase(outerEdge.begin()+getIndexOfLine(outerEdge,edge));
                           edge=pl2->getEdge1(current,edge);


                           //  Elist.Add(edge);
                           // outEdgeList.Remove(edge);
                           //edge = pl2.Edges.Single(s => s.V1.Equals(edge.V2));
                       }
                       else
                       {
                           current = this;
                           edge=this->getEdge2(current,edge);

                       }
                   }


               } while (Elist[0] != edge);


               for(int j=0;j<Elist.size();j++)
                   Vlist.push_back(Elist[j]->GetStartPoint());

               //Vlist = Elist.Select(s => s.V1).ToList();

               Polygon *p=new Polygon(Vlist);
               outputPolygonlist.push_back(p);

               i = 0;
           }


       }

       return outputPolygonlist;
}




void Polygon::setEdgePosition(Polygon* pl2)
{
	for(int i=0;i<this->m_Edges.size();i++)
	{
		if (pl2->EdgeInsidePolygon(this->m_Edges[i]))
			this->m_Edges[i]->Setlposition(in);
		else
			this->m_Edges[i]->Setlposition(out);
	}

}
bool Polygon::EdgeInsidePolygon(Line * l)
{
	Point* v = new Point((l->GetStartPoint()->GetXCoord()+l->GetEndPoint()->GetXCoord())/2,(l->GetStartPoint()->GetYCoord()+l->GetEndPoint()->GetYCoord())/2);
	if (this->pointPositionOfPolygon(v))
		return true;
	else
		return false;
}

void Polygon::setPointPosition(Polygon *p)
{

	for (int i=0;i<this->m_Edges.size();i++)
	{
		if (this->m_Edges[i]->GetStartPoint()->GetPposition() != On)
		{
			if (p->pointPositionOfPolygon(this->m_Edges[i]->GetStartPoint()))
			{
				this->m_Edges[i]->GetStartPoint()->SetPposition(In);


			}
			else
			{
				this->m_Edges[i]->GetStartPoint()->SetPposition(Out);

			}

		}

	}
}
int Polygon::getType()
{
	return 3;
}
vector<Line *> Polygon::getEdges()
{
	return m_Edges;
}
vector<Point *> Polygon::sortPointsData(Point *p,vector<Point *> pv)
{
	Point * v;
	vector<double> distanceData;
	double length;

	Line *l;
	for(int i=0;i<pv.size();i++)
	{
		l= new Line(p,pv[i]);
		distanceData.push_back( l->length());
		cout<<"length is :"<<l->length()<<endl;
	}



	for (int i = 0; i < distanceData.size() ; i++)
	{
		for (int j = i + 1; j <distanceData.size(); j++)
		{
			if (distanceData[j] < distanceData[i])
			{

				v=pv[i];
				pv[i]=pv[j];
				pv[j]=v;

				length=distanceData[i];
				distanceData[i]=distanceData[j];
				distanceData[j] = length;
			}
		}
	}


	return pv;
}
int Polygon::getIndexOfLine(vector<Line *> polygonEdges,Line * lsearch)
{
	for(int i=0;i<polygonEdges.size();i++)
		if(polygonEdges[i]==lsearch)
			return i;
}
void Polygon::splitByVertices(std::map<Line*,std::vector<Point*> > mydata)
{
	Polygon p;
	vector<Point *> pointsAfterSorted;
	int index;
	int i=0;
	Line *l;

    for(auto itr = mydata.begin(); itr!=mydata.end(); itr++) {
		cout<<endl;
		i=0;
		pointsAfterSorted=sortPointsData(itr->first->GetStartPoint(),itr->second);

		index=getIndexOfLine(this->m_Edges,itr->first);

		this->m_Edges.erase(m_Edges.begin()+index);
		//on position to set.
		l=new Line(itr->first->GetStartPoint(),pointsAfterSorted[0]);
		l->GetEndPoint()->SetPposition(On);
		this->m_Edges.insert(m_Edges.begin()+index,l);

		int j;
		for(j=1;j<pointsAfterSorted.size();j++)
		{
			index++;
			l=new Line(pointsAfterSorted[j-1],pointsAfterSorted[j]);
			l->GetStartPoint()->SetPposition(On);	
			l->GetEndPoint()->SetPposition(On);
			this->m_Edges.insert(m_Edges.begin()+index,l);
		}
		index++;
		l=new Line(pointsAfterSorted[j-1],itr->first->GetEndPoint());
		l->GetStartPoint()->SetPposition(On);
		this->m_Edges.insert(m_Edges.begin()+index,l);




		for(auto vitr = itr->second.begin(); vitr != itr->second.end(); vitr++){


			i++;
		}

	}


}
bool Polygon::pointPositionOfPolygon(Point* p)
{
	int i;
	double angle = 0;
	Point *p1;
	Point *p2;

	for (i = 0; i <this->getEdges().size(); i++)
	{
		p1=new Point(this->getEdges()[i]->GetStartPoint()->GetXCoord()- p->GetXCoord(),this->getEdges()[i]->GetStartPoint()->GetYCoord()- p->GetYCoord() );
		p2=new Point(this->getEdges()[i]->GetEndPoint()->GetXCoord()- p->GetXCoord(),this->getEdges()[i]->GetEndPoint()->GetYCoord()- p->GetYCoord() );



		angle += Angle2D(p1, p2);
	}

    if (abs(angle) < 3.14)
		return (false);
	else
		return (true);
}


double Polygon::Angle2D(Point* p1, Point* p2)
{
	double dtheta, theta1, theta2;

	theta1 = atan2(p1->GetYCoord(), p1->GetXCoord());
	theta2 = atan2(p2->GetYCoord(), p2->GetXCoord());
	dtheta = theta2 - theta1;
	while (dtheta > 3.14)
		dtheta -= 2 * 3.14;
	while (dtheta < -3.14)
		dtheta += 2 * 3.14;

	return (dtheta);
}
void Polygon::Drawintersection()
{
    glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);

    for(int i=0;i<this->m_Edges.size();i++)
    {
        glVertex2d(this->m_Edges[i]->GetStartPoint()->GetXCoord(), this->m_Edges[i]->GetStartPoint()->GetYCoord());
    }

    glEnd();

}
void Polygon::Draw()
{
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);

    for(int i=0;i<this->m_Edges.size();i++)
    {
        glVertex2d(this->m_Edges[i]->GetStartPoint()->GetXCoord(), this->m_Edges[i]->GetStartPoint()->GetYCoord());
    }

    glEnd();
}
