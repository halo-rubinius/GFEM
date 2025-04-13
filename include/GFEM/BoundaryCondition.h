#pragma once
#include <unordered_map>
#include <vector>

#include "Eigen/Dense"
#include "Eigen/Sparse"

#include "GFEM/Node.h"

namespace GFEM
{
    /**
     * @brief 边界条件的类
     * @tparam FemValueType 边界值类型，默认为 double
     */
    template<typename FemValueType = double>
    class BoundaryCondition
    {
        // TODO: 增加 Neumann 边界条件的支持
    private:
        using FemIntType = int;

        // Dirichlet 边界条件：{节点ID, {自由度编号 -> 约束值}}
        std::unordered_map<FemIntType, std::unordered_map<int, FemValueType>>
            dirichletBCs;

    public:
        /**
         * @brief 添加 Dirichlet 边界条件
         * @param nodeId 要添加 Dirichlet 边界条件的节点ID编号
         * @param dofIndex 要添加 Dirichlet 边界条件的节点的局部自由度索引
         * @param value 施加的Dirichlet 边界条件的值
         */
        void setDirichletBC(FemIntType nodeId, int dofIndex, FemValueType value)
        {
            dirichletBCs[nodeId][dofIndex] = value;
        }

        /**
         * @brief 判断某个节点的某个自由度是否有 Dirichlet 边界条件
         * @param nodeId 节点的编号ID
         * @param dofIndex 节点的自由度索引
         * @return true 有 Dirichlet 边界条件
         * @return false 无 Dirichlet 边界条件
         */
        bool hasDirichletBC(FemIntType nodeId, int dofIndex) const
        {
            return dirichletBCs.contains(nodeId)
                   && dirichletBCs.at(nodeId).contains(dofIndex);
        }

        /**
         * @brief 获取某个节点的某个自由度的Dirichlet边界条件值
         * @param nodeId 节点编号
         * @param dofIndex 节点的自由度索引
         * @return Dirichlet 边界条件值。如果该节点的自由度没有 Dirichlet
         * 边界条件，则返回 0.0
         */
        FemValueType getDirichletBC(FemIntType nodeId, int dofIndex) const
        {
            return hasDirichletBC(nodeId, dofIndex)
                       ? dirichletBCs.at(nodeId).at(dofIndex)
                       : 0.0;
        }

        /**
         * @brief 移除某个节点某个自由度的 Dirichlet 边界条件
         * @param nodeId 节点的编号ID
         * @param dofIndex 节点的自由度索引
         */
        void removeDirichletBC(FemIntType nodeId, int dofIndex)
        {
            if (hasDirichletBC(nodeId, dofIndex))
            {
                dirichletBCs.at(nodeId).erase(dofIndex);
                if (dirichletBCs.at(nodeId).empty())
                {
                    dirichletBCs.erase(nodeId);
                }
            }
        }

        /**
         * @brief 应用 Dirichlet 边界条件到全局刚度矩阵和右端项
         * @param globalMatrix 全局刚度矩阵
         * @param globalRHS 全局载荷向量
         * @param nodes 网格的所有节点列表。要求节点列表已经按照节点编号排序好
         */
        void applyDirichletBC(Eigen::SparseMatrix<FemValueType> &globalMatrix,
                              Eigen::VectorX<FemValueType> &globalRHS,
                              const std::vector<Node<FemValueType>> &nodes)
        {
            for (const auto &[nodeId, dofs] : dirichletBCs)
            {
                for (const auto &[dofIndex, value] : dofs)
                {
                    int globalDof =
                        nodes[nodeId].getDegreeOfFreedom()[dofIndex];

                    // 将全局矩阵相应自由度上的对角线元素设为1
                    globalMatrix.coeffRef(globalDof, globalDof) = 1.0;

                    // 将全局RHS相应自由度上的元素设为Dirichlet边界条件值
                    globalRHS[globalDof] = value;
                }
            }
        }

        /**
         * @brief 输出边界条件信息
         */
        void print() const
        {
            std::cout << "Dirichlet BCs:" << std::endl;
            for (const auto &[nodeId, dofs] : dirichletBCs)
            {
                for (const auto &[dofIndex, value] : dofs)
                {
                    std::cout << "Node " << nodeId << ", DOF " << dofIndex
                              << " -> " << value << std::endl;
                }
            }
        }
    };

}  // namespace GFEM
