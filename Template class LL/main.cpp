#include "Node.hpp"
#include "Node.cpp"
#include "Data.hpp"
#include <iostream>
#include <string>

int main()
{

    std::cout << "---start---\n";
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


    return 0;
}
