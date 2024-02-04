#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;

    Node <T>* GetNewNode(T data){
        Node<T> * newNode = new Node <T> (data,0,0);
        return newNode;
    }


    Node <T> * FindParent(Node <T> *node){
        Node <T> * ancestor= NULL;
        Node <T> * current = root;
        while( (current != NULL) && (current != node) ){
                if(node == NULL)
                    break;
                if(current -> element > node -> element){
                    ancestor = current;
                    current = current -> left;
                }
                else{
                    ancestor = current;
                    current = current -> right;
                }
        }
        return ancestor;
    }

    int FindHeight(Node <T> *node) const{
        int l_height, r_height;
        if(node == NULL)
            return -1;
        l_height = FindHeight(node -> left);
        r_height = FindHeight(node -> right);
        return (l_height > r_height) ? (l_height + 1) : (r_height + 1);
    }

    int FindSize(Node <T> * node) const{
        if(node == NULL)
            return 0;
        return (FindSize(node -> left) + FindSize(node -> right) + 1);
    }

    int insertNode(Node <T> *& node, const T &data){
        if(node == NULL){
            node = new Node <T> (data,0,0);
            upperBound++;
            return 1;
        }
        if(data == node -> element)
            return 0;
        if(data < node -> element)
            return insertNode(node -> left,data);
        else if(data > node -> element)
            return insertNode(node -> right, data);
    }
    
    

    Node <T> * find(T data, Node <T> * node) const{
        if(node == NULL)
            return NULL;
        else if(data < node -> element)
            return find(data, node -> left);
        else if(data > node -> element)
            return find(data, node -> right);
        else
            return node;
    }
    

    void PrintArray(Node <T> ** arr, int size){
        int index= 0;
        std::cout << "printing array:\n";
        for(;index < size;index++)
            std::cout  << arr[index]-> element << ","; 
        std::cout << "\n";
        return;
    }


    void MakeBalanced(Node <T> * &node){
        /* parentı yolla, yoksa root*/
        int size = FindSize(node); /* whole size of subtree*/
        int index_array = 0;
        if(node == NULL)
            return;
        Node <T> ** array = new Node <T> * [size];
        CreateArray(array, node, index_array);
        PrintArray(array,size);
        BuildFromArray(array,node, 0, size -1);
        delete[] array;
    }

    void CreateArray(Node <T> ** &arr, Node <T> * node,int& index) const{
        /* arr , pointer tutan array*/
        if(node == NULL)
            return;
        CreateArray(arr,node-> left,index);
        arr[index] = node;
        index++;
        CreateArray(arr,node -> right,index);
    }

    void BuildFromArray(Node <T> ** arr, Node <T> *& node, int low, int high){
        if(low > high)
            return;
        if(low == high){
            node = arr[low];
            node -> left = NULL;
            node -> right = NULL;
            return;
        }
        else{
            int mid = (low + high) / 2;
            node = arr[mid];
            node -> left = NULL;
            node -> right = NULL;
            BuildFromArray(arr,node -> left, low, mid-1);
            BuildFromArray(arr, node -> right, mid +1, high);
            return;
        }
     }


    void remove_all(Node <T> *& node){
        if(node == NULL)
            return;
        remove_all(node -> left);
        remove_all(node -> right);

        delete node;
        node = NULL;
        return;    
    }

    Node <T> * copy_tree(Node <T> * origin){
        if(origin == NULL)
            return NULL;
        else{
            Node <T> * created = new Node <T> (origin -> element, NULL, NULL );
            created -> left = copy_tree(origin -> left);
            created -> right = copy_tree(origin -> right);
            return created;
        }
    }

    Node <T> * find_max(Node <T> * node){
        while(node-> right)
            node = node -> right;
        return node;
    }

    Node <T> * remove_node(Node <T> * node, T element,int & check_remove){
        if(node == NULL)
            return node;
        else if(element < node -> element)
            node -> left = remove_node(node -> left, element,check_remove);
        else if(element > node -> element)
            node -> right = remove_node(node -> right, element,check_remove);
        else{ /* found the exact node*/
        check_remove = 1;
            if( (node -> left == NULL) && (node -> right == NULL)) {  /* no child*/
                delete node;
                node = NULL;
                return node;
            }
            else if(node -> left == NULL){
                Node <T> * holder = node;
                node = node -> right;
                delete holder;
                return node;
            }
            else if(node -> right == NULL){
                Node <T> * holder = node;
                node = node -> left;
                delete holder;
                return node;
            }

            else{  /* 2 child node case*/
                Node <T> * holder = find_max(node -> left);
                node -> element = holder -> element;
                node -> left = remove_node(node -> left, node -> element, check_remove);
                return node;
            }
        }
        return node;
    }


