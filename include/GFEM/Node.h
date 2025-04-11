#pragma once
#include <vector>

#include "GFEM/Types.h"

namespace GFEM
{

    /**
     * @brief 存储有限元网格中的单个节点
     */
    class Node
    {
    private:
        FemIntType nodeId;  // 唯一标识节点编号，起始编号为0

        /**
         * 存储节点的几何坐标（2D 或3D）
         * 二维(x,y)，三维(x,y,z)
         */
        std::vector<double> coordinates;

        /**
         * 存储该节点对应的全局自由度编号
         * 单元矩阵在组装时，能根据节点的 DOF 编号，正确映射到全局矩阵
         */
        std::vector<FemIntType> degreesOfFreedom;

        // 物理场变量（如位移、电势）
        std::vector<FemValueType> values;

    public:
        Node() = delete;

        /**
         * @brief 构造函数
         * @param id 节点编号，起始编号为0
         * @param coords 节点坐标
         * @param numOfDofs 节点自由度数目
         * @param globalOffset 全局自由度编号起始值，一般为0
         */
        Node(FemIntType id, const std::vector<double> &coords,
             int numOfDofs = 1, FemIntType globalOffset = 0);

        /**
         * @brief 构造函数
         * @param id 节点编号，起始编号为0
         * @param coords 节点坐标
         * @param dofs 节点自由度编号
         */
        Node(FemIntType id, const std::vector<double> &coords,
             const std::vector<FemIntType> &dofs);

        /**
         * @brief 获取节点编号
         * @return 节点编号
         */
        FemIntType getNodeId() const;

        /**
         * @brief 获取节点所在的坐标系维度，二维或三维
         *
         * @return 节点所在的坐标系维度
         */
        int getDimension() const;

        /**
         * @brief 获取节点坐标
         * @return 节点坐标
         */
        const std::vector<double> &getCoordinates() const;

        /**
         * @brief 获取节点自由度编号
         * @return 节点所有自由度的编号
         */
        const std::vector<FemIntType> &getDegreeOfFreedom() const;

        /**
         * @brief 获取节点的自由度数目
         *
         * @return 节点的自由度数目
         */
        int getNumOfDofs() const;

        /**
         * @brief 设置节点自由度编号
         * @param index 自由度索引，如节点有3个自由度，则 index=0,1或2
         * @param dofId 当前索引的自由度编号
         */
        void setDegreeOfFreedom(int index, FemIntType dofId);

        /**
         * @brief 设置节点的所有自由度的编号
         * @param newDofs 新的自由度编号
         */
        void setDegreeOfFreedom(const std::vector<FemIntType> &newDofs);

        /**
         * @brief 获取节点上的物理场变量值
         * @param index 自由度索引，如节点有3个自由度，则 index=0,1或2
         * @return 节点上自由度索引为 index 对应的物理场变量值
         */
        FemValueType getValue(int index) const;

        /**
         * @brief 设置节点上的物理场变量值
         * @param index 自由度索引，如节点由3个自由度，则 index=0,1或2
         * @param value 新的物理场变量值
         */
        void setValue(int index, FemValueType value);

        /**
         * @brief 打印节点信息
         */
        void print() const;
    };

}  // namespace GFEM
