#include "Node.hpp"
#include "DLList.hpp"
#include "TreeNode.hpp"
#include "AVLTree.hpp"
#include "HashTable.hpp"
#include "HashTableLP.hpp"
#include "Stack.hpp"
#include "GraphNode.hpp"
#include "Graph.hpp"
#include <fstream>

void makeGraph(Graph* graph, DLList* list);
void makeGraph2(Graph* graph, DLList* list);

int main()
{
///testing double linked list functions
    DLList* List = new DLList();
    List->setListName("Pokemon List");

    List->insert_front(1,"Bulbasaur");
    List->delete_node(1,"Bulbasaur");

    List->print();

    List->insert_front(1,"Bulbasaur");
    List->insert_front(2,"Ivysaur");
    List->insert_front(3,"Venusaur");
    List->insert_back(6,"Charizard");
    List->insert_back(4,"Charmander");
    List->insert_back(5,"Charmeleon");

    List->print(); //show the inserted nodes

    if(List->inList(5,"Charmeleon"))
        std::cout << "Charmeleon is in the list\n";
    else
        std::cout << "Charmeleon isn't in the list\n";

    if(List->getNode(4,"Charmander") != nullptr)
        std::cout << "test for getting node: " <<List->getNode(4,"Charmander")->getName() << "\n";
    if(List->getNode(3) != nullptr)
        std::cout << "test for getting node: " <<List->getNode(3)->getName() << "\n";
    if(List->getNode("Bulbasaur") != nullptr)
        std::cout << "test for getting node: " <<List->getNode("Bulbasaur")->getName() << "\n";

    List->delete_front();
    List->delete_back();

    List->print(); //show the first and last nodes were removed

    //reinserted deleted nodes from test
    List->insert_front(3,"Venusaur");
    List->insert_back(5,"Charmeleon");
    List->delete_node(6,"Charizard");
    List->print();
    std::cout << List->getKthNode(3)->getName() << " - kth node test\n";

    List->insert_back(6,"Charizard");
    List->insert_front(19,"Rattata");
    List->insert_front(24,"Arbok");
    List->insert_back(11,"Metapod");
    List->insert_front(7,"Squirtle");
    List->insert_front(54,"Psyduck");
    List->insert_back(97,"Hypno");
    List->insert_front(16,"Pidgey");

    List->sortList();
    List->print();

    List->insert_kth(4,151,"Mew");
    List->insert_kth(10,150,"Mewtwo");
    List->insert_kth(1,63,"Abra");
    List->insert_kth(16,57,"Primeape");
    List->insert_kth(18,50,"Diglett");
    List->print();

    List->sortList();
    List->reverse();
    List->delete_kth(14);
    List->insert_kth(14,5,"Charmeleon");
    List->print();
    //List->insert_back(5,"Charmeleon");

    DLList* newList = List->copy("copy list");
    //newList->print();

    DLList* pokeList = new DLList("List of all pokemon");
    pokeList->insert_from_file("kanto_alphabetical.txt");
    //pokeList->print();

    if(List->getNumNodes() == List->size())
        std::cout << "numNodes and size match!\n\n";

///testing avl tree functions
    AVLTree* tree = new AVLTree();
    tree->insert(List->getKthNode(1));
    tree->insert(List->getKthNode(2));
    tree->insert(List->getKthNode(3));
    tree->insert(List->getKthNode(4));
    tree->insert(List->getKthNode(5));
    tree->insert(List->getKthNode(6));
    tree->insert(List->getKthNode(7));
    tree->insert(List->getKthNode(8));
    tree->insert(List->getKthNode(9));
    tree->insert(List->getKthNode(10));
    tree->insert(List->getKthNode(11));
    tree->insert(List->getKthNode(12));
    tree->insert(List->getKthNode(13));
    tree->insert(List->getKthNode(14));
    tree->insert(List->getKthNode(15));
    tree->insert(List->getKthNode(16));
    tree->insert(List->getKthNode(17));
    std::cout << tree->insert(List->getKthNode(15)) << "\n\n"; //multiple insertion test
    tree->print();
    std::cout << tree->isMember(152) << "\n";
    std::cout << tree->isMember(151) << "\n";
    tree->remove(24);
    tree->print();
    AVLTree* newTree = tree->copy();
    newTree->print();
    for(int k = 1; k < tree->getNumNodes()+1; k++)
        std::cout << k << "th smallest is: " << tree->kthSmallest(k)->getDataNode()->getName() << "\n";
    tree->inOrderDump();

///testing chaining based hash table
    HashTable* table = new HashTable(13);
    table->insert(List->getKthNode(1));
    for(int i = 1; i < List->getNumNodes()+1; i++)
        table->insert(List->getKthNode(i));
    table->remove("Mewtwo");
    table->insert(List->getKthNode(2));
    table->print();
    std::cout << table->getNode("Mew")->getValue() << "\n";
    std::cout << table->size() << "\n";
    table->histogram();

///testing linear probe based hash table functions
    HashTableLP* tableLP = new HashTableLP(13);
    tableLP->insert(List->getKthNode(1));
    tableLP->print();
    for(int i = 1; i < List->getNumNodes()+1; i++)
        tableLP->insert(List->getKthNode(i));
    std::cout << tableLP->isMember("Dig") << "\n";
    tableLP->remove("Mew");
    tableLP->print();
    std::cout << tableLP->getNode("Mewtwo")->getValue() << "\n";


///testing stack
    Stack* stack = new Stack();
    stack->peek();
    stack->push(new GraphNode(List->getKthNode(1)));
    stack->push(new GraphNode(List->getKthNode(2)));
    stack->push(new GraphNode(List->getKthNode(12)));
    std::cout << stack->peek()->getDataNode()->getName() << "\n";
    stack->print();
    stack->pop();
    stack->print();
///testing Graph (and graphNode)
    Graph* graph = new Graph();
    makeGraph2(graph,pokeList);

    ///proves that a shared edge is added to both vertices
    std::cout << graph->getStartingNode()->getEdgeNodes()->at(0)->getDataNode()->getName() << "\n";
    std::cout << graph->getStartingNode()->getEdgeNodes()->at(0)->getEdgeNodes()->at(0)->getDataNode()->getName() << "\n";
    graph->dfs_itr_print();
    std::cout << graph->isMemberDFS(1) << "\n";
    std::cout << graph->isMemberDFS(999) << "\n";
    std::cout << graph->isMember(1) << "\n";
    std::cout << graph->isMember(999) << "\n";
    graph->dfs_itr_print();
    graph->bfs_print();
    //graph->removeVertex(1);
    //graph->removeVertex(0);
    //graph->setStartingNode(graph->getVertices()->at(0));
    //graph->dfs_itr_print();

///testing destructers
    delete stack;
    delete graph;
    delete tableLP;
    delete table;
    delete newTree;
    delete tree;
    delete pokeList;
    delete List;
    delete newList;


    return 0;
}



