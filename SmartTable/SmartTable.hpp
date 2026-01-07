#ifndef _SMART_TABLE_HPP
#define _SMART_TABLE_HPP

#include "SmartTableNode.hpp"
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
class SmartTable
{
public:
    /* Public member methods */
    //! Sets up the SmartTable.
    SmartTable();
    //! Cleans up the SmartTable.
    ~SmartTable();

    //! Insert an item at some index in the array.
    void PushAt(T newItem, int index);

    //! Remove an item in the middle of the array. Close up the gap.
    void PopAt(int index);

    //! Get an item in the array at some index.
    T& GetAt(int index) const;

    bool ItemAtIndex(int index) const;

    //! Search for an item by its value, return the index of its position.
    int Search(T item) const;

    //! Display all the elements of the array.
    void Display() const;

    //! Output all elements to the stream
    void Display(ostream& outstream) const;

    //! Returns the amount of items currently stored in the array.
    int Size() const;

    //! Returns the size of the internal array
    int ArraySize() const;

    //! Check if the array is currently empty.
    bool IsEmpty() const;

    //! Check if the array is currently full.
    bool IsFull() const;

    //! Deallocates memory for the array and resets the member variables.
    void Clear();

    //! Allocate memory for the dynamic array.
    void AllocateMemory(int size);

private:
    /* Private member variables */
    //! The pointer used for the dynamic array
    SmartTableNode<T>* m_array;

    //! The current size of the array
    int m_arraySize;

    //! The current amount of items inserted into the array
    int m_itemCount;

    /* Private member methods */

    //! Checks whether a number is prime
    bool IsPrime(int value);

    //! Gets the next prime value for m_arraySize
    int GetNextPrime(int value);

    friend class HashTableTester;
};

template <typename T>
SmartTable<T>::SmartTable()
{
    m_array = nullptr;
    Clear();
}

template <typename T>
SmartTable<T>::~SmartTable()
{
    Clear();
}

template <typename T>
void SmartTable<T>::Clear()
{
    if (m_array != nullptr)
    {
        delete[] m_array;
        m_array = nullptr;
    }
    m_arraySize = 0;
    m_itemCount = 0;
}

template <typename T>
void SmartTable<T>::Display() const
{
    Display(cout);
    //    throw NotImplementedException( "SmartTable<T>::Display" ); // Erase this once you work on this function
}

template <typename T>
void SmartTable<T>::Display(ostream& outstream) const
{
    for (int i = 0; i < m_itemCount; i++)
    {
        outstream << i << ". " << m_array[i] << endl;
    }
}

template <typename T>
int SmartTable<T>::Size() const
{
    return m_itemCount;
}

template <typename T>
int SmartTable<T>::ArraySize() const
{
    return m_arraySize;
}

template <typename T>
bool SmartTable<T>::IsFull() const
{
    return (m_itemCount == m_arraySize);
}

template <typename T>
bool SmartTable<T>::IsEmpty() const
{
    return (m_itemCount == 0);
}

template <typename T>
void SmartTable<T>::AllocateMemory(int size)
{
    if (m_array != nullptr)
    {
        throw logic_error("Can't allocate memory, m_array is already pointing to a memory address!");
    }

    m_array = new SmartTableNode<T>[size];
    m_arraySize = size;
    m_itemCount = 0;

    //    throw NotImplementedException( "SmartTable<T>::AllocateMemory" ); // Erase this once you work on this function
}

/**
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
void SmartTable<T>::PushAt(T newItem, int index)
{
    if (index < 0 || index > m_arraySize)
    {
        throw InvalidIndexException("SmartTable<T>::PushAt", "Index " + StringUtil::ToString(index) + " is out of bounds!");
    }

    if (m_array == nullptr)
    {
        AllocateMemory(10);
    }
    else if (IsFull())
    {
        throw StructureFullException("SmartTable<T>::PushAt", "Structure is full!");
    }

    m_array[index] = newItem;
    m_itemCount++;
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
void SmartTable<T>::PopAt(int index)
{
    if (IsEmpty())
    {
        throw StructureEmptyException("SmartTable<T>::PopAt", "Array is empty!");
    }
    else if (index < 0 || index >= m_arraySize)
    {
        throw InvalidIndexException("SmartTable<T>::PopAt", "Index " + StringUtil::ToString(index) + " is out of bounds!");
    }
    m_itemCount--;
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
T& SmartTable<T>::GetAt(int index) const
{
    if (IsEmpty())
    {
        throw StructureEmptyException("SmartTable<T>::GetAt", "Array is empty!");
    }
    else if (index < 0 || index >= m_arraySize)
    {
        throw InvalidIndexException("SmartTable<T>::GetAt", "Index " + StringUtil::ToString(index) + " is out of bounds!");
    }
    else if (!m_array[index].used)
    {
        throw ItemNotFoundException("Index not in use", "Index " + StringUtil::ToString(index));
    }

    return m_array[index].data;
}

template <typename T>
bool SmartTable<T>::ItemAtIndex(int index) const
{
    if (index < 0 || index >= m_arraySize)
    {
        throw InvalidIndexException("SmartTable<T>::GetAt", "Index " + StringUtil::ToString(index) + " is out of bounds!");
    }

    return (m_array[index].used);
}

/**
Use a for loop to check each element of the array. Within the loop,
if a match is found, return i. (Don't do an "else" case here.)

Outside of the for loop, we have searched the entire array and the
item hasn't been found. In this case, throw an ItemNotFoundException.
*/
template <typename T>
int SmartTable<T>::Search(T item) const
{
    for (int i = 0; i < m_arraySize; i++)
    {
        if (m_array[i] == item)
        {
            return i;
        }
    }
    throw ItemNotFoundException("SmartTable<T>::Search", "Could not find item!");
}

//! Checks whether a number is prime
template <typename T>
bool SmartTable<T>::IsPrime(int value)
{
    for (int i = 2; (i * i) <= value; i++)
    {
        if ((value % i) == 0)
        {
            return false;
        }
    }
    return true;
}

//! Gets the next prime value for m_arraySize
template <typename T>
int SmartTable<T>::GetNextPrime(int value)
{
    int i;
    for (i = value + 1; ; i++)
    {
        if (IsPrime(i))
        {
            break;
        }
    }

    return i;
}

#endif
