/* By: Scott Williams
several functions reference the logic on this page: http://kukuruku.co/hub/cpp/avl-trees
*/

#include "AVLTree.hpp"
#include <queue>

AVLTree::AVLTree()
{
    root = nullptr;
    numNodes = 0;
}

AVLTree::~AVLTree()
{
    //std::cout << "***start of AVLTree destructor***\n";
    delete root; //this will recursivly delete all nodes in the tree
}

//makes a new tree with a copy of each of the nodes in the old tree
//DOESNT guarantee that the structure will be identical like having the same root
//but all the nodes will be in there and the tree will behave about the same
AVLTree* AVLTree::copy()
{
    AVLTree* tree = new AVLTree(); //creates a new instance of a tree since we want a copy
    copy(root,tree); //recursivly copies the nodes starting at the root
    return tree;     //send back the finished tree
}

//helper function for copy
AVLTree* AVLTree::copy(TreeNode* node, AVLTree* tree)
{
    //base case
    if(node == nullptr) //if the node isnt there
        return tree;    //get out
    tree->insert(node->getDataNode()); //insert the node
    //recursive calls
    copy(node->getLeft(),tree); //recursivly insert left and right nodes
    copy(node->getRight(),tree);
    return tree; //send the tree back
}


//getter function for a specific nodes height that works with nullptrs
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
        numNodes++;
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
    {
        numNodes++;
        return new TreeNode(node);
    }

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
      else
        std::cout << "Number of nodes in tree: " << numNodes <<" with height: " << treeHeight() << "\n";
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

        std::cout << "\nLevel " << counter << ": ";
    }
}

int AVLTree::max(int x, int y) //given two ints, this function returns the larger of the two
{
    return x > y ? x : y;
}

//tree height gets the height of the tree, while the other height function above
//gets the height of a specific node in the tree
int AVLTree::treeHeight()
{
    if(root == nullptr) //if there is nothing in the tree then it has no height
        return 0;
    return 1 + max(treeHeight(root->getLeft()) , treeHeight(root->getRight())); //else it has 1 height to account for root plus the largest child height
}

//recursive helper function
int AVLTree::treeHeight(TreeNode* node)
{
    if(node == nullptr)
        return 0;
    return 1 + max(treeHeight(node->getLeft()) , treeHeight(node->getRight()));
}

TreeNode* AVLTree::findMin(TreeNode* node)
{
    if(node->getLeft() == nullptr) //as far left as possible
        return node;
    return findMin(node->getLeft()); //smaller nodes are always left
}

TreeNode* AVLTree::removeMin(TreeNode* node)
{
    if (node->getLeft() == nullptr)
        return node->getRight();
    node->setLeft(removeMin(node->getLeft()));
    return balance(node);
}

bool AVLTree::remove(int k)
{
    if(!isMember(k)) //checks if the node is in the tree, if not
        return false; //we cant remove it
    int rootValue = root->getDataNode()->getValue(); //temp var for holding the roots value just incase it is deleted
    TreeNode* node = remove(root,k); //first recursive call
    if(rootValue == k) //after the recursion, if the root was the node removed
        root = node;   //update the root to be the node that took its place ie the min node
    return true;      //tell us it was removed
}

//recursive helper function, where we know k is in the tree
TreeNode* AVLTree::remove(TreeNode* node, int k)
{
    //base case
    if(k == node->getDataNode()->getValue()) //if we are at k
    {
        TreeNode* left = node->getLeft();    //temp var for left
        TreeNode* right = node->getRight();  //temp var for right
        node->setLeft(nullptr);              //set the node's left to nullptr so destructor doesnt take out extra nodes on accident
        node->setRight(nullptr);             //set the node's right to nullptr same reason
        delete node;             //call the destructor
        numNodes--;                //account for the reduced size
        if(right == nullptr) //because of the balance property, if there isnt a right node
            return left;     //we can simply move the left node to where the delete node is
        TreeNode* min = findMin(right); //otherwise, we look in the right subtree for its smallest node
        min->setRight(removeMin(right)); //we want to move the min to the node that was removed, so we additionally release the node where the min was
        min->setLeft(left);              //have the min take the place of the deleted node
        return balance(min);             //balance it
    }
    //recursive calls - if we arent at k
    if(k < node->getDataNode()->getValue()) //go left if k is smaller than node's value
        node->setLeft(remove(node->getLeft(),k));
    else
        node->setRight(remove(node->getRight(),k)); //go right if k is larger than node's value
    return balance(node); //make sure node remains balance after returning from recursive calls
}

TreeNode* AVLTree::kthSmallest(int k)
{
    if( k > numNodes || k < 1)
    {
        std::cout << "Error, " << k << " is not between 1 and " << numNodes << " inclusive\n";
        exit(2);
    }
    return kthSmallest(k, root);
}

//recursive helper function
TreeNode* AVLTree::kthSmallest(int k, TreeNode* node)
{
    int numNodesLeft = size(node->getLeft());  //gets the amount of nodes in the left subtree
    if(numNodesLeft == k-1) //if the number of nodes in the left subtree is equal to the k value minus 1
        return node;        //then we are at the node we want
    if (numNodesLeft >= k)
        return kthSmallest(k,node->getLeft()); //go left, leave k alone
    return kthSmallest(k - numNodesLeft - 1,node->getRight()); //go right, subtract nodes in left subtree since we arent looking at those and -1 since the node wer'e at isnt it
}

int AVLTree::size()
{
    return size(root);
}

//recursive helper function
int AVLTree::size(TreeNode* node)
{
    if(node == nullptr)
        return 0;
    return 1 + size(node->getLeft()) + size(node->getRight());
}

void AVLTree::inOrderDump()
{
    inOrderDump(root);
    std::cout << "\n\n";
}

//recursive helper function
void AVLTree::inOrderDump(TreeNode* node)
{
    //base case
    if(node == nullptr)
        return;
    //recursive calls
    inOrderDump(node->getLeft());
    std::cout << node->getDataNode()->getName() << " ";
    inOrderDump(node->getRight());
}





