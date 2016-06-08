#ifndef _HT
#define _HT
#include "DLList.hpp"

//chaining based hash table
class HashTable{
public:
    HashTable(int v); //constructor which takes the table size parameter
    ~HashTable();     //destructor that calls DLList's destructor the same number of times as the table length

    bool insert(Node* node);      //inserts a new node into the table
    bool remove(std::string const& name); //removes a node from the table given the string key
    Node* getNode(std::string const& name); //return the address of a node given the string key
    int size(); //gets size, should be equal to numElements
    ///because each array slot is a DLList, DLList's isMember checks if the node is in the array, hence we don't need an is member for this table

    void print();   //prints the contents of the table
    void histogram(); //alternate way to look at the table

    //getter functions
    int getLength() {return length;}
    int getNumElements() {return numElements;}

private:
    DLList* array; //pointer to an array of linked lists
    int length; //initial length of the table array
    int numElements; //size of table, managed by insert/delete
    int hash(std::string const& itemKey); //hash function to turn a string into an index
};

#endif // _HT
