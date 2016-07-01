#include "LinkedList.hpp"

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
        {  //no need to test isMember here since otherList would have already gone through that process, so call the helper
            _push_back(node->getData()); //add the current node to the new list
            node = node->getNext();  //move to the next node in the passed list
        }
    }
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList otherList)
{
///LinkedList's copy constructor is first called on otherList since it's passed by value
///its variables are then swapped into the left hand list. Then once the function does out of
///scope the copy with the left hand list's contents is destroyed
    std::cout << "LL assign\n";
    std::swap(newCalls,otherList.newCalls);
    std::swap(delCalls,otherList.delCalls);

    std::swap(head,otherList.head);         //swap the head pointer with the copied head pointer
    std::swap(tail,otherList.tail);         //swap the tail pointer with the copied tail poinrwe
    std::swap(numNodes,otherList.numNodes); //swap the number of nodes with the copied list
    return *this;                           //return the modified dereferenced this list
}

template <class T>
int LinkedList<T>::size()
{
    return numNodes; //basically a getNumNodes() function
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
    return _push_front(data); //now that we've checked for the node, we can insert it
}

template <class T>
bool LinkedList<T>::_push_front(const T& data)
{
    Node<T>* node = new Node<T>(data); //create a new instance of a node that holds the data
    newCalls++;
    numNodes++;              //increase the list's size
    if(head == nullptr)          //if the list is empty
        return first_insert(node); //add the node to the list where head = tail = node
    node->setNext(head);         //the new node next pointer is now the head
    head->setPrev(node);         //the heads prev pointer is now the new node
    head = node;                 //update the head to be the new node since it is in front of the old head
    return true;                 //insertion finished
}

template <class T>
bool LinkedList<T>::push_back(const T& data)
{
    if(isMember(data))  //if the data is in the list
        return false;   //dont insert it
    return _push_back(data); //now that we've checked for the node, we can add it
}

template <class T>
bool LinkedList<T>::_push_back(const T& data)
{
    Node<T>* node = new Node<T>(data); //create a new node with the data
    newCalls++;
    numNodes++;              //increase the list's size
    if(head == nullptr) //if the list is empty
        return first_insert(node); //add the node to the list where head = tail = node
    tail->setNext(node);         //set the tail's next pointer to the new node
    node->setPrev(tail);         //set the new node's prev pointer to the tail
    tail = node;                 //update the tail to be the new node
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
        return _push_front(data); //let this function do the work, less code duplication
    if(index == numNodes) //if the index is at the end of the list
        return _push_back(data); //use this to put it in the back
    Node<T>* newNode = new Node<T>(data); //create a new node with the passed data
    newCalls++;
    numNodes++; //the size of the list goes up 1
    if(index-0 <= numNodes-1-index) //if the index is closer to the head than it is to the tail (or equal)
        return insert_middle(headToIndex(index),newNode); //set the pointers for the new node and indexed node
    return insert_middle(tailToIndex(index),newNode); //otherwise use the tail
}

template <class T>
bool LinkedList<T>::pop_front()
{
    if(head == nullptr)               //if the list is empty
        return false;                 //we cant delete anything
    return _pop_front();              //let this function do the work now that we know the list has nodes
}

template <class T>
bool LinkedList<T>::_pop_front()
{
    if(numNodes == 1)                 //if there is 1 node in the list
        return last_remove();
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
    return _pop_back();              //let this function delete the node since the list has at least 1 node in it
}

