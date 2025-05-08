#pragma once
#include <vector>

namespace GFEM
{

    /**
     * @brief 存储有限元网格中的单个节点
     * @tparam FemValueType 节点上物理场变量的类型，默认为double
     */
    template<typename FemValueType = double>
    class Node
    {
    private:
        using FemIntType = int;

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
             int numOfDofs = 1, FemIntType globalOffset = 0)
            : nodeId(id), coordinates(coords)
        {
            for (int i = 0; i < numOfDofs; ++i)
            {
                // XXX: 这种自由度全局编号的方式只对网格中只含一种单元类型时有效
                degreesOfFreedom.emplace_back(globalOffset + nodeId * numOfDofs
                                              + i);
            }
            values.resize(numOfDofs, 0.0);
        }

        /**
         * @brief 构造函数
         * @param id 节点编号，起始编号为0
         * @param coords 节点坐标
         * @param dofs 节点自由度编号
         */
        Node(FemIntType id, const std::vector<double> &coords,
             const std::vector<FemIntType> &dofs)
            : nodeId(id), coordinates(coords), degreesOfFreedom(dofs)
        {
            values.resize(dofs.size(), 0.0);
        }

        /**
         * @brief 获取节点编号
         * @return 节点编号
         */
        FemIntType getNodeId() const
        {
            return nodeId;
        }

        /**
         * @brief 获取节点所在的坐标系维度，二维或三维
         * @return 节点所在的坐标系维度
         */
        int getDimension() const
        {
            return coordinates.size();
        }

        /**
         * @brief 获取节点坐标
         * @return 节点坐标
         */
        const std::vector<double> &getCoordinates() const
        {
            return coordinates;
        }

        /**
         * @brief 获取节点自由度编号
         * @return 节点所有自由度的编号
         */
        const std::vector<FemIntType> &getDegreeOfFreedom() const
        {
            return degreesOfFreedom;
        }

        FemIntType getDegreeOfFreedom(int index) const
        {
            if (index >= 0 && index < degreesOfFreedom.size())
            {
                return degreesOfFreedom[index];
            }
            else
            {
                std::cerr << "Error: Invalid DOF index!" << std::endl;
                return -1;
            }
        }

        /**
         * @brief 获取节点的自由度数目
         *
         * @return 节点的自由度数目
         */
        int getNumOfDofs() const
        {
            return degreesOfFreedom.size();
        }

        /**
         * @brief 设置节点自由度编号
         * @param index 自由度索引，如节点有3个自由度，则 index=0,1或2
         * @param dofId 当前索引的自由度编号
         */
        void setDegreeOfFreedom(int index, FemIntType dofId)
        {
            if (index >= 0 && index < degreesOfFreedom.size())
            {
                degreesOfFreedom[index] = dofId;
            }
            else
            {
                std::cerr << "Error: Invalid DOF index!" << std::endl;
            }
        }

        /**
         * @brief 设置节点的所有自由度的编号
         * @param newDofs 新的自由度编号
         */
        void setDegreeOfFreedom(const std::vector<FemIntType> &newDofs)
        {
            if (newDofs.size() == degreesOfFreedom.size())
            {
                degreesOfFreedom = newDofs;
            }
            else
            {
                std::cerr << "Error: DOF size mismatch!" << std::endl;
            }
        }

        /**
         * @brief 获取节点上的物理场变量值
         * @param index 自由度索引，如节点有3个自由度，则 index=0,1或2
         * @return 节点上自由度索引为 index 对应的物理场变量值
         */
        FemValueType getValue(int index) const
        {
            if (index >= 0 && index < values.size())
            {
                return values[index];
            }
            else
            {
                std::cerr << "Error: Invalid DOF index!" << std::endl;
                return 0.0;
            }
        }

        /**
         * @brief 设置节点上的物理场变量值
         * @param index 自由度索引，如节点由3个自由度，则 index=0,1或2
         * @param value 新的物理场变量值
         */
        void setValue(int index, FemValueType value)
        {
            if (index >= 0 && index < values.size())
            {
                values[index] = value;
            }
            else
            {
                std::cerr << "Error: Invalid DOF index!" << std::endl;
            }
        }

        /**
         * @brief 打印节点信息
         */
        void print() const
        {
            std::cout << "Node " << nodeId << " | Coordinates: (";
            for (size_t i = 0; i < coordinates.size(); ++i)
            {
                std::cout << coordinates[i]
                          << (i < coordinates.size() - 1 ? ", " : "");
            }
            std::cout << ") | DOFs: [";
            for (size_t i = 0; i < degreesOfFreedom.size(); ++i)
            {
                std::cout << degreesOfFreedom[i]
                          << (i < degreesOfFreedom.size() - 1 ? ", " : "");
            }
            std::cout << "] | Values: [";
            for (size_t i = 0; i < values.size(); ++i)
            {
                std::cout << values[i] << (i < values.size() - 1 ? ", " : "");
            }
            std::cout << "]" << std::endl;
        }
    };

}  // namespace GFEM
