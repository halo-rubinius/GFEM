#include <iostream>

#include "GFEM/Node.h"

int main()
{
    // 创建一个 2D 节点 (x=1.0, y=2.0)，每个节点 2 个自由度
    GFEM::Node node(0, {1.0, 2.0}, 2);

    // 创建另一个 2D 节点 (x=3.0, y=4.0)，并指定节点的2个自由度编号
    GFEM::Node node2(1, {3.0, 4.0}, {2, 3});

    // 设置自由度编号
    node.setDegreeOfFreedom({0, 1});

    std::cout << "Node Id: " << node.getNodeId() << std::endl;

    std::cout << "Node coordinates: ";
    for (auto coord : node.getCoordinates())
    {
        std::cout << coord << " ";
    }
    std::cout << std::endl;

    std::cout << "Node DOFs: ";
    for (auto dof : node.getDegreeOfFreedom())
    {
        std::cout << dof << " ";
    }
    std::cout << std::endl;

    // 设置节点上的物理变量
    node.setValue(0, 0.1);
    node.setValue(1, 0.05);

    std::cout << "Node values: ";
    for (int i = 0; i < node.getNumOfDofs(); ++i)
    {
        std::cout << node.getValue(i) << " ";
    }
    std::cout << std::endl;

    // 输出节点信息
    node.print();

    node2.print();

    node2.setDegreeOfFreedom(0, 4);
    node2.setDegreeOfFreedom({34, 56});

    node2.print();

    return 0;
}
