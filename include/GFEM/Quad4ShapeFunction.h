#pragma once
#include <vector>
#include "Eigen/Dense"

#include "GFEM/ShapeFunction.h"

namespace GFEM
{
    /**
     * @brief 四边形线性单元对应的形函数类
     */
    class Quad4ShapeFunction : public ShapeFunction
    {
        /**
         * @brief 计算四边形线性单元形函数在局部坐标下的值
         * @param localCoordinates 局部坐标
         * @return 形函数在局部坐标下的值
         */
        Eigen::VectorXd evaluate(
            const std::vector<double> &localCoordinates) const override
        {
            double xi = localCoordinates[0];
            double eta = localCoordinates[1];

            return Eigen::VectorXd {
                {0.25 * (1.0 - xi) * (1.0 - eta),
                 0.25 * (1.0 + xi) * (1.0 - eta),
                 0.25 * (1.0 + xi) * (1.0 + eta),
                 0.25 * (1.0 - xi) * (1.0 + eta)}
            };
        }

        /**
         * @brief 计算四边形线性单元形函数对局部坐标的导数
         * @param localCoordinates 局部坐标
         * @return
         * 形函数对局部坐标的导数，第一行为形函数对xi的导数，第二行为形函数对eta的导数。
         * 四列分别对应于四个形函数的导数
         */
        Eigen::MatrixXd evaluateDerivatives(
            const std::vector<double> &localCoordinates) const override
        {
            double xi = localCoordinates[0];
            double eta = localCoordinates[1];

            return Eigen::MatrixXd {
                {-0.25 * (1.0 - eta), 0.25 * (1.0 - eta), 0.25 * (1.0 + eta),
                 -0.25 * (1.0 + eta)},
                { -0.25 * (1.0 - xi), -0.25 * (1.0 + xi),  0.25 * (1.0 + xi),
                 0.25 * (1.0 - xi)  }
            };
        }

        /**
         * @brief 获取四边形线性单元形函数相关的节点个数
         * @return 相关的节点个数
         */
        int getNumOfNodes() const override
        {
            return 4;
        }

        ElementType getElementType() const override
        {
            return ElementType::LinearQuadrilateral;
        }
    };
}  // namespace GFEM