private: // DO NOT CHANGE THIS PART.
    Node<T> *root;

    int upperBound;
};

#endif //TREE_H

template<class T>
ScapegoatTree<T>::ScapegoatTree() {
    /* TODO */
    root = NULL;
    upperBound = 0;
}

template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
    /* TODO */
    root = NULL;
    upperBound = 0;
    *this = obj;
}

template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    /* TODO */
    removeAllNodes();
}

template<class T>
bool ScapegoatTree<T>::isEmpty() const {
    /* TODO */
    return (root == NULL);
}

template<class T>
int ScapegoatTree<T>::getHeight() const {
    /* TODO */
    return FindHeight(root);
}

template<class T>
int ScapegoatTree<T>::getSize() const {
    /* TODO */
    return FindSize(root);
}

template<class T>
bool ScapegoatTree<T>::insert(const T &element) {
    /* TODO */
    /* element is the data type*/
    int value = insertNode(root, element);

    if(value == 1){
    Node <T> * inserted = find(element,root);
    Node <T> * scapegoat_child = NULL;
    Node <T> * scapegoat = NULL;
    Node <T> * scapegoat_parent = NULL;
    if((getHeight()) > (log2(upperBound) / log2((double)3/(double)2))){
         while(1){
             scapegoat_child = FindParent(inserted);
             scapegoat = FindParent(scapegoat_child);
             if( (scapegoat_child == NULL) || (scapegoat == NULL))
                 break;
             if( (3 * FindSize(scapegoat_child) - 2* FindSize(scapegoat)) > 0){
                std::cout << "balancing!!!"<<std::endl;
                 scapegoat_parent = FindParent(scapegoat);
                 if(scapegoat_parent == NULL){
                        MakeBalanced(root);
                     break;
                }
                std::cout << "PARENT:" << scapegoat_parent -> element << std::endl;
                if(scapegoat_parent -> element < scapegoat -> element)
                   MakeBalanced(scapegoat_parent -> right);
                else
                    MakeBalanced(scapegoat_parent -> left);
               break;
           }
            inserted = scapegoat_child;
         }
    }


    return true;
    }
    return false;
    
}

template<class T>
bool ScapegoatTree<T>::remove(const T &element) {
    /* TODO */
    /* doing removal*/
    int removed = 0;
    root = remove_node(root,element,removed);



    if( (upperBound > 2 * getSize()) || (upperBound < getSize())){
        balance();
        upperBound = getSize();
    }
    if(removed == 1)
        return true;
    else   
        return false;
}

template<class T>
void ScapegoatTree<T>::removeAllNodes() {
    /* TODO */
    remove_all(root);
    root = NULL;
}

template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {
    /* TODO */
    Node <T> * actual = find(element,root);
    if(actual == NULL)
        throw NoSuchItemException();
    else
        return actual -> element;
}

template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;

    }
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    } 
    else if (tp == postorder) {
        /* TODO */
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
}

template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder) {
        /* TODO */
        if(node == NULL)
            return; 
        std::cout << "\t" << node->element;
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node -> left, preorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node -> right, preorder);
    } 
    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
            return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    } 
    else if (tp == postorder) {
        /* TODO */
        if(node == NULL)
            return;
        print(node -> left, postorder);
        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node -> right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->element;
    }
    return;
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}

