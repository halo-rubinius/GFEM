#pragma once
#include "Eigen/Dense"
#include "Eigen/Sparse"

#include "GFEM/EquationSolver.h"

namespace GFEM
{
    /**
     * @brief 用于线性方程组的迭代求解器
     */
    class IterativeSolver : public EquationSolver
    {
    public:
        /**
         * @brief 构造函数
         * @param tol 收敛误差
         * @param maxIter 最大迭代次数
         */
        IterativeSolver(double tol = 1.0e-6, int maxIter = 1000)
            : tolerance(tol), maxIteration(maxIter)
        {
        }

        /**
         * @brief 运用预条件共轭梯度迭代法求解线性方程组
         * @param A 系数矩阵
         * @param b 右端项
         * @return 解向量
         */
        Eigen::VectorXd solve(const Eigen::SparseMatrix<double> &A,
                              const Eigen::VectorXd &b) override;

    private:
        double tolerance;
        int maxIteration;
    };

}  // namespace GFEM
