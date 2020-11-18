#ifndef CMODELER_H
#define CMODELER_H

//#include "dataTypes.h"
#include "Shape.h"
#include<vector>

using namespace std;

class CModeler
{
public:

    // default constructor

    CModeler();

    //destructor

    ~CModeler();



    void AddShape(Shape* InputShape);

    void RemoveShape(Shape* InputShape);

    void clearAllshapes();

    vector <Shape*> getshape();
    vector <Shape*> m_allShapes;

private:





};
#endif
