#ifndef _SMART_FIXED_ARRAY_HPP
#define _SMART_FIXED_ARRAY_HPP

#include "../Interfaces/ILinearDataStructure.hpp"
#include "../../Exceptions/ItemNotFoundException.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/StructureEmptyException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"
#include "../../Utilities/StringUtil.hpp"

#include <iostream>
using namespace std;

template <typename T>
//! A data structure that wraps a fixed array
class SmartFixedArray : public ILinearDataStructure<T>
{
public:
    /* Public member methods */
    //! Sets up the SmartFixedArray.
    SmartFixedArray();
    //! Cleans up the SmartFixedArray.
    ~SmartFixedArray();

    //! Insert an item to the END of the array.
    void PushBack( T newItem );
    //! Insert an item to the BEGINNING of the array.
    void PushFront( T newItem );
    //! Insert an item at some index in the array.
    void PushAt( T newItem, int index );

    //! Remove the LAST item in the array.
    void PopBack();
    //! Remove the FRONT item in the array. Shift everything to the left.
    void PopFront();
    //! Remove an item in the middle of the array. Close up the gap.
    void PopAt( int index );

    //! Get the LAST item in the array.
    T GetBack() const;
    //! Get the FIRST item in the array.
    T GetFront() const;
    //! Get an item in the array at some index.
    T GetAt( int index ) const;

    //! Search for an item by its value, return the index of its position.
    int Search( T item ) const;

    //! Display all the elements of the array.
    void Display() const;

    //! Output all elements to the stream
    void Display( ostream& outstream ) const;

    //! Returns the amount of items currently stored in the array.
    int Size() const;

    //! Check if the array is currently empty.
    bool IsEmpty() const;

    //! Check if the array is currently full.
    bool IsFull() const;

    //! Clear the data.
    void Clear();

private:
    /* Private member variables */
    //! The pointer used for the dynamic array
    T m_array[100];

    //! The current size of the array
    const int ARRAY_SIZE;

    //! The current amount of items inserted into the array
    int m_itemCount;

    /* Private member methods */
    //! Move all items past the given index to the left.
    void ShiftLeft( int index );

    //! Move all items past the given index to the right.
    void ShiftRight( int index );

    friend class SmartFixedArrayTester;
};

/**
Clear out the array to get ready to use it.
*/
template <typename T>
SmartFixedArray<T>::SmartFixedArray()
    : ARRAY_SIZE( 100 )
{
    Clear();
}

/**
Clean up the SmartFixedArray by calling the Clear function.
*/
template <typename T>
SmartFixedArray<T>::~SmartFixedArray()
{
    Clear();
}

/**
This function will:
- Reset the m_itemCount to 0.
*/
template <typename T>
void SmartFixedArray<T>::Clear()
{
    m_itemCount = 0;
}

/**
Return the value of m_itemCount;
*/
template <typename T>
int SmartFixedArray<T>::Size() const
{
    return m_itemCount;
//    throw NotImplementedException( "SmartFixedArray<T>::Size" ); // Erase this once you work on this function
}

/**
The array is full if m_itemCount is the same value as m_arraySize.

@return     true if the array is full, false otherwise.
*/
template <typename T>
bool SmartFixedArray<T>::IsFull() const
{
    return ( m_itemCount == ARRAY_SIZE );
//    throw NotImplementedException( "SmartFixedArray<T>::IsFull" ); // Erase this once you work on this function
}

/**
Check if the array is currently empty.
The array is empty if the m_itemCount is set to 0.

@return     true if empty, false otherwise.
*/
template <typename T>
bool SmartFixedArray<T>::IsEmpty() const
{
    return ( m_itemCount == 0 );
//    throw NotImplementedException( "SmartFixedArray<T>::IsEmpty" ); // Erase this once you work on this function
}

/**
Iterate through the entire array, displaying the index and value of each element.
*/
template <typename T>
void SmartFixedArray<T>::Display() const
{
    Display( cout );
}

/**
Iterate through the entire array, displaying the index and value of each element.
*/
template <typename T>
void SmartFixedArray<T>::Display( ostream& outstream ) const
{
    for ( int i = 0; i < m_itemCount; i++ )
    {
        outstream << i << ". " << m_array[i] << endl;
    }
}


