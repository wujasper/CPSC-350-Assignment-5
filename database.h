/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include <iostream>
#include <cstdlib>
#include <exception>
#include <list>
#include <limits>
#include "fileio.h"
#include "bst.cpp"
#include "student.h"
#include "faculty.h"

using namespace std;

class DatabaseTables {
public:
    BST<Faculty> *masterFaculty;
    BST<Student> *masterStudent;

    DatabaseTables() {
        masterFaculty = new BST<Faculty>;
        masterStudent = new BST<Student>;
    };
    ~DatabaseTables() {
        delete masterFaculty;
        delete masterStudent;
    };
    DatabaseTables(const DatabaseTables &obj) {
        *masterFaculty = *obj.masterFaculty;
        *masterStudent = *obj.masterStudent;
    };
    // overload = operator for rollback copy
    // cannot copy pointers only and have to copy everything
    DatabaseTables& operator=(const DatabaseTables &obj) {
        if (this == &obj) {
            return *this;
        }
        if (masterStudent != NULL) {
            masterStudent = new BST<Student>;
        }
        if (masterFaculty != NULL) {
            masterFaculty = new BST<Faculty>;
        }
        *masterFaculty = *obj.masterFaculty;
        *masterStudent = *obj.masterStudent;
        return *this;
    }
};

class Database{
private:
    DatabaseTables *tables;
    DatabaseTables rollbackDatabase[5];
    int rollbackIdx;
    int rollbackSize;

    void printMainMenu();
    string getUserString(string msg);
    int getUserInt(string msg, int empotyAllowed);
    double getUserDouble(string msg);
    int stringToInt(string inStr);
    double stringToDouble(string inStr);
    int getMainChoice();
    Student* getStudentRecord();
    Faculty* getFacultyRecord();
    int writeTable(string tableSelect);
    int readTable(string tableSelect);
    void initializeFromFile(ifstream &readStream, string tableSelect);
    void rollbackSnapshot();
    bool checkValidFacultyId(int facultyId);
    bool checkValidStudentId(int studentId);
    bool checkValidAdvisees(int facultyId, string adviseesString);
    bool existFacultyAdvisee(int facultyId, int studentId);
    bool existStudentAdvisor(int studentId, int facultyId);
    void removeFacultyAllAdvisees(int facultyId);
    int getStudentAdvisorId(int studentId);
    void removeAdviseesAdvisor(int faculytId);
    void addAdviseesAdvisor(int faculytId);

public:
    Database();
    ~Database();

    void printAllStudent(ostream& os);
    void printAllFaculty(ostream& os);
    void printStudent(ostream& os, int studentId);
    void printFaculty(ostream& os, int facultyId);
    void printStudentAdvisor(ostream& os, int studentId);
    void printFacultyAdvisees(ostream& os, int facultyId);
    void addStudent(Student* student);
    Student* removeStudent(int studentId);
    void addFaculty(Faculty* faculty);
    Faculty* removeFaculty(int facultyId);
    void changeStudentAdvisor(int studentId, int facultyId);
    void removeFacultyAdvisee(int facultyId, int studentId);
    void addFacultyAdvisee(int facultyId, int studentId);
    void rollback();
    void run();
    void pause(string message);
};
