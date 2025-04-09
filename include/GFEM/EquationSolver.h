#pragma once
#include "Eigen/Dense"
#include "Eigen/Sparse"

namespace GFEM
{
    /**
     * @brief 线性方程组的求解器基类
     */
    class EquationSolver
    {
    public:
        /**
         * @brief 求解线性方程组Ax=b
         * @param A 系数矩阵
         * @param b 右端项
         * @return 解向量
         */
        virtual Eigen::VectorXd solve(const Eigen::SparseMatrix<double> &A,
                                      const Eigen::VectorXd &b) = 0;
    };

}  // namespace GFEM
