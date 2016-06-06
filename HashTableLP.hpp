#ifndef _HTLP
#define _HTLP

#include "DLList.hpp"

class HashTableLP{
public:
    HashTableLP(int v);
    ~HashTableLP();

    bool insert(Node* node);
    bool remove(int value, std::string name);
    Node* getNode(std::string name);

    void print();
    void histogram();

    int getLength() {return length;}
    int getNumElements() {return numElements;}
    int size();
    bool isMember(std::string name);

private:
    Node** array; //pointer to an array of nodes
    int length;
    int numElements;
    int hash(std::string itemKey);








};









#endif // _HTLP
