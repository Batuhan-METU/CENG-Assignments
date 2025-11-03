#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <iostream>
#include "Exception.h"

template <class T>
struct SLLNode {
    T data;
    SLLNode<T>* next;

    SLLNode(const T& data, SLLNode<T>* next = NULL);
};

template <class T>
class SinglyLinkedList {
private:
    SLLNode<T>* head; // dummy node

public:
    // ---- Constructors & Destructor ----
    SinglyLinkedList();
    SinglyLinkedList(const SinglyLinkedList<T>& other);
    SinglyLinkedList<T>& operator=(const SinglyLinkedList<T>& other);
    ~SinglyLinkedList();

    // ---- Basic Operations ----
    void PushFront(const T& value);
    void PushBack(const T& value);
    T PopFront();
    T PopBack();

    // ---- Accessors ----
    bool IsEmpty() const;
    size_t GetSize() const;
    T& Front();
    const T& Front() const;
    T& Back();
    const T& Back() const;

    // ---- Searching & Removal ----
    bool Contains(const T& value) const;
    bool Remove(const T& value); 

    // ---- Utility ----
    void Clear();
    void Reverse();

    // ---- Operator Overload for Printing ----
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<U>& list);
};

// Operator overload for printing
template <class T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list);

#include "SinglyLinkedList_impl.h"

#endif // SINGLY_LINKED_LIST_H