#ifndef LINKED_LIST_NODE_HPP
#define LINKED_LIST_NODE_HPP

template <typename T>
//! A node structure for a doubly linked list's node
struct DoublyLinkedListNode
{
public:
    DoublyLinkedListNode();

    DoublyLinkedListNode<T>* m_ptrNext;
    DoublyLinkedListNode<T>* m_ptrPrev;

    T m_data;
};

/**
    Set the next and previous pointers to nullptr
*/
template <typename T>
DoublyLinkedListNode<T>::DoublyLinkedListNode()
{
    m_ptrNext = nullptr;
    m_ptrPrev = nullptr;
}

#endif
