#ifndef DLLIST
#define DLLIST


#include "Node.hpp"

//Doubly Linked List based class
class DLList {
public:
    DLList(); //default constructor
    DLList(std::string name); //parameterized constructor which names the list
    ~DLList();  //destructor, calls Node's destructor for each node in the list
    DLList* copy(); //copy constructor
    DLList* copy(std::string name); //copy constructor that allows a new list name to be specified

    void insert_from_file(std::string fileName); //see implementation for how this works

    //node is created "new" in insert based on passed parameters. A different
    //set of functions could need to be written if you wanted to create the
    //new node in main and pass that to the insert
    bool insert_front(int value, std::string name); //puts the node at the head value
    bool insert_back(int value, std::string name);  //puts the node at the tail value
    bool insert_kth(int k, int value, std::string name); //puts the node at the specified position

    //node is deleted to match the "new" in insert
    bool delete_front(); //removes first node
    bool delete_back();  //removes last node
    bool delete_node(int value, std::string name);//searches for node based on parameters then deletes it
    bool delete_kth(int k); //deletes whatever node is at position k in the list

    bool inList(int value, std::string name); //check if the node is in the list

    //sequential searches
    Node* getNode(int value, std::string name); //find the node in the list and gives its address
    Node* getNode(int value);                   //variation that takes only the value
    Node* getNode(std::string name);            //variation that takes only the name
    Node* getKthNode(int v); //returns the kth node in the list, similar to std::vector's "->at(k)" function

    void sortList();   //quicksorts the nodes from smallest to largest value
    bool isListSorted(); //checks if the list is sorted
    void reverse(); //trivial since you can start at tail and get prev til nullptr
    void print(); //prints the contents of the list
    int size();   //checks the size of the list. Should be equal to numNodes
    //getters/setters
    Node* getHead() {return head;}
    void setHead(Node* v) {head = v;}
    Node* getTail() {return tail;}
    void setTail(Node* v) {tail = v;}
    int getNumNodes() {return numNodes;}
    void setNumNodes(int v) {numNodes = v;}
    std::string getListName() {return listName;}
    void setListName(std::string v) {listName = v;}

private:
    std::string listName; //the name of the list
    Node* head; //points to front node
    Node* tail; //points to last node
    int numNodes; //number of nodes in list managed by insert/delete
    //quick sort helper functions
    void qsort(Node* left, Node* right);
    Node* partition(Node* left, Node* right);

};

#endif // DLLIST
