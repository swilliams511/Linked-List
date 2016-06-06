#ifndef _HT
#define _HT
#include "DLList.hpp"

class HashTable{
public:
    HashTable(int v);
    ~HashTable();

    bool insert(Node* node);
    bool remove(int value, std::string name);
    Node* getNode(std::string name);

    void print();
    void histogram();

    int getLength() {return length;}
    int getNumElements() {return numElements;}
    int size();


private:
    DLList* array; //pointer to an array of linked lists
    int length;
    int numElements;
    int hash(std::string itemKey);


};






#endif // _HT
