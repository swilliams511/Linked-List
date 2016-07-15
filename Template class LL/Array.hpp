#ifndef _a
#define _a
#include <iostream>

template <class T>
class Array{
    using size_type = unsigned int;
public:
    Array();
    Array(size_type inputCapacity);
    //could imp copy ctr, move ctr, copy assign, move assign
    ~Array();
    void push(const T& data);
    void push(T&& data);
    void pop();
    void clear();

    size_type size() const;
    bool empty() const;
    bool full() const;

    void print() const;
private:
    char* staticArray;
    char** test;
    size_type arrayCapacity;
    size_type numElements;


};



#endif // _a
