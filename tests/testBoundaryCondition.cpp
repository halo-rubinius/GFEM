#include <iostream>
#include "GFEM/BoundaryCondition.h"

int main()
{
    GFEM::BoundaryCondition boundary;

    // 添加 Dirichlet 边界条件
    boundary.setDirichletBC(0, 0, 1.0);   // 0号节点第0号自由度约束为 1.0
    boundary.setDirichletBC(0, 1, -1.0);  // 0号节点第1号自由度约束为 -1.0
    boundary.setDirichletBC(1, 0, 5.0);   // 1号节点第0号自由度约束为 5.0

    // 输出所有边界条件
    boundary.print();

    if (boundary.hasDirichletBC(1, 0))
    {
        std::cout << "Dirichlet BC on DOF 0 of Node 1: "
                  << boundary.getDirichletBC(1, 0) << std::endl;
    }

    if (!boundary.hasDirichletBC(2, 0))
    {
        std::cout << "No Dirichlet BC on DOF 0 of Node 2" << std::endl;
    }

    // 删除 Dirichlet 约束
    boundary.removeDirichletBC(1, 0);

    // 重新输出
    std::cout << "After Removing Boundary Conditions:" << std::endl;
    boundary.print();

    return 0;
}
