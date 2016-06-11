#ifndef _GNLL
#define _GNLL

#include "DLList.hpp"
//a graphNode is a standard node, but with properties that let it be put into a graph. Similar to how a tree
//node lets a standard node enter a tree
class GraphNodeLL{
public:
    GraphNodeLL(Node* node);
    ~GraphNodeLL();

    void addEdge(GraphNode* node); //adds a vertex graphNode that connects to this node

    //getters/setters
    Node* getDataNode() {return dataNode;}
    std::vector<GraphNode*>* getEdgeNodes() {return edgeNodes;}
    bool getVisited() {return visited;}
    void setVisited(bool v) {visited = v;}
    int getNodeNum() {return nodeNum;}
    void setNodeNum(int v) {nodeNum = v;}

private:
    Node* dataNode;                     //holds the data for the node
    DLList* edgeNodes; //hold pointers to each of the other GraphNodes that share an edge
    bool visited;                       //used to check if the node has been visited in traversal
    int nodeNum; //a simple index to match sampleGraph.png
};

#endif // _GNLL
