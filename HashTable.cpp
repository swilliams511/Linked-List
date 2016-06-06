#include "HashTable.hpp"

//creates a chain based hash table
HashTable::HashTable(int v)
{
    if( v <= 0)
        v = 23;     //some default prime number length
    length = v;
    array = new DLList[length];
}



HashTable::~HashTable()
{
    delete [] array; //DLList's destructor is called the same number of times as length
}

//hash function to convert a string to an index
int HashTable::hash(std::string itemKey)
{
    int value = 0;
    for(unsigned i = 0; i < itemKey.length(); i++)
        value += itemKey[i];
    return (value * itemKey.length()) % length;
}

bool HashTable::insert(Node* node)
{
    int index = hash(node->getName());  //using the name string, create an index
    if(!array[index].insert_back(node->getValue(),node->getName())) //insert the node into the list at that indez
        return false; //prevents the same element being put in multiple times
    numElements++;   //say the size has gone up by 1
    return true;     //say the node was inserted

}

bool HashTable::remove(int value, std::string name)
{
    int index = hash(name);
    return array[index].delete_node(value, name);
}


void HashTable::print()
{
    std::cout << "***Hash Table of size " << length << " with " << numElements << " elements contents***\n";
    for(int i = 0; i < length; i++)
    {
        std::cout << "---Bucket " << i+1 << "---\n";
        array[i].print();
        std::cout << "\n";
    }
}

//given the key, the node with the name will be returned
Node* HashTable::getNode(std::string name)
{
    int index = hash(name);
    return array[index].getNode(name);

}

int HashTable::size()
{
    int counter = 0;
    for(int i = 0; i < length; i++)
        counter += array[i].getNumNodes();
    return counter;
}

void HashTable::histogram()
{
    std::cout << "***Histogram for Hash Table***\n";
    for(int i = 0; i < length; i++)
    {
        std::cout << i+1 << ":\t";
        for(int j = 0; j < array[i].getNumNodes(); j++)
            std::cout << " X";
        std::cout << "\n";
    }
}

