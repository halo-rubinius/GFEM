#include "GFEM/BoundaryCondition.h"

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Eigen/Dense"
#include "Eigen/Sparse"

#include "GFEM/Types.h"

namespace GFEM
{

    void BoundaryCondition::setDirichletBC(FemIntType nodeId, int dofIndex,
                                           FemValueType value)
    {
        dirichletBCs[nodeId][dofIndex] = value;
    }

    bool BoundaryCondition::hasDirichletBC(FemIntType nodeId,
                                           int dofIndex) const
    {
        return dirichletBCs.contains(nodeId)
               && dirichletBCs.at(nodeId).contains(dofIndex);
    }

    FemValueType BoundaryCondition::getDirichletBC(FemIntType nodeId,
                                                   int dofIndex) const
    {
        return hasDirichletBC(nodeId, dofIndex)
                   ? dirichletBCs.at(nodeId).at(dofIndex)
                   : 0.0;
    }

    void BoundaryCondition::removeDirichletBC(FemIntType nodeId, int dofIndex)
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

    void BoundaryCondition::applyDirichletBC(
        Eigen::SparseMatrix<FemValueType> &globalMatrix,
        Eigen::VectorX<FemValueType> &globalRHS, const std::vector<Node> &nodes)
    {
        for (const auto &[nodeId, dofs] : dirichletBCs)
        {
            for (const auto &[dofIndex, value] : dofs)
            {
                int globalDof = nodes[nodeId].getDegreeOfFreedom()[dofIndex];

                // 将全局矩阵相应自由度上的对角线元素设为1
                globalMatrix.coeffRef(globalDof, globalDof) = 1.0;

                // 将全局RHS相应自由度上的元素设为Dirichlet边界条件值
                globalRHS[globalDof] = value;
            }
        }
    }

    void BoundaryCondition::print() const
    {
        std::cout << "Dirichlet BCs:" << std::endl;
        for (const auto &[nodeId, dofs] : dirichletBCs)
        {
            for (const auto &[dofIndex, value] : dofs)
            {
                std::cout << "Node " << nodeId << ", DOF " << dofIndex << " -> "
                          << value << std::endl;
            }
        }
    }

}  // namespace GFEM
