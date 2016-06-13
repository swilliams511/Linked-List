#include "Graph.hpp"
#include <queue>

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


bool Graph::isMember(int nodeIndex)
{
    for (unsigned i = 0; i < vertices->size(); i++)
        if(vertices->at(i)->getNodeNum() == nodeIndex)
            return true;
    return false;
}

//iterative dfs lookup
bool Graph::isMemberDFS(int nodeIndex)
{
    if(startingNode == nullptr) //checks if the graph is empty
    {
        std::cout << "Graph is empty\n";
        return false;                 //exit if it is
    }
    Stack* stack = new Stack(); //creates a new stack to hold nodes in the graph
    stack->push(startingNode);  //the first node we look at is the starting node, the stack now has 1 element
    while(!stack->isEmpty())    //once the stack is empty, we have looked at each node
    {
        GraphNode* node = stack->peek(); //get the top node on the stack
        stack->pop();                    //one we get it, remove it
        if(!node->getVisited())          //if we haven't visited the node yet
        {
            if(node->getNodeNum() == nodeIndex) //if the node has been found
            {
                while(!stack->isEmpty()) //we have found the node and are done
                    stack->pop();        //empty the stack
                delete stack;            //and delete it
                for(unsigned i = 0; i < vertices->size(); i++) //mark all the nodes as not visited now that the function
                    vertices->at(i)->setVisited(false);   //is done so the nodes can be revisited in other calls
                return true; //tell us the node is found
            }
            //if the node wasn't found...
            node->setVisited(true);      //mark it as visited so we dont go to it again


            for(unsigned i = 0; i < node->getEdgeNodes()->size(); i++) //looks at each one of the edges of the current node
                if(!node->getEdgeNodes()->at(i)->getVisited()) //if the node's current edge hasnt been visited
                    stack->push(node->getEdgeNodes()->at(i)); //add it to the stack
        }
    }
    //at this point all nodes have been traversed and the node wasnt found
    for(unsigned i = 0; i < vertices->size(); i++) //mark all the nodes as not visited now that the function
        vertices->at(i)->setVisited(false);   //is done so the nodes can be revisited in other calls
    delete stack;  //since the function is done, kill the stack to release memory
    return false; //tell us the node wasn't found
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
    }
    //at this point all nodes have been traversed
    for(unsigned i = 0; i < vertices->size(); i++) //mark all the nodes as not visited now that the function
        vertices->at(i)->setVisited(false);   //is done so the nodes can be revisited in other calls

    std::cout << "\n";
    delete stack;  //since the function is done, kill the stack to release memory
}

void Graph::bfs_print()
{
    if(startingNode == nullptr) //if the list is empty
        return;                 //dont print anything
    std::queue<GraphNode*> q;   //makes a queue to hold nodes
    q.push(startingNode);       //puts the starting node into the queue
    while(!q.empty())           //as long as the queue isn't empty
    {
        GraphNode* node = q.front(); //get the node at the front of the queue
        q.pop();                     //then remove it from the queue
        if(!node->getVisited())      //if the node hasnt been visited, print were in it
        {
            std::cout << "---In node: " << node->getNodeNum() << " - " << node->getDataNode()->getName() << "---\n";
            node->setVisited(true);  //set it to visited

            std::cout << "Edges: ";
            for(unsigned i = 0; i < node->getEdgeNodes()->size(); i++) //loop through the current node's edges
            {
                GraphNode* nnode = node->getEdgeNodes()->at(i); //temp var to make code easier to read
                std::cout <<  "("  << nnode->getNodeNum()
                    <<  "," << nnode->getDataNode()->getName() << ") ";
                if(!nnode->getVisited())                        //if the edge hasn't been visited
                    q.push(nnode);                              //add it to the queue
            }
            std::cout << "\n";
        } //once the queue is empty, the graph has been traversed
    }
    for(unsigned i = 0; i < vertices->size(); i++) //marks the nodes as unvisited since the search is done
        vertices->at(i)->setVisited(false);
    std::cout << "\n";
}






//Don't use this. Simpler to just make a new graph lol
//proof of concept if anything...
bool Graph::removeVertex(int nodeIndex)
{
    ///first checks if index is in vertex array
    ///then check all edge array for all vertex elements and remove the indexed node from them
    ///remove the indexed node from the vertex array
    ///vertices->erase(vertices->begin()+k); will remove the kth element of a vector [0,size()-1]
    ///***Assumes the graph will NOT become disconnected post removal***
    if(!isMember(nodeIndex) || startingNode == nullptr) //checks if the index isnt there or there is no graph
        return false;                                   //cant remove it
    for(int i = 0; i < vertices->size(); i++)          //look through each of the vertices
    {
        GraphNode* node = vertices->at(i);          //temp variable to make code easier to read
        for(int j = 0; j < node->getEdgeNodes()->size();j++) //given a specific vertex, loop through its edges
        {
            GraphNode* nnode = node->getEdgeNodes()->at(j);   //temp variable to make code easier to read
            if(nodeIndex == nnode->getNodeNum())            //if an edge matches the index
            {

                node->getEdgeNodes()->erase(node->getEdgeNodes()->begin()+j); //remove it from the edge list since it wont be there anymore
                break; //escape the for loop since size has decreased and the node would only be in there once
            }
        }
    }
    for(int i = 0; i < vertices->size(); i++) //again loop through each vertex
    {
        if(nodeIndex == vertices->at(i)->getNodeNum()) //find the vertex we wish to remove
        {
            GraphNode* node = vertices->at(i); //temp variable to make code easier to read
            vertices->erase(vertices->begin()+i); //remove it from the vector
            if(node == startingNode)              //if it was the starting vertex
            {
                    startingNode = vertices->at(0); //put the start at whatever the new first element of the vector is (assumes there is at least 1 element)
            }
            delete node;                           //matching delete for new
            return true; //escape the loop and say we erased the node
            ///could also first declare a GraphNode var, loop through the vertices, set the remove node to the
            ///one that was declared, erase it, then loop through the modified vertices to erase the node
            ///from each one of each vertex's edges, then delete the GraphNode
        }
        ///could have a dfs search that looks for vertices equal to vertices->size() and if false, then graph
        ///is disconnected and don't remove the node... just a note :)
    }
}
