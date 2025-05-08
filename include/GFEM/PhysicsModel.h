#pragma once
#include <memory>
#include "Eigen/Dense"
#include "Eigen/Sparse"
#include "GFEM/Element.h"
#include "GFEM/Mesh.h"
#include "GFEM/Quadrature.h"

namespace GFEM
{

    /**
     * @brief 有限元物理模型基类
     * @tparam FemValueType 求解物理量的数据类型，默认double
     */
    template<typename FemValueType = double>
    class PhysicsModel
    {
        using FemIntType = int;

    protected:
        Mesh<FemValueType> mesh;  // 网格

        // 全局刚度矩阵
        Eigen::SparseMatrix<FemValueType> globalStiffness;

        // 全局右端项
        Eigen::VectorX<FemValueType> globalRHS;

        // 解向量
        Eigen::VectorX<FemValueType> solution;

        std::unique_ptr<Quadrature> quadrature;  // 积分器

        /**
         * @brief 计算单元的本构矩阵，一般与单元材料属性相关
         * @return 单元的本构矩阵
         */
        virtual Eigen::MatrixXd computeElementConstitutive(
            const Element &element) = 0;

        /**
         * @brief 计算单元的刚度矩阵。由具体物理模型实现
         * @param element 单元
         * @return 单元的刚度矩阵
         */
        virtual Eigen::MatrixX<FemValueType> computeElementStiffness(
            Element &element) = 0;

        /**
         * @brief 计算单元方程的右端项
         * @param element 单元
         * @return 单元方程的右端项
         */
        virtual Eigen::VectorX<FemValueType> computeElementRHS(
            Element &element) = 0;

    public:
        /**
         * @brief 组装全局刚度矩阵和右端项
         */
        virtual void assembleGlobalSystem() = 0;

        /**
         * @brief 处理边界条件
         */
        virtual void applyBoundaryCondition() = 0;

        /**
         * @brief 有限元求解
         */
        virtual void solve() = 0;

        void assignSolutionToNodes()
        {
            FemIntType dofCounter = 0;
            for (const auto &node : mesh.getNodes())
            {
                for (int index = 0; index < node.getNumOfDofs(); ++index)
                {
                    node.setValue(index, solution[dofCounter++])
                }
            }
        }
    };

}  // namespace GFEM
