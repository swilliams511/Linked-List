/*
Scott Williams
simple array based class that uses:
-char* to save calling T's constructor on unused memory blocks in the array
-reinterpret_cast to change the char* pointer to a T* pointer
-placement new to call T's constructor when data is pushed
-placement delete to call T's destructor when data is popped
-Attempts to try using size_type and size_t

*/

#include "Array.hpp"
static const int defaultArrayCapacity = 10;  //if a value isn't specified, the array starts out being able to hold 10 things, it can grow


template <class T>
Array<T>::Array()
{
    numElements = 0;
    arrayCapacity = defaultArrayCapacity;
    staticArray = new char [sizeof(T) * arrayCapacity];
    test = new char* [sizeof(T) * 3];
    for (size_t i = 0; i < 3; ++i)
        test[i] = new char [sizeof(T) * 5];
}

template <class T>
Array<T>::Array(size_type inputCapacity)
{
    numElements = 0;
    arrayCapacity = inputCapacity;
    staticArray = new char [sizeof(T) * arrayCapacity];

}

template <class T>
Array<T>::~Array()
{
    clear();
    delete [] staticArray;
}


template <class T>
void Array<T>::push(const T& data)
{
    if(full())
    {
        std::cout << "Array is full\n";
        return;
    }
    new(reinterpret_cast<T*>(staticArray)+numElements) T(data);
    numElements++;

    new(reinterpret_cast<T**>(test)[0]) T(data);

}

template <class T>
void Array<T>::push(T&& data)
{
    if(full())
    {
        std::cout << "Array is full\n";
        return;
    }
    new(reinterpret_cast<T*>(staticArray)+numElements) T(std::move(data));
    numElements++;


}

template <class T>
void Array<T>::clear()
{
    while(!empty())
        pop();
}

template <class T>
void Array<T>::pop()
{
    if(empty())
        return;
    reinterpret_cast<T*>(staticArray)[numElements-1].~T(); //call T's destructor to match the placement new call push_back() made
    numElements--;                    //we use numElements to get the index for the back data, so decreasing this is sufficient
}

template <class T>
size_t Array<T>::size() const
{
    return numElements;
}

template <class T>
bool Array<T>::empty() const
{
    return numElements == 0;
}

template <class T>
bool Array<T>::full() const
{
    return numElements == arrayCapacity;
}

template <class T>
void Array<T>::print() const
{
    std::cout << "***start of array of size " << size() << " print***\n";
    for(size_type i = 0; i < numElements; ++i)
        reinterpret_cast<T*>(staticArray)[i].print();
    std::cout << "2d print array test??\n";

    reinterpret_cast<T**>(test)[0][0].print();

    std::cout << "end of print\n";
}
