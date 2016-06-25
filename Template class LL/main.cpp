#include "Node.hpp"
#include "Node.cpp"
#include "Data.hpp"
#include "LinkedList.hpp"
#include "LinkedList.cpp"
#include "Vector.hpp"
#include "Vector.cpp"
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
//    list->getHead()->print();
///non-class datatype test
    LinkedList<int>* list1 = new LinkedList<int>;
    list1->push_front(12121);
    list1->print_nonClass();

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
///data's ==/!= operator test
    Data comp(151,"Mew");                                      //expected results for data's == operator
//    std::cout << (comp == list->getHead()->getData()) << "\n"; //true
  //  std::cout << (comp != list->getHead()->getData()) << "\n"; //false
   // std::cout << (comp == list->getTail()->getData()) << "\n"; //false
   // std::cout << (comp != list->getTail()->getData()) << "\n"; //true

///node assignment test
   // std::cout << "head vs tail\n";
//    Node<Data>* hnode = list->getHead();
  //  Node<Data>* tnode = list->getTail();
//    hnode->print();
 //   tnode->print();
  //  *hnode = * tnode; //the node's data head points to becomes the data the node's data tail points to
 //   std::cout << "head vs tail after assignment\n";
  //  hnode->print();
   // tnode->print();
   // std::cout << "checking list contents after assignment test\n";
   // list->print(); //the data that head points to was changed, so we see that here. the pointer wasn't changed tho
///link copy test
    LinkedList<Data>* copyList = new LinkedList<Data>(*list);
    copyList->print();
    delete copyList;
///----
    list->pop_front();
    list->push_back(Data(151,"Mew"));
    list->print();
    std::cout << list->isMember(Data(151,"Mew")) << "\n";
    std::cout << "num  " << list->size() << "\n";
    list->insert(Data(2,"Ivysaur"),2);
    list->print();
    Data data = list->at(2);
    data.print();
    list->push_back(Data(3,"Venasaur"));
    list->push_front(Data(149,"Dragonite"));
    list->insert(Data(147,"Dratini"),3);
    list->print();
    list->sort();
    list->print();
    list->at(3).print(); //with 7 nodes, runtimes are 1,2,3,4,3,2,1. Thus worst case runtime is ceiling(numNomes/2)
    list->insert(Data(16,"Pidgey"),2);
    list->insert(Data(17,"Pidgeotto"),6);
    list->print();
    ///both removes tested for each of the 4 nodes in "list" works as desired
///implemented so if the last data is say Data(151,"Mew"), first remove(const T&) is called, then remove(int), then pop_back()
///reduces repeated code, but checks if the list is empty each function call (inexpensive luckily...)
///however, the worst case run time for both removes is O(n) thus in this case code duplication is should be overall cheaper
///for remove. Will leave it as is though because it looks nice ^_^ (like quite a bit better and easier to read...)

    delete list;




    return 0;
}
