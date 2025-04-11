#pragma once
#include <unordered_map>
#include <vector>

#include "Eigen/Dense"
#include "Eigen/Sparse"

#include "GFEM/Node.h"
#include "GFEM/Types.h"

namespace GFEM
{
    /**
     * @brief 边界条件的类
     */
    class BoundaryCondition
    {
        // TODO: 增加 Neumann 边界条件的支持
    private:
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
        void setDirichletBC(FemIntType nodeId, int dofIndex,
                            FemValueType value);

        /**
         * @brief 判断某个节点的某个自由度是否有 Dirichlet 边界条件
         * @param nodeId 节点的编号ID
         * @param dofIndex 节点的自由度索引
         * @return true 有 Dirichlet 边界条件
         * @return false 无 Dirichlet 边界条件
         */
        bool hasDirichletBC(FemIntType nodeId, int dofIndex) const;

        /**
         * @brief 获取某个节点的某个自由度的Dirichlet边界条件值
         * @param nodeId 节点编号
         * @param dofIndex 节点的自由度索引
         * @return Dirichlet 边界条件值。如果该节点的自由度没有 Dirichlet
         * 边界条件，则返回 0.0
         */
        FemValueType getDirichletBC(FemIntType nodeId, int dofIndex) const;

        /**
         * @brief 移除某个节点某个自由度的 Dirichlet 边界条件
         * @param nodeId 节点的编号ID
         * @param dofIndex 节点的自由度索引
         */
        void removeDirichletBC(FemIntType nodeId, int dofIndex);

        /**
         * @brief 应用 Dirichlet 边界条件到全局刚度矩阵和右端项
         * @param globalMatrix 全局刚度矩阵
         * @param globalRHS 全局载荷向量
         * @param nodes 网格的所有节点列表。要求节点列表已经按照节点编号排序好
         */
        void applyDirichletBC(Eigen::SparseMatrix<FemValueType> &globalMatrix,
                              Eigen::VectorX<FemValueType> &globalRHS,
                              const std::vector<Node> &nodes);

        /**
         * @brief 输出边界条件信息
         */
        void print() const;
    };

}  // namespace GFEM
