/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>

using namespace std;

// binary search tree virtual base class
template <class T>
class BSTBase{
public:

    virtual void insert(T data) = 0;
    virtual void remove(T data) = 0;
    virtual T* search(T data) = 0;
    virtual void printInorder(ostream& os) = 0;
};
