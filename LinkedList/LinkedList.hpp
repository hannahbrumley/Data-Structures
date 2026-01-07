#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "../Interfaces/ILinearDataStructure.hpp"

#include "LinkedListNode.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"
#include "../../Utilities/Logger.hpp"
#include "../../Utilities/StringUtil.hpp"

#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/StructureEmptyException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/ItemNotFoundException.hpp"
#include "../../Exceptions/NullptrException.hpp"

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class LinkedList : public ILinearDataStructure<T>
{
private:
    /* Member Variables */
    //! A pointer to the first item in the list
    DoublyLinkedListNode<T>* m_ptrFirst;
    //! A pointer to the last item in the list
    DoublyLinkedListNode<T>* m_ptrLast;
    //! The amount of items stored in the list
    int m_itemCount;

public:
    /* Member Functions */
    LinkedList();
    virtual ~LinkedList();

    //! Add a new item to the front of the list
    virtual void PushFront(T newData);
    //! Add a new item to the back of the list
    virtual void PushBack(T newData);
    //! Insert an item at some index in the list
    virtual void PushAt(T newItem, int index);

    //! Remove the front-most item
    virtual void PopFront();
    //! Remove the last item
    virtual void PopBack();
    //! Remove an item in the middle
    virtual void PopAt(int index);

    //! Get the data of the front-most item
    virtual T GetFront() const;
    //! Get the data of the back-most item
    virtual T GetBack() const;
    //! Subscript operator to get an item at an arbitrary index
    virtual T GetAt(int index) const;

    //! Display all the elements of the array.
    virtual void Display() const;

    //! Output all elements to the stream
    void Display(ostream& outstream) const;

    //! Returns the amount of items currently stored in the array.
    virtual int Size() const;

    //! Check if the array is currently empty.
    virtual bool IsEmpty() const;

    //! Clear all items out of the list
    virtual void Clear();

    //! Returns whether the given index is invalid.
    bool IsInvalidIndex(int index) const;

    friend class LinkedListTester;
};

/* -----------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------- LinkedList */
/**
    - Initialize the first and last pointers to nullptr.
    - Set the item count to 0.
*/
template <typename T>
LinkedList<T>::LinkedList()
{
    m_ptrFirst = nullptr;
    m_ptrLast = nullptr;
    m_itemCount = 0;
}

/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------- ~LinkedList */
/**
    Call the Clear function
*/
template <typename T>
LinkedList<T>::~LinkedList()
{

    Clear();
}

/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------- Clear */
/**
    @return void

    - While the list is not empty...
        - Pop the front most item.
*/
template <typename T>
void LinkedList<T>::Clear() /*                                                  Clear */
{
    while (!IsEmpty())
    {
        PopFront();

    }

}

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------ PushFront */
/**
    @param  T newData       New item to add to the list
    @return void

    Add a new item to the beginning of the list.

    - Create a DoublyLinkedListNode<T>* pointer, and allocate new memory via it.
    - Set the new node's data to the newData.
    - Increment the item count
    - If the list is currently empty...
        - Set the first and last pointers to this new pointer.
    - Otherwise...
        - Set the first pointer's previous item to this new pointer.
        - Set the new node's next pointer to the first item.
        - Update the first pointer to point to the new item.

```
    OLD LIST
                m_ptrFirst           m_ptrFirst->m_ptrNext
                -----       ->       ----- -> ...
                | A |                | B |
    nullptr <-  -----       <-       -----

    NEW LIST
                m_ptrFirst           m_ptrFirst->m_ptrNext
                -----       ->       -----      ->              -----   -> ...
                | X |                | A |                      | B |
    nullptr <-  -----       <-       -----      <-              -----
```
*/
template <typename T>
void LinkedList<T>::PushFront(T newData)
{
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>;

    newNode->m_data = newData;

    if (IsEmpty())
    {
        m_ptrFirst = newNode;
        m_ptrLast = newNode;
    }
    else
    {
        DoublyLinkedListNode<T>* oldFirst = m_ptrFirst;
        DoublyLinkedListNode<T>* newFirst = newNode;


        oldFirst->m_ptrPrev = newFirst;
        newFirst->m_ptrNext = oldFirst;

        m_ptrFirst = newFirst;
    }

    m_itemCount++;
}


