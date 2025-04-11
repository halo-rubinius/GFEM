#include "GFEM/Node.h"

#include <iostream>
#include <vector>

#include "GFEM/Types.h"

GFEM::Node::Node(FemIntType id, const std::vector<double> &coords,
                 int numOfDofs, FemIntType globalOffset)
    : nodeId(id), coordinates(coords)
{
    for (int i = 0; i < numOfDofs; ++i)
    {
        degreesOfFreedom.emplace_back(globalOffset + nodeId * numOfDofs + i);
    }
    values.resize(numOfDofs, 0.0);
}

GFEM::Node::Node(FemIntType id, const std::vector<double> &coords,
                 const std::vector<FemIntType> &dofs)
    : nodeId(id), coordinates(coords), degreesOfFreedom(dofs)
{
    values.resize(dofs.size(), 0.0);
}

GFEM::FemIntType GFEM::Node::getNodeId() const
{
    return nodeId;
}

int GFEM::Node::getDimension() const
{
    return coordinates.size();
}

const std::vector<double> &GFEM::Node::getCoordinates() const
{
    return coordinates;
}

const std::vector<GFEM::FemIntType> &GFEM::Node::getDegreeOfFreedom() const
{
    return degreesOfFreedom;
}

int GFEM::Node::getNumOfDofs() const
{
    return degreesOfFreedom.size();
}

void GFEM::Node::setDegreeOfFreedom(int index, FemIntType dofId)
{
    if (index >= 0 && index < degreesOfFreedom.size())
    {
        degreesOfFreedom[index] = dofId;
    }
    else
    {
        std::cerr << "Error: Invalid DOF index!" << std::endl;
    }
}

void GFEM::Node::setDegreeOfFreedom(const std::vector<FemIntType> &newDofs)
{
    if (newDofs.size() == degreesOfFreedom.size())
    {
        degreesOfFreedom = newDofs;
    }
    else
    {
        std::cerr << "Error: DOF size mismatch!" << std::endl;
    }
}

GFEM::FemValueType GFEM::Node::getValue(int index) const
{
    if (index >= 0 && index < values.size())
    {
        return values[index];
    }
    else
    {
        std::cerr << "Error: Invalid DOF index!" << std::endl;
        return 0.0;
    }
}

void GFEM::Node::setValue(int index, FemValueType value)
{
    if (index >= 0 && index < values.size())
    {
        values[index] = value;
    }
    else
    {
        std::cerr << "Error: Invalid DOF index!" << std::endl;
    }
}

void GFEM::Node::print() const
{
    std::cout << "Node " << nodeId << " | Coordinates: (";
    for (size_t i = 0; i < coordinates.size(); ++i)
    {
        std::cout << coordinates[i] << (i < coordinates.size() - 1 ? ", " : "");
    }
    std::cout << ") | DOFs: [";
    for (size_t i = 0; i < degreesOfFreedom.size(); ++i)
    {
        std::cout << degreesOfFreedom[i]
                  << (i < degreesOfFreedom.size() - 1 ? ", " : "");
    }
    std::cout << "] | Values: [";
    for (size_t i = 0; i < values.size(); ++i)
    {
        std::cout << values[i] << (i < values.size() - 1 ? ", " : "");
    }
    std::cout << "]" << std::endl;
}
