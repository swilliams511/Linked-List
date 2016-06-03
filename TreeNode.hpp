#ifndef treenode
#define treenode

#include "Node.hpp"

class TreeNode{
public:
    //this data type takes on the value from the passed node from the list
    //from there, it can then be put into a binary search tree
    //or an AVL tree
    TreeNode(Node* node);
    ~TreeNode();

    TreeNode* getLeft() {return leftSubtree;}
    TreeNode* getRight() {return rightSubtree;}
    Node* getDataNode() {return dataNode;}
    int getNodeHeight() {return nodeHeight;}
    void setLeft(TreeNode* node) {leftSubtree = node;}
    void setRight(TreeNode* node) {rightSubtree = node;}
    void setNodeHeight(int v) {nodeHeight = v;}
    void setDataNode(Node* node) {dataNode = node;}


private:
    Node* dataNode;
    TreeNode* leftSubtree;
    TreeNode* rightSubtree;
    int nodeHeight;



};









#endif
