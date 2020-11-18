#ifndef TWO_D_SHAPE_H
#define TWO_D_SHAPE_H

#include "Shape.h"

class Two_d_shape : public Shape
{
public:
	virtual double Area()=0;
	virtual double Perimeter()=0;
	virtual int getType()=0;
};
#endif
