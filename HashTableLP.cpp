#include "HashTableLP.hpp"

//creates a inear probe based hash table
HashTableLP::HashTableLP(int v)
{
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
    while(array[index] != nullptr)
    {
        if(array[index]->getName() == name)
            return true;
        index++;
        index %= length;
    }
}

bool HashTableLP::insert(Node* node)
{
    if(numElements == length)
    {
        std::cout << "Linear Probe Hash Table full\n";
        return false;
    }
    int index = hash(node->getName());  //using the name string, create an index
    while(array[index] != nullptr)
    {
        index++;
        index %= length;
    }
    numElements++;
    array[index] = node;

}

bool HashTableLP::remove(int value, std::string name)
{
    int index = hash(name);

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

//given the key, the node with the name will be returned
Node* HashTableLP::getNode(std::string name)
{
    int index = hash(name);
    return array[index];

}

int HashTableLP::size()
{
    int counter = 0;
    for(int i = 0; i < length; i++)
        if(array[i] != nullptr)
            counter++;
    return counter;
}

void HashTableLP::histogram()
{
    std::cout << "***Histogram for Hash Table***\n";
    for(int i = 0; i < length; i++)
    {
        std::cout << i+1 << ":\t";
        //for(int j = 0; j < array[i].getNumNodes(); j++)
            std::cout << " X";
        std::cout << "\n";
    }
}


