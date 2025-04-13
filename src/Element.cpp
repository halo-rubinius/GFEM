#include "GFEM/Element.h"
#include <iostream>
#include <vector>
#include "Eigen/Dense"

Eigen::VectorXd GFEM::Element::computeShapeFunction(
    const std::vector<double> &localCoordinates) const
{
    return shapeFunction->evaluate(localCoordinates);
}

Eigen::MatrixXd GFEM::Element::computeJacobian(
    const std::vector<double> &localCoordinates) const
{
    return shapeFunction->evaluateDerivatives(localCoordinates)
           * coordinatesMatrix;
}

Eigen::MatrixXd GFEM::Element::computeGloablShapeDerivatives(
    const std::vector<double> &localCoordinates) const
{
    Eigen::MatrixXd localShapeDerivatives =
        shapeFunction->evaluateDerivatives(localCoordinates);

    Eigen::MatrixXd Jacobian = localShapeDerivatives * coordinatesMatrix;

    return Jacobian.inverse() * localShapeDerivatives;
}

void GFEM::Element::computeDerivatives(
    const std::vector<double> &localCoordinates, Eigen::MatrixXd &Jacobian,
    Eigen::MatrixXd &globalShapeDerivatives) const
{
    Eigen::MatrixXd localShapeDerivatives =
        shapeFunction->evaluateDerivatives(localCoordinates);

    Jacobian = localShapeDerivatives * coordinatesMatrix;

    globalShapeDerivatives = Jacobian.inverse() * localShapeDerivatives;
}

void GFEM::Element::print() const
{
    std::cout << "Element " << elementId << std::endl;
    std::cout << "Nodes in element:";
    for (const auto node : nodesInElement)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}
