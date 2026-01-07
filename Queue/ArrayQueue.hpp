#ifndef ARRAY_QUEUE_HPP
#define ARRAY_QUEUE_HPP

#include "../SmartDynamicArray/SmartDynamicArray.hpp"
#include "../../Utilities/Logger.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

template <typename T>
//! A first-in-first-out (FIFO) queue structure built on top of an array
class ArrayQueue
{
    public:
    //! Push a new item into the back of the queue
    void Push(const T& newData );
    //! Remove the item at the front of the queue
    void Pop();
    //! Access the data at the front of the queue
    T Front() const;
    //! Get the amount of items in the queue
    int Size();
    //! Return whether the queue is empty
    bool IsEmpty();

    private:
    SmartDynamicArray<T> m_vector;

    friend class QueueTester;
};

template <typename T>
void ArrayQueue<T>::Push( const T& newData )
{
    m_vector.PushBack(newData); 
}

template <typename T>
void ArrayQueue<T>::Pop() 
{
    m_vector.PopFront(); 
}

template <typename T>
T ArrayQueue<T>::Front() const
{
    
    return m_vector.GetFront();
    
}

template <typename T>
int ArrayQueue<T>::Size()
{
    return m_vector.Size(); 
}

template <typename T>
bool ArrayQueue<T>::IsEmpty()
{
    return m_vector.IsEmpty(); 
}

#endif
