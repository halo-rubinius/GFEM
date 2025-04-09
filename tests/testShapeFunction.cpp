#include <iostream>
#include <vector>

#include "GFEM/Quad4ShapeFunction.h"
#include "GFEM/ShapeFunction.h"
#include "GFEM/Tri3ShapeFunction.h"

int main()
{
    std::vector<double> localCoordinates {0.3, 0.6};

    GFEM::ShapeFunction *shapeFunction;

    shapeFunction = new GFEM::Tri3ShapeFunction();

    shapeFunction->print(localCoordinates);

    delete shapeFunction;

    shapeFunction = new GFEM::Quad4ShapeFunction();

    shapeFunction->print(localCoordinates);

    delete shapeFunction;

    return 0;
}
