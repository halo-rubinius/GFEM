#pragma once
#include <vector>
#include "Eigen/Dense"

#include "GFEM/ShapeFunction.h"

namespace GFEM
{
    /**
     * @brief 三角形线性单元对应的形函数类
     */
    class Tri3ShapeFunction : public ShapeFunction
    {
    public:
        /**
         * @brief 计算三角形线性单元形函数在局部坐标下的值
         * @param localCoordinates 局部坐标
         * @return 形函数在局部坐标下的值
         */
        Eigen::VectorXd evaluate(
            const std::vector<double> &localCoordinates) const override
        {
            return Eigen::VectorXd {
                {1.0 - localCoordinates[0] - localCoordinates[1],
                 localCoordinates[0], localCoordinates[1]}
            };
        }

        /**
         * @brief 计算三角形线性单元形函数对局部坐标的导数
         * @param localCoordinates 局部坐标
         * @return
         * 形函数对局部坐标的导数，第一行为形函数对xi的导数，第二行为形函数对eta的导数。
         * 三列分别对应于三个形函数的导数
         */
        Eigen::MatrixXd evaluateDerivatives(
            const std::vector<double> &localCoordinates) const override
        {
            return Eigen::MatrixXd {
                {-1.0, 1.0, 0.0},
                {-1.0, 0.0, 1.0}
            };
        }

        /**
         * @brief 获取三角形线性单元形函数相关的节点个数
         * @return 相关的节点个数
         */
        int getNumOfNodes() const override
        {
            return 3;
        }
    };

}  // namespace GFEM
