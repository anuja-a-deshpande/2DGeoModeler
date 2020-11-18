#include "CModeler.h"

//default constructor
CModeler::CModeler()
{

}



//destructor
CModeler::~CModeler()
{
}


void CModeler::AddShape(Shape * InputShape)
{

    m_allShapes.push_back(InputShape);

}
void CModeler::RemoveShape(Shape * InputShape)

{
    m_allShapes.pop_back();
}

void CModeler::clearAllshapes()
{
    m_allShapes.clear();
}

std::vector <Shape*> CModeler::getshape()
{
    return this->m_allShapes;

}





