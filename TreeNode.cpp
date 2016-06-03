#include "TreeNode.hpp"

TreeNode::TreeNode(Node* node)
{
    dataNode = node;
    leftSubtree = nullptr;
    rightSubtree = nullptr;
    nodeHeight = 1;
}

TreeNode::~TreeNode()
{
    //if removing a single node, make sure to set left/right to nullptrs prior to
    //deletion so other nodes arent removed
    std::cout << "in node: " << dataNode->getValue() << "\n";
    delete leftSubtree;
    delete rightSubtree;
}
