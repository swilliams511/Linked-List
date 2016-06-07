#include "Node.hpp"

Node::Node()
{
    prev = nullptr;
    next = nullptr;
    value = 0;
    name = "";
    children = new std::vector<Node*>;
}

Node::Node(int x, std::string y)
{
    prev = nullptr;
    next = nullptr;
    value = x;
    name = y;
    children = new std::vector<Node*>;
}

Node* Node::copyNode()
{
    return new Node(value,name);
}

void Node::print()
{
    std::cout << "Current node information\n";
    std::cout << "Node name: " << name << "\n";
    std::cout << "Node value: " << value << "\n";
  //  if(prev == nullptr)
   //     std::cout << "Address for prev is: a nullptr\n";
   // else
   //     std::cout << "Address for prev is: " << prev << "\n";
   // if(next == nullptr)
   //     std::cout << "Address for next is: a nullptr\n";
   // else
    //    std::cout << "Address for next is: " << next << "\n";
}

void Node::addChild(Node *node)
{
    children->push_back(node);
}



