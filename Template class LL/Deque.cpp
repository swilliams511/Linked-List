/*
By: Scott Williams - swilliams511
Deque based class that uses:
-char* to save calling T's constructor on unused memory blocks in the array
-reinterpret_cast to change the char* pointer to a T* pointer
-placement new to call T's constructor when data is pushed
-placement delete to call T's destructor when data is popped
-Attempts to try using size_type and size_t

check "Deque - copy" for first implementation attempt (overall more expensive)
*/

#include "Deque.hpp"

template <class T>
Deque<T>::Deque()
{
    mapCapacity = startMapCapacity;                   //set the initial map capacity
    map = new char* [mapCapacity];                    //create a map which holds pointers
    for(size_t i = 0; i < mapCapacity; ++i)           //for each of these pointers
        map[i] = new char[sizeof(T) * chunkCapacity]; //let them point to a fixed size chunk which holds individual data elements
    numElements = 0;                                  //the deque starts out empty
}

template <class T>
Deque<T>::~Deque()
{
    std::cout << "destr\n";
    clear();                                //makes sure that each T created with placement new is destroyed
    for(size_t i = 0; i < mapCapacity; ++i) //for each of the chunks the map contains
        delete [] map[i];                   //delete each inner array (chunk)
    delete [] map;                          //then delete the outer array (map)
    std::cout << "destr end\n";
}


template <class T>
T& Deque<T>::at(const size_t index) const
{
    if(index < 0 || index > numElements-1)
    {
        std::cout << "[" << index << "] out of range, returning [0][0]\n";
        return reinterpret_cast<T**>(map)[0][0];                             //will likely break the program
    }
    int key = first_map_index*chunkCapacity+index+empty_left;                //this formula calculates the requested data
    return reinterpret_cast<T**>(map)[key/chunkCapacity][key%chunkCapacity]; //change the map pointer to a T pointer
}


template <class T>
void Deque<T>::first_insert(const T& data)
{   //initialize these variables when data is first inserted into the deque
    empty_left = chunkCapacity/2 + 1;              //not an index, so add 1
    empty_right = chunkCapacity/2 + 1;             //"   "
    first_map_index = mapCapacity/2;
    last_map_index = mapCapacity/2;
    new(reinterpret_cast<T**>(map)[first_map_index] + chunkCapacity/2) T(data);
    numElements++;                                 //number of elements goes up
    --empty_left;                                  //now the two empty vars each have one less empty slot
    --empty_right;
}

template <class T>
void Deque<T>::first_insert(T&& data)
{   //initialize these variables when data is first inserted into the deque
    empty_left = chunkCapacity/2 + 1;              //not an index, so add 1
    empty_right = chunkCapacity/2 + 1;             //"   "
    first_map_index = mapCapacity/2;
    last_map_index = mapCapacity/2;
    new(reinterpret_cast<T**>(map)[first_map_index] + chunkCapacity/2) T(std::move(data));
    numElements++;                                  //number of elements goes up
    --empty_left;                                   //now the two empty vars each have one less empty slot
    --empty_right;
}

template <class T>
void Deque<T>::push_back(const T& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(data);                    //insert the data using this
        return;
    }
    if(empty_right == 0)                       //if the current chunk is full
    {
        if(last_map_index+1 == mapCapacity)    //if the outer array is full at the end
            resize_back();                     //add more space at the end
        ++last_map_index;                      //move to the next chunk since the current one is full
        empty_right = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    new(reinterpret_cast<T**>(map)[last_map_index] + chunkCapacity-empty_right) T(data);
    --empty_right;                             //since there is 1 more data in back, there is one less space in the chunk
    ++numElements;                             //the number of data goes up by one
}

template <class T>
void Deque<T>::push_back(T&& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(std::move(data));         //insert the data using this
        return;
    }
    if(empty_right == 0)                       //if the current chunk is full
    {
        if(last_map_index+1 == mapCapacity)    //if the outer array is full at the end
            resize_back();                     //add more space at the end
        ++last_map_index;                      //move to the next chunk since the current one is full
        empty_right = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }                                          //change to char pointer to a T pointer and use placement new to insert the data of type T
    new(reinterpret_cast<T**>(map)[last_map_index] + chunkCapacity-empty_right) T(std::move(data));
    --empty_right;                             //since there is 1 more data in back, there is one less space in the chunk
    ++numElements;                             //the number of data goes up by one
}


