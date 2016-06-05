#include "HashTable.hpp"

HashTable::HashTable(int v)
{
    if( v <= 0)
        v = 23;     //some default prime number length
    length = v;
    array = new DLList[length];
}