/**
ERROR CHECK:

* If the index is invalid, throw an exception.

READY TO SHIFT:
Use a for loop, use a counter variable (like i),
- INITIALIZATION:   Starting at the index passed in
- CONDITION:        Continue looping while i is less than the index of the last element of the array.
- UPDATE:           Increment your i counter by 1 each time.

Within the array, set the element at position i to the value of the element at position i-1.

@param      index       The index where items will be shifted left from.
*/
template <typename T>
void SmartFixedArray<T>::ShiftLeft( int index )
{
    if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartFixedArray<T>::ShiftLeft", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }

    for ( int i = index; i < m_itemCount-1; i++ )
    {
        m_array[i] = m_array[i+1];
    }

//    throw NotImplementedException( "SmartFixedArray<T>::ShiftLeft" ); // Erase this once you work on this function
}

/**
ERROR CHECK:

* If the index is invalid, throw an exception.

PREP CHECK:
1. If adding one item to the list (m_itemCount+1) is equal to the m_arraySize, then throw a StructureFullException.

READY TO SHIFT:
Use a for loop, use a counter variable (like i),
- INITIALIZATION:   Starting at the first empty spot in the array.
- CONDITION:        Continue looping while i is greater than the index passed in we will keep looping.
- UPDATE:           Decrement i by 1 each time.

Within the array, set the element at position i to the value of the element at position i+1.

@param      index       The index where items will be shifted right from.
*/
template <typename T>
void SmartFixedArray<T>::ShiftRight( int index )
{
    if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartFixedArray<T>::ShiftRight", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }
    else if ( m_itemCount == ARRAY_SIZE )
    {
        throw StructureFullException( "SmartFixedArray<T>::ShiftRight", "Array is full and cannot store more items!" );
    }

    for ( int i = m_itemCount; i > index; i-- )
    {
        m_array[i] = m_array[i-1];
    }
//    throw NotImplementedException( "SmartFixedArray<T>::ShiftRight" ); // Erase this once you work on this function
}

/**
PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:

* Check if the array is full with the IsFull() function. If it is full, throw a StructureFullException.

READY TO INSERT:
1. Put the newItem into the array at the first empty position available.
2. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the end of the array.
*/
template <typename T>
void SmartFixedArray<T>::PushBack( T newItem )
{
    if ( IsFull() )
    {
        throw StructureFullException( "SmartFixedArray<T>::PushBack", "Array is full and cannot store more items!" );
    }

    m_array[ m_itemCount ] = newItem;
    m_itemCount++;

//    throw NotImplementedException( "SmartFixedArray<T>::PushBack" ); // Erase this once you work on this function
}

/**
PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:

* Check if the array is full with the IsFull() function. If it is full, throw a StructureFullException.
* Check if the array is not empty using the IsEmpty() function. If it is NOT empty, then call ShiftRight() with index 0 to make space for the new item.

READY TO INSERT:
1. Put the newItem into the array at the first index of the array.
2. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the beginning of the array.
*/
template <typename T>
void SmartFixedArray<T>::PushFront( T newItem )
{
    if ( IsFull() )
    {
        throw StructureFullException( "SmartFixedArray<T>::PushFront", "Array is full and cannot store more items!" );
    }
    if ( !IsEmpty() )
    {
        ShiftRight( 0 );
    }

    m_array[ 0 ] = newItem;
    m_itemCount++;
//    throw NotImplementedException( "SmartFixedArray<T>::PushFront" ); // Erase this once you work on this function
}

