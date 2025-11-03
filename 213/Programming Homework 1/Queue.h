#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "Exception.h"
#include "SinglyLinkedList.h"

template <class T>
class Queue {
private:
    SinglyLinkedList<T> list; // underlying linked list

public:
    // ---- Constructors & Destructor ----
    Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    ~Queue();

    // ---- Core Operations ----
    void Enqueue(const T& value); 
    T Dequeue();                  
    const T& Front() const;

    // ---- Utility ----
    bool IsEmpty() const;
    size_t GetSize() const;
    void Clear();

    // ---- Operator Overload for Printing ----
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const Queue<U>& q);
};

#include "Queue_impl.h"

#endif // QUEUE_H