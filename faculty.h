/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>
#include "person.h"
#include "doublylist.cpp"

using namespace std;

class Faculty: public Person{
private:
    string department;
    string advisees;

    string convertListToString(DoublyList<int> *adviseesList);
    DoublyList<int>* convertStringToList(string inStr);

public:
    Faculty();
    ~Faculty() {};
    Faculty(int id);
    Faculty(int id, string name, string level, string department, string advisees);

    void setDepartment(string department);
    void addAdvisee(int id);
    void removeAdvisee(int id);
    string getDepartment();
    string getAdvisees();
    int* getAdviseesArray();
    int getAdviseesSize();
    int* convertStringToArray(string inStr, int &size);
    bool operator==(const Faculty &a);
    bool operator!=(const Faculty &a);
    bool operator>(const Faculty &a);
    bool operator<(const Faculty &a);
    friend ostream& operator<<(ostream& os, const Faculty &a);
};