template <class T>
void Deque<T>::pop_back()
{
    if(empty())                      //if there is nothing in the deque
        return;                      //cant delete anything
    at(numElements-1).~T();          //call the destructor for the data at the back of the deque
    --numElements;                   //there is now 1 less element
    if(empty_right == chunkCapacity) //if the current chunk now has no elements left in it
    {
        --last_map_index;            //move to the prior chunk which will have data
        empty_right = 0;             //start at the right most element in the chunk
        return;
    }                                //otherwise
    ++empty_right;                   //there is now one less element it the current chunk
}

template <class T>
void Deque<T>::clear()
{
    while(!empty())
        pop_back();
}


template <class T>
size_t Deque<T>::size() const
{
    return numElements;
}

template <class T>
bool Deque<T>::empty() const
{
    return numElements == 0;
}


template <class T>
void Deque<T>::print() const
{
    std::cout << "***Contents of deque***\n";
    std::cout << "numElements: " << numElements << " mapCapacity: "
    << mapCapacity << "\nempty_left: " << empty_left << " empty_right: " << empty_right <<
        " first_map_index: " << first_map_index << " last_map_index " << last_map_index << "\n";
    for(size_t i = 0; i < numElements; ++i)
    {
        std::cout << "\"" << i << "th\" index: ";
        at(i).print();
    }
    std::cout << "\n";
}







template<class T>
void Deque<T>::resize_back()
{
    std::cout << "back resize\n";
    mapCapacity *= resizeConstant;                          //increase the map's capacity
    char** tempMap = new char* [mapCapacity];               //create a new map with the updated capacity
    for (size_t i = 0; i < last_map_index+1; ++i)           //for each of the chunks in the map
        tempMap[i] = map[i];                                //give ownership of the pointers to the temp map
    for (size_t i = last_map_index+1; i < mapCapacity; ++i) //once the old chunks are now owned by temp
        tempMap[i] = new char[sizeof(T) * chunkCapacity];   //create the new chunks to fill the temp map's capacity up
    delete [] map;                                          //since map no longer has ownership of its pointers, we dont need to delete them, but we need to delete map
    map = tempMap;                                          //assign the temp map to the map pointer
}

