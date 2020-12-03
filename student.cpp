/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include "student.h"

// default constructor to set default variables
Student::Student(): Person() {
    major = "";
    gpa = 0;
    advisorId = 0;
}
// constructor to initialize student's id
Student::Student(int id): Person(id) {
    major = "";
    gpa = 0;
    advisorId = 0;
}
// constructor to initialize student's record
Student::Student(int id, string name, string level, string major, double gpa, int advisorId): Person(id, name, level) {
    this->major = major;
    this->gpa = gpa;
    this->advisorId = advisorId;
}
// set student major
void Student::setMajor(string major) {
    this->major = major;
}
// set student GPA
void Student::setGPA(double gpa) {
    this->gpa = gpa;
}
// set student advisor's ID
void Student::setAdvisorId(int advisorId) {
    this->advisorId = advisorId;
}
// get student major
string Student::getMajor() {
    return major;
}
// get student GPA
double Student::getGPA() {
    return gpa;
}
// get student advisor's ID
int Student::getAdvisorId() {
    return advisorId;
}
// overload == operator
bool Student::operator==(const Student &a) {
    return (a.getId() == getId());
}
// overload != operator
bool Student::operator!=(const Student &a) {
    return (a.getId() != getId());
}
// overload > operator
bool Student::operator>(const Student &a) {
    return (getId() > a.getId());
}
// overload < operator
bool Student::operator<(const Student &a) {
    return (getId() < a.getId());
}
// overload << operator and choose to print to cout or to a file
ostream& operator<<(ostream& os, const Student &a) {
    if (&os != &cout) {
        os << a.getId() << endl;
        os << a.getName() << endl;
        os << a.major << endl;
        os << a.getLevel() << endl;
        os << a.gpa << endl;
        if (a.advisorId == -1) {
            os << "" << endl;
        } else {
            os << a.advisorId << endl;
        }
    } else {
        os << "-------------------- Student Record --------------------" << endl;
        os << "Student ID: " << a.getId() << endl;
        os << "Student Name: " << a.getName() << endl;
        os << "Student Major: " << a.major << endl;
        os << "Student Level: " << a.getLevel() << endl;
        os << "Student GPA: " << a.gpa << endl;
        if (a.advisorId == -1) {
            os << "Student Advisor ID: " << endl;
        } else {
            os << "Student Advisor ID: " << a.advisorId << endl;
        }
    }
    return os;
}
