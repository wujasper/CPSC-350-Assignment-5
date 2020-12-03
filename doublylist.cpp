/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>
#include "doublylistbase.cpp"

using namespace std;

// Node for doubly linked list
template <class T>
class DoublyListNode {

public:
    T data;
    DoublyListNode  *nxt;
    DoublyListNode  *prv;

    // default constructor
    DoublyListNode () {
        nxt = NULL;
        prv = NULL;
    };
    // default destructor
    ~DoublyListNode () {};
    // constructor to set data
    DoublyListNode (T data) {
        this->data = data;
        nxt = NULL;
        prv = NULL;
    }

};

// Implementation of doubly linked list
template <class T>
class DoublyList: public virtual DoublyListBase<T> {
private:
    DoublyListNode<T> *head;
    DoublyListNode<T> *tail;

public:
    DoublyList();
    ~DoublyList();
    void append(T data);
    void prepend(T data);
    void insertAfter(T ref, T data);
    void remove(T data);
    bool search(T data);
    void sort();
    bool isEmpty();
    unsigned int getSize();
    T* getAllElements();
    T peekHead();
    T peekTail();
};

// default constructor to set head and tail to null
template <class T>
DoublyList<T>::DoublyList() {
    head = NULL;
    tail = NULL;
}
// default destructor to delete linked list nodes
template <class T>
DoublyList<T>::~DoublyList() {

    // recursively remove the nodes from the head
    while (head != NULL) {
        remove(head->data);
    }
}
// append data to the tail
template <class T>
void DoublyList<T>::append(T data) {
    DoublyListNode<T> *node = new DoublyListNode<T>(data);

    // if list is empty, new node becomes head and tail
    if (head == NULL) {
        head = node;
        tail = node;
    }
    // otherwise, append the node and update tail
    else {
        node->nxt = NULL;
        node->prv = tail;
        tail->nxt = node;
        tail = node;
    }
}
// prepend data to the head
template <class T>
void DoublyList<T>::prepend(T data) {
    DoublyListNode<T> *node = new DoublyListNode<T>(data);

    // if list is empty, new node becomes head and tail
    if (head == NULL) {
        head = node;
        tail = node;
    }
    // otherwise, prepend the node and update head
    else {
        node->nxt = head;
        node->prv = NULL;
        head->prv = node;
        head = node;
    }
}
// insert data after reference data
template <class T>
void DoublyList<T>::insertAfter(T ref, T data) {
    DoublyListNode<T> *node = new DoublyListNode<T>(data);
    DoublyListNode<T> *cur = head;

    // first find the node that contains the reference data
    while (cur != NULL && cur->data != ref) {
        cur = cur->nxt;
    }
    // if found then cur is not null then insert the node and update
    // nxt and prv pointers
    // update tail to new node if the reference node is the tail
    if (cur != NULL) {
        if (cur->nxt != NULL) {
            cur->nxt->prv = node;
        }
        node->nxt = cur->nxt;
        node->prv = cur;
        cur->nxt = node;
        if (cur == tail) {
            tail = node;
        }
    }
}
// remove data from the linked list
template <class T>
void DoublyList<T>::remove(T data) {
    DoublyListNode<T> *cur = head;

    // only traverse the list if it is not empty
    if (head != NULL) {
        // find the data to be removed from the list
        while (cur != NULL && cur->data != data) {
            cur = cur->nxt;
        }
        // if found then continue the process
        if (cur != NULL) {
            // handle list only contains 1 node
            if (cur == head && cur == tail) {
                head = NULL;
                tail = NULL;
            }
            // handle head node removal
            else if (cur == head) {
                head->nxt->prv = NULL;
                head = head->nxt;
            }
            // handle tail node removal
            else if (cur == tail) {
                tail->prv->nxt = NULL;
                tail = tail->prv;
            }
            // handle internal node
            else {
                cur->prv->nxt = cur->nxt;
                cur->nxt->prv = cur->prv;
            }
            // delete the removed node
            delete cur;
        }
    }
}
// search if list contains the data
template <class T>
bool DoublyList<T>::search(T data) {
    DoublyListNode<T> *cur = head;

    // traverse the list and check if data matches
    while (cur != NULL && cur->data != data) {
        cur = cur->nxt;
    }

    // return true if data is found
    return (cur != NULL);
}
// sort the list using insertion sort
template <class T>
void DoublyList<T>::sort() {
    // create a empty sorted list
    DoublyListNode<T> *sortedHead = NULL;
    DoublyListNode<T> *sortedTail = NULL;
    DoublyListNode<T> *cur = head;
    DoublyListNode<T> *nxt;

    while (cur != NULL) {
        nxt = cur->nxt;
        DoublyListNode<T> *insert = cur;
        insert->nxt = NULL;
        insert->prv = NULL;
        // handle empty sorted list
        if (sortedHead == NULL) {
            sortedHead = insert;
            sortedTail = insert;
        // handle insertion in front of head
        } else if (sortedHead->data > insert->data) {
            insert->nxt = sortedHead;
            sortedHead->prv = insert;
            sortedHead = insert;
        // handle internal or tail node
        } else {
            DoublyListNode<T> *sortedCur = sortedHead;
            // find the insertion point
            while (sortedCur->nxt != NULL && sortedCur->nxt->data < insert->data) {
                sortedCur = sortedCur->nxt;
            }
            // update the pointers
            insert->nxt = sortedCur->nxt;
            sortedCur->nxt = insert;
            insert->prv = sortedCur;
            if (insert->nxt != NULL) {
                insert->nxt->prv = insert;
            } else {
                sortedTail = insert;
            }
        }
        cur = nxt;
    }

    head = sortedHead;
    tail = sortedTail;
}
// check if list is empty
template <class T>
bool DoublyList<T>::isEmpty() {

    return (head == NULL);
}
// get list size
template <class T>
unsigned int DoublyList<T>::getSize() {
    DoublyListNode<T> *cur = head;
    unsigned int size = 0;

    while (cur != NULL) {
        size++;
        cur = cur->nxt;
    }

    return size;
}
// peek the head
template <class T>
T DoublyList<T>::peekHead() {

    return head->data;
}
// peek the tail
template <class T>
T DoublyList<T>::peekTail() {

    return tail->data;
}
// get all elements and return as an array
template <class T>
T* DoublyList<T>::getAllElements() {
    DoublyListNode<T> *cur = head;

    if (cur == NULL) {
        return NULL;
    }

    T *allArr = new T[getSize()];
    int i = 0;
    while (cur != NULL) {
        allArr[i++] = cur->data;
        cur = cur->nxt;
    }
    return allArr;
}
