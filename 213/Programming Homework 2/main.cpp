#include <iostream>
#include <list>
#include "BinarySearchTree.h"

int main() {

    std::list<int> sortedList;
    sortedList.push_back(1);
    sortedList.push_back(2);
    sortedList.push_back(3);
    sortedList.push_back(4);
    sortedList.push_back(5);
    sortedList.push_back(6);
    sortedList.push_back(7);

    BinarySearchTree<int> bst(sortedList);

    std::cout << "=== COMPLETE BST FROM SORTED LIST ===\n";
    bst.print(std::cout);

    return 0;
}