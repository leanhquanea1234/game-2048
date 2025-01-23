#ifndef _LINKED_LIST_
#define _LINKED_LIST_

#include "my_library.h"

template<typename T>
struct Node {
    T value;
    Node *pNext;

    Node(T value) : value(value), pNext(nullptr) {}
};

template<typename T>
struct List {
	Node<T> *pHead, *pTail;
    size_t size;

    List() : pHead(nullptr), pTail(nullptr), size(0) {}

    ~List() {
        clear();  
    }
    
    void addHead(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (!size) pHead = pTail = newNode;
	    else {
		    newNode->pNext = pHead;
		    pHead = newNode;
	    }
        size++;
    }

    void addTail(const T& value) {
        Node<T>* newNode = new Node<T>(value);

        if (!size) 
		    pHead = pTail = newNode;
	    else {
		    pTail->pNext = newNode;
		    pTail = newNode;
	    }
        size++;
    }

    // return and delete
    T takeValue(const int& position) {
        // if(!size || position >= size) return NULL;

        Node<T> *previousNode, *pickedNode;
        int cnt = 0;
        T value;

        for(Node<T> *i = pHead; i != nullptr; i = i->pNext) {
            if(cnt == position) {
                pickedNode = i;
                break;
            }
            previousNode = i;
            cnt++;
        }
        value = pickedNode->value;

        if(size == 1) pHead = pTail = nullptr;
        else if (pickedNode == pHead)
		    pHead = pickedNode->pNext;
	    else if (pickedNode == pTail) {
		    previousNode->pNext = NULL;
		    pTail = previousNode;
	    }
	    else previousNode->pNext = pickedNode->pNext;

        size--;
        delete pickedNode;
        return value;
    } 

    T popHead() {
        if(!size) return NULL;
        
        Node<T> *temp = pHead;
        T value = temp->value;
        if(size == 1) pHead = pTail = nullptr;
        else pHead = pHead->pNext;
        size--;
        delete temp;
        return value;
    }

    T popTail() {
        if (!size) return NULL;

	    Node<T> *temp = pTail;
        T value = temp->value;
	    if(size == 1) pHead = pTail = nullptr;
	    else {
		    Node<T> *previousNode;
            for (Node<T> *p = pHead; p->pNext != nullptr; p = p->pNext)
		        if (p->pNext == pTail) {
                    previousNode = p;
                    break;
                }
		    previousNode->pNext = nullptr;
		    pTail = previousNode;
	    }
    size--;
	delete temp;
	return value;
    }

    bool empty() {
        return size == 0;
    }

    void clear() {
        Node<T> *temp = pHead;

        while (temp != nullptr) {
		    pHead = temp->pNext;
		    delete temp;
		    temp = pHead;
	    }
	    pHead = pTail = nullptr;
    }
};


#endif