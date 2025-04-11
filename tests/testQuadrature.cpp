#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>
#include "GFEM/QuadratureTriangle.h"
#include "GFEM/quadrature.h"

double func(const std::vector<double> &x)
{
    return pow(x[0], 4);
}

int main()
{
    using namespace GFEM;

    Quadrature quadrature(3);

    quadrature.print();

    auto points = quadrature.getAllPoints();

    auto weights = quadrature.getAllWeights();

    auto x = quadrature.getPoint(0)[0];

    auto w = quadrature.getWeight(0);

    std::cout << "Integral result: " << quadrature.integrate(func) << std::endl;

    QuadratureTriangle integrator(4);
    integrator.print();

    std::cout << "Integral result: " << std::setprecision(15)
              << integrator.integrate([](const std::vector<double> &x)
                                      { return x[0] * x[0] + exp(x[1]); });
    std::cout << std::endl;

    return 0;
}
