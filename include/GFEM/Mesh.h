#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "GFEM/BoundaryCondition.h"
#include "GFEM/Element.h"
#include "GFEM/Node.h"

namespace GFEM
{
    /**
     * @brief 网格管理类
     * @tparam FemValueType 节点物理量的类型，默认为double
     */
    template<typename FemValueType = double>
    class Mesh
    {
    private:
        using FemIntType = int;
        using NodeType = Node<FemValueType>;

        std::vector<NodeType> nodes;                        // 节点列表
        std::vector<Element> elements;                      // 单元列表
        BoundaryCondition<FemValueType> boundaryCondition;  // 边界条件

    public:
        Mesh() = default;

        /**
         * @brief 向网格中添加节点
         * @param node 待添加的节点
         */
        void addNode(const NodeType &node)
        {
            nodes.emplace_back(node);
        }

        /**
         * @brief 获取网格所有节点的列表
         * @return 网格节点列表
         */
        const std::vector<NodeType> &getNodes() const
        {
            return nodes;
        }

        /**
         * @brief 对节点列表进行排序(按照节点ID从小到大排序)
         * @return 排序后的节点列表引用
         */
        const std::vector<NodeType> &sortNodes()
        {
            std::sort(nodes.begin(), nodes.end(),
                      [](const NodeType &a, const NodeType &b)
                      { return a.getNodeId() < b.getNodeId(); });
            return nodes;
        }

        /**
         * @brief 向网格中添加一个单元
         * @param element 待添加的单元
         */
        void addElement(const Element &element)
        {
            elements.emplace_back(element);
        }

        /**
         * @brief 获取网格所有单元的列表
         * @return 单元列表的引用
         */
        std::vector<Element> &getElements()
        {
            return elements;
        }

        /**
         * @brief 获取边界条件的对象
         * @return 边界条件对象
         */
        BoundaryCondition<FemValueType> &getBoundaryCondition()
        {
            return boundaryCondition;
        }

        /**
         * @brief 从文件中加载网格信息
         * @param filename 网格文件名
         */
        void loadFromFile(const std::string &filename)
        {
            // TODO: 实现从文件中加载网格
        }

        /**
         * @brief 生成全局自由度编号
         * @return 网格中所有自由度的总和数量
         */
        FemIntType generateGlobalDOFs()
        {
            sortNodes();

            FemIntType dofCounter = 0;
            for (auto &node : nodes)
            {
                for (size_t i = 0; i < node.getDegreeOfFreedom().size(); ++i)
                {
                    node.setDegreeOfFreedom(i, dofCounter++);
                }
            }

            return dofCounter;
        }

        /**
         * @brief 输出网格信息
         */
        void print() const
        {
            std::cout << "Mesh Information:" << std::endl;
            std::cout << "Total Nodes: " << nodes.size() << std::endl;
            std::cout << "Total Elements: " << elements.size() << std::endl;

            std::cout << "Nodes:" << std::endl;
            for (const auto &node : nodes)
            {
                node.print();
            }

            std::cout << "Elements:" << std::endl;
            for (const auto &element : elements)
            {
                element.print();
            }

            std::cout << "Boundary Conditions:" << std::endl;
            boundaryCondition.print();
        }
    };

}  // namespace GFEM
