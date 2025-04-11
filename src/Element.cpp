#include "GFEM/Element.h"
#include <iostream>
#include <vector>
#include "Eigen/Dense"
#include "GFEM/Types.h"

Eigen::MatrixXd GFEM::Element::generateCoordinatesMatrix() const
{
    auto numNodes = nodesInElement.size();
    auto nDim = nodesInElement[0]->getDimension();

    Eigen::MatrixXd coordinatesMatrix(numNodes, nDim);
    for (int i = 0; i < numNodes; ++i)
    {
        for (int j = 0; j < nDim; ++j)
        {
            coordinatesMatrix(i, j) = nodesInElement[i]->getCoordinates()[j];
        }
    }
    return coordinatesMatrix;
}

Eigen::VectorXd GFEM::Element::computeShapeFunction(
    const std::vector<double> &localCoordinates) const
{
    return shapeFunction->evaluate(localCoordinates);
}

Eigen::MatrixXd GFEM::Element::computeJacobian(
    const std::vector<double> &localCoordinates) const
{
    return shapeFunction->evaluateDerivatives(localCoordinates)
           * generateCoordinatesMatrix();
}

Eigen::MatrixXd GFEM::Element::computeGloablShapeDerivatives(
    const std::vector<double> &localCoordinates) const
{
    Eigen::MatrixXd localShapeDerivatives =
        shapeFunction->evaluateDerivatives(localCoordinates);

    Eigen::MatrixXd coordinatesMatrix = generateCoordinatesMatrix();

    Eigen::MatrixXd Jacobian = localShapeDerivatives * coordinatesMatrix;

    return Jacobian.inverse() * localShapeDerivatives;
}

void GFEM::Element::computeDerivatives(
    const std::vector<double> &localCoordinates, Eigen::MatrixXd &Jacobian,
    Eigen::MatrixXd &globalShapeDerivatives) const
{
    Eigen::MatrixXd localShapeDerivatives =
        shapeFunction->evaluateDerivatives(localCoordinates);

    Eigen::MatrixXd coordinatesMatrix = generateCoordinatesMatrix();

    Jacobian = localShapeDerivatives * coordinatesMatrix;

    globalShapeDerivatives = Jacobian.inverse() * localShapeDerivatives;
}

std::vector<GFEM::FemIntType> GFEM::Element::getGlobalDofIndices() const
{
    std::vector<GFEM::FemIntType> globalDofs;
    for (const auto &node : nodesInElement)
    {
        globalDofs.insert(globalDofs.end(), node->getDegreeOfFreedom().begin(),
                          node->getDegreeOfFreedom().end());
    }
    return globalDofs;
}

void GFEM::Element::print() const
{
    std::cout << "Element " << elementId << " -> Global DOFs: ";
    for (auto dof : getGlobalDofIndices())
    {
        std::cout << dof << " ";
    }
    std::cout << "Nodes in element:";
    for (const auto node : nodesInElement)
    {
        std::cout << node->getNodeId() << " ";
    }
    std::cout << std::endl;
}
