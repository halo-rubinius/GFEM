#include <iostream>

#include "Eigen/Dense"
#include "Eigen/Sparse"

#include "GFEM/IterativeSolver.h"

Eigen::VectorXd GFEM::IterativeSolver::solve(
    const Eigen::SparseMatrix<double> &A, const Eigen::VectorXd &b)
{
    Eigen::ConjugateGradient<Eigen::SparseMatrix<double>,
                             Eigen::UpLoType::Lower | Eigen::UpLoType::Upper>
        cgSolver;

    cgSolver.setTolerance(tolerance);
    cgSolver.setMaxIterations(maxIteration);
    cgSolver.compute(A);

    Eigen::VectorXd x = cgSolver.solve(b);

    if (cgSolver.info() == Eigen::ComputationInfo::Success)
    {
        return x;
    }
    else
    {
        std::cerr << "CG solver failed." << std::endl;
        return Eigen::VectorXd();
    }
}
