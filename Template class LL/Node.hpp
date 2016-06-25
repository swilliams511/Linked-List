#ifndef _NODE
#define _NODE
#include <iostream>

//templated to hold ~any data type
template <class T>
//nodes for a linked list
class Node{
public:
///constructor based functions and overloaded operation functions
    Node();                            //default constructor
    Node(const T& data);               //parameterized constructor
    ~Node();                           //destructor
    Node(const Node& otherNode);       //copy constructor
    Node& operator=(Node otherNode);  //assignment operator

///getters/setters for the linked list to use
    T getData() {return nodeData;}
    void setData(const T& data) {nodeData = data;}
    Node* getPrev() {return prev;}
    Node* getNext() {return next;}
    void setPrev(Node* node) {prev = node;}
    void setNext(Node* node) {next = node;}

    //this function is build specific for dataTesting of type "Data"
    //don't call it if you are using a different datatype (int,string, etc)...
    void print();
    void print_nonClass();
private:
///node variables
    T nodeData;
    Node* prev;
    Node* next;
///helper functions
    void swap(Node& otherNode);

};

#endif // _NODE
