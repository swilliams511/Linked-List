#include "Node.hpp"
#include "Node.cpp"
#include "Data.hpp"
#include "LinkedList.hpp"
#include "LinkedList.cpp"
#include "Vector.hpp"
#include "Vector.cpp"
#include "Deque.hpp"
#include "Deque.cpp"
#include "Array.hpp"
#include "Array.cpp"
#include <iostream>
#include <string>

int main()
{
    /*
    Deque<Data> dq;
    dq.push_back(Data(151,"Mew"));
    dq.print();
    dq.push_back(Data(150,"Mewtwo"));
    dq.print();
    dq.push_back(Data(1,"Bulbasaur"));
    dq.push_back(Data(2,"Ivysaur"));
    dq.push_back(Data(2,"Ivysaur"));
    dq.push_back(Data(2,"Ivysaur"));
    dq.push_back(Data(2,"Ivysaur"));
    dq.push_back(Data(2,"Ivysaur"));
    dq.push_back(Data(2,"Ivysaur"));
    dq.push_back(Data(2,"Ivysaur"));



    dq.print();
    dq.print_index();
    dq.push_front(Data(89,"Muk"));
    dq.push_front(Data(92,"Gastly"));
    dq.push_front(Data(63,"Abra"));

    dq.print();
    dq.print_index();

    Array<Data> array;
    Data d(151,"mew");
    array.push(d);
    array.print();
*/
    Deque<Data> dq;
    dq.push_back(Data(4,"bulb"));
    dq.push_back(Data(2,"ivy"));
    dq.push_back(Data(3,"other"));
    dq.push_back(Data(6,"other"));
    dq.push_back(Data(8,"other"));
    dq.push_back(Data(9,"other"));
    dq.push_back(Data(8,"other"));
    dq.push_back(Data(7,"other"));
    dq.push_back(Data(6,"other"));
    dq.push_back(Data(5,"other"));
    dq.push_back(Data(4,"other"));
    dq.print();

    std::cout << "ehrstghdxghdfhdghdfghdfhdfghdh\n";
    Deque<Data> dq2(dq);
    dq2.push_back(Data(12,"eek"));
    dq2.print();
    dq2.push_front(Data(123,"hi"));
    dq2.push_front(Data(122,"hi"));
    dq2.push_front(Data(121,"hi"));
    dq2.push_front(Data(120,"hi"));
    dq2.push_front(Data(119,"hi"));
    dq2.push_front(Data(118,"hi"));
    dq2.push_front(Data(117,"hi"));
    dq2.push_front(Data(116,"hi"));
    dq2.push_front(Data(115,"hi"));





    dq2.print();

    dq2.begin()->print();
    Data t = *dq2.begin();
    t.print();
    Deque<Data>::Iterator itr = dq2.begin();
    itr += 10;
    itr->print();


    std::cout << "for loop iterator test\n";
    for(Deque<Data>::Iterator it = dq2.begin(); it != dq2.end(); ++it)
        it->print();
    dq2.print();

    for(Deque<Data>::Iterator it = dq2.rbegin(); it != dq2.rend(); --it)
        it->print();

    dq2.insert(1,Data(69,"lol wut"));
    dq2.insert(19,Data(124,"Mr mime"));

    dq2.print();
    dq2.erase(19);
    dq2.erase(1);
    dq2.print();

    return 0;
}
