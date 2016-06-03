#ifndef AVL
#define AVL

#include "TreeNode.hpp"

class AVLTree{
public:
    AVLTree();
    ~AVLTree();

    bool insert(Node* node);

    TreeNode* getRoot() {return root;}
    void setRoot(TreeNode* node) {root = node;}
    void print();
    bool isMember(int value);


private:
    TreeNode* root;

    //helper functions
    int height(TreeNode* node);
    int balanceFactor(TreeNode* node);
    void fixHeight(TreeNode* node);
    TreeNode* rotateRight(TreeNode* node);
    TreeNode* rotateLeft(TreeNode* node);
    TreeNode* balance(TreeNode* node);
    TreeNode* insert(TreeNode* topNode, Node* node);
    bool isMember(TreeNode* node, int value);


};




#endif // AVL
