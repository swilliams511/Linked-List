#ifndef _HT
#define _HT
#include "DLList.hpp"

class HashTable{
public:
    HashTable(int v);
    ~HashTable();


private:
    DLList* array; //pointer to an array of linked lists
    int length;


};






#endif // _HT
