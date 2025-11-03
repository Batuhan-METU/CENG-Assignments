#ifndef SINGLY_LINKED_LIST_IMPL_H
#define SINGLY_LINKED_LIST_IMPL_H

#include "SinglyLinkedList.h"
#include "Exception.h"

// -------------------------
// Node Implementation
// -------------------------
template <class T>
SLLNode<T>::SLLNode(const T& data, SLLNode<T>* next)
    : data(data), next(next) {}

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // dummy head node
    head = new SLLNode<T>(T(), NULL);
}

template <class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other) {
    // TODO: Implement

    head = new SLLNode<T>(T(), NULL); 
    SLLNode<T>* currentThis = head; 
    SLLNode<T>* currentOther = other.head->next;
    
    while(currentOther != NULL) {
        currentThis->next = new SLLNode<T>(currentOther->data, NULL); 
        currentThis = currentThis->next; 
        currentOther = currentOther->next; 
    }
}

template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO: Implement
    SLLNode<T> *current = head;
    while(current != NULL) {
        SLLNode<T> *nextNode = current->next; 
        delete current; 
        current = nextNode; 
    }
}



template <class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other) {
    // TODO: Implement
    if (this == &other) {
        return *this; 
    }
    
    SLLNode<T> *current = head->next;
    while(current != NULL) {
        SLLNode<T> *temp = current->next; 
        delete current; 
        current = temp; 
    }
    head->next = NULL; 
 
    SLLNode<T> *currentThis = head; 
    SLLNode<T> *currentOther = other.head->next; 
    
    while(currentOther != NULL) {
        currentThis->next = new SLLNode<T>(currentOther->data, NULL); 
        currentThis = currentThis->next; 
        currentOther = currentOther->next; 
    }

    return *this;
}

// -------------------------
// Basic Operations
// -------------------------
template <class T>
void SinglyLinkedList<T>::PushFront(const T& value) {
    // TODO: Implement
    SLLNode<T> *newNode = new SLLNode<T>(value, NULL); 
    newNode->next = head->next; 
    head->next = newNode; 
}

template <class T>
void SinglyLinkedList<T>::PushBack(const T& value) {
    // TODO: Implement
    SLLNode<T> *newNode = new SLLNode<T>(value, NULL); 
    SLLNode<T> *tail = head; 
    while(tail->next != NULL) {
        tail = tail->next; 
    }
    newNode->next = tail->next; 
    tail->next = newNode; 
}

template <class T>
T SinglyLinkedList<T>::PopFront() {
    // TODO: Implement
    if (head->next == NULL) {
        throw EmptyCollectionException(); 
    }
    SLLNode<T> *current = head->next; 
    T value = current->data; 
    head->next = current->next; 
    delete current; 
    
    return value;
}

template <class T>
T SinglyLinkedList<T>::PopBack() {
    // TODO: Implement
    if (head->next == NULL) {
        throw EmptyCollectionException(); 
    }
    SLLNode<T> *tail, *prev;
    tail = head; 
    while(tail->next != NULL) {
        prev = tail; 
        tail = tail->next; 
    }
    T value = tail->data; 
    prev->next = tail->next;
    
    delete tail; 
    
    return value;
}

// -------------------------
// Accessors
// -------------------------
template <class T>
bool SinglyLinkedList<T>::IsEmpty() const {
    if (head->next == NULL) {
        return true; 
    }
    return false; 
}

template <class T>
size_t SinglyLinkedList<T>::GetSize() const {
    // TODO: Implement
    if(head->next == NULL) {
        return 0; 
    }
    size_t count = 0;
    
    SLLNode<T> *current = head->next; 
    while(current!=NULL) {
        count++;
        current = current->next; 
    }
    return count; 
}

template <class T>
T& SinglyLinkedList<T>::Front() {
    // TODO: Implement
    if (head->next == NULL) {
        throw EmptyCollectionException(); 
    }
    return head->next->data; 
}

template <class T>
const T& SinglyLinkedList<T>::Front() const {
    // TODO: Implement
    if (head->next == NULL) {
        throw EmptyCollectionException(); 
    }
    return head->next->data; 
}

template <class T>
T& SinglyLinkedList<T>::Back() {
    // TODO: Implement
    if (head->next == NULL) {
        throw EmptyCollectionException(); 
    }
    SLLNode<T> *tail = head; 
    while(tail->next != NULL) {
        tail = tail->next; 
    }
    return tail->data; 
}

template <class T>
const T& SinglyLinkedList<T>::Back() const {
    // TODO: Implement
    if (head->next == NULL) {
        throw EmptyCollectionException(); 
    }
    SLLNode<T> *tail = head; 
    while(tail->next != NULL) {
        tail = tail->next; 
    }
    return tail->data; }

// -------------------------
// Searching & Removal
// -------------------------
template <class T>
bool SinglyLinkedList<T>::Contains(const T& value) const {
    // TODO: Implement
    if (head->next == NULL) {
        return false; 
    }
    SLLNode<T> *current = head->next;
    while(current != NULL) {
        if (current->data == value) {
            return true; 
        } 
        current = current->next; 
    }
    return false; 
}

template <class T>
bool SinglyLinkedList<T>::Remove(const T& value) {
    // TODO: Implement
    if (head->next == NULL) {
        return false; 
    }
    SLLNode<T> *prev, *current = head->next;
    while(current != NULL) {
        if (current->data == value) {
            prev->next = current->next;
            delete current; 
            current = prev->next; 
            return true; 
        }
        prev = current; 
        current = current->next; 
    }
    return false; 
    
}

// -------------------------
// Utility
// -------------------------
template <class T>
void SinglyLinkedList<T>::Clear() {
    // TODO: Implement
    SLLNode<T> *prev = head, *current = head->next; 
    while (current != NULL) {
        prev->next = current->next; 
        delete current; 
        current = prev->next; 
    }
}

template <class T>
void SinglyLinkedList<T>::Reverse() {
    // TODO: Implement
    if(head->next == NULL || head->next->next == NULL) {
        return; 
    }
    SLLNode<T> *prev = NULL, *current = head->next, *nextNode;
    while(current != NULL) {
        nextNode = current->next; 
        current->next = prev; 
        prev = current; 
        current = nextNode; 
    }
    // when list is finished, our current is pointing to null!! 
    head->next = prev; 
}

// -------------------------
// Operator << Overload
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
    if (list.head->next == NULL) {
        os << "Empty";
        return os;
    }
    SLLNode<T>* curr = list.head->next; 
    while (curr != NULL) {
        os << curr->data;
        if (curr->next != NULL)
            os << " -> ";
        curr = curr->next;
    }
    return os;
}

#endif // SINGLY_LINKED_LIST_IMPL_H
