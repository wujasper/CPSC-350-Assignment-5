/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iterator>
#include "faculty.h"

// default constructor to set default variables
Faculty::Faculty(): Person() {
    department = "";
    advisees = "";
}
// constructor to initialize faculty's id
Faculty::Faculty(int id): Person(id) {
    department = "";
    advisees = "";
}
// constructor to initialize faculty's record
Faculty::Faculty(int id, string name, string level, string department, string advisees): Person(id, name, level) {
    this->department = department;
    this->advisees = advisees;
}
// set faculty department
void Faculty::setDepartment(string department) {
    this->department = department;
}
// add faculty advisee
void Faculty::addAdvisee(int id) {
    DoublyList<int> *list = convertStringToList(advisees);
    list->append(id);
    advisees = convertListToString(list);
}
// remove faculty advisee
void Faculty::removeAdvisee(int id) {
    DoublyList<int> *list = convertStringToList(advisees);
    list->remove(id);
    advisees = convertListToString(list);
}
// get faculty department
string Faculty::getDepartment() {
    return department;
}
// get advisees
string Faculty::getAdvisees() {
    return advisees;
}
// get faculty advisees
int* Faculty::getAdviseesArray() {
    if (advisees == "") {
        return NULL;
    }
    int size;
    return convertStringToArray(advisees, size);
}
// get faculty advisees
int Faculty::getAdviseesSize() {
    if (advisees == "") {
        return 0;
    }
    DoublyList<int> *list = convertStringToList(advisees);
    return list->getSize();
}
// convert advisees list to string
string Faculty::convertListToString(DoublyList<int> *list) {
    list->sort();
    string str = "";

    int *allArr = list->getAllElements();
    if (allArr != NULL) {
        int size = list->getSize();
        for (int i = 0; i < size; ++i) {
            str += to_string(allArr[i]);
            if (i != (size - 1)) {
                str += ", ";
            }
        }
    }

    return str;
}
// Convert advisees from string to doubly list
DoublyList<int>* Faculty::convertStringToList(string inStr) {
    DoublyList<int> *list = new DoublyList<int>;
    string tmpStr = "";

    int i = 0;
    while (i < inStr.length()) {
        if (inStr[i] != ' ' && inStr[i] != ',') {
            tmpStr += inStr[i];
        }
        if ((inStr[i] == ',' || (i == (inStr.length() - 1))) && tmpStr != "") {
            list->append(stoi(tmpStr));
            tmpStr = "";
        }
        ++i;
    }
    return list;
}
// Convert string to array
int* Faculty::convertStringToArray(string inStr, int &size) {
    DoublyList<int> *list = convertStringToList(advisees);
    size = list->getSize();

    return list->getAllElements();
}
// overload == operator
bool Faculty::operator==(const Faculty &a) {
    return (a.getId() == getId());
}
// overload != operator
bool Faculty::operator!=(const Faculty &a) {
    return (a.getId() != getId());
}
// overload > operator
bool Faculty::operator>(const Faculty &a) {
    return (getId()> a.getId());
}
// overload < operator
bool Faculty::operator<(const Faculty &a) {
    return (getId() < a.getId());
}
// overload << operator and choose to print to cout or to a file
ostream& operator<<(ostream& os, const Faculty &a) {
    if (&os != &cout) {
        os << a.getId() << endl;
        os << a.getName() << endl;
        os << a.department << endl;
        os << a.getLevel() << endl;
        os << a.advisees << endl;
    } else {
        os << "-------------------- Faculty Record --------------------" << endl;
        os << "Faculty ID: " << a.getId()<< endl;
        os << "Faculty Name: " << a.getName()<< endl;
        os << "Faculty Department: " << a.department << endl;
        os << "Faculty Level: " << a.getLevel() << endl;
        os << "Faculty Advisees: " << a.advisees << endl;
    }
    return os;
}
