#include "LinkedList.hpp"

///keeping old implementation for reference, but going to clean up some functions


template <class T>
LinkedList<T>::LinkedList()
{
    std::cout << "List's constructor\n";
    head = nullptr; //by default, head and tail of a list point to nothing since there are no nodes
    tail = nullptr;
    numNodes = 0;   //likewise, there are no nodes so we set size to 0
    //debug variables
    newCalls = 0;
    delCalls = 0;
}

template<class T>
LinkedList<T>::~LinkedList()
{
    std::cout << "List's destructor\n";
    while(head != nullptr) //we must delete each node that is under ownership of the list
        pop_front();       //the first node is deleted until the list is empty
///tracker for number of new/delete node calls List makes. Should be equal
    std::cout << "New total: " << newCalls << "\ndelete total: "  << delCalls << "\n";
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList& otherList)
{
    std::cout << "LL copy\n";
    //default values
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
    //debug variables
    newCalls = 0;
    delCalls = 0;
    //will only use these if the passed list is empty
    if(otherList.head != nullptr)                         //the list contains node, so we must create a new copy of each node
    {                            //and put it in the copy list
        Node<T>* node = otherList.head;    //node variable starting at the passed list's head
        while(node != nullptr)             //while we are not at the end of the list
        {
            push_back(node->getData()); //add the current node to the new list
            node = node->getNext();  //move to the next node in the passed list
        }
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList& otherList)
{
///this is NOT called for pointer types, must dereference pointers for this to be called
///copy/swap implementation doesn't seem practical since not using smart pointers
    std::cout << "LL assign\n";
    while(head != nullptr)            //while there are nodes in this list
        pop_front();                  //delete all of them

    Node<T>* node = otherList.head;   //get the other list's head

    while(node != nullptr)            //while the other list has node's in it
    {
        push_back(node->getData());   //insert the data in those nodes into the this list
        node = node->getNext();       //move to the next node in the other list
    }                                 //once all nodes have been copied from the other list
    return *this;                     //return the modified dereferenced this list
}


template <class T>
int LinkedList<T>::size()
{
    return numNodes; //basically a getNumNodes() function
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
bool LinkedList<T>::isMember(const T& data)
{
    if (head == nullptr)           //if the list is empty
        return false;              //the data isn't in there
    Node<T>* node = head;          //set a node pointer equal to the head
    while(node != nullptr)         //while the list still has more nodes in it...
    {
        if(node->getData() == data)//if the current node has the data
            return true;           //say we found it
        node = node->getNext();    //otherwise move to the next node
    }                              //if we make it to the end of the list
    return false;                  //the data isn't in there so return false
}

template <class T>
bool LinkedList<T>::push_front(const T& data)
{
    if(isMember(data))           //if the data is already in the list
        return false;            //dont insert it and tell the user it wasn't inserted
    Node<T>* node = new Node<T>(data); //create a new instance of a node that holds the data
    newCalls++;

    if(head == nullptr)          //if the list is empty
    {                            //one node is inserted
        head = node;             //that node is both the head and tail
        tail = node;
        numNodes++;              //increase the list's size
        return true;             //insertion finished
    }                            //if the list isn't empty...
    node->setNext(head);         //the new node next pointer is now the head
    head->setPrev(node);         //the heads prev pointer is now the new node
    head = node;                 //update the head to be the new node since it is in front of the old head
    numNodes++;                  //increase the size of the list
    return true;                 //insertion finished
}

template <class T>
bool LinkedList<T>::push_back(const T& data)
{
    if(isMember(data))  //if the data is in the list
        return false;   //dont insert it
    if(head == nullptr) //if the list is empty
    {
        return push_front(data); //let this function do the work, less code duplication
    }
    Node<T>* node = new Node<T>(data); //create a new node with the data
    newCalls++;
    tail->setNext(node);         //set the tail's next pointer to the new node
    node->setPrev(tail);         //set the new node's prev pointer to the tail
    tail = node;                 //update the tail to be the new node
    numNodes++;                  //increase the number of nodes
    return true;                 //tell the user the node was inserted
}

template <class T>
bool LinkedList<T>::insert(const T& data, int index)
{
///range for index is [0,size()]
///index 0 equals push_front() range: {0}
///index size() = push_back()  range: {size()}
///see "LinkedListInsert.png" for illustration for the case where we are inserting a middle node. range: [1,size()-1]
    if(index < 0 || index > numNodes) //range check
    {
        std::cout << "Error: " << index << " is out of range [0," << numNodes << "]. Node not inserted\n";
        return false; //can't insert a node if out of range error is obtained
    }
    if(isMember(data))  //if the data is in the list
        return false;   //dont insert it
    if(head == nullptr || index == 0) //if the list is empty or we are inserting to the front of the list
    {
        return push_front(data); //let this function do the work, less code duplication, but extra isMember() calls
    }
    if(index == numNodes) //if the index is at the end of the list
        return push_back(data); //use this to put it in the back
    Node<T>* newNode = new Node<T>(data); //create a new node with the passed data
    newCalls++;
    Node<T>* node = head;           //get a node pointer to the head
    int counter = 0;                //counter to know what node we're on
    while(counter < index)       //while we arent at the index node
    {
        node = node->getNext();     //move the node pointer to the next node in the list
        counter++;                  //account for each time we move to the next node
    } //see the "LinkedListInsert.png" to see where these pointers are set to
    newNode->setPrev(node->getPrev()); //set the new nodes prev pointer point to the node that came before the node at the index
    newNode->setNext(node);            //set the new nodes next pointer to the node that was at the index
    node->getPrev()->setNext(newNode); //have the node that came before the indexed node's next point to the new node
    node->setPrev(newNode);            //have the node that was at the index prev pointer set to the new node
    numNodes++;                        //number of nodes in the list went up by 1
    return true;                       //tell the user insert was success
}

template <class T>
bool LinkedList<T>::pop_front()
{
    if(head == nullptr)               //if the list is empty
        return false;                 //we cant delete anything

    if(numNodes == 1)                 //if there is 1 node in the list
    {
        delete head;                  //delete that node
        delCalls++;
        head = nullptr;               //set the list's pointers to its starting state
        tail = nullptr;
        numNodes--;                   //decrease the size of the list (should be 0 now)
        return true;                  //say the node was deleted
    }                                 //if there is more than one node
    Node<T>* node = head->getNext();  //get a pointer to the node after the head node
    node->setPrev(nullptr);           //set the node we got prev pointer to nullptr
    delete head;                      //free the memory that head points too
    delCalls++;
    head = node;                      //update the head pointer to point to the node we got earlier
    numNodes--;                       //decrease the size of the list
    return true;                      //tell the user the first node was deleted
}

template <class T>
bool LinkedList<T>::pop_back()
{
    if(head == nullptr)              //if the list is empty
        return false;                //we cant delete anything
    if(numNodes == 1)                //if there is only one node
        return pop_front();          //let pop front do the work
    Node<T>* node = tail->getPrev(); //otherwise get the pointer to the node before the tail
    node->setNext(nullptr);          //set that nodes next pointer to a nullptr
    delete tail;                     //delete the node tail points too
    delCalls++;
    tail = node;                     //let the tail point to the node that was behind the deleted node
    numNodes--;                      //decrease the number of nodes
    return true;                     //say we deleted the node
}

template <class T>
bool LinkedList<T>::remove(int index)
{
    if (head == nullptr) //if the list is empty
        return false;    //there are no nodes to remove
    if(index < 0 || index > numNodes-1) //if the index is out of range [0,size()-1]
        return false;                   //dont delete anything
    if(index == 0)                      //if the index is the first node
        return pop_front();             //let this function do the work
    if(index == numNodes-1)             //if the index is the last node
        return pop_back();              //let this function do the work
    Node<T>* node = head;               //get the pointer to the first node in the list
    int counter = 0;                    //counter for getting to the correct index
    while(counter < index)              //while we aren't at the index
    {
        node = node->getNext();         //move to the next node in the list
        counter++;                      //increase the counter
    }
    node->getPrev()->setNext(node->getNext()); //sets the node that comes before indexed node next pointer to the node after indexed node
    node->getNext()->setPrev(node->getPrev()); //sets the node that comes after indexed node prev pointer to the the node before indexed node
    delete node;   //free's the memory of the indexed node since it's no longer being pointed too
    delCalls++;
    numNodes--;    //reduce the size of the list by 1
    return true;   //tell the user the node was removed
}

template <class T>
bool LinkedList<T>::remove(const T& data)
{ //uses isMember() implementation and calls remove with the found index
    if (head == nullptr)           //if the list is empty
        return false;              //the data isn't in there
    Node<T>* node = head;          //set a node pointer equal to the head
    int counter = 0;               //a counter for finding the index of the node
    while(node != nullptr)         //while the list still has more nodes in it...
    {
        if(node->getData() == data)//if the current node has the data
            return remove(counter);           //let this function do the work with the found index
        node = node->getNext();    //otherwise move to the next node
        counter++;                 //increase the index counter
    }                              //if we make it to the end of the list
    return false;                  //the data isn't in there so return false
}

template <class T>
T LinkedList<T>::at(int index)
{
///This function will have bad behavior if the list is empty or if the index is out of range
///The program will segfault (probably) if the list is empty
///if the list is less than the range, the 0th node's data will be returned
///if the list is more than the range, the size()-1th node's data will be returned
    if (head == nullptr) //if the list is emoty
        std::cout << "Error: at() can't be called on an empty list\nProgram will likely segfault\n";
    //if the requested index is not in range
    if(index > numNodes-1)
        std::cout << "Error: at(" << index << ") is out of range [0," << numNodes-1 << "]. Can't get data\nProgram will return at(" << numNodes-1 << ")\n";
    if(index < 0)
        std::cout << "Error: at(" << index << ") is out of range [0," << numNodes-1 << "]. Can't get data\nProgram will return at(0)\n";

    Node<T>* node = head; //get the pointer to the first node
    int counter = 0;      //counter to move to the correct index
    while(counter < index && node->getNext() != nullptr) //while we arent at the index...
    {                  //note: the && part of the loop allows for out of range value call to return
        node = node->getNext(); //move to the next node
        counter++;              //increase the counter
    } //at this point the node will be the requested node (or an exception node)
    return node->getData(); //return whatever data is in the node
}


//print function to be used when class T has a print() function implemented
template <class T>
void LinkedList<T>::print()
{
    std::cout << "***Contents of Linked List***\n";
    if(head == nullptr)
    {
        std::cout << "List empty\n";
        return;
    }
    Node<T>* node = head;      //start at the head node
    int counter = 1;           //variable for counting what node we are on
    while(node != nullptr)
    {
        std::cout << "Node " << counter << " holds: ";
        node->print();         //print what's in the node
        node = node->getNext();//move to the next node
        counter++;             //increase the counter
    }
    std::cout << "\n";
}

//print function to be used with simple data types like int, float, string...
template <class T>
void LinkedList<T>::print_nonClass()
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
        node->print_nonClass();
        node = node->getNext();
        counter++;
    }
    std::cout << "\n";
}

