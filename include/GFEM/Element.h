#pragma once
#include <cassert>
#include <memory>
#include <vector>

#include "Eigen/Dense"

#include "GFEM/Material.h"
#include "GFEM/Node.h"
#include "GFEM/ShapeFunction.h"

namespace GFEM
{
    /**
     * @brief 存储一个有限元单元的信息
     */
    class Element
    {
    private:
        using FemIntType = int;
        Eigen::MatrixXd coordinatesMatrix;  // 单元坐标矩阵

    protected:
        FemIntType elementId;                    // 单元编号
        std::vector<FemIntType> nodesInElement;  // 单元节点ID列表

        // 该单元对应的形函数对象
        std::shared_ptr<ShapeFunction> shapeFunction;

        std::shared_ptr<Material> elementMaterial;  // 单元材料

    public:
        Element() = delete;

        /**
         * @brief 构造函数
         * @param id 单元编号
         * @param nodes 单元节点列表
         * @param shapeFunc 单元形函数对象
         */
        Element(FemIntType id, const std::vector<FemIntType> &nodes,
                std::shared_ptr<ShapeFunction> shapeFunc)
            : elementId(id), nodesInElement(nodes), shapeFunction(shapeFunc)
        {
            assert(shapeFunc->getNumOfNodes() == nodes.size());
        }

        /**
         * @brief 设置单元材料属性
         * @param material 要设置的材料
         */
        void setMaterial(std::shared_ptr<Material> material)
        {
            elementMaterial = material;
        }

        ElementType getElementType() const
        {
            return shapeFunction->getElementType();
        }

        /**
         * @brief 获取单元编号
         * @return 单元编号
         */
        FemIntType getElementId() const
        {
            return elementId;
        }

        /**
         * @brief 获取单元上的节点ID列表
         * @return 单元上的节点ID列表
         */
        const std::vector<FemIntType> &getNodeIndices() const
        {
            return nodesInElement;
        }

        /**
         * @brief 获取单元的节点数量
         * @return 单元的节点数量
         */
        int getNumOfNodes() const
        {
            return nodesInElement.size();
        }

        /**
         * @brief 生成单元的坐标矩阵
         * @param nodesInMesh 包含网格所有节点的列表
         * @return
         * 单元坐标矩阵。每一行对应于一个节点的坐标，每一列对应于一个坐标维度
         */
        template<typename T>
        void generateCoordinatesMatrix(const std::vector<Node<T>> &nodesInMesh)
        {
            auto numNodes = nodesInElement.size();
            auto nDim = nodesInMesh[nodesInElement[0]].getDimension();
            coordinatesMatrix.resize(numNodes, nDim);
            for (int i = 0; i < numNodes; ++i)
            {
                for (int j = 0; j < nDim; ++j)
                {
                    coordinatesMatrix(i, j) =
                        nodesInMesh[nodesInElement[i]].getCoordinates()[j];
                }
            }
        }

        /**
         * @brief 计算单元的形函数值
         * @param localCoordinates 局部坐标
         * @return 形函数值
         */
        Eigen::VectorXd computeShapeFunction(
            const std::vector<double> &localCoordinates) const;

        /**
         * @brief 计算单元的雅可比矩阵。计算之前要先生成单元的坐标矩阵
         * @param localCoordinates 单元局部坐标
         * @return 单元的雅可比矩阵
         */
        Eigen::MatrixXd computeJacobian(
            const std::vector<double> &localCoordinates) const;

        /**
         * @brief
         * 计算单元形函数对全局坐标的导数矩阵。计算之前要先生成单元的坐标矩阵
         * @param localCoordinates 局部坐标
         * @return 单元形函数对全局坐标的导数矩阵
         */
        Eigen::MatrixXd computeGloablShapeDerivatives(
            const std::vector<double> &localCoordinates) const;

        /**
         * @brief
         * 计算单元雅可比矩阵和形函数的全局坐标导数矩阵。计算之前要先生成单元的坐标矩阵
         * @param localCoordinates 局部坐标
         * @param Jacobian 单元的雅可比矩阵
         * @param globalShapeDerivatives 形函数的全局坐标导数矩阵
         */
        void computeDerivatives(const std::vector<double> &localCoordinates,
                                Eigen::MatrixXd &Jacobian,
                                Eigen::MatrixXd &globalShapeDerivatives) const;

        void print() const;
    };

}  // namespace GFEM
