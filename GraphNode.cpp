#include "GraphNode.hpp"

GraphNode::GraphNode(Node* node)
{
    dataNode = node;
    edgeNodes = new std::vector<GraphNode*>;
    visited = false;  //by default the node isnt visited
}

GraphNode::~GraphNode()
{
    delete edgeNodes; //only need to delete the vector, not the nodes it points to
}

//an edge is shared between two nodes, thus both nodes need to point to each other in their edgeNodes
void GraphNode::addEdge(GraphNode* node)
{
    node->edgeNodes->push_back(this); //the passed node gets the calling node added to its list
    edgeNodes->push_back(node); //adds the passed node to the edge list
}
