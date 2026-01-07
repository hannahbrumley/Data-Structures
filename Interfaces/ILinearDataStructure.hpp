#ifndef _I_LINEAR_DATA_STRUCTURE_HPP
#define _I_LINEAR_DATA_STRUCTURE_HPP

#include <ostream>
using namespace std;

template <typename T>
//! An interface of methods that our linear data structures should have
class ILinearDataStructure
{
public:
    virtual ~ILinearDataStructure() { }

    //! Insert an item to the END of the array.
    virtual void PushBack( T newItem ) = 0;
    //! Insert an item to the BEGINNING of the array.
    virtual void PushFront( T newItem ) = 0;
    //! Insert an item at some index in the array.
    virtual void PushAt( T newItem, int index ) = 0;

    //! Remove the LAST item in the array.
    virtual void PopBack() = 0;
    //! Remove the FRONT item in the array. Shift everything to the left.
    virtual void PopFront() = 0;
    //! Remove an item in the middle of the array. Close up the gap.
    virtual void PopAt( int index ) = 0;

    //! Get the LAST item in the array.
    virtual T GetBack() const = 0;
    //! Get the FIRST item in the array.
    virtual T GetFront() const = 0;
    //! Get an item in the array at some index.
    virtual T GetAt( int index ) const = 0;

    //! Display all the elements of the array.
    virtual void Display() const = 0;

    //! Output all elements to the stream
//    virtual void Display( ostream& outstream ) const = 0;

    //! Returns the amount of items currently stored in the array.
    virtual int Size() const = 0;

    //! Check if the array is currently empty.
    virtual bool IsEmpty() const = 0;

    //! Clear the data.
//    virtual void Clear() = 0;
};


#endif
