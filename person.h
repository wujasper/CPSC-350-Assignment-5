/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>

using namespace std;

#ifndef PERSON_H
#define PERSON_H

class Person {
private:
    int id;
    string name;
    string level;

public:
    Person();
    ~Person() {};
    Person(int id);
    Person(int id, string name, string level);

    void setName(string name);
    void setLevel(string level);
    int getId() const;
    string getName() const;
    string getLevel() const;
};

#endif
