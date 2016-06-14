#include "Node.hpp"
#include "Node.cpp"
#include "Data.hpp"
#include "LinkedList.hpp"
#include <iostream>
#include <string>
#include <vector>

int main()
{

    std::cout << "---start of node test---\n";
    /*
///analysis of "Data" object and start of making a "Node"
    Data test(151,"Mew"); //calls data's paraterized constructor
    std::cout << "------\n";
    Data otherTest = Data(150,"Mewtwo"); //also calls data's paraterized constructor
    std::cout << "------\n";
    Node<Data>* node = new Node<Data>; //first calls data's constructor, then Node's constructor
    std::cout << "------\n";
    node->setData(test);  //data's copy constructor called, then assignment, then copy again, then destructor twice for both of data's old elements
    std::cout << "------\n";
    std::cout << node->getData().getName()<< "\n"; //first copy constructor is called, then cout, then data's destructor is called after printing since cout's scope is finished
    std::cout << "------\n";
    std::cout << node->getData().getValue() << "\n"; //same as getName in cout
    std::cout << "------\n";
    std::cout << (otherTest > test) << "\n";
    std::cout << "------\n";
    std::cout << (test > otherTest) << "\n";
    std::cout << "------\n";
    otherTest = test; //same data calls as setData
    std::cout << "------\n";
    std::cout << test.getName() << "\n"; //nothing special called
    std::cout << "------\n";



    std::cout << "Next node...\n";
    Node<std::string>* node2 = new Node<std::string>;
    node2->setData("hi thar");
    std::cout << node2->getData() << "\n";

    Node<int>* node3 = new Node<int>;
    node3->setData(12);
    std::cout << node3->getData() << "\n";
    std::cout << "------\n";

    */
///default way of constructing a node of type "Data"
    Node<Data>* node = new Node<Data>(Data(1,"Bulbasaur"));
    std::cout << "------\n";

    std::cout << node->getData().getName() << "\n"; //this way has 1 copy call and one destru call
    node->print();                                  //this way has no calls (besides Data's print), less expensive...?

    delete node;

    std::cout << "---start of List test---\n";
///custom object list test
    LinkedList<Data>* list = new LinkedList<Data>;
    list->push_front(Data(150,"Mewtwo"));
    std::cout << list->size() << "\n";
    list->getHead()->print();

///non-class datatype test
    LinkedList<int>* list1 = new LinkedList<int>;
    list1->push_front(12121);
    std::cout << list1->getHead()->getData() << "\n";

    list->push_front(Data(151,"Mew"));
    list->push_back(Data(1,"Bulbasaur"));
    delete list1;

///LL assignment operator test
    LinkedList<Data>* list3 = new LinkedList<Data>;
    list3->push_front(Data(154,"Mewtwo"));
    std::cout << "------\n";
    *list3 = *list;           //must dereference the pointers for assignment to work
    std::cout << "------\n";
    list3->print();
    delete list3;
///-------




    delete list;
    return 0;
}
