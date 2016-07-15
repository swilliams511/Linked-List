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


    return 0;
}