/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------- PushBack */
/**
    @param  T newData       New item to add to the list
    @return void

    Add a new item to the end of the list.

    - Create a DoublyLinkedListNode<T>* pointer, and allocate new memory via it.
    - Set the new node's data to the newData.
    - Increment the item count
    - If the list is currently empty...
        - Set the first and last pointers to this new pointer.
    - Otherwise...
        - Set the last pointer's next item to this new pointer.
        - Set the new node's previous pointer to the last item.
        - Update the last pointer to point to the new item.

```
    OLD LIST
           m_ptrLast->ptrPrev   m_ptrLast
           -----   ->           ----- -> nullptr
           | A |                | B |
    ... <- -----   <-           -----

    NEW LIST
                                m_ptrLast->ptrPrev      m_ptrLast
           -----   ->           -----       ->          -----   --> nullptr
           | A |                | B |                   | X |
    ... <- -----   <-           -----       <-          -----
```
*/
template <typename T>
void LinkedList<T>::PushBack(T newData)
{
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>;

    newNode->m_data = newData;

    if (IsEmpty())
    {
        m_ptrLast = newNode;
        m_ptrFirst = newNode;
    }
    else
    {
        DoublyLinkedListNode<T>* oldLast = m_ptrLast;
        DoublyLinkedListNode<T>* newLast = newNode;


        oldLast->m_ptrNext = newLast;
        newLast->m_ptrPrev = oldLast;

        m_ptrLast = newLast;
    }

    m_itemCount++;
}


/* -----------------------------------------------------------------------------------------*/
/* --------------------------------------------------------------------------------- PushAt */
/**
    @param  T       newItem
    @param  int     index

    Add a new item mid-list

    - If the index is 0, then call PushFront, passing in the newItem
    - Otherwise if the index is m_itemCount, then call PushBack, passing in the newItem
    - Otherwise if the index is invalid, throw an InvalidIndexException
    - Otherwise if all is in good order, then allocate memory for the new node and update pointers appropriately.

```
    OLD LIST
           index-1     index
           -----   ->  ----- -> ...
           | A |       | B |
    ... <- -----   <-  -----

    NEW LIST
           index-1     index       index + 1
           -----   ->  -----   ->  ----- -> ...
           | A |       | X |       | B |
    ... <- -----   <-  -----   <-  -----
```
*/
template <typename T>
void LinkedList<T>::PushAt(T newItem, int index)
{
    DoublyLinkedListNode<T>* newNode = new DoublyLinkedListNode<T>;

    newNode->m_data = newItem;
    if (index == 0)
    {
        PushFront(newItem);
    }
    else if (index == m_itemCount)
    {
        PushBack(newItem);
    }
    else if (IsInvalidIndex(index))
    {
        throw InvalidIndexException("LinkedList<T>::PushAt", "Invalid Index!");
    }

    else
    {
        DoublyLinkedListNode<T>* ptrCurrent = m_ptrFirst;

        int counter = 0;

        while (counter != index)
        {
            ptrCurrent = ptrCurrent->m_ptrNext;
            counter++;
        }


        ptrCurrent->m_ptrPrev->m_ptrNext = newNode;
        newNode->m_ptrPrev = ptrCurrent->m_ptrPrev;
        ptrCurrent->m_ptrPrev = newNode;
        newNode->m_ptrNext = ptrCurrent;

        m_itemCount++;





    }
}

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------- PopFront */
/**
    @return void

    Remove the first-most item in the list, and update the m_ptrFirst to point
    to the new first item.

    - If the list is Empty... do nothing
    - Else, if there is only one item in the list:
        - Delete (either the first or last) node in the list (only one).
        - Set the first and last pointer to nullptr
        - Decrement the item count
    - Else:
        - Create a pointer to point to the second item.
        - Set the second item's previous pointer to nullptr.
        - Delete the first item
        - Set the m_ptrFirst pointer to that second item.
        - Decrement the item count

```
    OLD LIST
                    m_ptrFirst           m_ptrFirst->m_ptrNext
                    -----        ->      ----- -> ...
                    | A |                | B |
    nullptr     <-  -----        <-      -----

    NEW LIST
                    m_ptrFirst
                    -----        ->     ...
                    | A |
    nullptr     <-  -----

```
*/
template <typename T>
void LinkedList<T>::PopFront()
{
    if (IsEmpty())
    {
        throw StructureEmptyException("LinkedList<T>::PopFront", "Cannot pop from empty list");
    }

    else if (Size() == 1)
    {
        delete m_ptrFirst;
        m_ptrFirst = nullptr;
        m_ptrLast = nullptr;
    }
    else
    {




        DoublyLinkedListNode<T>* oldFirst = m_ptrFirst;
        DoublyLinkedListNode<T>* newFirst = m_ptrFirst->m_ptrNext;

        m_ptrFirst = newFirst;
        delete oldFirst;
        //newFirst->m_ptrPrev = nullptr; 

        /*
        DoublyLinkedListNode<T>* oldLast = m_ptrLast;
        DoublyLinkedListNode<T>* newLast = m_ptrLast->m_ptrPrev;

        m_ptrLast = newLast;
        delete oldLast;
        newLast->m_ptrNext = nullptr;
        */
    }

    m_itemCount--;
}


