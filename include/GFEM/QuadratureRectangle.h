#pragma once
#include "GFEM/Quadrature.h"

namespace GFEM
{
    class QuadratureRectangle : public Quadrature
    {
    public:
        QuadratureRectangle(int n)
        {
            generateGaussQuadrature(n);
        }

    private:
        void generateGaussQuadrature(int n)
        {
            Quadrature standardQuadrature(n);
            auto standardPoints = standardQuadrature.getAllPoints();
            auto standardWeights = standardQuadrature.getAllWeights();

            weights.clear();
            points.clear();

            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    double w = standardWeights[i] * standardWeights[j];
                    weights.emplace_back(w);

                    double p = standardPoints[i][0];
                    double q = standardPoints[j][0];
                    points.emplace_back(std::vector<double> {p, q});
                }
            }
        }
    };
}  // namespace GFEM
