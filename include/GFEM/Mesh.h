#pragma once
#include <string>
#include <vector>

#include "GFEM/BoundaryCondition.h"
#include "GFEM/Element.h"
#include "GFEM/Node.h"
#include "GFEM/Types.h"

namespace GFEM
{
    /**
     * @brief 网格管理类
     */
    class Mesh
    {
    private:
        std::vector<Node> nodes;              // 节点列表
        std::vector<Element> elements;        // 单元列表
        BoundaryCondition boundaryCondition;  // 边界条件

    public:
        Mesh() = default;

        /**
         * @brief 向网格中添加节点
         * @param node 待添加的节点
         */
        void addNode(const Node &node);

        /**
         * @brief 获取网格所有节点的列表
         * @return 网格节点列表
         */
        const std::vector<Node> &getNodes() const;

        /**
         * @brief 对节点列表进行排序(按照节点ID从小到大排序)
         * @return 排序后的节点列表引用
         */
        const std::vector<Node> &sortNodes();

        /**
         * @brief 向网格中添加一个单元
         * @param element 待添加的单元
         */
        void addElement(const Element &element);

        /**
         * @brief 获取网格所有单元的列表
         * @return 单元列表的引用
         */
        const std::vector<Element> &getElements() const;

        /**
         * @brief 获取边界条件的对象
         * @return 边界条件对象
         */
        BoundaryCondition &getBoundaryCondition();

        /**
         * @brief 从文件中加载网格信息
         * @param filename 网格文件名
         */
        void loadFromFile(const std::string &filename);

        /**
         * @brief 生成全局自由度编号
         */
        void generateGlobalDOFs();

        /**
         * @brief 输出网格信息
         */
        void print() const;
    };

}  // namespace GFEM
