#include "Node.hpp"

template <class T>
Node<T>::Node()   //this is the primary way to create a temporary node
{
    //std::cout << "Node's constructor called\n";
    prev = nullptr;
    next = nullptr;
    //we don't know what data type T is so leave data uninitialized
}

template <class T>
Node<T>::Node(const T& data) //this is the primary way to create a new node
{
    //std::cout << "Node's para constructor called\n";
    prev = nullptr; //by default the node points to nothing
    next = nullptr; //it is the job of the linked list to set them
    nodeData = data;//set the data to the passed data since we know the data type
}


template <class T>
Node<T>::~Node()
{
    //std::cout << "Node's destructor called\n";
}

//because of how the linked list is constructed, the parameterized constructor will
//be primarily used over this
template <class T>
Node<T>::Node(const Node& otherNode)
{
    std::cout << "Node's copy constructor\n";
    prev = nullptr;  //because a linked list should only own a node, coping
    next = nullptr;  //the pointers wouldn't be ideal
    nodeData = otherNode.nodeData; //set this's data to the other's data
}

template <class T>
Node<T>& Node<T>::operator=(Node otherNode) //must pass by value for copy/swap to work
{
    //only used for dereferenced nodes
    std::cout << "Node's assignment\n";
///note: if operator is passed (Node& otherNode), the below comment applies
    //calling swap instead of the line below will literally swap the nodes
    //ex: *headVar = *tailVar; this call will switch the head and tail nodes
    swap(otherNode);
    return *this;                  //return the dereferenced node
}

///not used right now
template <class T>
void Node<T>::swap(Node& otherNode)
{
    //swapping the pointers will break the linked list, only swap the data
    std::swap(nodeData,otherNode.nodeData);
}

template <class T>
void Node<T>::print()
{
///precondition: T is a class with a print() function
///else dont call this
    nodeData.print();
}

template <class T>
void Node<T>::print_nonClass()
{
///for use if the type is simple like int, string, float, etc...
    std::cout << nodeData << "\n";
}
