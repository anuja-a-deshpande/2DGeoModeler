#ifndef CIRCLE_H
#define CIRCLE_H

#include "Two_d_shape.h"
#include "Point.h"

static const double pi=3.14159;

class Circle : public Two_d_shape
{
public:
        //radi means radius circle.
        Circle(double radi,Point* center);

        //destructor
        ~Circle();

        virtual void Draw();
        virtual void GenerateData(Shape* secondShape);
        virtual double Area();
        virtual double Perimeter();

       //copy constructor
        Circle(const Circle &circle);
        const Circle& operator=(const Circle & equal);

        Point* GetCenter() const;
        double GetRadius() const;

private:
        //default constructor
        Circle();

        //r means radius of circle
        void SetRadius(double r);

        Point* m_center;
        double m_radius;
};
#endif
