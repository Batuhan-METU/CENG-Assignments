#ifndef MULTIPLE_QUEUE_IMPL_H
#define MULTIPLE_QUEUE_IMPL_H

#include "MultipleQueue.h"
#include "Exception.h"

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
MultipleQueue<T>::MultipleQueue(size_t n)
    : count(n)
{
    queues = new Queue<T>[count];
}

template <class T>
MultipleQueue<T>::~MultipleQueue() {
    // TODO: Implement
    delete[] queues; 
}

// -------------------------
// Core Operations
// -------------------------
template <class T>
int MultipleQueue<T>::Enqueue(const T& value) {
    // TODO: Implement
    if (count == 0) return -1; 
    int minSize = queues[0].GetSize(); 
    for (int i = 0; i<count; i++) {
        if (queues[i].GetSize() < minSize) {
            minSize = queues[i].GetSize(); 
        }
    }
    for(int j = 0; j<count; j++) {
        if (queues[j].GetSize() == minSize) {
            queues[j].Enqueue(value); 
            return j;
        }
    }
    return -1; 
}

template <class T>
T MultipleQueue<T>::Dequeue(size_t index) {
    // TODO: Implement
    if (index >= count) {
        throw IndexOutOfRangeException(); 
    }
    if (queues[index].IsEmpty()) {
        throw EmptyCollectionException(); 
    }
    
    return queues[index].Dequeue(); 
}

template <class T>
const Queue<T>& MultipleQueue<T>::GetQueue(size_t index) const {
    // TODO: Implement
    if (index >= count) {
        throw IndexOutOfRangeException(); 
    }
    
    return queues[index]; 
}

// -------------------------
// Utility
// -------------------------
template <class T>
size_t MultipleQueue<T>::GetNumberOfQueues() const {
    // TODO: Implement
    return count;
}

template <class T>
size_t MultipleQueue<T>::GetTotalSize() const {
    // TODO: Implement
    size_t sum = 0; 
    for (int i = 0; i<count; i++) {
        sum += queues[i].GetSize(); 
    }
    return sum; 
}

template <class T>
size_t MultipleQueue<T>::GetSizeOfQueue(size_t index) const {
    // TODO: Implement
    if (index >= count) {
        return 0; 
    }
    return queues[index].GetSize(); 
}

// -------------------------
// Operator <<
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const MultipleQueue<T>& mq) {
    for (size_t i = 0; i < mq.count; ++i) {
        os << "Queue " << i << ": " << mq.queues[i];
        if (i < mq.count - 1) {
            os << std::endl;
        }
    }
    return os;
}
#endif // MULTIPLE_QUEUE_IMPL_H