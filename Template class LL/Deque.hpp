#ifndef _deque
#define _deque

#include <iostream>




template <class T>
class Deque{
    static const size_t chunkCapacity = 5;  //for this implementation, this must be an odd number. Starting with a small number for testing
    static const size_t startMapCapacity = 3; //we'll just start out with 3 inner array for now... this can grow
    const float resizeConstant = 2;    //where mapCapacity *= resizeConstant in resize

public:
    Deque();
    ~Deque();

    T& operator[](const size_t index) const;   //access the kth element of a vector. RANGE: [0,size()-1]
    T& at(size_t index) const;           //if using a pointer, use this    RANGE: [0,size()-1]
    size_t size() const;
    bool empty() const;

    void push_back(const T& data);      //copy-based function to put new data at the back
    void push_back(T&& data);           //move-based function to put new data at the back
    void push_front(const T& data);     //copy-based function to put new data at the front
    void push_front(T&& data);          //move-based function to put new data at the front

    void pop_back();
    void clear();


    void print() const;
    void print_index() const;
private:
    char** map;
    size_t mapCapacity;
    size_t numElements;

    size_t first_map_index;
    size_t last_map_index;
    size_t empty_left;
    size_t empty_right;

    void first_insert(const T& data); //copy insert based
    void first_insert(T&& data); //move insert based
    void resize_back();
    void resize_front();




};






#endif // _deque
