#include "Node.hpp"
#include "Data.hpp"
#include <type_traits>


template <class T>
Node<T>::Node()
{
    //std::cout << "Node's constructor called\n";
    prev = nullptr;
    next = nullptr;
}

template <class T>
Node<T>::Node(const T& data)
{
    //std::cout << "Node's para constructor called\n";
    prev = nullptr;
    next = nullptr;
    nodeData = data;
}


template <class T>
Node<T>::~Node()
{
    //std::cout << "Node's destructor called\n";
}

template <class T>
Node<T>::Node(const Node& otherNode)
{
    std::cout << "Node's copy constructor\n";
    prev = otherNode.prev;
    next = otherNode.next;
    nodeData = otherNode.nodeData;
}

template <class T>
Node<T>* Node<T>::operator=(Node otherNode)
{
    std::cout << "Node's assignment\n";
    swap(otherNode);
    return this;
}

template <class T>
void Node<T>::swap(Node& otherNode)
{
    std::swap(prev,otherNode.prev);
    std::swap(next,otherNode.next);
    std::swap(nodeData,otherNode.nodeData);
}

template <class T>
void Node<T>::print()
{
///precondition: T is a class with a print() function
///else dont call this
    nodeData.print();
///comment the above code and uncomment this for types like string, int...
    //std::cout << nodeData << "\n";
}
