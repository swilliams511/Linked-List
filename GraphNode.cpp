#include "GraphNode.hpp"

GraphNode::GraphNode(Node* node)
{
    dataNode = node;
    edgeNode = new std::vector<GraphNode*>;
}

GraphNode::~GraphNode()
{
    delete edgeNode; //only need to delete the vector, not the nodes it points to
}
