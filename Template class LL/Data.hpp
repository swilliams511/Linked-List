#ifndef _DATA
#define _DATA
#include <string>
#include <iostream>

//sample data object to be used by a template class
class Data{
public:
    //base object functions
    Data();                           //default constructor
    Data(int v, std::string n);       //parameter constructor
    ~Data();                          //destructor
    Data(const Data& otherData);        //copy constructor
    Data operator=(Data otherData); //assignment operator
///overloaded for sorting the data
    bool operator<(const Data& otherData);
    bool operator>(const Data& otherData);
///overloaded for finding specified data
    bool operator==(const Data& otherData);
    bool operator!=(const Data& otherData);

    //getters/setters for private variables. Shouldn't appear in other class implementation (only main)
    //or specified print functions
    int getValue() {return value;}
    void setValue(int v) {value = v;}
    std::string getName() {return name;}
    void setName(std::string n) {name = n;}

    void print();

private:
    //private variables
    int value;                      //holds an int
    std::string name;               //holds a string
    //helper functions
    void swap(Data& otherData);   //helper function for assignment
};
#endif // _DATA