template <class T>
void LinkedList<T>::sort() //using quicksort
{ //if the head and tail arent nullptrs
    if(head != nullptr && tail != nullptr)
    {
        Node<T>* node = partition(head,tail); //swaps data of nodes and returns the pivot node
        //recursive calls
        qsort(head,node->getPrev());
        qsort(node->getNext(),tail);
    }
}

//recursive call helper function for sorting nodes
template <class T>
void LinkedList<T>::qsort(Node<T>* left, Node<T>* right)
{  //if left and right arent nullptrs and left doesnt equal the next node of right
    if(left != nullptr && right != nullptr && left != right->getNext())
    {
        Node<T>* node = partition(left,right);
        //recursive calls
        qsort(left,node->getPrev());
        qsort(node->getNext(),right);
    }
}

//helper function that swaps the nodes in the DLList
template <class T>
Node<T>* LinkedList<T>::partition(Node<T>* left, Node<T>* right)
{
    T data = right->getData(); //quicksort pivot element
    Node<T>* node = left->getPrev(); //gets the pointer that comes before the left node
    for(Node<T>* j = left; j != right; j = j->getNext()) //loops through each node, from left to right
    {
        if(j->getData() < data) //if the current nodes data is smaller than pivot data
        {                                                     //if the lefts prev node is nullptr, set node to left
            node = (node == nullptr)? left : node->getNext(); //else set node to the node after left
            //swaps the data between node and the jth node
            T tempData = node->getData();
            node->setData(j->getData());
            j->setData(tempData);
        }
    }
    node = (node == nullptr)? left : node->getNext();
    //swaps the data between node and the right npde
    T tempData = node->getData();
    node->setData(right->getData());
    right->setData(tempData);
    return node;              //return the end node after swapping is done
}
