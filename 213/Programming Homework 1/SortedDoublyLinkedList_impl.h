#ifndef SORTED_DOUBLY_LINKED_LIST_IMPL_H
#define SORTED_DOUBLY_LINKED_LIST_IMPL_H

#include "SortedDoublyLinkedList.h"
#include "Exception.h"


// -------------------------
// Node Implementation
// -------------------------
template <class T>
DLLNode<T>::DLLNode(const T& item, DLLNode<T>* nextNode, DLLNode<T>* prevNode)
    : item(item), next(nextNode), prev(prevNode) {}

// -------------------------
// Constructors & Destructor
// -------------------------
template <class T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList() {
    head = new DLLNode<T>(T());
    tail = new DLLNode<T>(T());
    head->next = tail;
    tail->prev = head;
}

template <class T>
SortedDoublyLinkedList<T>::~SortedDoublyLinkedList() {
    // TODO: Implement
    DLLNode<T> *current = head; 
    while(current != NULL) {
        DLLNode<T> *temp = current->next;
        delete current; 
        current = temp; 
    }
}

template <class T>
SortedDoublyLinkedList<T>::SortedDoublyLinkedList(const SortedDoublyLinkedList<T>& other) {
    // TODO: Implement
    head = new DLLNode<T>(T()); 
    tail = new DLLNode<T>(T()); 
    head->next = tail; 
    tail->prev = head; 
    
    DLLNode<T> *currentOther = other.head->next; 
    
    while(currentOther != other.tail) {
        InsertItem(currentOther->item); 
        currentOther = currentOther->next; 
    }
}

template <class T>
SortedDoublyLinkedList<T>& SortedDoublyLinkedList<T>::operator=(const SortedDoublyLinkedList<T>& other) {
    // TODO: Implement
    if (this == &other)
        return *this; 
    
    DLLNode<T> *curr = head->next; 
    while(curr != tail) {
        DLLNode<T> *temp = curr->next; 
        delete curr; 
        curr = temp; 
    }
    head->next = tail; 
    tail->prev = head; 
    
    DLLNode<T> *currentOther = other.head->next; 
    while(currentOther != other.tail) {
        InsertItem(currentOther->item); 
        currentOther = currentOther->next; 
    }
    return *this; 
}

// -------------------------
// Core Operations
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::InsertItem(const T& item) {
    // TODO: Implement
    DLLNode<T> *current = head->next;
    while(current != tail && (current->item < item)) {
        current = current->next; 
    }
    while(current != tail && !(item<current->item) && current->item==item) {
        current = current->next; 
    }
    DLLNode<T> *newNode = new DLLNode<T> (item, current, current->prev); 
    current->prev->next = newNode; 
    current->prev = newNode; 
}

