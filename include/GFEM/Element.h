#pragma once
#include <cassert>
#include <memory>
#include <vector>

#include "Eigen/Dense"

#include "GFEM/Node.h"
#include "GFEM/ShapeFunction.h"
#include "GFEM/Types.h"

namespace GFEM
{
    /**
     * @brief 存储一个有限元单元的信息
     */
    class Element
    {
    protected:
        FemIntType elementId;                // 单元编号
        std::vector<Node *> nodesInElement;  // 单元节点列表

        // 该单元对应的形函数对象
        std::shared_ptr<ShapeFunction> shapeFunction;

    public:
        Element() = delete;

        /**
         * @brief 构造函数
         * @param id 单元编号
         * @param nodes 单元节点列表
         * @param shapeFunc 单元形函数对象
         */
        Element(FemIntType id, const std::vector<Node *> &nodes,
                std::shared_ptr<ShapeFunction> shapeFunc)
            : elementId(id), nodesInElement(nodes), shapeFunction(shapeFunc)
        {
            assert(shapeFunc->getNumOfNodes() == nodes.size());
        }

        /**
         * @brief 生成单元的坐标矩阵
         * @return
         * 单元坐标矩阵。每一行对应于一个节点的坐标，每一列对应于一个坐标维度
         */
        Eigen::MatrixXd generateCoordinatesMatrix() const;

        /**
         * @brief 计算单元的雅可比矩阵
         * @param localCoordinates 单元局部坐标
         * @return 单元的雅可比矩阵
         */
        Eigen::MatrixXd computeJacobian(
            const std::vector<double> &localCoordinates) const;

        /**
         * @brief 计算单元形函数对全局坐标的导数矩阵
         * @param localCoordinates 局部坐标
         * @return 单元形函数对全局坐标的导数矩阵
         */
        Eigen::MatrixXd computeGloablShapeDerivatives(
            const std::vector<double> &localCoordinates) const;

        /**
         * @brief 计算单元雅可比矩阵和形函数的全局坐标导数矩阵
         * @param localCoordinates 局部坐标
         * @param Jacobian 单元的雅可比矩阵
         * @param globalShapeDerivatives 形函数的全局坐标导数矩阵
         */
        void computeDerivatives(const std::vector<double> &localCoordinates,
                                Eigen::MatrixXd &Jacobian,
                                Eigen::MatrixXd &globalShapeDerivatives) const;

        /**
         * @brief 计算单元刚度矩阵
         * @return 单元刚度矩阵
         */
        virtual Eigen::MatrixXd computeElementStiffness()
        {
            // TODO: 实现单元刚度矩阵的计算
            return Eigen::MatrixXd();
        }

        std::vector<FemIntType> getGlobalDofIndices() const;

        void print() const;
    };

}  // namespace GFEM
