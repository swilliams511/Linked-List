#ifndef _HTLP
#define _HTLP

#include "DLList.hpp"

//linear probing based hash table
class HashTableLP{
public:
    HashTableLP(int tableSize); //constructor which takes the table size parameter
    ~HashTableLP();             //destructor which will call Node's destructor for each node in the table

    bool insert(Node* node);    //inserts a new node into the table
    bool remove(std::string name); //removes a node from the table given the string key
    Node* getNode(std::string name); //returns the pointer to a node in the table given the string key
    int size();                      //returns the size of the table, should be equal to numElements
    bool isMember(std::string name); //given the string key, check if the node is in the table

    void print(); //prints contents of the table

    //getter functions
    int getLength() {return length;}
    int getNumElements() {return numElements;}

private:
    Node** array; //pointer to an array of node pointers
    int length;   //initial length of the table array
    int numElements;  //size of table, managed by insert/delete
    int hash(std::string itemKey); //hash function to turn a string into an index
};

#endif // _HTLP
