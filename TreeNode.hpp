#ifndef treenode
#define treenode

#include "Node.hpp"

//Node object for tree based operations
class TreeNode{
public:
    //this data type takes on the value from the passed node from the list
    //from there, it can then be put into a binary search tree
    //or an AVL tree
    TreeNode(Node* node); //default constructor which takes the passed list node for information
    ~TreeNode();          //destructor, recursivly deletes left/right nodes

    //getters/setters
    TreeNode* getLeft() {return leftSubtree;}
    TreeNode* getRight() {return rightSubtree;}
    Node* getDataNode() {return dataNode;}
    int getNodeHeight() {return nodeHeight;}
    void setLeft(TreeNode* node) {leftSubtree = node;}
    void setRight(TreeNode* node) {rightSubtree = node;}
    void setNodeHeight(int v) {nodeHeight = v;}
    void setDataNode(Node* node) {dataNode = node;}

private:
    Node* dataNode;  //stores the information of the tree node (name, value)
    TreeNode* leftSubtree; //points to left child
    TreeNode* rightSubtree; //points to right child
    int nodeHeight;         //how high up the node is in the tree

};

#endif
