#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <cmath>
#include <functional>

#include "Node.h"
#include "NoSuchItemException.h"

template<class T>
class DefaultBalanceCondition {
public:
    bool operator()(int current, int ideal) const {
        // Default BST: NEVER triggers rebalancing
        return true;
    }
};


template<class T,
         typename BalanceCondition = DefaultBalanceCondition<T>,
         typename Comparator = std::less<T> >
class BinarySearchTree {
public:
    BinarySearchTree(); // default constructor 
    Node<T>* constructBST(int start, int end, std::vector<T>&list); 
    BinarySearchTree(const std::list<T> &sortedList); // copy constructor with parameter list. 
    BinarySearchTree(const BinarySearchTree &obj); // copy constructor with another object. 
    ~BinarySearchTree(); // destructor. 

    BinarySearchTree &operator=(const BinarySearchTree &rhs); // assignment operator. 
    
    void insertRec(Node<T>*&node, const T &element, bool &insertedNew); // insert helper 
    bool insert(const T &element);
    bool removeRec(Node<T>*&node, const T &element, bool &removed); // remove helper 
    bool remove(const T &element);
    void removeAllNodes();

    bool isEmpty() const;
    int getHeight() const;
    int getSize() const;

    const T &get(const T &element) const;
    const T &getMin() const;
    const T &getMax() const;
    const T &getNext(const T &element) const;
    const T &getCeiling(const T &element) const;
    const T &getFloor(const T &element) const;

    void findRange(Node<T>*node, const T &low, const T &high, std::list<Node<T>*>&result) const; 
    std::list<Node<T> *> find(const T &low, const T &high) const;

    void collectInorder(Node<T>* node, std::vector<Node<T>*>& arr); // toCompleteBST helper 
    int computeLeftSubtreeSize(int n); // toCompleteBST helper
    Node<T>* buildCompleteFromArray(std::vector<Node<T>*>& nodes, int l, int r); //toCompleteBST helper
    int recomputeMetadata(Node<T>* node); // toCompleteBST helper 
    void toCompleteBST(Node<T>*&node); 
    void toCompleteBST();

    void printPreorder(Node<T>*node) const;
    void printInorder(Node<T>*node) const;
    void printPostorder(Node<T>*node) const;
    void printPretty(Node<T>*node, int depth, bool isLeft) const;



    void printPreorder() const;
    void printInorder() const;
    void printPostorder() const;
    void printPretty() const;

    void printTree(Node<T>* node, std::ostream& out) const; 

    void print(std::ostream &out) const;

private:
    Node<T> *root;
    int numNodes;
    Comparator isLessThan;
    BalanceCondition isBalancedFunctor;

    int log2(int n) {
        int log = 0;
        while (n > 1) {
            n >>= 1;     
            log++;
        }
        return log;
    }

    void deleteSubtree(Node<T> *node) {
        if(node == NULL) return; 
        deleteSubtree(node->left); 
        deleteSubtree(node->right); 
        delete node; 
    }
    Node<T>* cloneSubtree(Node<T> *n) {
        if(n == NULL) 
            return NULL;
        
        Node<T> *newNode = new Node<T>(n->element); 
        newNode->height = n->height; 
        newNode->subsize = n->subsize; 

        newNode->left = cloneSubtree(n->left); 
        newNode->right = cloneSubtree(n->right); 

        return newNode; 
    }
    
    mutable bool firstPrintFlag;
}
;

/////////////////////////////////////////////////////////////
///////////  CONSTRUCTORS / DESTRUCTOR  /////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree() {
    //TODO
    root = NULL; 
    numNodes = 0; 
    isLessThan = C(); 
    isBalancedFunctor = B(); 
}

