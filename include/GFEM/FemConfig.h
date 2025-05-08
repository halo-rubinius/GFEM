#pragma once

namespace GFEM
{
    class FemConfig
    {
    public:
        int quadratureOrder;  // 数值积分的阶数，默认为3个积分点

        FemConfig() : quadratureOrder(3) {}

        FemConfig(int quadOrder) : quadratureOrder(quadOrder) {}

    } ConfigSet;
}  // namespace GFEM
