#ifndef _deque
#define _deque

#include <iostream>




template <class T>
class Deque{
    static const size_t chunkCapacity = 5;  //for this implementation, this must be an odd number. Starting with a small number for testing
    static const size_t startMapCapacity = 3; //we'll just start out with 3 inner array for now... this can grow
    const float resizeConstant = 2;    //where mapCapacity *= resizeConstant in resize
public:
    ///Nested iterator class. Since the iterator class is the inner class, a pointer to the outer deque
    ///needs to be passed when the iterator is constructed. Then getter functions must be called
    ///to access the deque's private variables (which are important to some overload functions...)
    class Iterator{
    public:
        Iterator(T* data, size_t index, Deque* deque);

        //Iterator(const Iterator& otherIterator);
        //Iterator operator=(Iterator otherIterator);
        T* operator->() const {return itr_data;}
        T& operator*() const {return *itr_data;}
        Iterator operator+(int value) const;
        Iterator operator-(int value) const;
        Iterator operator+=(int value);
        Iterator operator-=(int value);
        Iterator operator++();
        Iterator operator++(int);
        Iterator operator--();
        Iterator operator--(int);
        bool operator==(const Iterator& otherIterator) const;
        bool operator!=(const Iterator& otherIterator) const;


    private:
        Deque* owner;     //because the iterator class is nested, a pointer to the deque must be passed
        T* itr_data;      //holds the pointer to the data
        size_t itr_index; //used for calculations and keeping track of where in the deque we are

    };

    class const_Iterator{
    public:
        const_Iterator(T* data, size_t index, const Deque* deque);

        //const_Iterator(const const_Iterator& otherIterator);
        //const_Iterator operator=(const_Iterator otherIterator);
        const T* operator->()const {return itr_data;}
        const T& operator*()const {return *itr_data;}
        const_Iterator operator+(int value);
        const_Iterator operator-(int);
        const_Iterator operator++();
        const_Iterator operator++(int);
        const_Iterator operator--();
        const_Iterator operator--(int);
        bool operator==(const const_Iterator& otherIterator) const;
        bool operator!=(const const_Iterator& otherIterator) const;

    private:
        const Deque* owner;   //because the iterator class is nested, a pointer to the deque must be passed
        const T* itr_data;    //holds the pointer to the data
        size_t itr_index;     //used for calculations and keeping track of where in the deque we are

    };

public:
    Deque();
    ~Deque();
    Deque(const Deque& otherDeque);
    Deque& operator=(Deque otherDeque);


    T& operator[](const size_t index) const; //access the kth element of the deque. RANGE: [0,size()-1]
    T& at(size_t index) const;               //if using a pointer, use this    RANGE: [0,size()-1]
    size_t size() const;                     //returns the number of elements in the deque
    bool empty() const;                      //returns true if there are no elements in the deque

    void push_back(const T& data);      //copy-based function to put new data at the back of the deque
    void push_back(T&& data);           //move-based function to put new data at the back of the deque
    void push_front(const T& data);     //copy-based function to put new data at the front of the deque
    void push_front(T&& data);          //move-based function to put new data at the front of the deque

    //inserts data at given index (doesn't use iterators). Prereq: index is between 0 and size() inclusive
    void insert(size_t index, const T& data);
    void insert(size_t index, T&& data);
    //removes data at given index (doesn't use iterators). Prereq: index is between 0 and size()-1 inclusive
    void erase(size_t index);

    void pop_back();                    //removes the last element from the deque. Does nothing if the deque is empty
    void pop_front();                   //removes the first element from the deque. Does nothing if the deque is empty
    void clear();                       //removes all elements from the deque. Does nothing if the deque is empty

    Iterator begin();                   //precondition: The deque isn't empty. Returns an iterator (pointer) to the first element in the deque
    Iterator end();                     //precondition: The deque isn't empty. Returns an iterator (pointer) to the after last element (undefined memory)
    Iterator rbegin();
    Iterator rend();

    const_Iterator cbegin() const;      //same as above, but the elements are const and can't be modified


    void print() const;
    void print_index() const;

    char** get_map() const {return map;}
    size_t get_first_map_index() const {return first_map_index;}
    size_t get_last_map_index() const {return last_map_index;}
    size_t get_empty_left() const {return empty_left;}
    size_t get_empty_right() const {return empty_right;}
private:
    char** map;
    size_t mapCapacity;
    size_t numElements;

    size_t first_map_index;
    size_t last_map_index;
    size_t empty_left;
    size_t empty_right;

    void first_insert(const T& data); //copy insert based
    void first_insert(T&& data); //move insert based
    void resize_back();
    void resize_front();




};






#endif // _deque
