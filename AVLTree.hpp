#ifndef _AVL
#define _AVL

#include "TreeNode.hpp"

//Binary search tree that uses AVL balancing properties
class AVLTree{
public:
    AVLTree(); //default constructor
    ~AVLTree(); //destructor, calls TreeNode destructor for root node (which recursivly deletes all child nodes)
    AVLTree* copy();  //copy constructor
    int size(); //counts the number of nodes, should be equal to numNodes

    bool insert(Node* node); //inserts a new node into the tree
    bool remove(int k); //removes a node from the tree
    int treeHeight();  //gets the tree's height from root to lowest leaf
    TreeNode* kthSmallest(int k); //returns the kth smallest node in the tree
    bool isMember(int value); //checks if a node is in the tree or not

    //getters/setters
    TreeNode* getRoot() {return root;}
    void setRoot(TreeNode* node) {root = node;}
    int getNumNodes() {return numNodes;}
    void setNumNodes(int v) {numNodes = v;}

    void print(); //prints contents of the tree based on level order traversal
    void inOrderDump(); //prints the contents of the tree from smallest to largest



private:
    TreeNode* root; //pointer to the top most node of the tree
    int numNodes; //number of nodes in the tree managed by insert/remove

    //helper functions
    AVLTree* copy(TreeNode* node, AVLTree* tree); //helper for copy constructor
    int max(int x,int y); //given two ints, this returns the larger of the two
    int treeHeight(TreeNode* node); //helper for getting height of tree
    int height(TreeNode* node);  //helper that gets how high a node is, can take nullptrs
    int balanceFactor(TreeNode* node);  //gets the balance factor which is right height - left height
    void fixHeight(TreeNode* node);     //helper that rebalances the tree after insert/remove of nodes
    TreeNode* rotateRight(TreeNode* node); //right rotation function, returns the node that was rotated up
    TreeNode* rotateLeft(TreeNode* node); //left rotation function, returns the node that was rotated up
    TreeNode* balance(TreeNode* node);    //takes care of balancing the tree and making sure it keeps AVL structure
    TreeNode* insert(TreeNode* topNode, Node* node); //inserts a new node into the tree
    bool isMember(TreeNode* node, int value); //checks if a node is in the tree or not
    TreeNode* findMin(TreeNode* node); //returns the smallest child of the given node
    TreeNode* removeMin(TreeNode* node); //gets rid of the smallest node since it takes the removed nodes place
    TreeNode* remove(TreeNode* node, int k); //removes a node from the tree
    TreeNode* kthSmallest(int k, TreeNode* node); //helper for kth smallest
    int size(TreeNode* node); //helper for size
    void inOrderDump(TreeNode* node); //helper for dump

};

#endif // AVL
