#include "Deque.hpp"

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
T& Deque<T>::at(const int index) const
{
    if(index < 0 || index > numElements-1)
    {
        std::cout << "[" << index << "] out of range, returning [0][0]\n";
        return dynamicArray[0][0];
    }
    int key = first_map_index*chunkCapacity+index+empty_left;
    return dynamicArray[key/chunkCapacity][key%chunkCapacity];
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
void Deque<T>::first_insert(T&& data)
{
    dynamicArray[first_map_index][chunkCapacity/2] = std::move(data); //move insert the first data in the middle index of the middle array
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
void Deque<T>::push_back(const T& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(data);                    //insert the data using this
        return;
    }
    if(empty_right == 0)                       //if the current chunk is full
    {
        if(last_map_index+1 == arrayCapacity)  //if the outer array is full at the end
            resize_back();                     //add more space at the end
        ++last_map_index;                      //move to the next chunk since the current one is full
        empty_right = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    dynamicArray[last_map_index][chunkCapacity-empty_right] = data; //insert the data at the back index
    --empty_right;     //since there is 1 more data in back, there is one less space in the chunk
    ++numElements;     //the number of data goes up by one
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
int Deque<T>::size() const
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
    std::cout << "numElements: " << numElements << " arrayCapacity: "
    << arrayCapacity << "\nempty_left: " << empty_left << " empty_right: " << empty_right <<
        " first_map_index: " << first_map_index << " last_map_index " << last_map_index << "\n";
    for(int i = 0; i < arrayCapacity; ++i)
    {
        std::cout << "---\"" << i << "th\" chunk---\n";
        for(int j = 0; j < chunkCapacity; ++j)
            dynamicArray[i][j].print();
    }
    std::cout << "\n";
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
