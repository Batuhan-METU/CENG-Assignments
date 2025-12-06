#ifndef TREEMAP_H
#define TREEMAP_H

#include <iostream>
#include <vector>

#include "KeyValuePair.h"
#include "BinarySearchTree.h"

template<class K, class V>
class TreeMap {
public:
    TreeMap();

    void clear();
    const V &get(const K &key) const;
    const V &operator[](const K &key) const;

    void put(const K &key, const V &value);

    bool containsKey(const K &key);
    bool deletekey(const K &key);
    bool pop(const K &key);
    bool update(const K &key, const V &value);

    const KeyValuePair<K, V> &ceilingEntry(const K &key);
    const KeyValuePair<K, V> &floorEntry(const K &key);
    const KeyValuePair<K, V> &firstEntry();
    const KeyValuePair<K, V> &lastEntry();

    void pollFirstEntry();
    void pollLastEntry();
    
    void print() const;
    int size();

private:
    BinarySearchTree<KeyValuePair<K, V> > stree;
};

template<class K, class V>
TreeMap<K, V>::TreeMap() {}

template<class K, class V>
void TreeMap<K, V>::clear() {
    //TODO
    stree.removeAllNodes(); 
}

template<class K, class V>
const V &TreeMap<K, V>::get(const K &key) const {
    //TODO
    const KeyValuePair<K,V> &p = stree.get(KeyValuePair<K,V>(key)); 
    return p.getValue();  
}

template<class K, class V>
bool TreeMap<K, V>::pop(const K &key) {
    //TODO
    return stree.remove(KeyValuePair<K,V>(key)); 
}

template<class K, class V>
bool TreeMap<K, V>::update(const K &key, const V &value) {
    //TODO
    try
    {
        KeyValuePair<K,V> &p = const_cast<KeyValuePair<K,V>&>(stree.get(KeyValuePair<K,V>(key)));
        p.setValue(value); 
        return true; 
    }
    catch(NoSuchItemException &e)
    {
        return false; 
    }
    
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::ceilingEntry(const K &key) {
    //TODO
    return stree.getCeiling(KeyValuePair<K,V>(key)); 
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::floorEntry(const K &key) {
    //TODO
    return stree.getFloor(KeyValuePair<K,V>(key)); 
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::firstEntry() {
    //TODO
    return stree.getMin(); 
}

template<class K, class V>
const KeyValuePair<K, V> &TreeMap<K, V>::lastEntry() {
    //TODO
    return stree.getMax(); 
}

template<class K, class V>
void TreeMap<K, V>::pollFirstEntry() {
    //TODO
    const KeyValuePair<K,V> &minEntry = stree.getMin(); 

    stree.remove(minEntry); 
}

template<class K, class V>
void TreeMap<K, V>::pollLastEntry() {
    //TODO
    const KeyValuePair<K,V> &maxEntry = stree.getMax(); 

    stree.remove(maxEntry); 
}

template<class K, class V>
void TreeMap<K, V>::print() const {
    std::cout << "# TreeMap (BinarySearchTree):" << std::endl;
    stree.printPretty();
    std::cout << "# End TreeMap" << std::endl;
}



template<class K, class V>
int TreeMap<K, V>::size() {
    //TODO
    return stree.getSize(); 
}

template<class K, class V>
void TreeMap<K, V>::put(const K &key, const V &value) {
    //TODO
    stree.insert(KeyValuePair<K,V>(key,value)); 
}

template<class K, class V>
const V &TreeMap<K, V>::operator[](const K &key) const {
    //TODO
    return get(key); 
}

template<class K, class V>
bool TreeMap<K, V>::deletekey(const K &key) {
    //TODO
    return stree.remove(KeyValuePair<K,V>(key)); 
}

template<class K, class V>
bool TreeMap<K, V>::containsKey(const K &key) {
    //TODO
    try {
        stree.get(KeyValuePair<K,V>(key)); 
        return true; 
    } catch(NoSuchItemException &e) {
        return false; 
    }
}

#endif
