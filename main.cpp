#include "Node.hpp"
#include "DLList.hpp"
#include "TreeNode.hpp"
#include "AVLTree.hpp"
#include <fstream>

int main()
{
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

    delete newTree;
    delete tree;
    delete pokeList;
    delete List;
    delete newList;


    return 0;
}
