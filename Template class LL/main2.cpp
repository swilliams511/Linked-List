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
    std::cout << "pre inserting first data\n"; //before push_back() starts, data's constructor is called
    array.push_back(Data(151,"Mew")); //the passed data's copy constructor is called inside of push_back)_
    std::cout << "post inserting first data\n"; //after push_back() ends data's destructor is called
    array.print();
    std::cout << "pre removing first data\n";
    array.pop_back();
    std::cout << "post removing first data\n";
    array.print();


///copy constructor and assignment operator test
    //Vector<Data> test;
    //std::cout << "---copy/assignment should be called\n";
    //test = array; //copy swap implementation has Vector's destructor called on the copy of array
    //std::cout << "------\n";
    //test.print();

    array.push_back(Data(151,"Mew"));
    array.push_back(Data(150,"MewTwo"));
    array.push_back(Data(1,"Bulbasaur"));
    array.push_back(Data(25,"Pikachu"));
    array.push_back(Data(11,"Metapod"));
    array.push_back(Data(43,"Oddish"));
    array.push_back(Data(50,"Diglett"));
    array.push_back(std::move(Data(89,"Muk")));
    array.push_back(Data(149,"Dragonite"));
    array.push_back(Data(148,"Dragonair"));
    array.print();
    Data data1(1,"bulb");
    Data data2(2,"ivy");
    data1 = data2;
    data1.print();
    data2.print();
    std::cout << "iterator test\n";
    array.begin()->print();
    array.end()->print();
    array.print_iterator();

    std::cout << "better insert start\n";
    array.push_back(Data(2,"Ivysaur"));
    array.push_back(Data(3,"Ivysaur"));

    array.print();

    array.pop_back();

    Vector<int> intV;
    intV.push_back(8);
    std::cout << intV[0] << "\n";


    return 0;
}
