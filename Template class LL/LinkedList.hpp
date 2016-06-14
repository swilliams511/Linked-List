#ifndef _LL
#define _LL

#include "Node.hpp"
///see "template_tip.png" for why the implementation is in this file

template <class T>
class LinkedList{
public:
    LinkedList(); //: head(nullptr), tail(nullptr), numNodes(0) {std::cout << "List's destructor\n";}
    ~LinkedList();
    LinkedList(const LinkedList& otherList);
    LinkedList& operator=(LinkedList& otherList);

    int size();
    void push_front(T data);
    void push_back(T data);
    void pop_front();

    Node<T>* getHead() {return head;}
    Node<T>* getTail() {return tail;}
    void setHead(Node<T>* node) {head = node;}
    void setTail(Node<T>* node) {head = node;}

    void print();


private:
    Node<T>* head;
    Node<T>* tail;
    int numNodes;

    //debug variables for tracking number of new/delete calls the list makes
    //Will be displayed when the List's destructor finishes deleting all nodes
    int newCalls;
    int delCalls;



};

template <class T>
LinkedList<T>::LinkedList()
{
    std::cout << "List's constructor\n";
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
    //debug variables
    newCalls = 0;
    delCalls = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    std::cout << "List's destructor\n";
    while(head != nullptr)
        pop_front();
///tracker for number of new/delete node calls List makes. Should be equal
    std::cout << "New total: " << newCalls << "\ndelete total: "  << delCalls << "\n";
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& otherList)
{
    std::cout << "LL copy";
    if(otherList.head == nullptr)
    {
        head = nullptr;
        tail = nullptr;
        numNodes = 0;
        //debug variables
        newCalls = 0;
        delCalls = 0;
    }
    else
    {
        Node<T>* node = head;
        while(node != nullptr)
            push_back(node.getData);
    }

}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList& otherList)
{
///this is NOT called for pointer types, must dereference pointers for this to be called
    std::cout << "LL assign\n";
    while(head != nullptr)
        pop_front();

    Node<T>* node = otherList.head;

    while(node != nullptr)
    {
        push_back(node->getData());
        node = node->getNext();
    }

    return *this;
}


template <class T>
int LinkedList<T>::size()
{
    return numNodes;
///note: possible to not use memory and count each node starting at the head
///looks something like this...
/*
    if(head == nullptr)
        return 0;
    Node<T>* node = head;
    counter = 0;
    while(node != nullptr)
    {
        node = node->getNext();
        counter++;
    }
    return counter;
*/
}

template <class T>
void LinkedList<T>::push_front(T data)
{
    Node<T>* node = new Node<T>; //create a new instance of a node that holds the requested dataType
    newCalls++;
    node->setData(data);         //set the passed data to the node

    if(head == nullptr)          //if the list is empty
    {                            //one node is inserted
        head = node;             //that node is both the head and tail
        tail = node;
        numNodes++;              //increase the list's size
        return;                  //insertion finished
    }                            //if the list isn't empty...
    node->setNext(head);         //the new node next pointer is now the head
    head->setPrev(node);         //the heads prev pointer is now the new node
    head = node;                 //update the head to be the new node since it is in front of the old head
    numNodes++;                  //increase the size of the list
}

template <class T>
void LinkedList<T>::push_back(T data)
{
    if(head == nullptr) //if the list is empty
    {
        push_front(data); //let this function do the work, less code duplication
        return;
    }


    Node<T>* node = new Node<T>;
    newCalls++;
    node->setData(data);
    tail->setNext(node);
    node->setPrev(tail);
    tail = node;
    numNodes++;

}

template <class T>
void LinkedList<T>::pop_front()
{
    if(head == nullptr)
        return;

    if(numNodes == 1)
    {
        delete head;
        delCalls++;
        head = nullptr;
        tail = nullptr;
        numNodes--;
        return;
    }
    Node<T>* node = head->getNext();
    node->setPrev(nullptr);
    delete head;
    delCalls++;
    head = node;
    numNodes--;

}


template <class T>
void LinkedList<T>::print()
{
    std::cout << "***Contents of Linked List***\n";
    if(head == nullptr)
    {
        std::cout << "List empty\n";
        return;
    }
    Node<T>* node = head;
    int counter = 1;
    while(node != nullptr)
    {
        std::cout << "Node " << counter << " holds: ";
        node->print();
        node = node->getNext();
        counter++;
    }
    std::cout << "\n";
}








#endif // _LL