template <class T>
void SortedDoublyLinkedList<T>::InsertItemPrior(const T& item) {
    // TODO: Implement
    DLLNode<T> *current = head->next;
    while(current != tail && (current->item < item)) {
        current = current->next; 
    }
    DLLNode<T> *newNode = new DLLNode<T> (item, current, current->prev); 
    current->prev->next = newNode; 
    current->prev = newNode; 
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveFirstItem() {
    // TODO: Implement
    if (head->next == tail) {
        throw EmptyCollectionException(); 
    }
    DLLNode<T> *temp = head->next;
    T item = temp->item; 
    
    temp->next->prev = temp->prev; 
    temp->prev->next = temp->next; 
    
    delete temp; 
     
    return item; 
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveFirstItem(int priority) {
    // TODO: Implement
    if(head->next == tail) {
        throw EmptyCollectionException(); 
    }
    DLLNode<T> *current = head->next; 
    T temp(priority, 0); 
    DLLNode<T> *match = NULL; 
    
    while(current != tail) {
        if(!(current->item < temp) && !(temp<current->item)) {
            match = current; 
            break; 
        }
        current = current->next; 
    }
    if(!match) throw NotFoundException(); 
    
    match->prev->next = match->next; 
    match->next->prev = match->prev; 
    T removedItem = match->item; 
    delete match; 
    
    return removedItem; 
}

template <class T>
T SortedDoublyLinkedList<T>::RemoveLastItem(int priority) {
    // TODO: Implement
    if(head->next == tail) throw EmptyCollectionException(); 
    
    DLLNode<T> *current = tail->prev; 
    T temp(priority, 0); 
    DLLNode<T> *match = NULL;  
    
    while(current != head) {
        if(!(current->item < temp) && !(temp<current->item)) {
            match = current; 
            break; 
        }
        current = current->prev; 
    }
    if(!match) throw NotFoundException(); 
    
    match->prev->next = match->next; 
    match->next->prev = match->prev; 
    T removedItem = match->item; 
    delete match; 
    
    return removedItem; 
}

// -------------------------
// Query
// -------------------------
template <class T>
const T& SortedDoublyLinkedList<T>::FirstItem() const {
    // TODO: Implement
    if (head->next == tail) {
        throw EmptyCollectionException(); 
    }
    return head->next->item; 
}

template <class T>
const T& SortedDoublyLinkedList<T>::LastItem() const {
    // TODO: Implement
    if (head->next == tail) {
        throw EmptyCollectionException(); 
    }
    return tail->prev->item; 
    
}

template <class T>
bool SortedDoublyLinkedList<T>::IsEmpty() const {
    // TODO: Implement
    if (head->next == tail) {
        return true; 
    }
    return false; 
}

template <class T>
size_t SortedDoublyLinkedList<T>::GetSize() const {
    // TODO: Implement
    size_t count = 0; 
    
    if (head->next == tail) {
        return count; 
    }
    DLLNode<T> *current = head->next; 
    while(current != tail) {
        count++; 
        current = current->next; 
    }
    return count; 
}

// -------------------------
// Modification
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::SplitByPriority(SortedDoublyLinkedList<T>& low,
                                                SortedDoublyLinkedList<T>& high,
                                                int pivotPriority) {
    // TODO: Implement
    if(head->next == tail) return; 
    
    DLLNode<T> *current = tail->prev;
    T temp(pivotPriority, 0);
    DLLNode<T> *match = NULL; 
    while(current != head) {
        if(!(current->item < temp) && !(temp<current->item)) {
            match = current; 
            break; 
        }
        current = current->prev;
    }
    current = head->next; 
    while(current != match->next) {
        low.InsertItem(current->item); 
        current = current->next; 
    }
    current = match->next; 
    while(current != tail) {
        high.InsertItem(current->item); 
        current = current->next; 
    }
}


template <class T>
void SortedDoublyLinkedList<T>::SplitAlternating(SortedDoublyLinkedList<T>& listA,
                                                 SortedDoublyLinkedList<T>& listB) {
    // TODO: Implement
    if(head->next == tail) {
        return; 
    }
    DLLNode<T> *current = head->next;
    bool toAdd = true; 
    while(current != tail) {
        if(toAdd) {
            listA.InsertItem(current->item); 
        } else {
            listB.InsertItem(current->item); 
        }
        toAdd = !toAdd;
        current = current->next; 
    }
    
}

template <class T>
SortedDoublyLinkedList<T>
SortedDoublyLinkedList<T>::Merge(const SortedDoublyLinkedList<T>& a,
                                 const SortedDoublyLinkedList<T>& b) {
    // TODO: Implement
    if(a.IsEmpty() && b.IsEmpty())
        return SortedDoublyLinkedList<T>();
        
    SortedDoublyLinkedList<T> result; 
    
    DLLNode<T> *current = a.head->next; 
    while(current != a.tail) {
        result.InsertItem(current->item); 
        current = current->next; 
    }
    
    current = b.head->next; 
    while(current != b.tail) {
        result.InsertItem(current->item); 
        current = current->next; 
    }
    return result; 
}

// -------------------------
// Modification
// -------------------------
template <class T>
void SortedDoublyLinkedList<T>::Clear() {
    // TODO: Implement
    if(head->next == tail) return; 
    
    DLLNode<T> *current = head->next; 
    while(current!=tail) {
        DLLNode<T> *temp = current->next; 
        delete current; 
        current = temp; 
    }
    head->next = tail; 
    tail->prev = head; 
}

// -------------------------
// Operator <<
// -------------------------
template <class T>
std::ostream& operator<<(std::ostream& os, const SortedDoublyLinkedList<T>& list) {
    if (list.head->next == list.tail) {
        os << "Empty";
        return os;
    }
    DLLNode<T>* curr = list.head->next;
    while (curr != list.tail) {
        os << curr->item;
        if (curr->next != list.tail)
            os << " -> ";
        curr = curr->next;
    }
    return os;
}

#endif // SORTED_DOUBLY_LINKED_LIST_IMPL_H
