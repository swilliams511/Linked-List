#include "AVLTree.hpp"
#include <queue>

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    std::cout << "***start of AVLTree destructor***\n";
    delete root;
}



int AVLTree::height(TreeNode* node)
{
    if(node == nullptr) //if the node (usually a left or right node) is a nullptr
        return 0;       //say it doesn't have any size
    return node->getNodeHeight(); //else return the node's stored height
    //alternate code
    //return node ? node->getNodeHeight() : 0;
}

int AVLTree::balanceFactor(TreeNode* node)
{
    //in most definitions of AVL tree's that I've read, the balance factor
    //is typically h(left)-h(right)
    //however, as long as the logic is consistant throughout the program,
    //h(right)-h(left) would work as well since it would just be the opposite
    //signs of the typical definition.

    //TODO : once code is running, try to change the definition to the
    //one I'm use too
    if(node == nullptr)
        return 0;
    return height(node->getRight()) - height(node->getLeft());
}

void AVLTree::fixHeight(TreeNode* node)
{
    int left = height(node->getLeft());   //gets the height of the left node
    int right = height(node->getRight()); //gets the height of the right node
    if(left > right)                   //this code looks at the 2 nodes and sets
        node->setNodeHeight(left+1);   //the new height to the larger of the 2 sides
    else                               //plus 1. if they are equal it doesnt matter which one
        node->setNodeHeight(right+1);  //is used, so the right is just for this. its possible both
                                        //left and right are nullptrs, so they have a height of zero
//alternate code
    //int height = (left>right ? left : right) + 1;
    //node->setNodeHeight(height);
}

//right rotation around node
TreeNode* AVLTree::rotateRight(TreeNode* node)
{
    TreeNode* rotNode = node->getLeft();
    node->setLeft(rotNode->getRight());
    rotNode->setRight(node);
    if(root == node)
        root = rotNode;
    fixHeight(node);
    fixHeight(rotNode); //the node that was the left node is now the root node
    return rotNode;   //of the tree, and it's right node is the node that was passed
}

TreeNode* AVLTree::rotateLeft(TreeNode* node)
{
    TreeNode* rotNode = node->getRight(); //we get the right node of the passed node
    node->setRight(rotNode->getLeft()); //we update the right node of the passed node to become the old right nodes left node
    rotNode->setLeft(node);             //we say that the old right node is now tha left parent of the passed node
    if(root == node)   //if the node happened to be the root node
        root = rotNode; //update the root since the node is now a child of the rot node
    fixHeight(node);                    //updates height since the nodes moved
    fixHeight(rotNode);                 //rot nodes height should be above the passed node now
    return rotNode;   //ir ia up to the calling function to now set the new root which we return
}

/*refer to "AVL visual of balance - where p is passed node.jpg"
in the files in Linked List for a visual of this function at work */
TreeNode* AVLTree::balance(TreeNode* node)  //O(1)
{
    fixHeight(node);   //adjusts the nodes height to account for any inserting or deletion
    if(balanceFactor(node) == 2) //the right outweighs the left and is unbalanced
    {   //***remember h(right) - h(left) is being used for this balance factor***
        if(balanceFactor(node->getRight()) < 0) //if the left node has a negative balance factor
            node->setRight(rotateRight(node->getRight())); //do a right rotation and set the rotated node as the new right node
        return rotateLeft(node); //take the passed node and do a left rotation to account for the balance factor of 2
    }
    if(balanceFactor(node) == -2) //the left outweighs the right and is unbalanced
    {
        if(balanceFactor(node->getLeft()) > 0) //if the right subtree has a positive balance factor
            node->setLeft(rotateLeft(node->getLeft())); //do a left rotation and set the rotated node as the new left node
        return rotateRight(node); //take the passed node and do a right rotation to account for the balance factor of -2
    }
    return node;   //no balancing is needed
}

bool AVLTree::insert(Node* node)
{
    if(isMember(node->getValue())) //if the node is already in the tree
        return false;              //say it wasnt inserted
    if(root == nullptr) //if the tree is empty
    {
        TreeNode* newNode = new TreeNode(node); //make a new treenode
        root = newNode;    //say that it is the root of the tree
        return true;    //say the node was inserted
    }
    if(node->getValue() < root->getDataNode()->getValue()) //if the passed nodes value is less than the roots value
        root->setLeft(insert(root->getLeft(),node)); //recursive call left, root's left is set since rotations may occur while balancing
    else
        root->setRight(insert(root->getRight(),node));//recursive call right
    balance(root); //should the root be updated during balance, the rotate left/right functions will take care of that
    return true; //say the node was inserted
}
//recursive helper function for insert
TreeNode* AVLTree::insert(TreeNode* topNode, Node* node)
{
    //base case
    if(topNode == nullptr)
        return new TreeNode(node);
    //recursive calls
    if(node->getValue() < topNode->getDataNode()->getValue())
        topNode->setLeft(insert(topNode->getLeft(),node));
    else
        topNode->setRight(insert(topNode->getRight(),node));
    // returning from recursive calls
    return balance(topNode);
}

bool AVLTree::isMember(int value)
{
    if(root == nullptr) //if the tree is empty
        return false; //then the value cant be in there
    if(root->getDataNode()->getValue() == value) //if the roots value is equal to the passed value
        return true;                             //the node is in the tree
    if(value < root->getDataNode()->getValue())  //if its smaller than the root value
        return isMember(root->getLeft(),value);  //go left
    return isMember(root->getRight(),value);     //else go right
}

//recursive helper function for isMember. Same behavior has public function, where node is the root of a subtree
bool AVLTree::isMember(TreeNode* node, int value)
{
    //base cases
    if(node == nullptr)
        return false;
    if(node->getDataNode()->getValue() == value)
        return true;
    //recursive calls
    if(value < node->getDataNode()->getValue())
        return isMember(node->getLeft(),value);
    return isMember(node->getRight(),value);
}



void AVLTree::print()
{
    std::cout << "***Level order traversal of AVLTree***\n";

      if (root == nullptr) //if the tree is empty
      {
          std::cout << "The AVLTree is empty\n";
          return;         //stop printing
      }
    //making sure rotate function do their job updating the root when needed
    std::cout << "Root is (" << root->getDataNode()->getValue() << "," << root->getDataNode()->getName() << ")\n";

    std::queue<TreeNode*> curr;  //queue for holding the nodes at the current level
    std::queue<TreeNode*> next;  //queue for holding the nodes at the next level
    curr.push(root);             //add the root to the queue
    int counter = 1;             //say we are at level 1

    std::cout << "Level " << counter << ": ";

    while(true)
    {
        while(curr.empty() == false) //if this is empty, then the current level of the tree is finished
        {
            TreeNode *node = curr.front();

            std::cout << "(" << node->getDataNode()->getValue() << "," << node->getDataNode()->getName() << ") ";

            curr.pop(); //remove the node that was just printed
            if(node->getLeft() != nullptr)
               next.push(node->getLeft()); //store the non null left node in the queue
            if(node->getRight() != nullptr)
                next.push(node->getRight()); //store the non null right node in the queue
        }
    if (curr.empty() == true && next.empty() == true)
    {
        std::cout << "\n\n"; //when both queues are empty all the nodes have been printed
        return;
    }
                                   //exit the function
    std::queue<TreeNode*> temp = curr;    //temp queue for swapping the other two queues
    curr = next;
    next = temp;
    counter++;  //move to the next level of the tree

    std::cout << "\nLevel " << counter << ":";
    }
}

