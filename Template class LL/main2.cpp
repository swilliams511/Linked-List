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
    std::cout << "Creating vector\n";
    Vector<Data> array;
    std::cout << "pre inserting first data\n";
    array.push_back(Data(151,"Mew"));
    std::cout << "post inserting first data\n";
    array.push_back(Data(152,"Mew"));
    array.push_back(Data(1525,"Mew"));
    array.push_back(Data(1425,"Mew"));
    array.push_back(Data(154,"Mew"));
    array.push_back(Data(125,"Mew"));
    array.push_back(Data(5,"Mew"));
    array.push_back(Data(124,"Mew"));
    array.push_back(Data(55,"Mew"));
    array.push_back(Data(77,"Mew"));
    array.push_back(Data(34,"Mew"));
    array.push_back(Data(77,"Mew"));
    array.push_back(Data(34,"Mew"));
    array.push_back(Data(13,"Mew"));
    array.push_back(Data(34,"Mew"));
    array.push_back(Data(3333,"Mew"));

///copy constructor and assignment operator test
    Vector<Data> test = array;
    std::cout << "---pop_back test\n---";
    array.pop_back();
    std::cout << "------\n";
    test = array;
    test.print();
    //array.print();
    test.clear();

    std:: cout << test.empty() << "\n";


    return 0;
}