/*
static const int chunkCapacity = 5;  //for this implementation, this must be an odd number. Starting with a small number for testing
static const int startArrayCapacity = 3; //we'll just start out with 3 inner array for now... this can grow

template <class T>
Deque<T>::Deque()
{
    arrayCapacity = startArrayCapacity;
    dynamicArray = new T* [arrayCapacity];         //create a pointer to an array of pointers
    for(int i = 0; i < arrayCapacity; ++i)         //for each index in the outer array
        dynamicArray[i] = new T [chunkCapacity];   //assign each of those pointers a new array
    numElements = 0;                               //there is no data to start out with
    empty_left = chunkCapacity/2 + 1;              //not an index, so add 1
    empty_right = chunkCapacity/2 + 1;             //"   "
    first_map_index = arrayCapacity/2;
    last_map_index = arrayCapacity/2;
}

template <class T>
Deque<T>::~Deque()
{
    for(int i = 0; i < arrayCapacity; ++i) //first...
        delete [] dynamicArray[i];         //delete each inner array (chunk)
    delete [] dynamicArray;                //then delete the outer array (map)
}

template <class T>
T& Deque<T>::operator[](const int index) const
{
    ///first index is key/cap using int division. 2nd index is the remainder of key/cap
    int key = first_map_index*chunkCapacity+index+empty_left;   //using these values, we can
    return dynamicArray[key/chunkCapacity][key%chunkCapacity];  //compute where the index corresponds to
}




template <class T>
void Deque<T>::first_insert(const T& data)
{
    dynamicArray[first_map_index][chunkCapacity/2] = data; //insert the first data in the middle index of the middle array
    numElements++;                                         //number of elements goes up
    --empty_left;    //now the two empty vars each have one less empty slot
    --empty_right;
}



template <class T>
void Deque<T>::resize_back()
{
    std::cout << "back resize\n";
    int temp = arrayCapacity;                    //holds the old value for when we delete the old array
    arrayCapacity = arrayCapacity*2;             //increases the capacity of the array by 2x
    T** tempArray = new T* [arrayCapacity];      //creates an instance of an array (map) with 2x more inner array
    for(int i = 0; i < arrayCapacity; ++i)       //creates the new chunks in the map
        tempArray[i] = new T [chunkCapacity];
    for(int i = first_map_index; i < last_map_index+1; ++i)     //for each element in the original array
        std::swap(tempArray[i],dynamicArray[i]);  //swap the empty chunk in temp with the old chunk in this index of the map
    for(int i = 0; i < temp; ++i)
        delete [] dynamicArray[i];                //delete each inner array (chunk)
    delete [] dynamicArray;                       //free the memory that dynamicArray points to (map)
    dynamicArray = tempArray;                     //assign dynamicArray pointer to the "new" temp array we created and populated here
    std::cout << "end of resize\n";
}

template <class T>
void Deque<T>::resize_front()
{
    ///a new array with double the elements is created. Half of those are newly created chunks
    ///because we want the first half of chunks to be empty, we start swapping in data at the
    ///i + old array capacity position
    std::cout << "front resize\n";
    int temp = arrayCapacity;                    //holds the old value for when we delete the old array
    arrayCapacity = arrayCapacity*2;             //increases the capacity of the array by 2x
    T** tempArray = new T* [arrayCapacity];      //creates an instance of an array (map) with 2x more inner array
    for(int i = 0; i < arrayCapacity; ++i)       //creates the new chunks in the map
        tempArray[i] = new T [chunkCapacity];
    for(int i = first_map_index; i < last_map_index+1; ++i)     //for each element in the original array
        std::swap(tempArray[i+temp],dynamicArray[i]);  //swap the empty chunk in temp with the old chunk in this index of the map
    for(int i = 0; i < temp; ++i)
        delete [] dynamicArray[i];                //delete each inner array (chunk)
    delete [] dynamicArray;                       //free the memory that dynamicArray points to (map)
    dynamicArray = tempArray;                     //assign dynamicArray pointer to the "new" temp array we created and populated here
    first_map_index = temp;                      //arrayCapacity chunks are inserted at the front so move first index
    std::cout << "end of resize\n";
}



template <class T>
void Deque<T>::push_back(T&& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(std::move(data));         //insert the data using this (move based tho)
        return;
    }
    if(empty_right == 0)                       //if the current chunk is full
    {
        if(last_map_index+1 == arrayCapacity)  //if the outer array is full at the end
            resize_back();                     //add more space at the end
        ++last_map_index;                      //move to the next chunk since the current one is full
        empty_right = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    dynamicArray[last_map_index][chunkCapacity-empty_right] = std::move(data); //move the data at the back index
    --empty_right;     //since there is 1 more data in back, there is one less space in the chunk
    ++numElements;     //the number of data goes up by one
}

template <class T>
void Deque<T>::push_front(const T& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(data);                    //insert the data using this
        return;
    }
    if(empty_left == 0)                       //if the current chunk is full
    {
        if(first_map_index == 0)  //if the outer array is full at the front
            resize_front();                     //add more space at the front
        --first_map_index;                      //move to the previous chunk since the current one is full
        empty_left = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    dynamicArray[first_map_index][empty_left-1] = data; //insert the data at the front index
    --empty_left;     //since there is 1 more data in front, there is one less space in the chunk
    ++numElements;     //the number of data goes up by one
}

template <class T>
void Deque<T>::push_front(T&& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(data);                    //insert the data using this
        return;
    }
    if(empty_left == 0)                       //if the current chunk is full
    {
        if(first_map_index == 0)  //if the outer array is full at the front
            resize_front();                     //add more space at the front
        --first_map_index;                      //move to the previous chunk since the current one is full
        empty_left = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    dynamicArray[first_map_index][empty_left-1] = std::move(data); //insert the data at the front index
    --empty_left;     //since there is 1 more data in front, there is one less space in the chunk
    ++numElements;     //the number of data goes up by one
}





template <class T>
void Deque<T>::print_index() const
{
    std::cout << "***Deque only looking at indexes with data***\n";
    for(int i = 0; i < numElements; ++i)
    {
        std::cout << "\"" << i << "th\" index: ";
        at(i).print();
    }

    std::cout << "\n";
}
*/
