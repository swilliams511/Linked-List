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
: newCalls(0), delCalls(0) ///using initializer list for debug variables.
{
    numElements = 0;                      //naturally the array starts out empty
    arrayCapacity = defaultCapacity;      //initialize the variable to the default value
    dynamicArray = new T [arrayCapacity]; //create a new instance of an array that holds data of type "T" with default 10 capacity
                                          //T's default constructor is called for each slot the array has
    newCalls++;
}

//parameterized constructor
template <class T>
Vector<T>::Vector(int startingSize)
: newCalls(0), delCalls(0) ///using initializer list for debug variables.
{
    numElements = 0;                      //array starts out empty
    if(startingSize < 1)                  //makes sure the initial capacity starts out valid
        startingSize = defaultCapacity;   //use default size if passed size is no good
    arrayCapacity = startingSize;         //set the array capacity
    dynamicArray = new T [arrayCapacity]; //create a new instance of an array of T's

    newCalls++;
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

    //clear(); //calling this ensures any remaining "placement new" objects are destroyed
    delete [] dynamicArray; //free's the data dynamicArray points to

    delCalls++;
    std::cout << "New calls: " << newCalls << " Del calls: " << delCalls <<   "\n";
}

//copy constructor
template <class T>
Vector<T>::Vector(const Vector& otherVector)
: newCalls(0), delCalls(0) ///using initializer list for debug variables.
{
    std::cout << "in copy constructor\n";

    numElements = 0;                                 //initialize the new vector as empty
    arrayCapacity = otherVector.arrayCapacity;       //set the capacity to the other vectors capacity
    dynamicArray = new T [arrayCapacity];            //create a new array of type T holding the passed vectors capacity
    for(int i = 0; i < otherVector.numElements; i++) //for each value in the passed array
        push_back(otherVector.dynamicArray[i]);      //insert it into the newly created array

    newCalls++;
}

//assignment operator
template <class T>
Vector<T>& Vector<T>::operator=(Vector otherVector)
{
    std::cout << "in assignment operator\n";
    std::swap(newCalls,otherVector.newCalls); //swaps the debug calls to be consistent
    std::swap(delCalls,otherVector.delCalls);

    std::swap(dynamicArray,otherVector.dynamicArray);   //swap the back array with the copy
    std::swap(numElements,otherVector.numElements);     //swap the number of elements with the copy
    std::swap(arrayCapacity,otherVector.arrayCapacity); //swap the capacity with the copy
    return *this;                                       //returns the Vector that got that data swapped into it
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
    return dynamicArray[index];            //uses array's [] access to get the element
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

    if(arrayCapacity == newCapacity)         //if the new size of the array is the same
        return;                              //dont do anything
    T* tempArray = new T [newCapacity];      //creates an instance of an array with the new capacity
    while(numElements > newCapacity)         //if there is data outside of the new capacity (shrinking an array)
        pop_back();                          //delete it
    for(int i = 0; i < numElements; i++)     //for each element in the original array
        std::swap(tempArray[i],dynamicArray[i]); //swaps the empty data in temp with the placement new data in this array
    int elementCount = numElements;          //temporarily keeps the number of elements here since clear() will reduce this to 0
    delete [] dynamicArray;                  //free the memory that dynamicArray points to
    dynamicArray = tempArray;                //assign dynamicArray pointer to the "new" temp array we created and populated here
    arrayCapacity = newCapacity;             //increases the capacity of the array to the specified value
    numElements = elementCount;              //update the number of elements in the srray

    newCalls++;
    delCalls++;
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
    std::cout << "---push back start **************---\n";

    if(numElements == arrayCapacity)           //if the array is full
        resize(arrayCapacity+arrayCapacity/2); //increase the number of elements it can hold by 1.5
    /*dynamicArray[numElements] = data;*/      ///see below line for placement new way of inserting data into the container
    new(numElements + dynamicArray) T(std::move(data));   //use "placement new" to put a copy of the data at the back of the array
    numElements++;                             //the size of the array goes up by 1

    std::cout << "---push back end---\n";
    newCalls++;
}

template <class T>
void Vector<T>::push_back(T&& data)
{
     std::cout << "---push back start &&---\n";
    if(numElements == arrayCapacity)           //if the array is full
        resize(arrayCapacity+arrayCapacity/2); //increase the number of elements it can hold by 1.5
    /*dynamicArray[numElements] = data;*/      ///see below line for placement new way of inserting data into the container
    new(numElements + dynamicArray) T(std::move(data));   //use "placement new" to put a copy of the data at the back of the array
    numElements++;                             //the size of the array goes up by 1

    std::cout << "---push back end---\n";
    newCalls++;
}

//removes an element from the back of the vector
template <class T>
void Vector<T>::pop_back()
{ ///To see this in action, in Data.cpp's destructor, put print() in it.
  ///When pop_back() is called, the data prints right before it is destroyed
  ///When the program ends, the destructor prints for any unused vector indexes since
  ///only the default constructor was used on them.
  ///The indexes that had data will have undefined behavior, which implies pop_back() does
  ///delete the data! See "trying_to_access_destoyed_data.png" for example
  std::cout << "---pop back start---\n";

    if(empty())                       //if the array is empty
        return;                       //don't do anything
    dynamicArray[numElements-1].~T(); //call T's destructor to match the placement new call push_back() made
    numElements--;                    //we use numElements to get the index for the back data, so decreasing this is sufficient

    delCalls++;
    std::cout << "---pop back end---\n";
}


template <class T>
bool Vector<T>::empty()
{
    if(numElements == 0) //if there are no elements in the array
        return true;     //then its empty
    return false;        //otherwise its not empty
}

template <class T>
void Vector<T>::clear()
{
    while(!empty()) //as long as there are elements in the array
        pop_back(); //delete the last element until there aren't any left
}

template <class T>
T* Vector<T>::begin()
{
    return dynamicArray;
}

template <class T>
T* Vector<T>::end()
{
    return dynamicArray + numElements - 1;
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

template <class T>
void Vector<T>::print_iterator()
{
    std::cout << "***Contents of vector (using iterator)***\n";
    std::cout << "size: " << numElements << "   capacity: " << arrayCapacity << "\n";
    int counter = 0;
    for(T* iterator = begin(); iterator != end()+1; iterator++)
    {
        std::cout << "\"" << counter << "th\" index at address: " << iterator << " holds: ";
        iterator->print();
        counter++;
    }

}