template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::constructBST(int start, int end, std::vector<T>&list) {
    Node<T> *node; 
    if(start > end) return NULL; 

    int index = (start + end + 1) / 2; 
    node = new Node<T>(list[index]); 

    node->left = constructBST(start, index-1, list); 
    node->right = constructBST(index+1, end, list); 

    int leftHeight = (node->left != NULL) ? node->left->height : -1; 
    int rightHeight = (node->right != NULL) ? node->right->height : -1; 

    node->height = 1 + std::max(leftHeight, rightHeight); 

    int leftSubsize = (node->left != NULL) ? node->left->subsize : 0; 
    int rightSubsize = (node->right != NULL) ? node->right->subsize : 0; 

    node->subsize = 1 + leftSubsize + rightSubsize; 

    return node; 
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree(const std::list<T> &sortedList)
{
  //TODO
    root = NULL; 
    numNodes = 0; 

    if(sortedList.empty()) return;
    
    std::vector<T> list; 
    for(typename std::list<T>::const_iterator it = sortedList.begin();
     it != sortedList.end(); ++it) {
        list.push_back(*it); 
    }
    int length = list.size(); 
    root = constructBST(0, length-1, list); // constructBST creates a BST with median root index (not completeBST). 
    numNodes = length; 

    toCompleteBST(); // to convert a BST to completeBST.  
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree(const BinarySearchTree &obj)
{
    //TODO
    numNodes = obj.numNodes; 
    isLessThan = obj.isLessThan; 
    isBalancedFunctor = obj.isBalancedFunctor; 

    if(obj.root == NULL) {
        root = NULL; 
        return; 
    }

    root = cloneSubtree(obj.root); 
}



template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::~BinarySearchTree() {
    //TODO
    deleteSubtree(root); 
    root = NULL; 
    numNodes = 0; 
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C> &
BinarySearchTree<T,B,C>::operator=(const BinarySearchTree &rhs)
{
    //TODO
    if(this == &rhs) {
        return *this; 
    }

    removeAllNodes(); // clean the BST. 
    numNodes = rhs.numNodes; 
    isLessThan = rhs.isLessThan; 
    isBalancedFunctor = rhs.isBalancedFunctor; 

    if(rhs.root == NULL) {
        root = NULL; 
        return *this; 
    }

    root = cloneSubtree(rhs.root); 
    return *this; 
}



template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::removeAllNodes()
{
    //TODO
    deleteSubtree(root); 
    numNodes = 0; 
    root = NULL; 
}

/////////////////////////////////////////////////////////////
//////////////////// GETTERS ////////////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::isEmpty() const {
    //TODO
    if(root == NULL) return true; 
    
    return false; 
 }

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getHeight() const {
    //TODO
    if(root == NULL) return -1; 

    return root->height; 
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getSize() const {
    //TODO
    return numNodes; 
 }


/////////////////////////////////////////////////////////////
////////////////////// FIND NODE ////////////////////////////
/////////////////////////////////////////////////////////////



template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::get(const T &element) const
{
    //TODO

    Node<T> *current = root; 
    while(current != NULL) {
        if(current->element == element) {
            return current->element; 
        }
        else if(isLessThan(element, current->element)) {
            current = current->left; 
        }
        else {
            current = current->right; 
        }
    }
    throw NoSuchItemException(); 
}

/////////////////////////////////////////////////////////////
//////////////////// INSERT / REMOVE ////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::insertRec(Node<T>*&node, const T &element, bool &insertedNew) {
    if(node == NULL) {
        node = new Node<T>(element); 
        node->left = node->right = NULL;
        node->height = 0;
        node->subsize = 1; 
        numNodes++; 
        insertedNew = true; 
        return;   
    }

    if(!isLessThan(element, node->element) && !isLessThan(node->element, element)) {
        node->element = element; 
        insertedNew = false; 
        return; 
    }

    else if(isLessThan(element, node->element)) {
        insertRec(node->left, element, insertedNew); 
    }
    else {
        insertRec(node->right, element, insertedNew); 
    }

    // metadata update. 
    int leftH = (node->left != NULL) ? node->left->height : -1; 
    int rightH = (node->right != NULL) ? node->right->height : -1; 
    node->height = 1 + std::max(leftH, rightH); 

    int leftS = (node->left != NULL) ? node->left->subsize : 0; 
    int rightS = (node->right != NULL) ? node->right->subsize : 0;   
    node->subsize = 1 + leftS + rightS; 

    int N = node->subsize; 
    int ideal = std::floor(log2(N)); 

    if(!isBalancedFunctor(node->height, ideal)) { // if there is an imbalance between height of node and ideal height.  
        toCompleteBST(node); 
    }
}


template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::insert(const T &element)
{
    //TODO
    bool insertedNew = false; 
    insertRec(root, element, insertedNew); 
    return insertedNew; 
}


template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::removeRec(Node<T>*&node, const T &element, bool &removed) {
    if(node == NULL) {
        return false; // in order to terminate recursion. 
    }
    if(isLessThan(element, node->element)) {
        removeRec(node->left, element, removed); 
    }
    else if(isLessThan(node->element, element)) {
        removeRec(node->right, element, removed); 
    }
    else {
        removed = true; 
        numNodes--; 

        if(node->left == NULL && node->right == NULL) { // leaf node case. 
            delete node; 
            node = NULL; 
            return true; 
        }

        else if(node->left == NULL || node->right == NULL) { // one child case. 
            Node<T>* childNode = (node->left != NULL) ? node->left : node->right; 
            Node<T>* oldNode = node; 
            node = childNode; 
            delete oldNode; 
            return true; 
        }

        else { // two child case. 
        // we cannot use findMin and copy the value since it is wanted to not change the pointer adresses. 
            Node<T> *successorNode = node->right; 
            Node<T> *successorParent = node; 

            while(successorNode->left != NULL) {
                successorParent = successorNode; 
                successorNode = successorNode->left; 
            }
            if(successorParent != node) {
                successorParent->left = successorNode->right; // successor parent->left = nullptr. 
                successorNode->right = node->right; //
            }
            successorNode->left = node->left; // we disconnect node with its childs and put the successor node into it. 
            delete node; 
            node = successorNode; 
        }
    }

    int leftH = (node->left != NULL) ? node->left->height : -1;
    int rightH = (node->right != NULL) ? node->right->height : -1;
    node->height = 1 + std::max(leftH, rightH); 

    int leftS = (node->left != NULL) ? node->left->subsize : 0; 
    int rightS = (node->right != NULL) ? node->right->subsize : 0; 
    node->subsize = 1 + leftS + rightS; 

    int N = node->subsize; 
    int ideal = std::floor(log2(N)); 
    if(!isBalancedFunctor(node->height, ideal)) {
        toCompleteBST(node); 
    }

    return true; // in order to continue recursion ! 
}

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::remove(const T &element) {
    //TODO
    bool removed = false; 
    removeRec(root, element, removed); 
    return removed; 
}

/////////////////////////////////////////////////////////////
//////////////////// MIN/MAX/NEXT ///////////////////////////
/////////////////////////////////////////////////////////////



template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getMin() const {
    //TODO
    if(root == NULL) throw NoSuchItemException(); 
    Node<T>*current = root; 

    while(current->left != NULL) {
        current = current->left; 
    }
    return current->element; 
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getMax() const {
    //TODO
    if(root == NULL) throw NoSuchItemException(); 
    Node<T>*current = root; 

    while(current->right != NULL) {
        current = current->right; 
    }
    return current->element; 
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getNext(const T &key) const {
    //TODO
    // return a minimum element which is bigger than key. 

    Node<T>*current = root; 
    Node<T>*successor = NULL; 

    while(current != NULL) {
        if(isLessThan(key, current->element)) { // key < current->element
            successor = current; 
            current = current->left; 
        } else {
            current = current->right; 
        }
    }
    if(successor == NULL) throw NoSuchItemException(); 

    return successor->element; 
}

/////////////////////////////////////////////////////////////
//////////////// CEILING & FLOOR ////////////////////////////
/////////////////////////////////////////////////////////////
template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getCeiling(const T &key) const {
    // returns the minimum value which is greater than or equal to key.  

    Node<T>*current = root; 
    Node<T>*ceilingNode = NULL;
    
    while(current != NULL) {
        if(!isLessThan(key,current->element) && !isLessThan(current->element, key)) {
            return current->element; 
        }
        else if(isLessThan(current->element, key)) {
            current = current->right; 
        }
        else { // current->element > key
            ceilingNode = current;  
            current = current->left; 
        }
    }
    if(ceilingNode == NULL) throw NoSuchItemException(); 

    return ceilingNode->element; 
}




template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getFloor(const T &key) const { 
    //TODO
    // returns the minimum value which is smaller or equal to key. 
    
    Node<T>*current = root; 
    Node<T>*floorNode = NULL;
    
    while(current != NULL) {
        if(!isLessThan(key, current->element) && !isLessThan(current->element, key)) {
            return current->element; 
        }
        else if(isLessThan(key, current->element)) {
            current = current->left; 
        }
        else {
            floorNode = current; 
            current = current->right; 
        }
    }
    if(floorNode ==NULL) throw NoSuchItemException(); 

    return floorNode->element; 
}

/////////////////////////////////////////////////////////////
/////////////////////// RANGE FIND //////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::findRange(Node<T>*node, const T &low, const T &high, std::list<Node<T>*>&result) const{
    if(node == NULL) return; 

    if(!isLessThan(node->element, low)) { // node->element >= low
        findRange(node->left, low, high, result); 
    }
    if(!isLessThan(node->element, low) && !isLessThan(high, node->element)) { // node->element >=low && node->element <= high
        result.push_back(node); 
    }
    if(!isLessThan(high, node->element)) { // node->element <= high
        findRange(node->right, low, high, result); 
    }
}
template<class T, typename B, typename C>
std::list<Node<T> *> BinarySearchTree<T,B,C>::find(const T &low, const T &high) const
{
    //TODO
    std::list<Node<T>*> result; 
    findRange(root, low, high, result); 
    return result; 
}

/////////////////////////////////////////////////////////////
//////////////////// COMPLETE BST ///////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::collectInorder(Node<T>*node, std::vector<Node<T>*>&arr) {
    if(node == NULL) return; 

    collectInorder(node->left, arr); 
    arr.push_back(node); 
    collectInorder(node->right, arr); 
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::computeLeftSubtreeSize(int n) {
    if(n<=1) return 0; 

    int h = (int)std::floor(log2(n)); 
    int fullLevelNodes = (int)std::pow(2, h) - 1; 
    int lastLevelNodes = n - fullLevelNodes; 

    int leftMax = (int)std::pow(2, h-1); 
    int lastLevelLeftNodes = std::min(lastLevelNodes, leftMax); 

    int fullLevelLeftNodes = (int)std::pow(2, h-1) -1; 

    int leftSubtreeSize = lastLevelLeftNodes + fullLevelLeftNodes; 
    return leftSubtreeSize; 
}

template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::buildCompleteFromArray(std::vector<Node<T>*>& nodes, int l, int r) {
    if(l>r) return NULL; 

    int n = r-l+1; 
    int leftSize = computeLeftSubtreeSize(n); 
    int rootIndex = l + leftSize; 

    Node<T> *rootNode = nodes[rootIndex];

    rootNode->left = buildCompleteFromArray(nodes, l, rootIndex-1); 
    rootNode->right = buildCompleteFromArray(nodes,rootIndex+1, r);
    
    return rootNode; 
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::recomputeMetadata(Node<T>* node)
{
    if (node == NULL) return -1;   // base case for recursion !! 

    int lh = recomputeMetadata(node->left);
    int rh = recomputeMetadata(node->right);

    node->height = std::max(lh, rh) + 1;

    int ls = node->left  ? node->left->subsize : 0;
    int rs = node->right ? node->right->subsize : 0;
    node->subsize = ls + rs + 1;

    return node->height;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::toCompleteBST(Node<T>*& node) {
    if(node == NULL) return; 

    std::vector<Node<T>*> arr; 
    collectInorder(node, arr); 

    for(size_t i = 0; i<arr.size(); i++) {
        arr[i]->left = NULL; 
        arr[i]->right = NULL; 
    }
    node = buildCompleteFromArray(arr,0,arr.size()-1);
    recomputeMetadata(node);  
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::toCompleteBST()
{
    //TODO
    toCompleteBST(root); 
}

/////////////////////////////////////////////////////////////
//////////////////////// PRINTS /////////////////////////////
/////////////////////////////////////////////////////////////

// === PREORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPreorder(Node<T>*node) const {
    if (node == NULL) return;

    if (!firstPrintFlag)
        std::cout << ",\n";
    else
        firstPrintFlag = false;
        
    std::cout << "\t" << node->element;
    printPreorder(node->left);
    printPreorder(node->right);
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPreorder() const {
    //TODO
    std::cout << "BST_preorder{\n";
    firstPrintFlag = true; 
    printPreorder(root);
    std::cout<<std::endl; 
    std::cout << "}\n";
    
}

// === INORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printInorder(Node<T>*node) const {
    if (node == NULL) return;

    printInorder(node->left);

    if (!firstPrintFlag)
        std::cout << ",\n";
    else
        firstPrintFlag = false;
        
    std::cout << "\t" << node->element;
        
    printInorder(node->right);
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printInorder() const {
    //TODO
    std::cout << "BST_inorder{\n";
    firstPrintFlag = true; 
    printInorder(root);
    std::cout<<std::endl; 
    std::cout << "}\n";
    
}

// === POSTORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPostorder(Node<T>*node) const {
    if (node == NULL) return;

    printPostorder(node->left);
    printPostorder(node->right);
    if (!firstPrintFlag)
        std::cout << ",\n";
    else
        firstPrintFlag = false;
        
    std::cout << "\t" << node->element;}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPostorder() const {
    //TODO
    std::cout << "BST_postorder{\n";
    firstPrintFlag = true; 
    printPostorder(root);
    std::cout<<std::endl; 
    std::cout << "}\n";
    
}

/////////////////////////////////////////////////////////////
/////////////////////// PRETTY PRINT ////////////////////////
/////////////////////////////////////////////////////////////
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPretty(Node<T>*node, int depth, bool isLeft) const {
    if (node == NULL) return;

    if (depth == 0) {
        std::cout << "\n\troot:" << node->element << "\n";
    } else {
        std::cout<<"\t"; 
        for (int i = 0; i < depth; i++)
            std::cout << "---";

        std::cout << (isLeft ? "l:" : "r:") << node->element << "\n";
    }

    printPretty(node->left, depth + 1, true);
    printPretty(node->right, depth + 1, false);
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPretty() const
{
    //TODO
    std::cout << "BST_pretty{";
    printPretty(root, 0, false);
    std::cout << "}\n";
    
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printTree(Node<T>* node, std::ostream& out) const {
    if (node == NULL) return;

    if (node->left == NULL && node->right == NULL) {
        out << "(" << node->element << ")";
        return;
    }

    out << "[";
    printTree(node->left, out);

    out << "{" << node->element
        << ",H" << node->height
        << ",S" << node->subsize
        << "}";

    printTree(node->right, out);
    out << "]";
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::print(std::ostream &out) const {
    //TODO
    printTree(root, out); 
    out << std::endl;
}
// Print pair<int,float> or any std::pair<K,V>
template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A,B>& p) {
    os << p.first;   // ONLY print the key
    return os;
}




#endif // BINARY_SEARCH_TREE_H
