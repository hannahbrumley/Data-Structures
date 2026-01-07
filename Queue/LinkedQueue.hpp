#ifndef LINKED_QUEUE_HPP
#define LINKED_QUEUE_HPP

#include "../LinkedList/LinkedList.hpp"
#include "../../Utilities/Logger.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

template <typename T>
//! A first-in-first-out (FIFO) queue structure built on top of a linked list
class LinkedQueue
{
public:
    //! Push a new item into the back of the queue
    void Push(const T& newData );
    //! Remove the item at the front of the queue
    void Pop();
    //! Access the data at the front of the queue
    T Front();
    //! Get the amount of items in the queue
    int Size();
    //! Return whether the queue is empty
    bool IsEmpty();

private:
    LinkedList<T> m_list;

    friend class QueueTester;
};

template <typename T>
void LinkedQueue<T>::Push(const T& newData )
{
    m_list.PushBack(newData); 
}

template <typename T>
void LinkedQueue<T>::Pop() 
{
    m_list.PopBack(); 
}

template <typename T>
T LinkedQueue<T>::Front()
{
    return m_list.GetBack(); 
}

template <typename T>
int LinkedQueue<T>::Size()
{
    return m_list.Size(); 
}

template <typename T>
bool LinkedQueue<T>::IsEmpty()
{
    return m_list.IsEmpty(); 
}

#endif