/* -----------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------- PopBack */
/**
    @return void

    Remove the last-most item in the list, and update the m_ptrLast to point
    to the new last item.

    - If the list is Empty... do nothing
    - Else, if there is only one item in the list:
        - Delete (either the first or last) node in the list (only one).
        - Set the first and last pointer to nullptr
        - Decrement the item count
    - Else:
        - Create a pointer to point to the second-to-last item.
        - Set the second-to-last item's next pointer to nullptr.
        - Delete the last item
        - Set the m_ptrLast pointer to that second-to-last item.
        - Decrement the item count

```
    OLD LIST
                m_ptrLast->m_ptrPrev           m_ptrLast
                -----                   ->      ----- -> nullptr
                | A |                           | B |
    ...     <-  -----                   <-      -----

    NEW LIST
                m_ptrLast
                -----       -> nullptr
                | A |
    ...     <-  -----
```
*/
template <typename T>
void LinkedList<T>::PopBack()
{
    if (IsEmpty())
    {
        throw StructureEmptyException("LinkedList<T>::PopBack", "Cannot pop from empty list");
    }

    else if (Size() == 1)
    {
        delete m_ptrLast;
        m_ptrFirst = nullptr;
        m_ptrLast = nullptr;
    }
    else
    {
        DoublyLinkedListNode<T>* oldLast = m_ptrLast;
        DoublyLinkedListNode<T>* newLast = m_ptrLast->m_ptrPrev;

        m_ptrLast = newLast;
        delete oldLast;
        newLast->m_ptrNext = nullptr;
    }

    m_itemCount--;
}


