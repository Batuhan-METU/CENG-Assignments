#ifndef MULTIPLE_QUEUE_H
#define MULTIPLE_QUEUE_H

#include <iostream>
#include "Exception.h"
#include "Queue.h"

template <class T>
class MultipleQueue {
private:
    Queue<T>* queues;
    const size_t count;       

public:
    // ---- Constructors & Destructor ----
    MultipleQueue(size_t n);              
    ~MultipleQueue();

    // ---- Core Operations ----
    int Enqueue(const T& value);
    T Dequeue(size_t index);
    const Queue<T>& GetQueue(size_t index) const;

    // ---- Utility ----
    size_t GetNumberOfQueues() const;
    size_t GetTotalSize() const;
    size_t GetSizeOfQueue(size_t index) const;

    // ---- Operator Overload for Printing ----
    template <class U>
    friend std::ostream& operator<<(std::ostream& os, const MultipleQueue<U>& mq);
};

#include "MultipleQueue_impl.h"

#endif // MULTIPLE_QUEUE_H