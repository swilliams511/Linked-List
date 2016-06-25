/* Vector.hpp
By: Scott Williams
implementation based off std::vector. Done to practice maintaining c++ dynamic arrays
read function and implementation comments for more information
*/
#ifndef _v
#define _v

#include <iostream>

template <class T>
class Vector{
public:
///structors
    Vector();                           //default constructor
    Vector(int startingSize);           //parameterized constructor
    ~Vector();                          //destructor
    Vector(const Vector& otherVector);  //copy constructor
///operator overloads
    Vector<T>& operator=(Vector otherVector); //assignment operator
    T& operator[](int index);                 //access the kth element of a vector. RANGE: [0,size()-1]
///member functions
    T& at(int index);              //if using a pointer to a vector, use this    RANGE: [0,size()-1]
    int size();                    //getter for numElements; returns the number of elements in the vector
    void push_back(const T& data); //inserts the data at the back of the vector. Calls resize() if the vector is full
    void pop_back();               // "removes" the data at the back of the vector
    bool empty();                  //returns true if the vector is empty
    void resize(int newCapacity);  //copies the data from calling vector to a new vector with the new capacity
    int capacity();                //getter for how many elements the vector can currently hold (push_back can change this via resize if space is needed)
    void clear();                  //removes all data from the array
///debug funtions
    void print();

private:
    T* dynamicArray;   //the array storing the data for vector
    int numElements;   //the number of elements the vector currently holds
    int arrayCapacity; //the maximum number of elements the vector can hold
///debug variables
    int newCalls;
    int delCalls;

};






#endif // _v
