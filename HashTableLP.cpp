#include "HashTableLP.hpp"

//creates a inear probe based hash table
HashTableLP::HashTableLP(int v)
{
    numElements = 0;
    if( v <= 0)
        v = 23;     //some default prime number length
    length = v;
    array = new Node*[length];
    for(int i=0; i < length; i++)
        array[i] = nullptr;
}



HashTableLP::~HashTableLP()
{
    delete [] array; //DLList's destructor is called the same number of times as length
}

//hash function to convert a string to an index
int HashTableLP::hash(std::string itemKey)
{
    int value = 0;
    for(unsigned i = 0; i < itemKey.length(); i++)
        value += itemKey[i];
    return (value * itemKey.length()) % length;
}

bool HashTableLP::isMember(std::string name)
{
    int index = hash(name);
    int temp = index; //temp var to assign start to the starting index in the while loop
    int start = -1;   //the index will never be -1 so the 2nd condition of the while loop will hold entering it the first time
    while(array[index] != nullptr && index != start)//will wrap around until we get back to the starting index
    {                                               //if the array is full
        start = temp;          //now that we are in the loop, update start to equal index. The temp value ensure that start will always be equal to length even though it is assigned each pass of the loop
        if(array[index]->getName() == name) //if the node is found
            return true;                    //tell us its there
        index++;                       //move to the next index
        index %= length;               //modulo wrapper to ensure index stays less than length
    }
    return false; //if we get to here, the node isn't in the table
}

bool HashTableLP::insert(Node* node)
{
    if(numElements == length) //if the table is full
    {
        std::cout << "Linear Probe Hash Table full\n"; //print this
        return false;                                  //dont insert the node
    }
    if(isMember(node->getName()))                      //if the node is already in the table
        return false;                                  //dont insert it
    int index = hash(node->getName());  //using the name string, create an index
    while(array[index] != nullptr)       //probe each node starting at the index until an empty one is found
    {
        index++;         //move to the next node
        index %= length; //wraps index around incase it get bigger than length, if its smaller nothing happens
    }
    numElements++;       //indicate the number of nodes has increased
    array[index] = node->copyNode(); //clones the node so we dont have to worry about hash's destructor eliminating the original node
    return true;                     //tell us insert was success
}

bool HashTableLP::remove(std::string name)
{
    if(!isMember(name)) //if the node isn't in the table
        return false;   //we cant remove it
    int index = hash(name);  //otherwise we know the node is in the table
    while(array[index] != nullptr)       //probe each node starting at the index until an empty one is found
    {
        if(array[index]->getName() == name) //if the node is found
        {
            delete array[index];  //delete it
            array[index] = nullptr; //set that space in the array to a nullptr
            numElements--;       //decrease the number of elements
            return true;   //tell us the node was removed
        }
        index++; //move to the next node
        index %= length; //modulo wrapper
    }
    return false; //shouldnt reach here but just incase

}


void HashTableLP::print()
{
    std::cout << "***Hash Table of size " << length << " with " << numElements << " elements contents***\n";
    for(int i = 0; i < length; i++)
    {
        std::cout << "---Bucket " << i+1 << "---\n";
        if(array[i] == nullptr)
            std::cout << "empty";
        else
            array[i]->print();
        std::cout << "\n";
    }
}

//given the key, the node with the name will be returned. works about the same as isMember
Node* HashTableLP::getNode(std::string name)
{
    if(!isMember(name))
    {
        std::cout << "Couldn't find requested node. Program will segfault if there is no if statement checking for nullpointers\n";
        return nullptr;
    }
    int index = hash(name);
    int temp = index; //temp var to assign start to the starting index in the while loop
    int start = -1;   //the index will never be -1 so the 2nd condition of the while loop will hold entering it the first time
    while(array[index] != nullptr && index != start)//will wrap around until we get back to the starting index
    {                                               //if the array is full
        start = temp;          //now that we are in the loop, update start to equal index. The temp value ensure that start will always be equal to length even though it is assigned each pass of the loop
        if(array[index]->getName() == name) //if the node is found
            return array[index];                    //tell us its there
        index++;                       //move to the next index
        index %= length;               //modulo wrapper to ensure index stays less than length
    }
    return nullptr; //shouldnt reach here but just incase...
}

int HashTableLP::size()
{
    int counter = 0;
    for(int i = 0; i < length; i++)
        if(array[i] != nullptr)
            counter++;
    return counter;
}
