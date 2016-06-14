#ifndef _NODE
#define _NODE
#include <iostream>

template <class T>
class Node{
public:
    Node();
    Node(const T& data);
    ~Node();
    Node(const Node& otherNode);
    Node* operator= (Node otherNode);


    T getData() {return nodeData;}
    void setData(const T& data) {nodeData = data;}
    Node* getPrev() {return prev;}
    Node* getNext() {return next;}
    void setPrev(Node* node) {prev = node;}
    void setNext(Node* node) {next = node;}

    //this function is build specific for dataTesting of type "Data"
    //don't call it if you are using a different datatype (int,string, etc)...
    void print();
private:
    T nodeData;
    Node* prev;
    Node* next;
    void swap(Node& otherNode);


};


#endif // _NODE
