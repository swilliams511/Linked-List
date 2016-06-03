#include "DLList.hpp"
#include <fstream>
#include <cassert>
#include <iostream>

DLList::DLList() //default constructor
{
    listName = "";
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
}

DLList::DLList(std::string name) //parameterized constructor
{
    listName = name;
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
}


DLList::~DLList() //destructor
{
    while(numNodes > 0) //numNodes is managed by the delete functions
        delete_back();  //the last node in the list is removed til there are no more nodes
}

DLList* DLList::copy() //creates an exact copy of the current list
{
    DLList* newList = new DLList(); //creates a new instance of a list
    if(head == nullptr) //if the list that called this function is empty
        return newList; //dont do anything and return the new list as is
    Node* node = head;  //starting node
    while(node != nullptr) //while we arent in the tail
    {   //this creates new nodes in the new list with the corresponding node's value from the list that called
        newList->insert_back(node->getValue(),node->getName());
        node = node->getNext(); //go to the next node
    }
    return newList; //return the newly created list. remember to have a matching delete for it
}

DLList* DLList::copy(std::string name) //creates an exact copy of the list, except you can specify the list's name
{
    DLList* newList = new DLList();
    newList->setListName(name);
    if(head == nullptr)
        return newList;
    Node* node = head;
    while(node != nullptr)
    {
        newList->insert_back(node->getValue(),node->getName());
        node = node->getNext();
    }
    return newList;
}

void DLList::insert_from_file(std::string fileName)
{
    std::string pkmnNum;
    std::string pkmnName;

    std::fstream stream;
    stream.open (fileName, std::fstream::in | std::fstream::out | std::fstream::app);
    /* The requested file must have its data stored in a way like this:
    pokemon number, newline, pokemon name, newline, repeat
    Otherwise the nodes will corrupt. See http://www.dragonflycave.com/list.aspx
    for generating lists of pokemon. Using the list format:
                %[national_dex]%<br>%[name]%<br>
    will give you results on each line like this "1<br>Bulbasaur<br>"
    If you copy and paste all of that into an html file then view the page,
    the line breaks "<br>" will do their job, and you will have a list
    that cam be used for this program!!
     */
    while(std::getline(stream,pkmnNum))
    {

        std::getline(stream,pkmnName);
        insert_back(atoi(pkmnNum.c_str()),pkmnName); //atoi turns the read string number into an int. needs to be in c str form
    }
    stream.close();
}

bool DLList::insert_front(int value, std::string name)
{
    if(inList(value,name))  //if the node is already in the list
        return false; //don't insert it
    Node* node = new Node(value,name); //create a new node instance holding the passed parameters
    if(head == nullptr)  //if there are no nodes
    {
        head = node;
        tail = node;
        numNodes++;
        return true;
    }
    else
    {
        node->setNext(head);
        head->setPrev(node);
        head = node;
        numNodes++;
        return true;
    }
    return false;
}

bool DLList::insert_back(int value, std::string name)
{
    if(inList(value,name))//if the node is already in the list
        return false; //don't insert it
    Node* node = new Node(value,name); //creates a new instance of a node with the passed values
    if(head == nullptr)//if there are no nodes
    {
        head = node; //set the head and tail to that node
        tail = node;
        numNodes++; //increase the number of nodes by 1
        return true;
    }
    else //if there are already nodes in the list
    {
        tail->setNext(node); //the tail now points to the inserted node
        node->setPrev(tail); //the inserted node now points to the tail node
        tail = node; //the tail node is updated to become the node value
        numNodes++; //number of nodes increases by 1
        return true;
    }
    return false; //for whatever reason if the above return were't hit, the node wasn't inserted. shouldnt happen tho
}

void DLList::print()
{
    if(head == nullptr)
    {
        std::cout << "The list is empty\n";
        return;
    }

    Node* node = head;
    int index = 1;
    std::cout << "Nodes in DLList: " << listName << "\n";

    while( node != nullptr)
    {
        std::cout << "***Node " << index << " holds***\nvalue: " << node->getValue() << "\nname: "
        << node->getName() << "\n\n";
        node = node->getNext();
        index++;
    }
}

//sequential search
bool DLList::inList(int value, std::string name)
{
    Node* node = head; //set the head nodes address to a temporary node for traversing the list
    while (node != nullptr) //while the node isn't empty
    {
        if(node->getName() == name && node->getValue() == value) //if the current node matches the parameters
            return true; //say that it was found
        node = node->getNext(); //if the node wasn't found, set the temporary node equal to the next node in the list
    }
    return false; //if the node couldn't get found, the function will get here and say it wasn't found
}