///makes a sample graph to match the file "sampleGraph.png"
void makeGraph(Graph* graph, DLList* list)
{
    for(int i = 1; i < 11; i++)
        graph->addVertex(list->getKthNode(i));

    graph->getVertices()->at(0)->addEdge(graph->getVertices()->at(1));
    //graph->getVertices()->at(1)->addEdge(graph->getVertices()->at(0));

    graph->getVertices()->at(0)->addEdge(graph->getVertices()->at(2));
    //graph->getVertices()->at(2)->addEdge(graph->getVertices()->at(0));

    graph->getVertices()->at(0)->addEdge(graph->getVertices()->at(3));
    //graph->getVertices()->at(3)->addEdge(graph->getVertices()->at(0));

    graph->getVertices()->at(3)->addEdge(graph->getVertices()->at(4));
    //graph->getVertices()->at(4)->addEdge(graph->getVertices()->at(3));

    graph->getVertices()->at(3)->addEdge(graph->getVertices()->at(6));
   // graph->getVertices()->at(6)->addEdge(graph->getVertices()->at(3));

    graph->getVertices()->at(4)->addEdge(graph->getVertices()->at(2));
    //graph->getVertices()->at(2)->addEdge(graph->getVertices()->at(4));

    graph->getVertices()->at(6)->addEdge(graph->getVertices()->at(5));
    //graph->getVertices()->at(5)->addEdge(graph->getVertices()->at(6));

    graph->getVertices()->at(5)->addEdge(graph->getVertices()->at(7));
    //graph->getVertices()->at(7)->addEdge(graph->getVertices()->at(5));

    graph->getVertices()->at(7)->addEdge(graph->getVertices()->at(8));
    //graph->getVertices()->at(8)->addEdge(graph->getVertices()->at(7));

    graph->getVertices()->at(8)->addEdge(graph->getVertices()->at(9));
    //graph->getVertices()->at(9)->addEdge(graph->getVertices()->at(8));

}



///makes a sample graph to match the file "sampleGraph2.png"
void makeGraph2(Graph* graph, DLList* list)
{
    for(int i = 1; i < 18; i++)
        graph->addVertex(list->getKthNode(i));

    graph->getVertices()->at(0)->addEdge(graph->getVertices()->at(1));
    graph->getVertices()->at(0)->addEdge(graph->getVertices()->at(2));
    graph->getVertices()->at(0)->addEdge(graph->getVertices()->at(16));
    graph->getVertices()->at(1)->addEdge(graph->getVertices()->at(5));
    graph->getVertices()->at(1)->addEdge(graph->getVertices()->at(9));
    graph->getVertices()->at(2)->addEdge(graph->getVertices()->at(4));
    graph->getVertices()->at(2)->addEdge(graph->getVertices()->at(8));
    graph->getVertices()->at(2)->addEdge(graph->getVertices()->at(3));
    graph->getVertices()->at(2)->addEdge(graph->getVertices()->at(14));
    graph->getVertices()->at(3)->addEdge(graph->getVertices()->at(6));
    graph->getVertices()->at(3)->addEdge(graph->getVertices()->at(13));
    graph->getVertices()->at(5)->addEdge(graph->getVertices()->at(7));
    graph->getVertices()->at(7)->addEdge(graph->getVertices()->at(12));
    graph->getVertices()->at(8)->addEdge(graph->getVertices()->at(14));
    graph->getVertices()->at(9)->addEdge(graph->getVertices()->at(12));
    graph->getVertices()->at(10)->addEdge(graph->getVertices()->at(11));
    graph->getVertices()->at(11)->addEdge(graph->getVertices()->at(16));
    graph->getVertices()->at(13)->addEdge(graph->getVertices()->at(14));
    graph->getVertices()->at(14)->addEdge(graph->getVertices()->at(15));

}



