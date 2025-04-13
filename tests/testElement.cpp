#include <memory>
#include <vector>

#include "GFEM/Element.h"
#include "GFEM/Node.h"
#include "GFEM/Quad4ShapeFunction.h"
#include "GFEM/Tri3ShapeFunction.h"

int main()
{
    using namespace GFEM;

    std::vector<Node<double>> nodes;

    nodes.emplace_back(Node(0, {0.0, 0.0}));
    nodes.emplace_back(Node(1, {2.0, 0.0}));
    nodes.emplace_back(Node(2, {2.0, 1.0}));
    nodes.emplace_back(Node(3, {0.0, 1.0}));

    std::vector<Element> elements;

    std::shared_ptr<Tri3ShapeFunction> shapeFunction =
        std::make_shared<Tri3ShapeFunction>();
    Element element(0, {0, 1, 2}, shapeFunction);
    elements.emplace_back(element);

    element = Element(1, {0, 1, 2, 3}, std::make_shared<Quad4ShapeFunction>());
    elements.emplace_back(element);

    for (auto &element : elements)
    {
        element.print();

        std::vector<double> localCoordinates {0.3, 0.6};

        element.generateCoordinatesMatrix(nodes);

        std::cout << "Jacobian Matrix: " << std::endl
                  << element.computeJacobian(localCoordinates) << std::endl;

        std::cout << "Golobal Shape Derivatives Matrix: " << std::endl
                  << element.computeGloablShapeDerivatives(localCoordinates)
                  << std::endl;

        Eigen::MatrixXd Jacobian, globalShapeDerivatives;
        element.computeDerivatives(localCoordinates, Jacobian,
                                   globalShapeDerivatives);
        std::cout << Jacobian << std::endl
                  << globalShapeDerivatives << std::endl;

        std::cout << globalShapeDerivatives.transpose() * globalShapeDerivatives
                  << std::endl;
    }

    return 0;
}
