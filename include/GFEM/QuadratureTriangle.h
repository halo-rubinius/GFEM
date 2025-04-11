#pragma once
#include "GFEM/Quadrature.h"

namespace GFEM
{
    class QuadratureTriangle : public Quadrature
    {
    public:
        QuadratureTriangle(int n)
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
                    double w = (1.0 + standardPoints[i][0]) / 8.0
                               * standardWeights[i] * standardWeights[j];
                    weights.emplace_back(w);

                    double p = (1.0 + standardPoints[i][0])
                               * (1.0 + standardPoints[j][0]) / 4.0;
                    double q = (1.0 + standardPoints[i][0])
                               * (1.0 - standardPoints[j][0]) / 4.0;
                    points.emplace_back(std::vector<double> {p, q});
                }
            }
        }
    };
}  // namespace GFEM
