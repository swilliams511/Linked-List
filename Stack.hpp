#ifndef _STACK
#define _STACK

#include <vector>
#include "GraphNode.hpp"

//standard stack data structure, using a dynamic array (vector) to hold nodes (possible to use linked list)
//and holding datatype "graphNode" which is a standard node with graph functions/variables
class Stack{
public:
    Stack();
    ~Stack();

    void push(GraphNode* node); //storing an element on the stack
    void pop();                 //removing an element from the stack
    GraphNode* peek();          //get the top data element from the stack
    bool isEmpty();             //check if stack is empty
    int size();                 //returns the size of the stack

    void print();          //prints from the top of the stack down to the bottom


private:
    std::vector<GraphNode*>* nodeStack;  //datatype is graphNode for this stack

};

#endif // _STACK
