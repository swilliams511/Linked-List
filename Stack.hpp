#ifndef _STACK
#define _STACK

#include <vector>
#include "GraphNode.hpp"

class Stack{
public:
    Stack();
    ~Stack();

    void push(GraphNode* node); //storing an element on the stack
    void pop();                 //removing an element from the stack
    GraphNode* peek();          //get the top data element from the stack
    bool isEmpty();             //check if stack is empty
    int size();                 //returns the size of the stack

    void print();



private:
    std::vector<GraphNode*>* nodeStack;  //datatype is graphNode for this stack


};








#endif // _STACK