template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
    /* TODO */
    if(this == &rhs)
        return *this;
    removeAllNodes();
    root = NULL;
    root = copy_tree(rhs.root);
    return *this;
}

template<class T>
void ScapegoatTree<T>::balance() {
    /* TODO */
    /*taking preorder to array and rebuilding*/
    MakeBalanced(root);
}

template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {
    /* TODO */
        int moved_to_left = 0; /* sola gittikten sonra, ilk sağa kıracakken kesmelisin */
    if(root == NULL)
        throw NoSuchItemException();
    Node <T> * mover = find(element,root);
    if(mover == NULL){ /* successorı bul*/
        Node <T> * successor = NULL;
        mover = root;
        while(mover != NULL){
            if(element < mover -> element){
                successor = mover;
                mover = mover -> left;
                moved_to_left = 1;
            }
            else{
                if(moved_to_left == 1){
                    if(mover -> element > element){
                      successor = mover;
                      break;
                    }
                    else{
                        return successor -> element;
                    }
                }
                mover = mover -> right;
            }
        }
        if(successor != NULL){
             return successor -> element;
        }
        else
            throw NoSuchItemException();
    }
    else{
        return mover -> element;
    }
}

template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {
    /* TODO */
   int index = 0;
    int size = getSize();
    Node <T>** array = new Node <T> * [size];  
    CreateArray(array, root , index);
    index = 0;
    while((index < size) && (array[index] -> element <= element))
        index++;
    index--;
    if(index < 0){
        delete[] array;
        throw NoSuchItemException();
    }
    else{
        Node<T> * holder = find(array[index] -> element,root);
        delete[] array;
        return holder -> element;
    }
}


template<class T>
const T &ScapegoatTree<T>::getMin() const {
    /* TODO */
    Node <T> * node = root;
    if(root == NULL)
        throw NoSuchItemException();
    while(node -> left != NULL){
        node = node -> left;
    }
    return node -> element;
}


template<class T>
const T &ScapegoatTree<T>::getMax() const {
    /* TODO */
    Node <T> * node = root;
    if(root == NULL)
        throw NoSuchItemException();
    while(node -> right != NULL){
        node = node -> right;
    }
    return node -> element;
}

template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {
    /* TODO */
    int index = 0;
    int size = getSize();
    Node <T>** array = new Node <T> * [getSize()];  
    CreateArray(array, root , index);
    index = 0;
    while((index < size) && (array[index] -> element <= element))
        index++;
    if(index >= size){
        delete[] array;
        throw NoSuchItemException();
    }
    else{
        Node<T> * holder = find(array[index] -> element,root);
        delete[] array;
        return holder -> element;
    }

    /*
    // right subtree or finding successor from top
    if(root == NULL)
        throw NoSuchItemException();
    Node <T> * node = find(element,root);
    
    if(node != NULL){
        if(node -> right != NULL){
            Node <T> * current = node -> right;
            while(current -> left != NULL){
             current = current -> left;
            }
          return current -> element;
            // current gives next element
        }
        else{
            Node <T> * successor = NULL;
            Node <T> * ancestor = root;
            for(; ancestor != node;){
                if(ancestor -> element > node -> element){ // current is in the left subtree of ancestor
                    successor = ancestor;
                    ancestor = ancestor -> left;
                }
                else{
                    ancestor = ancestor -> right; // successorı hareket ettirme, aşağıda var mı diye test edilecek
                }
            }
            if(successor == NULL){
                if(ancestor == root)
                    if(root -> element > element)
                        return root -> element;
                throw NoSuchItemException();
            }
            return successor -> element;
        }

    }
    else{
        Node <T> * successor = NULL;
        Node <T> * ancestor = root;
        while(ancestor -> element > element){

        }

    }
    */
}