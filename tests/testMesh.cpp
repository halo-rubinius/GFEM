#include <memory>
#include <vector>
#include "GFEM/BoundaryCondition.h"
#include "GFEM/Element.h"
#include "GFEM/Mesh.h"
#include "GFEM/Node.h"
#include "GFEM/Quad4ShapeFunction.h"
#include "GFEM/ShapeFunction.h"
#include "GFEM/Tri3ShapeFunction.h"

int main()
{
    using namespace GFEM;
    Mesh mesh;

    // 添加节点
    mesh.addNode(Node(3, {0.0, 1.0}, 2));
    mesh.addNode(Node(0, {0.0, 0.0}, 2));
    mesh.addNode(Node(2, {2.0, 1.0}, 2));
    mesh.addNode(Node(1, {2.0, 0.0}, 2));

    auto nodes = mesh.sortNodes();

    // 添加一个三角形单元
    mesh.addElement(Element(0, {&nodes[0], &nodes[1], &nodes[2]},
                            std::make_shared<Tri3ShapeFunction>()));

    // 添加一个四边形单元
    mesh.addElement(Element(1, {&nodes[0], &nodes[1], &nodes[2], &nodes[3]},
                            std::make_shared<Quad4ShapeFunction>()));

    // 添加边界条件
    auto &boundary = mesh.getBoundaryCondition();
    boundary.setDirichletBC(0, 0, 1.0);   // 0号节点第0号自由度约束为 1.0
    boundary.setDirichletBC(0, 1, -1.0);  // 0号节点第1号自由度约束为 -1.0
    boundary.setDirichletBC(1, 0, 5.0);   // 1号节点第0号自由度约束为 5.0

    // 生成全局自由度编号
    mesh.generateGlobalDOFs();

    mesh.print();

    return 0;
}
