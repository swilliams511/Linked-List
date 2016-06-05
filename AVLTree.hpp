#ifndef _AVL
#define _AVL

#include "TreeNode.hpp"

class AVLTree{
public:
    AVLTree();
    ~AVLTree();
    AVLTree* copy();

    bool insert(Node* node);
    bool remove(int k);
    int treeHeight();

    TreeNode* getRoot() {return root;}
    void setRoot(TreeNode* node) {root = node;}
    int getNumNodes() {return numNodes;}
    void setNumNodes(int v) {numNodes = v;}

    void print();
    bool isMember(int value);


private:
    TreeNode* root;
    int numNodes;

    //helper functions
    AVLTree* copy(TreeNode* node, AVLTree* tree);
    int max(int x,int y);
    int treeHeight(TreeNode* node);
    int height(TreeNode* node);
    int balanceFactor(TreeNode* node);
    void fixHeight(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* balance(TreeNode* node);
    TreeNode* insert(TreeNode* topNode, Node* node);
    bool isMember(TreeNode* node, int value);
    TreeNode* findMin(TreeNode* node);
    TreeNode* removeMin(TreeNode* node);
    TreeNode* remove(TreeNode* node, int k);


};




#endif // AVL
