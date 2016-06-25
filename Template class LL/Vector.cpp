/* Vector.cpp
By: Scott Williams
implementation based off std::vector. Done to practice maintaining c++ dynamic arrays
read function and implementation comments for more information
*/

#include "Vector.hpp"

static const int defaultCapacity = 10;  //if a value isn't specified, the array starts out being able to hold 10 things, it can grow

//default constructor
template <class T>
Vector<T>::Vector()
{
    newCalls = 0;
    delCalls = 0;
    arrayCapacity = defaultCapacity;      //initialize the variable to the default value
    dynamicArray = new T [arrayCapacity]; //create a new instance of an array that holds data of type "T" with default 10 capacity
    newCalls++;
    numElements = 0;                      //naturally the array starts out empty
}

//parameterized constructor
template <class T>
Vector<T>::Vector(int startingSize)
{
    newCalls = 0;
    delCalls = 0;
    if(startingSize < 1)                //makes sure the initial capacity starts out valid
        startingSize = defaultCapacity;
    arrayCapacity = startingSize;
    dynamicArray = new T [arrayCapacity];
    newCalls++;
    numElements = 0;
}

//destructor
template <class T>
Vector<T>::~Vector()
{
    ///NOTE: if we have a vector of pointers, like Vector<int*>, an outside function (like in main) needs to
    ///iterate through the vector and call delete on each pointer. Then this destructor should
    ///be called after. Memory leak will occur if the application using the data structure
    ///doesn't delete its pointers
    std::cout << "in vector destructor\n";
    delete [] dynamicArray;
    delCalls++;
    std::cout << "New calls: " << newCalls << " Del calls: " << delCalls <<   "\n";
}

//copy constructor
template <class T>
Vector<T>::Vector(const Vector& otherVector)
{
    newCalls = 0;
    delCalls = 0;
    std::cout << "in copy constructor\n";
    numElements = 0; //initialize the new vector as empty
    arrayCapacity = otherVector.arrayCapacity;
    dynamicArray = new T [arrayCapacity]; //create a new array of type T holding the passed vectors capacity
    newCalls++;
    for(int i = 0; i < otherVector.numElements; i++) //for each value in the passed array
        push_back(otherVector.dynamicArray[i]); //insert it into the newly created array
}

//assignment operator
template <class T>
Vector<T>& Vector<T>::operator=(Vector otherVector)
{
    std::cout << "in assignment operator\n";

    std::swap(dynamicArray,otherVector.dynamicArray);
    std::swap(numElements,otherVector.numElements);
    std::swap(arrayCapacity,otherVector.arrayCapacity);
    std::swap(newCalls,otherVector.newCalls);
    std::swap(delCalls,otherVector.delCalls);
    //while(numElements > 0)
     //   pop_back();
    //for (int i = 0; i < otherVector.numElements; i++)
     //   push_back(otherVector.dynamicArray[i]);
    return *this;
}

//bracket operator
template <class T>
T& Vector<T>::operator[](int index)
{
    if(index < 0 || index > numElements-1) //will give undefined behavior if empty, returns 0th index
    {                                      //element if the index is out of range [0,size()-1]
        std::cout << "[" << index << "] out of range, returning [0]\n";
        return dynamicArray[0];
    }
    return dynamicArray[index];
}

//Returns the data at the index, given it't in range. O(1) run time
template <class T>
T& Vector<T>::at(int index)
{
    if(index < 0 || index > numElements-1)
    {
        std::cout << "[" << index << "] out of range, returning [0]\n";
        return dynamicArray[0];
    }
    return dynamicArray[index];
}

//copies the data in the vector to a new one with a different capacity
template <class T>
void Vector<T>::resize(int newCapacity)
{
    std::cout << "resizing vector...\n";
    if(arrayCapacity == newCapacity) //if the new size of the array is the same
        return; //dont do anything
    T* tempArray = new T [newCapacity];     //creates an instance of an array with the new capacity
    newCalls++;
    if(arrayCapacity < newCapacity)  //if we are increasing the size of the array
    {
        for(int i = 0; i < numElements; i++) //for each element in the original array
            tempArray[i] = dynamicArray[i];  //put it into the new array at the corresponding index
    }
    else  //if we are decreasing the size of the array
    {  //if there are more elements than the new capacity of the array, then they will be removed from the array (and the array will be full)
        for(int i = 0; i < newCapacity; i++) //numElements can't exceed capacity, so to be safe go to every index within capacity range
            tempArray[i] = dynamicArray[i];  //put it into the new array at the corresponding index
    }
    arrayCapacity = newCapacity;         //increases the capacity of the array to the specified value
    delete [] dynamicArray;              //free the memory that dynamicArray points too
    delCalls++;
    dynamicArray = tempArray;            //assign dynamicArray pointer to the "new" temp array we created and populated here
}

//getter for numElements
template <class T>
int Vector<T>::size()
{
    return numElements; //simple getter function
}

//getter for arrayCapacity
template <class T>
int Vector<T>::capacity()
{
    return arrayCapacity;
}

//inserts an element at the back of the vector
template <class T>
void Vector<T>::push_back(const T& data)
{
    if(numElements == arrayCapacity)       //if the array is full
        resize(arrayCapacity+arrayCapacity/2);        //increase the number of elements it can hold by 1.5
    dynamicArray[numElements] = data; //insert the data into the back of the array
    numElements++;                    //the size of the array goes up by 1
}

//removes an element from the back of the vector
template <class T>
void Vector<T>::pop_back()
{ ///note: data isn't actually destroyed, it just can't be accessed anymore with this data structure
  ///and will be overwritten if new data is pushed onto the popped index
    if(numElements > 0) //if the array isn't empty
        numElements--;  //we use numElements to get the index for the back data, so decreasing this is sufficient
}


template <class T>
bool Vector<T>::empty()
{
    if(numElements == 0) //if there are no elements in the array
        return true;    //then its empty
    return false;    //otherwise its not empty
}

template <class T>
void Vector<T>::clear()
{
    while(!empty())
        pop_back();
}

template <class T>
void Vector<T>::print()
{
    std::cout << "***Contents of vector***\n";
    std::cout << "size: " << numElements << "   capacity: " << arrayCapacity << "\n";
    for(int i = 0; i < numElements; i++)
    {
        std::cout << "\"" << i << "th\" index holds: ";
        dynamicArray[i].print();
    }
}
