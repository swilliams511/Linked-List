#ifndef _deque
#define _deque

#include <iostream>

template <class T>
class Deque{
public:
    Deque();
    ~Deque();

    T& operator[](const int index) const;   //access the kth element of a vector. RANGE: [0,size()-1]
    T& at(const int index) const;           //if using a pointer, use this    RANGE: [0,size()-1]
    int size() const;
    bool empty() const;

    void push_back(const T& data);      //copy-based function to put new data at the back
    void push_back(T&& data);           //move-based function to put new data at the back
    void push_front(const T& data);     //copy-based function to put new data at the front
    void push_front(T&& data);          //move-based function to put new data at the front


    void print() const;
    void print_index() const;
private:
    T** dynamicArray;
    int arrayCapacity;
    int numElements;

    int first_map_index;
    int last_map_index;
    int empty_left;
    int empty_right;

    void first_insert(const T& data); //copy insert based
    void first_insert(T&& data); //move insert based
    void resize_back();
    void resize_front();




};






#endif // _deque