/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------- PopAt */
/**
    @return void
    @param  int     index

    Removes an item at the position `index`.

    - If the list is empty, throw a StructureEmptyException.
    - Otherwise, if the index is invalid, throw an InvalidIndexException.
    - Otherwise, if the index is 0, call PopFront instead.
    - Otherwise, if the index is m_itemCount-1, call PopBack instead.
    - Otherwise...
        - Traverse through the nodes finding the node at the `index`.
        - Take note of the node at index-1 (node->ptrPrev)
        - Take note of the node at index+1 (node->ptrNext)
        - Point node[index-1]'s next ptr to node[index+1]
        - Point node[index+1]'s prev ptr to node[index-1]
        - free the memory for node[index].
        - Decrement the item count

```*/
/*
    OLD LIST
                index-1              index                  index + 1
                -----       ->       -----      ->          -----   -> ...
                | A |                | B |                  | C |
    nullptr <-  -----       <-       -----      <-          -----


    NEW LIST
                index-1                                     index
                -----                   ->                  -----      ->      ...
                | A |                                       | C |
    nullptr <-  -----                   <-                  -----
```

*/
template <typename T>
void LinkedList<T>::PopAt(int index)
{
    if (IsEmpty())
    {
        throw StructureEmptyException("LinkedList<T>::PopAt", "Cannot pop from empty list");
    }
    else if (IsInvalidIndex(index))
    {
        throw InvalidIndexException("LinkedList<T>::PopAt", "Invalid Index!");
    }
    else if (index == 0)
    {
        PopFront();
    }
    else if (index == m_itemCount - 1)
    {
        PopBack();
    }

    else
    {
        DoublyLinkedListNode<T>* ptrCurrent = m_ptrFirst;
        int counter = 0;

        while (counter != index)
        {
            ptrCurrent = ptrCurrent->m_ptrNext;
            counter++;
        }




        ptrCurrent->m_ptrPrev->m_ptrNext = ptrCurrent->m_ptrNext;
        ptrCurrent->m_ptrNext->m_ptrPrev = ptrCurrent->m_ptrPrev;
        delete ptrCurrent;
        ptrCurrent = nullptr;


        /*
=======
>>>>>>> 6daa3407194fd2f70c83df656b042b8f8ce53d80
        ptrCurrent->m_ptrPrev->m_ptrNext = ptrCurrent->m_ptrNext;

        // Alternative: Using some additional pointers can make your code more clear -- Rachel
        //DoublyLinkedListNode<T>* ptrBefore = ptrCurrent->m_ptrPrev;
        //ptrBefore->m_ptrNext = ptrCurrent->m_ptrNext;

        // Removed:
        //ptrCurrent->m_ptrPrev = ptrCurrent->m_ptrNext;                  // Don't need to update ptrCurrent's next, ptrCurrent will be removed.
                                                                          // That line of code was messing up the functionality.
        ptrCurrent->m_ptrNext->m_ptrPrev = ptrCurrent->m_ptrPrev;

        // Alternative: Clearer code
        //DoublyLinkedListNode<T>* ptrAfter = ptrCurrent->m_ptrNext;
        //ptrAfter->m_ptrPrev = ptrCurrent->m_ptrPrev;

        // Removed:
        //ptrCurrent->m_ptrNext = ptrCurrent->m_ptrPrev;                  // Don't need to update ptrCurrent's prev, ptrCurrent will be removed.
                                                                          // That line of code was messing up the functionality.

        // Delete ptrCurrent at this point.
        delete ptrCurrent; // Added -- Rachel
        ptrCurrent = nullptr;


        */

        m_itemCount--;
    }









}

/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------------- GetFront */
/**
    @return T&          The front item in the list is returned

    Error checks:
    - If the list is empty, throw an exception.

    Otherwise, return the data that belongs to the front pointer (m_ptrFirst).

```
                    vvvvv Return this one's data
                    m_ptrFirst                                       m_ptrLast
                    -----        ->           -----       ->         -----   -->  nullptr
                    | A |                    | B |                   | C |
    nullptr     <-  -----        <-           -----       <-         -----
```
*/
template <typename T>
T LinkedList<T>::GetFront() const
{
    if (IsEmpty())
    {
        throw StructureEmptyException("LinkedList<T>::GetFront", "Cannot retrieve data from empty list!");

    }
    return m_ptrFirst->m_data;
}


