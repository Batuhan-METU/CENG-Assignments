#ifndef SORTED_DOUBLY_LINKED_LIST_H
#define SORTED_DOUBLY_LINKED_LIST_H

#include <iostream>
#include "Exception.h"

template <class T>
struct DLLNode {
    T item;
    DLLNode<T>* next;
    DLLNode<T>* prev;

    DLLNode(const T& item,
            DLLNode<T>* nextNode = NULL,
            DLLNode<T>* prevNode = NULL);
};

template <class T>
class SortedDoublyLinkedList {
private:
    DLLNode<T>* head; // dummy head
    DLLNode<T>* tail; // dummy tail  

public:
    // ---- Constructors & Destructor ----
    SortedDoublyLinkedList();
    SortedDoublyLinkedList(const SortedDoublyLinkedList<T>& other);
    SortedDoublyLinkedList<T>& operator=(const SortedDoublyLinkedList<T>& other);
    ~SortedDoublyLinkedList();

    // ---- Core Operations ----
    void InsertItem(const T& item);
    void InsertItemPrior(const T& item);
    T RemoveFirstItem();
    T RemoveFirstItem(int priority);
    T RemoveLastItem(int priority);

    // ---- Query ----
    bool IsEmpty() const;
    size_t GetSize() const;
    const T& FirstItem() const;
    const T& LastItem() const;

    // ---- Modification ----
    void SplitByPriority(SortedDoublyLinkedList<T>& low,
                        SortedDoublyLinkedList<T>& high,
                        int pivotPriority);
    void SplitAlternating(SortedDoublyLinkedList<T>& listA,
                        SortedDoublyLinkedList<T>& listB);
    static SortedDoublyLinkedList<T> Merge(const SortedDoublyLinkedList<T>& a,
                                        const SortedDoublyLinkedList<T>& b);

    // ---- Utility ----
    void Clear();

    // ---- Operator Overload for Printing ----
    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const SortedDoublyLinkedList<U>& list);
};

#include "SortedDoublyLinkedList_impl.h"

#endif // SORTED_DOUBLY_LINKED_LIST_H
