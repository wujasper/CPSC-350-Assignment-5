/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include "person.h"

// base class default constructor
Person::Person() {
    id = -1;
    name = "";
    level ="";
}
// base class constructor
Person::Person(int id) {
    this->id = id;
    name = "";
    level = "";
}
// base class constructor
Person::Person(int id, string name, string level) {
    this->id = id;
    this->name = name;
    this->level = level;
}
// set name
void Person::setName(string name) {
    this->name = name;
}
// set level
void Person::setLevel(string level) {
    this->level = level;
}
// get ID
int Person::getId() const {
    return id;
}
// get name
string Person::getName() const {
    return name;
}
// get level
string Person::getLevel() const {
    return level;
}
