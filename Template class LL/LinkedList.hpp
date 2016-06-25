#ifndef _LL
#define _LL

#include "Node.hpp"
///see "template_tip.png" for why the implementation is in this file
///switched from implementing all in .hpp file to moving to .cpp file
///and including that in main. Seems to work the same ^_^

//templated so node can hold ~any data type
template <class T>
//implemented as a double linked list with "Node's" storing the data
class LinkedList{
public:
///constructor based functions and overloaded operation functions
    LinkedList(); //default constructor. Alternate way to implement commented out below
   /* LinkedList() : head(nullptr), tail(nullptr), numNodes(0) {std::cout << "List's constructor\n";}  */
    ~LinkedList();//destructor
    LinkedList(const LinkedList& otherList);//copy constructor
    LinkedList& operator=(LinkedList& otherList);//overloaded assignment operator
///member functions
    int size();                      //returns the number of nodes in the list
    bool isMember(const T& data);    //sequential search to lookup if the passed data is in the list
    bool push_front(const T& data);  //adds a node to the start of the list
    bool push_back(const T& data);   //adds a node to the back of the list
    bool insert(const T& data, int index); //inserts the data at the kth position
    bool pop_front();                //deletes the first node of the list
    bool pop_back();                 //deletes the last node of the list
    bool remove(int index);          //removes the data at the kth position
    bool remove(const T& data);      //removes the passed data from the list
    T at(int index);                 //returns the data from the node at the index. Must be nonEmpty list with index in range [0,size()]
    void sort();                     //sorts the list using quicksort algorithm
    T front();                       //returns the data at the front of the list
    T back();                        //returns the data at the back of the list
    ///could implement sort using merge sort
///getters/setters for testing
    //Node<T>* getHead() {return head;}
    //Node<T>* getTail() {return tail;}
    //void setHead(Node<T>* node) {head = node;}
    //void setTail(Node<T>* node) {tail = node;}
    //no getter/setter for numNodes since it doesn't need to be set and size() gets the nodes
    /* int getNumNodes() {return numNodes;}        */
    /* void setNumNodes(int num) {numNodes = num;} */
///debug functions to view whats happening
    void print();                    //use this if the data type has a print function
    void print_nonClass();           //use this if the data type is a primitive data type
private:
///Variables that make a linked list
    Node<T>* head;
    Node<T>* tail;
    int numNodes;
///helper functions.
    bool first_insert(Node<T>* node);
    bool last_remove();
    bool insert_middle(Node<T>* node,Node<T>* newNode);
    bool remove_middle(Node<T>* node);
    Node<T>* headToIndex(int index);
    Node<T>* tailToIndex(int index);
    bool _push_front(const T& data);  //assumes isMember is checked
    bool _push_back(const T& data);   //"  "
    bool _insert(const T& data, int index); //
    bool _pop_front();                //
    bool _pop_back();                 //
    bool _remove(int index);          //
    bool _remove(const T& data);      //
    void _sort(Node<T>* left, Node<T>* right);
    Node<T>* partition(Node<T>* left, Node<T>* right);

///debug variables for tracking number of new/delete calls the list makes
    //Will be displayed when the List's destructor finishes deleting all nodes
    int newCalls;
    int delCalls;
};
/*
Runtime table for member functions
size() = O(1) (since numNodes is managed by insert/remove. Would be O(n) for sequential counting)
at() = O(ceiling(n/2))
isMember() = O(n)
push_front() = O(1) + O(n) for isMember() check
push_back() = O(1) + O(n) for isMember() check
insert(index) =    TODO
pop_front() = O(1)
pop_back() = O(1)
remove() = O(n)
remove(index) =    TODO



*/
#endif // _LL
