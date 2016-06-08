#ifndef _GN
#define _GN

#include "Node.hpp"
class GraphNode{
public:
    GraphNode(Node* node);
    ~GraphNode();

    Node* getDataNode() {return dataNode;}

private:
    Node* dataNode;
    std::vector<GraphNode*>* edgeNode;



};








#endif // _GN
