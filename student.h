/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>
#include "person.h"

using namespace std;

class Student: public Person {
private:
    string major;
    double gpa;
    int advisorId;

public:
    Student();
    ~Student() {};
    Student(int id);
    Student(int id, string name, string level, string major, double gpa, int advisorId);

    void setMajor(string major);
    void setGPA(double gpa);
    void setAdvisorId(int advisorId);
    string getMajor();
    double getGPA();
    int getAdvisorId();
    bool operator==(const Student &a);
    bool operator!=(const Student &a);
    bool operator>(const Student &a);
    bool operator<(const Student &a);
    friend ostream& operator<<(ostream& os, const Student &a);
};
