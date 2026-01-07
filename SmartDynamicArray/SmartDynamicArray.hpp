#ifndef _SMART_DYNAMIC_ARRAY_HPP
#define _SMART_DYNAMIC_ARRAY_HPP

#include "../Interfaces/ILinearDataStructure.hpp"
#include "../../Utilities/StringUtil.hpp"

#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/StructureEmptyException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/ItemNotFoundException.hpp"
#include "../../Exceptions/NullptrException.hpp"

#include <iostream>
using namespace std;

template <typename T>
//! A data structure that wraps a dynamic array
class SmartDynamicArray : public ILinearDataStructure<T>
{
public:
    /* Public member methods */
    //! Sets up the SmartDynamicArray.
    SmartDynamicArray();
    //! Cleans up the SmartDynamicArray.
    ~SmartDynamicArray();

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

    //! Deallocates memory for the array and resets the member variables.
    void Clear();

private:
    /* Private member variables */
    //! The pointer used for the dynamic array
    T* m_array;

    //! The current size of the array
    int m_arraySize;

    //! The current amount of items inserted into the array
    int m_itemCount;

    /* Private member methods */
    //! Move all items past the given index to the left.
    void ShiftLeft( int index );
    //! Move all items past the given index to the right.
    void ShiftRight( int index );

    //! Allocate memory for the dynamic array.
    void AllocateMemory( int size );
    //! Resize the dynamic array.
    void Resize( int newSize );

    //! Check if the array is currently full.
    bool IsFull() const;

    friend class SmartDynamicArrayTester;
};

/**
When initializing a class that contains POINTERS, those pointers should be initialized to nullptr.
Initialize the m_array variable to nullptr and then call the Clear function.
*/
template <typename T>
SmartDynamicArray<T>::SmartDynamicArray()
{
    m_array = nullptr;
    Clear();
}

/**
Clean up the SmartDynamicArray by calling the Clear function.
*/
template <typename T>
SmartDynamicArray<T>::~SmartDynamicArray()
{
    Clear();
}

/**
This function will:
- Check if m_array is pointing to a memory address, if so:
    - Free the memory at that address.
    - Reset m_array to nullptr.
- Reset the m_arraySize to 0.
- Reset the m_itemCount to 0.
*/
template <typename T>
void SmartDynamicArray<T>::Clear()
{
    if ( m_array != nullptr )
    {
        delete [] m_array;
        m_array = nullptr;
    }
    m_arraySize = 0;
    m_itemCount = 0;
}



/**
Iterate through the entire array, displaying the index and value of each element.
*/
template <typename T>
void SmartDynamicArray<T>::Display() const
{
    for ( int i = 0; i < m_itemCount; i++ )
    {
        cout << i << ". " << m_array[i] << endl;
    }
//    throw NotImplementedException( "SmartDynamicArray<T>::Display" ); // Erase this once you work on this function
}

/**
Iterate through the entire array, displaying the index and value of each element.
*/
template <typename T>
void SmartDynamicArray<T>::Display( ostream& outstream ) const
{
}

/**
Return the value of m_itemCount;
*/
template <typename T>
int SmartDynamicArray<T>::Size() const
{
    return m_itemCount;
}

/**
The array is full if m_itemCount is the same value as m_arraySize.

@return     true if the array is full, false otherwise.
*/
template <typename T>
bool SmartDynamicArray<T>::IsFull() const
{
    return ( m_itemCount == m_arraySize );
}

/**
Check if the array is currently empty.
The array is empty if the m_itemCount is set to 0.

@return     true if empty, false otherwise.
*/
template <typename T>
bool SmartDynamicArray<T>::IsEmpty() const
{
    return ( m_itemCount == 0 );
}