//similar to above, but returns the address of the found node
Node* DLList::getNode(int value, std::string name)
{
    Node* node = head;
    while (node != nullptr)
    {
        if(node->getName() == name && node->getValue() == value)
            return node;
        node = node->getNext();
    }
    std::cout << "Couldn't find requested node. Program will segfault if there is no if statement checking for nullpointers\n";
    return nullptr;
}

//similar to above, only takes the value parameter
Node* DLList::getNode(int value)
{
    Node* node = head;
    while (node != nullptr)
    {
        if(node->getValue() == value)
            return node;
        node = node->getNext();
    }
    std::cout << "Couldn't find requested node. Program will segfault if there is no if statement checking for nullpointers\n";
    return nullptr; //this will cause the program to reference a nullpointer and segmentation fault
}

//similar to above, only takes the name parameter
Node* DLList::getNode(std::string name)
{
    Node* node = head;
    while (node != nullptr)
    {
        if(node->getName() == name)
            return node;
        node = node->getNext();
    }
    std::cout << "Couldn't find requested node. Program will segfault if there is no if statement checking for nullpointers\n";
    return nullptr;
}

bool DLList::delete_front()
{
    if(head == nullptr)
        return false;
    if(head->getNext() == nullptr || head == tail)
    {
        delete head; //get rid of head's old value
        head = nullptr; //put head/tail into their starting state of a nullptr
        tail = nullptr;
        numNodes--;
        return true;
    }
    Node* node = head->getNext();
    node->setPrev(nullptr);
    delete head;            //no memory leak
    head = node;
    numNodes--;
    return true;
}

bool DLList::delete_back()
{
    if(tail == nullptr) //no nodes in the list
        return false;
    if(tail->getPrev() == nullptr || tail == head) //one node in the list
    {
        delete tail; //get rid of tail's old value
        head = nullptr; //put head/tail into their starting state of a nullptr
        tail = nullptr;
        numNodes--; //reduce count of nodes
        return true;
    }
    Node* node = tail->getPrev(); //set the node to the value before the tail
    node->setNext(nullptr); //that node now doesnt point to anything infront of it
    delete tail;            //no memory leak
    tail = node;            //assign the tail to the node that came before tail
    numNodes--; //reduce count of nodes
    return true;
}

bool DLList::delete_node(int value, std::string name)
{
    if(head == nullptr) //if there are no nodes
        return false; //cant delete
    Node* node = head;
    while ((node->getValue() != value && node->getName() != name))
    {
        if(node == nullptr)//couldn't find the node
            return false;//so it couldnt delete it
        node = node->getNext(); //find where the requested node is
    }
    if(node == head) //if the node is the first one
    {
        delete_front(); //use this function
        return true; //say the node was removed
    }
    if(node == tail) //if the node is the last one
    {
        delete_back(); //use this function
        return true; //say the node was removed
    }
    //possible to not use temporary pointers, see delete_kth
    //leaving them here though for coding style comparison
    Node* prev = node->getPrev(); //temporary pointers for the nodes around the one
    Node* next = node->getNext(); //we want to remove
    prev->setNext(next);          //set the temp nodes to point at each other
    next->setPrev(prev);
    delete node;                //delete the node
    numNodes--;                 //reduce the number of nodes
    return true;
}

Node* DLList::getKthNode(int k) //similar to ->at(n) with vector
{
    if(k > numNodes)
    {
        std::cout << "Indexing starts at 1 and goes to " << numNodes
        << ". Input value: " << k << " is too LARGE\n";
        exit(0);
    }
    if(k < 1)//indexing for DLList starts at 1 for head
    {
        std::cout << "Indexing starts at 1 and goes to " << numNodes
        << ". Input value: " << k << " is too SMALL\n";
        exit(1);
    }
    Node* node = head;
    int counter = 1;
    while(counter < k) //loops until the counter equals k
    {
        node = node->getNext();
        counter++;
    }
    return node;   //then the kth node has been found
}


void DLList::sortList() //using quicksort
{
    if(head != nullptr && tail != nullptr && head != tail->getNext())
    {
        Node* node = partition(head,tail);

        qsort(head,node->getPrev());
        qsort(node->getNext(),tail);
    }
}

//recursive call helper function for sorting nodes
void DLList::qsort(Node* left, Node* right)
{
    if(left != nullptr && right != nullptr && left != right->getNext())
    {
        Node* node = partition(left,right);

        qsort(left,node->getPrev());
        qsort(node->getNext(),right);
    }
}

