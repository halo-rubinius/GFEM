#pragma once
#include <iostream>
#include <vector>

#include "Eigen/Dense"

namespace GFEM
{
    enum class ElementType
    {
        None = -1,
        LinearTriangle,
        LinearQuadrilateral
    };

    /**
     * @brief 定义单元的形函数基类
     */
    class ShapeFunction
    {
    public:
        /**
         * @brief 计算形函数在局部坐标下的值
         * @param localCoordinates 局部坐标
         * @return 形函数在局部坐标下的值
         */
        virtual Eigen::VectorXd evaluate(
            const std::vector<double> &localCoordinates) const = 0;

        /**
         * @brief 计算形函数对局部坐标的导数
         * @param localCoordinates 局部坐标
         * @return 形函数对局部坐标的导数。
         * m x n矩阵，m为坐标系维度，n为单元形函数个数
         */
        virtual Eigen::MatrixXd evaluateDerivatives(
            const std::vector<double> &localCoordinates) const = 0;

        /**
         * @brief 获取形函数相关的节点个数
         * @return 相关的节点个数
         */
        virtual int getNumOfNodes() const = 0;

        virtual ElementType getElementType() const
        {
            return ElementType::None;
        }

        void print(const std::vector<double> &localCoordinates) const
        {
            std::cout << "Number of nodes for shape function: "
                      << getNumOfNodes() << std::endl;
            std::cout << "Values of shape function: "
                      << evaluate(localCoordinates).transpose() << std::endl;
            std::cout << "Derivatives of shape function: " << std::endl
                      << evaluateDerivatives(localCoordinates) << std::endl;
        }
    };

}  // namespace GFEM
