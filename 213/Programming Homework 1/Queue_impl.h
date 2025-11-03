#ifndef QUEUE_IMPL_H
#define QUEUE_IMPL_H

#include "Queue.h"
#include "Exception.h"

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
Queue<T>::Queue() {}

template <class T>
Queue<T>::Queue(const Queue<T>& other) : list(other.list) {}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this != &other)
        list = other.list;
    return *this;
}

template <class T>
Queue<T>::~Queue() {}

// -------------------------
// Core Operations
// -------------------------
template <class T>
void Queue<T>::Enqueue(const T& value) {
    // TODO: Implement
    list.PushBack(value); 
}

template <class T>
T Queue<T>::Dequeue() {
    // TODO: Implement
    if(list.IsEmpty()) {
        throw EmptyCollectionException(); 
    }
    return list.PopFront(); 
}

template <class T>
const T& Queue<T>::Front() const {
    // TODO: Implement
    if(list.IsEmpty()) {
        throw EmptyCollectionException(); 
    }
    return list.Front(); 
}

// -------------------------
// Utility
// -------------------------
template <class T>
bool Queue<T>::IsEmpty() const {
    // TODO: Implement
    return list.IsEmpty(); 
}

template <class T>
size_t Queue<T>::GetSize() const {
    // TODO: Implement
    return list.GetSize(); 
}

template <class T>
void Queue<T>::Clear() {
    // TODO: Implement
    list.Clear(); 
}

// -------------------------
// Operator << definition
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const Queue<T>& q) {
    os << q.list;
    return os;
}

#endif // QUEUE_IMPL_H