//helper function that swaps the nodes in the DLList
Node* DLList::partition(Node* left, Node* right)
{
    int x = right->getValue(); //pivot element

    Node *node = left->getPrev(); //assigns a node value to the node before left
    for(Node* j = left; j != right; j = j->getNext()) //loops through each node
    {
        if(j->getValue() <= x) //if the current nodes value is smaller than pivot value
        {
            node = (node == nullptr)? left : node->getNext(); //this is more or less the same as below code
            /*
            if(node == nullptr)          //if the node before left is a nullptr
                node = left;             //update node to just be left
            else                         //otherwise
                node = node->getNext();  //let node be equal to the next node in the list
            */
            int temp = node->getValue(); //temporary variables for swapping
            std::string tempName = node->getName();

            node->setValue(j->getValue()); //swapped the for loop node value into the node
            node->setName(j->getName());

            j->setValue(temp); //swapped the nodes value into the for loop node
            j->setName(tempName);
        }
    }
    node = (node == nullptr)? left : node->getNext(); //this is more or less the same as below code
    /*
    if(node == nullptr)          //if the node before left is a nullptr
        node = left;             //update node to just be left
    else                         //otherwise
        node = node->getNext();  //let node be equal to the next node in the list
    */
    int temp = node->getValue();            //temporary variables for swapping
    std::string tempName = node->getName();

    node->setValue(right->getValue()); //swapped the right node's value into the node
    node->setName(right->getName());

    right->setValue(temp);            //swapped the node's value into the right node
    right->setName(tempName);

    return node;              //return the end node after swapping is done
}

bool DLList::isListSorted() //checks if the nodes go from smallest to greatest, doesn't modily the list at all
{
    Node* node = head;
    if (node == nullptr)
        return true;     //an empty list is a sorted list
    while(node->getNext() != nullptr && node->getValue() < node->getNext()->getValue())
        node = node->getNext(); //if the current nodes value is less than the next node, advance along the list
    return node->getNext() == nullptr; //next will only be  nullptr at the end of the list meaning it is sorted
}



//inserts a new node at the kth position in the list
bool DLList::insert_kth(int k, int value, std::string name)
{
    if(k > numNodes+1) //if input position exceeds size of list plus 1 (since we're adding a node)
    {
        std::cout << "Indexing starts at 1 and goes to " << numNodes+1
        << ". Input value: " << k << " is too LARGE\n";
        exit(0);
    }
    if(k < 1)//indexing for DLList starts at 1 for head
    {
        std::cout << "Indexing starts at 1 and goes to " << numNodes+1
        << ". Input value: " << k << " is too SMALL\n";
        exit(1);
    }
    if(k == 1) //1 is the start of the list, so just use this function
    {
        insert_front(value,name);
        return true;
    }
    if(k == numNodes+1) //the size + 1 is the end of the list, so use this
    {
        insert_back(value,name);
        return true;
    }
    int counter = 1;
    Node* node = new Node(value,name); //new instance of node with the passed parameters
    Node* current = head; //temporary variable for the node currently at the kth position
    while(counter < k)
    {

        current = current->getNext();
        counter++;
    }
    current->getPrev()->setNext(node);
    node->setPrev(current->getPrev());
    node->setNext(current);
    current->setPrev(node);
    numNodes++;             //says the lists size has increased
    return true;

}

//deletes the node at the kth position in the list
bool DLList::delete_kth(int k)
{
    if(k > numNodes) //if input position exceeds size of list
    {
        std::cout << "Indexing starts at 1 and goes to " << numNodes+1
        << ". Input value: " << k << " is too LARGE\n";
        exit(0);
    }
    if(k < 1)//indexing for DLList starts at 1 for head
    {
        std::cout << "Indexing starts at 1 and goes to " << numNodes+1
        << ". Input value: " << k << " is too SMALL\n";
        exit(1);
    }
    if(k == 1) //1 is the start of the list, so just use this function
    {
        delete_front();
        return true;
    }
    if(k == numNodes) //the size is the end of the list, so use this
    {
        delete_back();
        return true;
    }
    int counter = 1;
    Node* node = head;

    while(counter < k) //loops until the counter equals k
    {
        node = node->getNext();
        counter++;
    }
    node->getPrev()->setNext(node->getNext());
    node->getNext()->setPrev(node->getPrev());
    delete node;
    numNodes--;
    return true;
}

void DLList::reverse()
{
    if(head == nullptr) //if the list is empty, it doesnt need any changing
        return;
    if(numNodes == 1) //if the list has 1 node, it doesnt need to be changed
        return;
    Node* node = head;
    while(node != nullptr)
    {
        Node* prev = node->getPrev(); //temporarily holds the previous node address
        node->setPrev(node->getNext()); //swaps the next and prev addresses
        node->setNext(prev);
        node = node->getPrev();  //moves to the prior node (since next was swapped with prev, meaning to move forward we have to go backwards)
    }
    Node* temp = head; //temporarily holds the head's address
    head = tail; //makes the head where the tail was
    tail = temp; //makes the tail where the head was
}

int DLList::size() //simply for testing if numNodes managed by insert/delete
{                  //is doing its job
    int counter = 0;
    Node* node = head;
    while(node != nullptr)
    {
        node = node->getNext();
        counter++;
    }
    return counter;
}

