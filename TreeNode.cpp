#include "TreeNode.hpp"

TreeNode::TreeNode(Node* node)
{
    dataNode = node;
    leftSubtree = nullptr;
    rightSubtree = nullptr;
    nodeHeight = 1;
}