/* -----------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------- GetBack */
/**
    @return T&          The back item in the list is returned

    Error checks:
    - If the list is empty, throw an exception.

    Otherwise, return the data that belongs to the last pointer (m_ptrLast).

```
                                                                    vvvvv Return this one's data
                    m_ptrFirst                                       m_ptrLast
                    -----        ->           -----       ->         -----   -->  nullptr
                    | A |                    | B |                   | C |
    nullptr     <-  -----        <-           -----       <-         -----
```
*/
template <typename T>
T LinkedList<T>::GetBack() const
{
    if (IsEmpty())
    {
        throw StructureEmptyException("LinkedList<T>::GetBack", "Cannot retrieve data from empty list!");

    }
    return m_ptrLast->m_data;
}


/* -----------------------------------------------------------------------------------------*/
/* ---------------------------------------------------------------------------------- GetAt */
/**
    @param  int index   The position of the item to return.
    @return T&          Returns the item at the given index.

    Error checks:
    - If the list is empty, throw an exception.
    - If the index is invalid, throw an exception.

    Functionality:
    You'll need to traverse through the list, starting at the beginning and moving forward, one-by-one.

    - Create a DoublyLinkedListNode<T>* "walker" pointer to walk through the items. Start it at the m_ptrFirst position.
    - Make a loop that will loop 'index' amount of times. Within the loop...
        - Move your walking pointer forward by one (current = current->m_ptrNext)
    - Once done, return the data of the item (access via the walker pointer.)

```
                                            GetAt( 1 )
                                            vvvvv Return this one's data
                    m_ptrFirst                                       m_ptrLast
                    -----        ->          -----       ->         -----   -->  nullptr
                    | A |                    | B |                   | C |
    nullptr     <-  -----        <-          -----       <-         -----
```
*/
template <typename T>
T LinkedList<T>::GetAt(int index) const
{
    if (IsInvalidIndex(index))
    {
        throw InvalidIndexException("LinkedList<T>::GetAt", "Invalid Index!");
    }


    DoublyLinkedListNode<T>* ptrCurrent = m_ptrFirst;
    int counter = 0;

    while (counter != index)
    {
        ptrCurrent = ptrCurrent->m_ptrNext;
        counter++;
    }

    return ptrCurrent->m_data;
}


/* -----------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------- IsEmpty */
/**
    @return bool    Return true if there are no items stored in the list, and false otherwise.
*/
template <typename T>
bool LinkedList<T>::IsEmpty() const
{
    return (m_itemCount == 0);
}


/* -----------------------------------------------------------------------------------------*/
/* ----------------------------------------------------------------------------------- Size */
/**
    @return int     The amount of items stored in the List. Use m_itemCount here.
*/
template <typename T>
int LinkedList<T>::Size() const
{
    return m_itemCount;
}


/* -----------------------------------------------------------------------------------------*/
/* -------------------------------------------------------------------------------- Display */
// TODO: Implement me
template <typename T>
void LinkedList<T>::Display() const
{
    Display(cout);
}


/**
Iterate through the entire array, displaying the index and value of each element.
*/
template <typename T>
void LinkedList<T>::Display(ostream& outstream) const
{
    DoublyLinkedListNode<T>* ptrCurrent = m_ptrFirst;
    int counter = 0;
    /*while (ptrCurrent != nullptr)
    {
        outstream << counter << ". " << ptrCurrent->m_data << endl;
        ptrCurrent = ptrCurrent->m_ptrNext;
        counter++;
    }*/
    /*
    for ( auto ptrCurrent = m_ptrFirst; ptrCurrent != nullptr; ptrCurrent = ptrCurrent->m_ptrNext )
    {
        outstream << ptrCurrent->m_data << endl;
    }
    */
}


/* -----------------------------------------------------------------------------------------*/
/* ------------------------------------------------------------------------- IsInvalidIndex */
/**
    @param int index    The index to look at.
    @return bool        true if invalid index (less than 0 or >= m_arraySize),
                        or false if not invalid.
*/
//! Check to see if a given index is invalid (i.e., negative).
template <typename T>
bool LinkedList<T>::IsInvalidIndex(int index) const
{
    return (index < 0 || index >= m_itemCount);
}



#endif
