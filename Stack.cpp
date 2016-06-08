#include "Stack.hpp"

Stack::Stack()
{
    nodeStack = new std::vector<GraphNode*>;
}

Stack::~Stack()
{
      //delete all pointers in the vector, then delete the vector

    ///if stack is going to be used for a graph, then only the vector should be destroyed here
    ///the graph class would take care making new GraphNodes and deleting them
    for(unsigned i = 0; i < nodeStack->size(); i++)
        delete nodeStack->at(i);

    delete nodeStack;
}







void Stack::push(GraphNode *node)
{
    nodeStack->push_back(node);
}

void Stack::pop()
{
    if(!nodeStack->empty())
        nodeStack->pop_back();
}

GraphNode* Stack::peek()
{
    if(nodeStack->empty())
    {
        std::cout << "Stack empty, returning nullptr\n";
        return nullptr;
    }
    return nodeStack->back();
}

bool Stack::isEmpty()
{
    return nodeStack->empty();
}

int Stack::size()
{
    return nodeStack->size();
}

void Stack::print()
{
    std::cout << "***Contents of stack of size: " << size() << "***\n";
    if(size() == 0 )
        std::cout << "Stack is empty\n";
    else
    {
        for(int i = size()-1; i >-1;i--)
        {
            std::cout << "Node " << i+1  << " on the stack holds: " << nodeStack->at(i)->getDataNode()->getName() << "\n";
        }
        std::cout << "\n";
    }
}
