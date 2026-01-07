#ifndef ARRAY_STACK_HPP
#define ARRAY_STACK_HPP

#include "../SmartDynamicArray/SmartDynamicArray.hpp"
#include "../../Utilities/Logger.hpp"
#include "../../Exceptions/NotImplementedException.hpp"
#include "../../Exceptions/StructureFullException.hpp"
#include "../../Exceptions/InvalidIndexException.hpp"
#include "../../Exceptions/NullptrException.hpp"

template <typename T>
//! A last-in-first-out (LIFO) stack structure built on top of an array
class ArrayStack
{
    public:
    //! Push a new item into the back of the queue
    void Push(const T& newData );
    //! Remove the item at the front of the queue
    void Pop();
    //! Access the data at the front of the queue
    T Top() const;
    //! Get the amount of items in the queue
    int Size();
    //! Return whether the queue is empty
    bool IsEmpty();

    private:
    SmartDynamicArray<T> m_vector;

    friend class StackTester;
};

template <typename T>
void ArrayStack<T>::Push( const T& newData )
{
    m_vector.PushBack(newData); 
}

template <typename T>
void ArrayStack<T>::Pop() 
{
    m_vector.PopBack(); 
}

template <typename T>
T ArrayStack<T>::Top() const
{
    return m_vector.GetBack(); 
}

template <typename T>
int ArrayStack<T>::Size()
{
    return m_vector.Size(); 
}

template <typename T>
bool ArrayStack<T>::IsEmpty()
{
    return m_vector.IsEmpty(); 
}

#endif
