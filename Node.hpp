#ifndef NODE
#define NODE


#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

class Node{
public:
    Node();
    Node(int x, std::string y);
    Node* copyNode(Node* v);
    void print();
    //getters/setters
    Node* getPrev() {return prev;}
    void setPrev(Node * v) {prev = v;}
    Node* getNext() {return next;}
    void setNext(Node * v) {next = v;}
    int getValue() {return value;}
    void setValue(int v) {value = v;}
    std::string getName() {return name;}
    void setName(std::string v) {name = v;}

    std::vector<Node*> * getChildren() {return children;}
    void addChild(Node* node);

private:
    Node* prev;
    Node* next;
    int value;
    std::string name;
    std::vector<Node*>* children;

};
#endif
