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
: map(new char* [mapCapacity]), mapCapacity(startMapCapacity), numElements(0)
{
    //set the initial map capacity and create a map which holds pointers
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
Deque<T>::Deque(const Deque& otherDeque)
: map(new char* [mapCapacity]), mapCapacity(otherDeque.mapCapacity), numElements(0),
first_map_index(otherDeque.first_map_index), last_map_index(otherDeque.last_map_index),
empty_left(otherDeque.empty_left), empty_right(otherDeque.empty_right)
{
    //copy all the index based variables from other and initialize a map to hold pointers
    for(size_t i = 0; i < mapCapacity; ++i)           //for each of these pointers
        map[i] = new char[sizeof(T) * chunkCapacity]; //let them point to a fixed size chunk which holds individual data elements
    for(size_t i = 0; i < otherDeque.numElements; ++i)
    { //in order to create an "identical" deque, each element from other is copied using the "at()" formula to decide where to call placement new
      //trying to use push_back made this complicated, but this solution gets the job done
        int key = first_map_index*chunkCapacity+i+empty_left;                //this formula calculates the requested data
        new(reinterpret_cast<T**>(map)[key/chunkCapacity] + key%chunkCapacity) T(otherDeque.at(i)); //places the appropriate data in the appropriate spot
        ++numElements;
    }
}

template <class T>
Deque<T>& Deque<T>::operator=(Deque otherDeque)
{
    //every private variable is swapped with a copy of the other deque. Destructor takes out copy with old data when function ends
    std::swap(map,otherDeque.map);
    std::swap(mapCapacity,otherDeque.mapCapacity);
    std::swap(numElements,otherDeque.numElements);
    std::swap(empty_left,otherDeque.empty_left);
    std::swap(empty_right,otherDeque.empty_right);
    std::swap(first_map_index,otherDeque.first_map_index);
    std::swap(last_map_index,otherDeque.last_map_index);
    return *this;
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
T& Deque<T>::operator[](const size_t index) const
{
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
void Deque<T>::push_front(const T& data)
{
    if(numElements == 0)                       //if no elements have been inserted
    {
        first_insert(data);                   //insert the data using this
        return;
    }
    if(empty_left == 0)                       //if the current chunk is full
    {
        if(first_map_index == 0)              //if the outer array is full at the front
            resize_front();                   //add more space at the front
        --first_map_index;                    //move to the previous chunk since the current one is full
        empty_left = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    new(reinterpret_cast<T**>(map)[first_map_index] + empty_left-1) T(data);
    --empty_left;     //since there is 1 more data in front, there is one less space in the chunk
    ++numElements;     //the number of data goes up by one
}

template <class T>
void Deque<T>::push_front(T&& data)
{
    if(numElements == 0)                      //if no elements have been inserted
    {
        first_insert(std::move(data));        //insert the data using this
        return;
    }
    if(empty_left == 0)                       //if the current chunk is full
    {
        if(first_map_index == 0)              //if the outer array is full at the front
            resize_front();                   //add more space at the front
        --first_map_index;                    //move to the previous chunk since the current one is full
        empty_left = chunkCapacity;           //since the chunk is empty, set this to how many elements can fit in the chunk
    }
    new(reinterpret_cast<T**>(map)[first_map_index] + empty_left-1) T(std::move(data));
    --empty_left;     //since there is 1 more data in front, there is one less space in the chunk
    ++numElements;     //the number of data goes up by one
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
void Deque<T>::pop_front()
{
    if(empty())                      //if there is nothing in the deque
        return;                      //cant delete anything
    at(0).~T();          //call the destructor for the data at the back of the deque
    --numElements;                   //there is now 1 less element
    if(empty_right == chunkCapacity) //if the current chunk now has no elements left in it
    {
        ++first_map_index;           //move to the prior chunk which will have data
        empty_left = 0;              //start at the left most element in the chunk
        return;
    }                                //otherwise
    ++empty_left;                    //there is now one less element it the current chunk
}

template <class T>
typename Deque<T>::const_Iterator Deque<T>::cbegin() const
{
    int index = 0;
    int key = first_map_index*chunkCapacity+index+empty_left;                //this formula calculates the requested data
    return const_Iterator(reinterpret_cast<T**>(map)[key/chunkCapacity]+key%chunkCapacity,index,this); //change the map pointer to a T pointer
}





template <class T>
void Deque<T>::insert(size_t index, T&& data)
{
    if(index == 0)
        return push_front(std::move(data));
    if(index == numElements)
        return push_back(std::move(data));
    if(index > numElements-index)
    {
        //std::cout << "closer to back\n";
        push_back(std::move(data));                   //insert the data at the back
        for(size_t i = numElements-1; i > index; --i) //i will get to 1 at the lowest because of previous checks
            std::swap(at(i),at(i-1));                 //swap it from the back into the given index
        return;
    }
    //std::cout << "closer to front\n";
    push_front(std::move(data));                      //insert the data at the front
    for(size_t i = 0; i < index; ++i)
        std::swap(at(i),at(i+1));                     //swap it from the front into the given index
}

template <class T>
void Deque<T>::insert(size_t index, const T& data)
{
    if(index == 0)
        return push_front(data);
    if(index == numElements)
        return push_back(data);
    if(index > numElements-index)
    {
        //std::cout << "closer to back\n";
        push_back(data);                              //insert the data at the back
        for(size_t i = numElements-1; i > index; --i) //i will get to 1 at the lowest because of previous checks
            std::swap(at(i),at(i-1));                 //swap it from the back into the given index
        return;
    }
    //std::cout << "closer to front\n";
    push_front(data);                                 //insert the data at the front
    for(size_t i = 0; i < index; ++i)
        std::swap(at(i),at(i+1));                     //swap it from the front into the given index
}

template <class T>
void Deque<T>::erase(size_t index)
{
    if(index == 0)
        return pop_front();
    if(index == numElements-1)
        return pop_back();
    if(index > numElements-1-index)   //checks which end of the deque the index is closer to
    {
        for(size_t i = index; i < numElements-1; ++i)
            std::swap(at(i),at(i+1)); //swap the index data to the back of the deque
        return pop_back();            //pop back to remove it
    }
    for(size_t i = index; i > 0; --i)
        std::swap(at(i),at(i-1));     //swap the index data to the front of the deque
    return pop_front();               //pop front to remove it
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

template <class T>
void Deque<T>::resize_front()
{
    std::cout << "front resize\n";
    size_t oldCapacity = mapCapacity;
    mapCapacity *= resizeConstant;                              //increase the map's capacity
    size_t shift = mapCapacity-oldCapacity;                     //how far the original chunks will move
    char** tempMap = new char* [mapCapacity];                   //create a new map with the updated capacity
    for (size_t i = 0; i < shift; ++i)                          //at the start of the temp map
        tempMap[i] = new char[sizeof(T) * chunkCapacity];       //create the new chunks to fill the temp map's capacity up
    for (size_t i = first_map_index; i < last_map_index+1; ++i) //for each of the chunks in the map after the chunks already created
        tempMap[i+shift] = map[i];                              //give ownership of the pointers to the temp map
    first_map_index = shift;                                    //update the index variables since there are new chinks in the front
    last_map_index += shift;
    delete [] map;                                              //since map no longer has ownership of its pointers, we dont need to delete them, but we need to delete map
    map = tempMap;
}

template <class T>
typename Deque<T>::Iterator Deque<T>::begin()
{
    int index = 0;
    int key = first_map_index*chunkCapacity+index+empty_left;                //this formula calculates the requested data
    return Iterator(reinterpret_cast<T**>(map)[key/chunkCapacity]+key%chunkCapacity,index,this); //change the map pointer to a T pointer
}

template <class T>
typename Deque<T>::Iterator Deque<T>::rbegin()
{
    int index = numElements-1;
    int key = first_map_index*chunkCapacity+index+empty_left;                //this formula calculates the requested data
    return Iterator(reinterpret_cast<T**>(map)[key/chunkCapacity]+key%chunkCapacity,index,this); //change the map pointer to a T pointer
}

template <class T>
typename Deque<T>::Iterator Deque<T>::end()
{ //c++ standard says this should return an iterator to the past-the-end element in the container
    int index = numElements; //past-the-end element (dont dereference otherwise undefined behavior)
    int key = first_map_index*chunkCapacity+index+empty_left;                //this formula calculates the requested data
    return Iterator(reinterpret_cast<T**>(map)[key/chunkCapacity]+key%chunkCapacity,index,this); //change the map pointer to a T pointer
}

template <class T>
typename Deque<T>::Iterator Deque<T>::rend()
{ //c++ standard says this should return an iterator to the before-the-first element in the container
    int index = -1; //before-the-first element (dont dereference otherwise undefined behavior)
    int key = first_map_index*chunkCapacity+index+empty_left;                //this formula calculates the requested data
    return Iterator(reinterpret_cast<T**>(map)[key/chunkCapacity]+key%chunkCapacity,index,this); //change the map pointer to a T pointer
}





///******Iterator function implementations******
template <class T>
Deque<T>::Iterator::Iterator(T* data, size_t index, Deque* deque)
: owner(deque),itr_data(data), itr_index(index)
{
    //creates a starting iterator based on the passed data pointer (should be begin() or end() pointer)
}



template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator+(int value) const
{
    Iterator temp = *this;
    temp.itr_index += value;
    if(temp.itr_index > owner->size()) //checks to make sure data outside the deque isnt accessed
    {
        std::cout << "Iterator index too high, not changing anything\n";
        return *this;
    }
    int key = owner->get_first_map_index()*chunkCapacity+temp.itr_index+owner->get_empty_left();  //using the at() formula to calculate where the data is                //this formula calculates the requested data
    temp.itr_data = reinterpret_cast<T**>(owner->get_map())[key/chunkCapacity]+key%chunkCapacity; //updates the pointer to the new index value
    return temp;
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator-(int value) const
{
    if((int)itr_index-value < 0)     //after casting itr_index to an int, if the difference is negative
    {
        std::cout << std::cout << "Iterator index too low, not changing anything\n";
        return *this;                //dont do anything
    }
    return *this + (-value);
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator+=(int value)
{
//plus equals overload, used to shift to a data pointer by "value" places.
    itr_index += value;             //increases the index by the rhs
    if(itr_index > owner->size()) //checks to make sure data outside the deque isnt accessed
    {
        std::cout << "Iterator index too high, not changing anything\n";
        return *this;
    }
    int key = owner->get_first_map_index()*chunkCapacity+itr_index+owner->get_empty_left();  //using the at() formula to calculate where the data is                //this formula calculates the requested data
    itr_data = reinterpret_cast<T**>(owner->get_map())[key/chunkCapacity]+key%chunkCapacity; //updates the pointer to the new index value
    return *this;                                                                            //returns the iterator
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator-=(int value)
{
    if(itr_index == 0)          //if we are at the 0th index
    {                           //set the pointer to the before-the-first element in the deque, which is at(0) - 1
        int key = owner->get_first_map_index()*chunkCapacity+owner->get_empty_left();
        itr_data = reinterpret_cast<T**>(owner->get_map())[key/chunkCapacity]+key%chunkCapacity-1;
        return *this;           //return the before-the-first pointer
    }
    return *this += (-value);   //let operator+ do the work with the negative of value
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator++()
{
    return *this += 1;
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator++(int)
{
    Iterator* temp = this;
    ++(*this);
    return *temp;
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator--()
{
    return *this -= 1;
}

template <class T>
typename Deque<T>::Iterator Deque<T>::Iterator::operator--(int)
{
    Iterator* temp = this;
    --(*this);
    return temp;
}

template <class T>
bool Deque<T>::Iterator::operator==(const Iterator& otherIterator) const
{
    return itr_data == otherIterator.itr_data;
}

template <class T>
bool Deque<T>::Iterator::operator!=(const Iterator& otherIterator) const
{
    return !(*this == otherIterator);
}

///******





///******const_Iterator function implementations******
///All of it is the same as the above iterator, but it's const so the data that's pointed to can't
///be modified
template <class T>
Deque<T>::const_Iterator::const_Iterator(T* data, size_t index, const Deque* deque)
: owner(deque),itr_data(data), itr_index(index)
{
    //creates a starting iterator based on the passed data pointer (should be begin() or end() pointer)
}

template <class T>
typename Deque<T>::const_Iterator Deque<T>::const_Iterator::operator+(int value)
{
//plus overload, used to shift to a data pointer by "value" places.
    itr_index += value;             //increases the index by the rhs
    if(itr_index > owner->size()) //checks to make sure data outside the deque isnt accessed
    {
        std::cout << "Iterator index too high, not changing anything\n";
        return *this;
    }
    int key = owner->get_first_map_index()*chunkCapacity+itr_index+owner->get_empty_left();  //using the at() formula to calculate where the data is                //this formula calculates the requested data
    itr_data = reinterpret_cast<T**>(owner->get_map())[key/chunkCapacity]+key%chunkCapacity; //updates the pointer to the new index value
    return *this;                                                                            //returns the iterator
}

template <class T>
typename Deque<T>::const_Iterator Deque<T>::const_Iterator::operator-(int value)
{
    if((int)itr_index-value < 0)     //after casting itr_index to an int, if the difference is negative
    {
        std::cout << std::cout << "Iterator index too low, not changing anything\n";
        return *this;                //dont do anything
    }
    return *this + (-value);         //let operator+ do the work with the negative of value
}
///******
