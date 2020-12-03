/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>

using namespace std;

// doubly linked list virtual base class
template <class T>
class DoublyListBase{
public:

    virtual void append(T data) = 0;
    virtual void prepend(T data) = 0;
    virtual void insertAfter(T ref, T data) = 0;
    virtual void remove(T data) = 0;
    virtual void sort() = 0;
    virtual bool search(T data) = 0;
    virtual bool isEmpty() = 0;
    virtual T* getAllElements() = 0;
    virtual unsigned int getSize() = 0;
    virtual T peekHead() = 0;
    virtual T peekTail() = 0;
};
