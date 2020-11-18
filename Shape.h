#ifndef SHAPE_H
#define SHAPE_H

#include<vector>

class Shape
{
public:
	virtual void Draw()=0;
    virtual void GenerateData(Shape* secondShape)=0;
	virtual int getType()=0;
};
#endif


//#ifndef checks whether the given token has been #defined earlier in the file or in an included file;
//if not, it includes the code between it and the closing #else or, if no #else is present, #endif statement.


