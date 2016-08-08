#include "Data.hpp"


Data::Data()
: value(0), name("")
{
    //std::cout << "Data's constructor called\n";
}

Data::Data(int v, std::string n)
: value(v), name(n)
{
    std::cout << "Data's para constructor called\n";
}

Data::~Data()
{
    std::cout << "Data's destructor called\n";
}

Data::Data(const Data& otherData)
: value(otherData.value), name(otherData.name)

{
    std::cout << "Data's copy constructor called\n";
}

Data::Data(Data&& otherData)
: value(std::move(otherData.value)), name(std::move(otherData.name))
{
    std::cout << "Data's move constructor\n";
}

void Data::swap(Data& otherData)
{
    std::swap(value,otherData.value); //switches the value
    std::swap(name,otherData.name);   //switches the name
}

Data& Data::operator=(const Data& otherData)
{
    std::cout << "Data's const? assignment\n";
    value = otherData.value;
    name = otherData.name;
    return *this;
}
Data& Data::operator=(Data&& otherData)
{
    std::cout << "Data's move assignment\n";
    value = std::move(otherData.value);
    name = std::move(otherData.name);
    return *this;
}

//Data Data::operator=(Data otherData)
//{
//    std::cout << "In data assignment operation\n";
//    //uses copy/swap implementation
//    //otherData is passed by value, which creates a copy of the data
//    //we swap the copied data into the left hand data
//    //then going out of scope deletes the old swapped out data
//    swap(otherData);
//    return *this;    //returns the dereferenced data
//}

bool Data::operator<(const Data& otherData) const
{
    if(value < otherData.value)  //this data type compares which data is bigger based off value
        return true;             //value is an int so int's "<" works here
    return false;
}

bool Data::operator>(const Data& otherData) const
{
    return !(*this < otherData); //opposite of < operator
}

bool Data::operator==(const Data& otherData) const
{
    if(name == otherData.name && value == otherData.value) //the data type is the name if
        return true;   //both the name and value compare using string and int's "=="
    return false;
}

bool Data::operator!=(const Data& otherData) const
{
    return !(*this == otherData); //opposite of == operator
}

void Data::print() const
{
    std::cout << "#" << value << " - " << name << "\n";
}