template <class T>
bool LinkedList<T>::_pop_back()
{
    if(numNodes == 1)                //if there is only one node
        return last_remove();        //remove it
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
    if (head == nullptr || index < 0 || index > numNodes-1) //if the list is empty or if the index is out of range [0,size()-1]
        return false;    //there are no nodes to remove
    if(index == 0)                      //if the index is the first node
        return _pop_front();             //let this function do the work
    if(index == numNodes-1)             //if the index is the last node
        return _pop_back();              //let this function do the work
    if(index-0 < numNodes-index-1)       //if the node is closer to the head
        return remove_middle(headToIndex(index)); //get to the indexed node starting at the head and remove it
    return remove_middle(tailToIndex(index-1)); //else get to the indexed node starting at the tail and remove it
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
    if(numNodes%2 == 1)
        std::cout << "Worst case runtime should be " << (numNodes+1)/2 << "\n";
    else
        std::cout << "Worst case runtime should be " << (numNodes)/2 << "\n";
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
///checking the index's distance from both end points reduces runtime to ceiling(n/2)
    if(index-0 <= numNodes-1-index) //if the index is closer to the head than it is to the tail (or equal)
        return headToIndex(index)->getData(); //return whatever data is in the node
    return tailToIndex(index)->getData(); //otherwise start from the tail and return the data from there
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
T LinkedList<T>::front()
{
    return head->getData();
}

template <class T>
T LinkedList<T>::back()
{
    return tail->getData();
}

template <class T>
void LinkedList<T>::sort() //using quicksort
{
    _sort(head,tail); //pass in the only two node's we have access too as the starting nodes
}

//recursive call helper function for sorting nodes
template <class T>
void LinkedList<T>::_sort(Node<T>* left, Node<T>* right)
{  //if left and right arent nullptrs and left doesnt equal the next node of right
    if(left != nullptr && right != nullptr && left != right->getNext())
    {
        Node<T>* node = partition(left,right); //swap node values and return the pivot node
        //recursive calls
        _sort(left,node->getPrev());
        _sort(node->getNext(),right);
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

///functions to remove some code duplication

template <class T>
bool LinkedList<T>::insert_middle(Node<T>* node,Node<T>* newNode)
{
    newNode->setPrev(node->getPrev()); //set the new nodes prev pointer point to the node that came before the node at the index
    newNode->setNext(node);            //set the new nodes next pointer to the node that was at the index
    node->getPrev()->setNext(newNode); //have the node that came before the indexed node's next point to the new node
    node->setPrev(newNode);            //have the node that was at the index prev pointer set to the new node
    return true; //return that the node was inserted
}

template <class T>
bool LinkedList<T>::remove_middle(Node<T>* node)
{
    node->getPrev()->setNext(node->getNext()); //sets the node that comes before indexed node next pointer to the node after indexed node
    node->getNext()->setPrev(node->getPrev()); //sets the node that comes after indexed node prev pointer to the the node before indexed node
    delete node;   //free's the memory of the indexed node since it's no longer being pointed too
    delCalls++;
    numNodes--;    //reduce the size of the list by 1
    return true;   //tell the user the node was removed
}

template <class T>
Node<T>* LinkedList<T>::tailToIndex(int index)
{
    Node<T>* node = tail;           //get the pointer to the last node
    int counter = numNodes-1-index; //since we are starting at the end, we need to move backwards this many times
    int runTime = 1;
    while(counter > 0)              //while we aren't at the node
    {
        node = node->getPrev();     //move to the previous node
        counter--;                  //decrease the counter since we are moving backwards
        runTime++;
    }                               //once we get to 0, we are at the node
    std::cout << "Operations performed in at: " << runTime << "\n";
    return node;
}

template <class T>
Node<T>* LinkedList<T>::headToIndex(int index)
{
    Node<T>* node = head; //get the pointer to the first node
    int counter = 0;      //counter to move to the correct index
    int runTime = 1;
    while(counter < index) //while we arent at the index...
    {
        node = node->getNext(); //move to the next node
        counter++;              //increase the counter
        runTime++;
    } //at this point the node will be the requested node (or an exception node)
    std::cout << "Operations performed in at: " << runTime << "\n";
    return node;
}

template <class T>
bool LinkedList<T>::first_insert(Node<T>* node)
{
    head = node;   //that node is both the head and tail
    tail = node;
    return true;   //insertion finished
}

template <class T>
bool LinkedList<T>::last_remove()
{
    delete head;    //delete that node
    delCalls++;
    head = nullptr; //set the list's pointers to its starting state
    tail = nullptr;
    numNodes--;     //decrease the size of the list (should be 0 now)
    return true;    //say the node was deleted
}
