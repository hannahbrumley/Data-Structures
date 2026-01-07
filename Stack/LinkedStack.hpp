#ifndef LINKED_STACK_HPP
#define LINKED_STACK_HPP

#include "../LinkedList/LinkedList.hpp"
#include "../../Utilities/Logger.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

template <typename T>
//! A last-in-first-out (LIFO) stack structure built on top of a linked list
class LinkedStack
{
public:
    //! Push a new item into the back of the queue
    void Push(const T& newData );
    //! Remove the item at the front of the queue
    void Pop();
    //! Access the data at the front of the queue
    T Top();
    //! Get the amount of items in the queue
    int Size();
    //! Return whether the queue is empty
    bool IsEmpty();

private:
    LinkedList<T> m_list;

    friend class StackTester;
};

template <typename T>
void LinkedStack<T>::Push(const T& newData )
{
    m_list.PushBack(newData); 
}

template <typename T>
void LinkedStack<T>::Pop() 
{
    m_list.PopBack(); 
}

template <typename T>
T LinkedStack<T>::Top()
{
    return m_list.GetBack(); 
}

template <typename T>
int LinkedStack<T>::Size()
{
    return m_list.Size(); 
}

template <typename T>
bool LinkedStack<T>::IsEmpty()
{
    return m_list.IsEmpty(); 
}

#endif