/**
ERROR CHECK:
1. If m_array is not nullptr, then throw a logic_error - we don't want to remove data that has been allocated.
(https://www.cplusplus.com/reference/stdexcept/logic_error/)

READY TO ALLOCATE:
1. Use the m_array pointer to allocate space for a new T array of the size given.
2. Set the m_arraySize to the size given.
3. Set the m_itemCount to 0.

@param      size        The size to set up the array with.
*/
template <typename T>
void SmartDynamicArray<T>::AllocateMemory( int size )
{
    if ( m_array != nullptr )
    {
        throw logic_error( "Can't allocate memory, m_array is already pointing to a memory address!" );
    }

    m_array = new T[ size ];
    m_arraySize = size;
    m_itemCount = 0;

//    throw NotImplementedException( "SmartDynamicArray<T>::AllocateMemory" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the newSize is smaller than the current m_arraySize, throw a invalid_argument exception.
(https://www.cplusplus.com/reference/stdexcept/invalid_argument/)

DRY CHECK - Don't Repeat Yourself:
1. If m_array is currently poing to nullptr, call AllocateMemory() with the newSize instead.

READY TO RESIZE:
1. Create a new pointer of type T*, use it to allocate space for an array of T of size newSize.     (`T* newArray = new T[newSize];`)
2. Copy the values over from m_array to newArray (use a for loop).
3. Deallocate the memory for the old array via m_array.                                             (`delete [] m_array;`)
4. Update the pointer; point m_array to the newArray address.                                       (`m_array = newArray;`)
5. Update the m_arraySize to the newSize.
*/
template <typename T>
void SmartDynamicArray<T>::Resize( int newSize )
{
    if ( newSize < m_arraySize )
    {
        throw logic_error( "New array size is smaller than old array size!" );
    }
    else if ( m_array == nullptr )
    {
        AllocateMemory( newSize );
    }
    else
    {
        // Allocate more memory
        T* newArray = new T[newSize];

        // Copy values over
        for ( int i = 0; i < m_itemCount; i++ )
        {
            newArray[i] = m_array[i];
        }

        // Deallocate old space
        delete [] m_array;

        // Update pointer
        m_array = newArray;

        // Update size
        m_arraySize = newSize;
    }

//    throw NotImplementedException( "SmartDynamicArray<T>::Resize" ); // Erase this once you work on this function
}


/**
ERROR CHECK:
1. If m_array is pointing to nullptr, then throw a NullptrException.
2. If the index is invalid, throw an InvalidIndexException

READY TO SHIFT:
Use a for loop, use a counter variable (like i),
- INITIALIZATION:   Starting at the index passed in
- CONDITION:        Continue looping while i is less than the index of the last element of the array.
- UPDATE:           Increment your i counter by 1 each time.

Within the array, set the element at position i to the value of the element at position i-1.

@param      index       The index where items will be shifted left from.
*/
template <typename T>
void SmartDynamicArray<T>::ShiftLeft( int index )
{
    if ( m_array == nullptr )
    {
        throw NullptrException( "SmartDynamicArray<T>::ShiftLeft", "m_array is nullptr!" );
    }
    else if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartDynamicArray<T>::ShiftLeft", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }

    for ( int i = index; i < m_itemCount-1; i++ )
    {
        m_array[i] = m_array[i+1];
    }

//    throw NotImplementedException( "SmartDynamicArray<T>::ShiftLeft" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If m_array is pointing to nullptr, then throw a NullptrException.
2. If the index is invalid, throw an InvalidIndexException.

PREP CHECK:
1. If adding one item to the list (m_itemCount+1) is equal to the m_arraySize, then call the Resize() function with a larger size.

READY TO SHIFT:
Use a for loop, use a counter variable (like i),
- INITIALIZATION:   Starting at the first empty spot in the array.
- CONDITION:        Continue looping while i is greater than the index passed in we will keep looping.
- UPDATE:           Decrement i by 1 each time.

Within the array, set the element at position i to the value of the element at position i+1.

@param      index       The index where items will be shifted right from.
*/
template <typename T>
void SmartDynamicArray<T>::ShiftRight( int index )
{
    if ( m_array == nullptr )
    {
        throw NullptrException( "SmartDynamicArray<T>::ShiftRight", "m_array is nullptr!" );
    }
    else if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartDynamicArray<T>::ShiftRight", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }
    else if ( m_itemCount + 1 == m_arraySize )
    {
        Resize( m_arraySize + 10 );
    }

    for ( int i = m_itemCount; i > index; i-- )
    {
        m_array[i] = m_array[i-1];
    }
//    throw NotImplementedException( "SmartDynamicArray<T>::ShiftRight" ); // Erase this once you work on this function
}

/**
PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:
1. Check if the m_array is pointing to nullptr. If so, call AllocateMemory() with some initial array size.
2. Check if the array is full with the IsFull() function. If it is full, call the Resize() function with a new size.

READY TO INSERT:
1. Put the newItem into the array at the first empty position available.
2. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the end of the array.
*/
template <typename T>
void SmartDynamicArray<T>::PushBack( T newItem )
{
    if ( m_array == nullptr )
    {
        AllocateMemory( 10 );
    }
    else if ( IsFull() )
    {
        Resize( m_arraySize + 10 );
    }

    m_array[ m_itemCount ] = newItem;
    m_itemCount++;

//    throw NotImplementedException( "SmartDynamicArray<T>::PushBack" ); // Erase this once you work on this function
}

/**
PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:
1. Check if the m_array is pointing to nullptr. If so, call AllocateMemory() with some initial array size.
2. Check if the array is full with the IsFull() function. If it is full, call the Resize() function with a new size.
3. Check if the array is not empty using the IsEmpty() function. If it is NOT empty, then call ShiftRight() with index 0 to make space for the new item.

READY TO INSERT:
1. Put the newItem into the array at the first index of the array.
2. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the beginning of the array.
*/
template <typename T>
void SmartDynamicArray<T>::PushFront( T newItem )
{
    if ( m_array == nullptr )
    {
        AllocateMemory( 10 );
    }
    else if ( IsFull() )
    {
        Resize( m_arraySize + 10 );
    }
    if ( !IsEmpty() )
    {
        ShiftRight( 0 );
    }

    m_array[ 0 ] = newItem;
    m_itemCount++;
//    throw NotImplementedException( "SmartDynamicArray<T>::PushFront" ); // Erase this once you work on this function
}

/**
DRY CHECK - Don't Repeat Yourself:
1. If index is 0, you can call InsertFront() with the newItem instead.
2. If index is m_itemCount, you can call InsertBack() with the newItem istead.

PREP CHECKS - do these before inserting the data to make sure the array is in a valid state:
1. Check if the m_array is pointing to nullptr. If so, call AllocateMemory() with some initial array size.
2. Check if the array is full with the IsFull() function. If it is full, call the Resize() function with a new size.

READY TO INSERT:
1. Call ShiftRight() on the index to make space for this newItem.
2. Put the newItem into the array at the first index of the array.
3. Increment the m_itemCount by 1.

@param      newItem         The new item to store at the beginning of the array.
@param      index           Index location in the array - where to put the newItem.
*/
template <typename T>
void SmartDynamicArray<T>::PushAt( T newItem, int index )
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

    if ( m_array == nullptr )
    {
        AllocateMemory( 10 );
    }
    else if ( IsFull() )
    {
        Resize( m_arraySize + 10 );
    }

    ShiftRight( index );
    m_array[ index ] = newItem;
    m_itemCount++;

//    throw NotImplementedException( "SmartDynamicArray<T>::PushAt" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.

READY TO REMOVE:
When we're just removing the last item of the array, we only need to decrement m_itemCount by 1.
This is known as a "Lazy Deletion"; we're not explicitly removing the item, but it will be replaced later on.
*/
template <typename T>
void SmartDynamicArray<T>::PopBack()
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartDynamicArray<T>::PopBack", "Array is empty!" );
    }
    m_itemCount--;

//    throw NotImplementedException( "SmartDynamicArray<T>::PopBack" ); // Erase this once you work on this function
}


/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.

READY TO REMOVE:
1. Call ShiftLeft() on index 0; this will replace the item at index 0 with its neighbor to the right (and everything else will be shifted, too.)
2. Decrement the m_itemCount by 1.
*/
template <typename T>
void SmartDynamicArray<T>::PopFront()
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartDynamicArray<T>::PopFront", "Array is empty!" );
    }
    ShiftLeft( 0 );
    m_itemCount--;

