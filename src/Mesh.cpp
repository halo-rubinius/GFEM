#include "GFEM/Mesh.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "GFEM/BoundaryCondition.h"
#include "GFEM/Element.h"
#include "GFEM/Node.h"
#include "GFEM/Types.h"

void GFEM::Mesh::addNode(const Node &node)
{
    nodes.emplace_back(node);
}

const std::vector<GFEM::Node> &GFEM::Mesh::getNodes() const
{
    return nodes;
}

const std::vector<GFEM::Node> &GFEM::Mesh::sortNodes()
{
    std::sort(nodes.begin(), nodes.end(), [](const Node &a, const Node &b)
              { return a.getNodeId() < b.getNodeId(); });
    return nodes;
}

void GFEM::Mesh::addElement(const Element &element)
{
    elements.emplace_back(element);
}

const std::vector<GFEM::Element> &GFEM::Mesh::getElements() const
{
    return elements;
}

GFEM::BoundaryCondition &GFEM::Mesh::getBoundaryCondition()
{
    return boundaryCondition;
}

void GFEM::Mesh::loadFromFile(const std::string &filename)
{
    // TODO: 实现从文件中加载网格
}

void GFEM::Mesh::generateGlobalDOFs()
{
    sortNodes();

    GFEM::FemIntType dofCounter = 0;
    for (auto &node : nodes)
    {
        for (size_t i = 0; i < node.getDegreeOfFreedom().size(); ++i)
        {
            node.setDegreeOfFreedom(i, dofCounter++);
        }
    }
}

void GFEM::Mesh::print() const
{
    std::cout << "Mesh Information:" << std::endl;
    std::cout << "Total Nodes: " << nodes.size() << std::endl;
    std::cout << "Total Elements: " << elements.size() << std::endl;

    std::cout << "Nodes:" << std::endl;
    for (const auto &node : nodes)
    {
        node.print();
    }

    std::cout << "Elements:" << std::endl;
    for (const auto &element : elements)
    {
        element.print();
    }

    std::cout << "Boundary Conditions:" << std::endl;
    boundaryCondition.print();
}