/**
DRY CHECK - Don't Repeat Yourself:
1. If index is 0, you can call InsertFront() with the newItem instead.
2. If index is m_itemCount, you can call InsertBack() with the newItem istead.

PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:

* Check if the array is full with the IsFull() function. If it is full, throw a StructureFullException.

READY TO INSERT:
1. Call ShiftRight() on the index to make space for this newItem.
2. Put the newItem into the array at the first index of the array.
3. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the beginning of the array.
@param      index           Index location in the array - where to put the newItem.
*/
template <typename T>
void SmartFixedArray<T>::PushAt( T newItem, int index )
{
    if ( index == 0 )
    {
        PushFront( newItem );
        return;
    }
    else if ( index == m_itemCount )
    {
        PushBack( newItem );
        return;
    }

    if ( index < 0 || index > m_itemCount )
    {
        throw InvalidIndexException( "SmartDynamicArray<T>::PushAt", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }

    if ( IsFull() )
    {
        throw StructureFullException( "SmartFixedArray<T>::PushAt", "Array is full and cannot store more items!" );
    }

    ShiftRight( index );
    m_array[ index ] = newItem;
    m_itemCount++;

//    throw NotImplementedException( "SmartFixedArray<T>::PushAt" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is currently empty, then throw a StructureEmptyException exception - we cannot remove an item from an empty array!

READY TO REMOVE:
When we're just removing the last item of the array, we only need to decrement m_itemCount by 1.
This is known as a "Lazy Deletion"; we're not explicitly removing the item, but it will be replaced later on.
*/
template <typename T>
void SmartFixedArray<T>::PopBack()
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartFixedArray<T>::PopBack", "Array is empty!" );
    }
    m_itemCount--;

//    throw NotImplementedException( "SmartFixedArray<T>::PopBack" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is currently empty, then throw a StructureEmptyException exception - we cannot remove an item from an empty array!

READY TO REMOVE:
1. Call ShiftLeft() on index 0; this will replace the item at index 0 with its neighbor to the right (and everything else will be shifted, too.)
2. Decrement the m_itemCount by 1.
*/
template <typename T>
void SmartFixedArray<T>::PopFront()
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartFixedArray<T>::PopFront", "Array is empty!" );
    }
    ShiftLeft( 0 );
    m_itemCount--;

//    throw NotImplementedException( "SmartFixedArray<T>::PopFront" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is currently empty, then throw a StructureEmptyException exception - we cannot remove an item from an empty array!
2. If the index is invalid, throw a InvalidIndexException.

READY TO REMOVE:
1. Call ShiftLeft() with the index passed in; this will overwrite the item we're removing, and also shift everything after it to the left.
2. Decrement the m_itemCount by 1.

@param      index       The index of the element to remove.
*/
template <typename T>
void SmartFixedArray<T>::PopAt( int index )
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartFixedArray<T>::PopAt", "Array is empty!" );
    }
    else if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartFixedArray<T>::PopAt", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }
    ShiftLeft( index );
    m_itemCount--;

//    throw NotImplementedException( "SmartFixedArray<T>::PopAt" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.

READY TO GET:
Return the last element stored in the array.
*/
template <typename T>
T SmartFixedArray<T>::GetBack() const
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartFixedArray<T>::GetBack", "Array is empty!" );
    }

    return m_array[m_itemCount - 1];

//    throw NotImplementedException( "SmartFixedArray<T>::GetBack" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.

READY TO GET:
Return the first element stored in the array.
*/
template <typename T>
T SmartFixedArray<T>::GetFront() const
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartFixedArray<T>::GetFront", "Array is empty!" );
    }

    return m_array[0];

//    throw NotImplementedException( "SmartFixedArray<T>::GetFront" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.
2. If the index is out of range, throw a InvalidIndexException.

READY TO GET:
Return the element at this index.

@param      index       The index of the element to return.
*/
template <typename T>
T SmartFixedArray<T>::GetAt( int index ) const
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartFixedArray<T>::GetAt", "Array is empty!" );
    }
    else if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartFixedArray<T>::GetAt", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }

    return m_array[index];

//    throw NotImplementedException( "SmartFixedArray<T>::GetAt" ); // Erase this once you work on this function
}

/**
Use a for loop to check each element of the array. Within the loop,
if a match is found, return i. (Don't do an "else" case here.)

Outside of the for loop, we have searched the entire array and the
item hasn't been found. In this case, throw a ItemNotFoundException.
*/
template <typename T>
int SmartFixedArray<T>::Search( T item ) const
{
    for ( int i = 0; i < m_itemCount; i++ )
    {
        if ( m_array[i] == item )
        {
            return i;
        }
    }
    throw ItemNotFoundException( "SmartFixedArray<T>::Search", "Could not find item!" );
//    throw NotImplementedException( "SmartFixedArray<T>::Search" ); // Erase this once you work on this function
}


#endif
