#include "TwoDArray.hpp"



template <class T>
TwoDArray<T>::~TwoDArray()
{

}

template <class T>
TwoDArray<T>::TwoDArray(int rows,int columns) : row(rows), column(columns)
{
    array = new T* [row];
    for (int i = 0; i < row; i++)
        array[i] = new T[column];
}
