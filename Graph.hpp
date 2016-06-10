#ifndef _G
#define _G

#include "GraphNode.hpp"
#include "Stack.hpp"

//a graph holds a collection of graphNodes
class Graph{
public:
    Graph();
    ~Graph();

    bool addVertex(Node* node); //add a new vertex point to the graph

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
