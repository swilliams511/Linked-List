#ifndef _2d
#define _2d

template <class T>
class TwoDArray{
public:

    ~TwoDArray();
    TwoDArray(int rows,int columns);


private:
    const int row;
    const int column;
    T** array;



};





#endif // _2d
