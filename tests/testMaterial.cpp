#include <iostream>
#include "GFEM/Material.h"

int main()
{
    using namespace GFEM;

    Material material(0, "Steel");

    material.setProperty("conductivity", 50.0);
    material.setProperty("density", 7850.0);

    material.print();

    return 0;
}