//    throw NotImplementedException( "SmartDynamicArray<T>::PopFront" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.
2. If the index is out of range, throw an InvalidIndexException exception.

READY TO REMOVE:
1. Call ShiftLeft() with the index passed in; this will overwrite the item we're removing, and also shift everything after it to the left.
2. Decrement the m_itemCount by 1.

@param      index       The index of the element to remove.
*/
template <typename T>
void SmartDynamicArray<T>::PopAt( int index )
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartDynamicArray<T>::PopAt", "Array is empty!" );
    }
    else if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartDynamicArray<T>::PopAt", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }
    ShiftLeft( index );
    m_itemCount--;

//    throw NotImplementedException( "SmartDynamicArray<T>::PopAt" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.

READY TO GET:
Return the last element stored in the array.
*/
template <typename T>
T SmartDynamicArray<T>::GetBack() const
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartDynamicArray<T>::GetBack", "Array is empty!" );
    }

    return m_array[m_itemCount - 1];

//    throw NotImplementedException( "SmartDynamicArray<T>::GetBack" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.

READY TO GET:
Return the first element stored in the array.
*/
template <typename T>
T SmartDynamicArray<T>::GetFront() const
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartDynamicArray<T>::GetFront", "Array is empty!" );
    }

    return m_array[0];

//    throw NotImplementedException( "SmartDynamicArray<T>::GetFront" ); // Erase this once you work on this function
}

/**
ERROR CHECK:
1. If the array is empty, then we can't return anything; throw a StructureEmptyException.
2. If the index is out of range, throw an InvalidIndexException exception.

READY TO GET:
Return the element at this index.

@param      index       The index of the element to return.
*/
template <typename T>
T SmartDynamicArray<T>::GetAt( int index ) const
{
    if ( IsEmpty() )
    {
        throw StructureEmptyException( "SmartDynamicArray<T>::GetAt", "Array is empty!" );
    }
    else if ( index < 0 || index >= m_itemCount )
    {
        throw InvalidIndexException( "SmartDynamicArray<T>::GetAt", "Index " + StringUtil::ToString( index ) + " is out of bounds!" );
    }

    return m_array[index];

//    throw NotImplementedException( "SmartDynamicArray<T>::GetAt" ); // Erase this once you work on this function
}

/**
Use a for loop to check each element of the array. Within the loop,
if a match is found, return i. (Don't do an "else" case here.)

Outside of the for loop, we have searched the entire array and the
item hasn't been found. In this case, throw an ItemNotFoundException.
*/
template <typename T>
int SmartDynamicArray<T>::Search( T item ) const
{
    for ( int i = 0; i < m_itemCount; i++ )
    {
        if ( m_array[i] == item )
        {
            return i;
        }
    }
    throw ItemNotFoundException( "SmartDynamicArray<T>::Search", "Could not find item!" );
}


#endif
