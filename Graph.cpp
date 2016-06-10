#include "Graph.hpp"

Graph::Graph()
{
    vertices = new std::vector<GraphNode*>;
    startingNode = nullptr;   //by default, the graph starts with no nodes
}

Graph::~Graph()
{
    for(unsigned i = 0; i < vertices->size(); i++)
        delete vertices->at(i);              //calls the destructor for each graphNode stored in the vector
    delete vertices;                         //deletes the vector
}

bool Graph::addVertex(Node* node)
{
    if(node == nullptr) //if we pass in an empty node..
        return false;   //dont add it, we dont need it
    GraphNode* gNode = new GraphNode(node); //put the node into a new instance of a graphNode
    gNode->setNodeNum(vertices->size());
    vertices->push_back(gNode);           //add it to the array of vertex nodes
    if(startingNode == nullptr)        //if this is the first node to be added
        startingNode = gNode;         //let this be the default starting node for traversal
    return true;                      //tell us the insert happened
}

//iterative dfs
void Graph::dfs_itr_print()
{
    if(startingNode == nullptr) //checks if the graph is empty
    {
        std::cout << "Graph is empty\n";
        return;                 //exit if it is
    }
    std::cout << "***Depth first search print traversal of nodes***\n";
    Stack* stack = new Stack(); //creates a new stack to hold nodes in the graph
    stack->push(startingNode);  //the first node we look at is the starting node, the stack now has 1 element
    while(!stack->isEmpty())    //once the stack is empty, we have looked at each node
    {
        GraphNode* node = stack->peek(); //get the top node on the stack
        stack->pop();                    //one we get it, remove it
        if(!node->getVisited())          //if we haven't visited the node yet
        {                                //print that we are visiting it
            std::cout << "---In node: " << node->getNodeNum() << " - " << node->getDataNode()->getName() << "---\n";
            node->setVisited(true);      //mark it as visited so we dont go to it again
        }
        std::cout << "Edges: ";
        for(unsigned i = 0; i < node->getEdgeNodes()->size(); i++) //looks at each one of the edges of the current node
        {
            std::cout <<  "("  << node->getEdgeNodes()->at(i)->getNodeNum()
                <<  "," << node->getEdgeNodes()->at(i)->getDataNode()->getName() << ") ";
            if(!node->getEdgeNodes()->at(i)->getVisited()) //if the node's current edge hasnt been visited
            {
                stack->push(node->getEdgeNodes()->at(i)); //add it to the stack
            }
        }
        std::cout << "\n";
    }
    //at this point all nodes have been traversed
    for(int i = 0; i < vertices->size(); i++) //mark all the nodes as not visited now that the function
        vertices->at(i)->setVisited(false);   //is done so the nodes can be revisited in other calls

    std::cout << "\n";
    delete stack;  //since the function is done, kill the stack to release memory
}
