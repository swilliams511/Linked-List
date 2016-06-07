#ifndef NODE
#define NODE


#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

//basic object for holding information. Has pointers so it can be used in a DLList
class Node{
public:
    Node(); //default constructor
    Node(int x, std::string y); //parameterized constructor
    Node* copyNode();  //copy constructor
    void print(); //prints the contents of the node
    //getters/setters
    Node* getPrev() {return prev;}
    void setPrev(Node * v) {prev = v;}
    Node* getNext() {return next;}
    void setNext(Node * v) {next = v;}
    int getValue() {return value;}
    void setValue(int v) {value = v;}
    std::string getName() {return name;}
    void setName(std::string v) {name = v;}

    ///these are currently unused
    std::vector<Node*> * getChildren() {return children;}
    void addChild(Node* node);

private:
    Node* prev;
    Node* next;
    int value;
    std::string name;
    ///currently unused
    std::vector<Node*>* children;

};

#endif
