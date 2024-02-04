#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    /* TODO */
    size = 0;
    head = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    /* TODO */
    /* copy constructor */
    head = 0;
    size = 0;
    *this = obj;
    
}

template<class T>
LinkedList<T>::~LinkedList()
{
    /* TODO */
    removeAllNodes();
    size = 0; 
    head = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    /* TODO */
    if(this != &rhs){
        if(rhs.head == 0){
            size = 0;
            this -> head = 0;
        }
        else{
            Node <T> * rhs_mover;
            removeAllNodes();
            prepend((rhs.head) -> data);
            rhs_mover = rhs.head -> next;
            while(rhs_mover != rhs.head){
                append(rhs_mover->data);
                rhs_mover = rhs_mover -> next;
            }
        }
    }
    return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    /* TODO */
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    /* TODO */
    if(head == 0)
        return 1;
    else
        return 0;
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    /* TODO */
    Node <T> * mover = head;
    int counter;
    if(node == head)
        return 1;
    for(counter = 0;counter < size ; counter++){
        if(mover == node){
            return 1;
        }
        mover = mover -> next;
    }
    return 0;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    /* TODO */
    if(head == 0)
        return NULL;
    return head;
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    /* TODO */
    if(head == 0)
        return NULL;
    return head -> prev;
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    /* TODO */
    Node <T> * mover = head;
    if(mover == 0){
        return NULL;
    }
    if(mover-> data == data)
        return head;
    mover = mover -> next;
    for(;mover != head; mover = mover -> next){
        if(mover == 0)
            std::cout << "hata!"<< std::endl;
        if(mover -> data == data)
            return mover;
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    /* TODO */
    int counter;
    Node <T> * mover = head;
    if(index >= size)
        return NULL;
    if(index < 0)
        return NULL;
    for(counter = 0; counter < size ; counter++){
        if(counter == index)
            return mover;
        mover = mover -> next;
    }
    return 0;
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    /* TODO */
    size++;           /* size'ı modifiye et!! */
    if(head == 0){
        Node <T>* created = new Node <T> (data, 0,0);
        head = created;
        created -> prev = created;
        created -> next = created;
        return;
    }
    else if(head -> next == head){ /* tek node var */
        Node <T> * created = new Node <T> (data, head,head);
        head -> prev = created;
        head -> next = created;
        return;
    }
    else{
        Node <T> * created = new Node <T> (data,head -> prev, head);
        head -> prev -> next = created;
        head -> prev = created;
        return;
    }
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    /* TODO */
    size++;
    if(head == 0){
        Node <T> * created = new Node <T> (data, 0,0);
        head = created;
        created -> prev = created;
        created -> next = created;
        return;
    }
    else if(head -> next == head){ /* tek node var*/
        Node <T> * created = new Node <T> (data, head, head);
        head -> prev = created;
        head -> next = created;
        head = created;
        return;
    }
    else{
        Node<T> * created = new Node <T> (data, head -> prev, head);
        head -> prev -> next= created;
        head -> prev = created;
        head = created;
        return;
    }
    
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    /* TODO */
    Node <T> * mover = head;
    /*
    if(head == 0){
        head = created;
        created -> prev = created;
        created -> next = created;
        size++;
        return;
    }*/
    if(head == 0)
        return;
    else if(mover == node){
        Node <T> * created = new Node <T> (data,0,0);
        created -> next = mover -> next;
        created -> prev = mover;
        mover -> next -> prev = created;
        mover -> next = created;
        size++;
        return;
    }
    else{
        mover = mover -> next;
        for(;mover != head; mover = mover -> next){
            if(mover == node)
                break;
        }
    if(mover != node)
        return;
    else{
          Node <T> * created = new Node <T> (data,0,0);
      created -> prev = mover;
     created -> next = mover -> next;
      mover -> next -> prev = created;
     mover -> next = created;
     size++;
    return;
    }
    }
}

    

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    /* TODO */
    if(index > size)
        return;
    
    if(index == 0){
        if(head == NULL){
          Node <T> *created = new Node <T> (data,0,0);
          created -> prev = created;
           created -> next = created;
            head = created;
            size++;
           return;
        }
        else{
            Node <T> * created = new Node <T> (data,0,0);
            created -> prev = head -> prev;
            created -> next = head;
            head -> prev -> next = created;
            head -> prev = created;
            head = created;
            size++;
            return;
        }
    }
    else if(size == index) /* special case,son olucak*/{
        Node <T> *created = new Node <T> (data,0,0);
        Node <T> *mover = head;
        created -> next = head;
        created -> prev = head -> prev;
        mover -> prev -> next = created;
        mover -> prev = created;
        size++;
        return;
    }
    else{
        Node <T> *created = new Node <T> (data,0,0);
        Node <T> *mover = head;
        int counting;
        for(counting = 0;counting < size;counting++){
            if(index == counting){
                created -> prev = mover -> prev;
                created -> next = mover;
                mover -> prev -> next = created;
                mover -> prev = created;
                size++;
                return;
            }
            mover = mover -> next;
        }
        return;
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    /* TODO */
    int counter;
    Node <T> * mover = head;
    if(mover == node)
        return 0;
    mover = mover -> next;
    for(counter = 0; (counter < size) && (mover != head); counter++){
        if(mover == node)
            return counter;
        mover = mover -> next;
    }
    return -1;
}

template <class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    /* TODO */
    int counter;
    Node <T> * mover = head;
    Node <T> * holder;
    if(currentIndex >= size)
        return;
    for(counter = 0;;counter++){
        if(counter == currentIndex)
            break;
        mover = mover -> next;
    }
    if(counter == 0){
        if(head -> next == head)
            return;
        /* removing first node*/
        holder = head;
        head -> prev -> next = head -> next;
        head -> next -> prev = head -> prev;
        head = head -> next;
    }
    else{
        holder = mover;
        mover -> prev -> next = mover -> next;
        mover -> next -> prev = mover -> prev;
    }
    /* node removed,finding new place*/
    mover = head;
    size--;

    if(newIndex == 0){
        holder -> next = mover;
        holder -> prev = mover -> prev;
        mover -> prev -> next = holder;
        mover -> prev = holder;
        head = holder;
        size++;
        return;
    }
    else if(newIndex >= size){
        holder -> next = head;
        holder -> prev = head -> prev;
        head -> prev -> next = holder;
        head -> prev = holder;
        size++;
        return;
    }
    else{
        int counter = 0;
        mover = head;
        while(counter != newIndex){
            mover = mover -> next;
            counter++;
        }
        holder -> next = mover;
        holder -> prev = mover -> prev;
        mover -> prev -> next = holder;
        mover -> prev = holder;
        size++;
        return;
    }

}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    /* TODO */
    Node <T> * mover = head;
    if(head == NULL)
        return;
    if(head -> next == head){
        /* tek node var kontrolü bu!!!*/
        if(head == node){
          delete head;
          head = 0;
          size--;        
         return;
        }
        
    }
    if(mover == node){
        Node <T> * object;
            object = mover;
            mover -> prev -> next = mover -> next;
            mover -> next -> prev = mover -> prev;
            head = mover -> next;
            delete object;
            size--;
            return;
    }
    mover = mover -> next;
    for(;mover != head;){
        if(mover == node){
            Node <T> * object;
            object = mover;
            mover -> prev -> next = mover -> next;
            mover -> next -> prev = mover -> prev;
            mover = mover -> next;
            delete object;
            size--;
            return;
        }
        else{
            mover = mover -> next;
        }
    }
    return;
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    Node <T> * mover = head;
    if(head == NULL)
        return;
    if(head -> next == head){
        if(head -> data == data){
            delete head;
            head = NULL;
            size--;
            return;
        }
    }
    while(head -> data == data){
        Node <T> * holder = head;
        head -> next -> prev = head -> prev;
        head -> prev -> next = head -> next;
        head = head -> next;
        delete holder;
        size--;
     }
    mover = head;
    mover = mover -> next;
    for(;mover != head;){
        if(mover -> data == data){ /* ilk node değil*/
        Node<T> * holder = mover;
        mover -> next -> prev = mover -> prev;
        mover -> prev -> next = mover -> next;
        mover = mover -> next;
        delete holder;
        size--;
        }
        else{
            mover = mover -> next;
        }

    }
    return;
    
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    int counter = 0;
    Node <T> * mover = head;
    if(head == NULL)
        return;
    if(index >= size)
        return;
    if((index == 0) && (head -> next == head)){
        /* std::cout << "son elemanı siliciEm" << std::endl; */
        delete head;
        mover = 0;
        head = 0;
        size--;
        return;
    }
    if((index == 0) && (head -> next != head)){
        /*std::cout << "ilki siliyom daha varrR" << std::endl; */
        Node <T> * holder = head;
        mover -> prev -> next = mover -> next;
        mover -> next -> prev = mover -> prev;
        head = head -> next;
        delete holder;
        holder = 0;
        mover = 0;
        size--;
        return;
    }
    for(;counter < size;counter++, mover = mover -> next){
        if(counter == index){
            Node <T> * holder = mover;
            mover -> next -> prev = mover -> prev;
            mover -> prev -> next = mover -> next;
            delete holder;
            holder = 0;
            mover = 0;
            size--;
            return;
        }
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    while(head != 0)
        removeNodeAtIndex(0);
    size = 0; 
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H