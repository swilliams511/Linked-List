#ifndef _G
#define _G

#include "GraphNode.hpp"
#include "Stack.hpp"

//a graph holds a collection of graphNodes
//possible to implement using a linked list, might be better for removing nodes
class Graph{
public:
    Graph();
    ~Graph();

    bool addVertex(Node* node); //add a new vertex point to the graph
    bool removeVertex(int nodeIndex); //precondition: the selected node when removed must still be 1 discontinuous graph
    bool isMember(int nodeIndex);
    bool isMemberDFS(int nodeIndex); //much less efficient since we have a vector with nodes, just showing an application of dfs

    //getters/setters
    GraphNode* getStartingNode() {return startingNode;}
    void setStartingNode(GraphNode* v) {startingNode = v;}
    std::vector<GraphNode*>* getVertices() {return vertices;}

    void dfs_itr_print(); //using depth first traversal (iterative), print the graph

private:
    GraphNode* startingNode; //this is the first node traversal will use for the graph. by default it is first inserted node
    std::vector<GraphNode*>* vertices; //holds the nodes in the graph


};

#endif // _G
