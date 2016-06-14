#include "Data.hpp"


Data::Data()
{
    //std::cout << "Data's constructor called\n";
    value = 0;
    name = "";
}

Data::Data(int v, std::string n)
{
    //std::cout << "Data's para constructor called\n";
    value = v;
    name = n;
}

Data::~Data()
{
    //std::cout << "Data's destructor called\n";
}

Data::Data(const Data& otherData)
{
    //std::cout << "Data's copy constructor called\n";
    value = otherData.value;
    name = otherData.name;
}

void Data::swap(Data& otherData)
{
    std::swap(value,otherData.value);
    std::swap(name,otherData.name);
}

Data Data::operator=(Data otherData)
{
    //std::cout << "In assignment operation\n";
    swap(otherData);
    return *this;
}

bool Data::operator<(const Data& otherData)
{
    if(value < otherData.value)
        return true;
    return false;
}

bool Data::operator>(const Data& otherData)
{
    return !(*this < otherData);
    //if(value > second_Data.value)
   //     return true;
  //  return false;
}

void Data::print()
{
    std::cout << "#" << value << " - " << name << "\n";
}


