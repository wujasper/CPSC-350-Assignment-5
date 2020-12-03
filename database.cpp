/*
  Full Name: Jasper Wu
  Student ID: 2339715
  Chapman email: jaswu@chapman.edu
  Course number and section: 350-01
  Assignment Number: 5
*/

#include "database.h"

// default constructor to set default variables
Database::Database() {
    tables = new DatabaseTables();
    for (int i = 0; i < 5; ++i) {
        rollbackDatabase[i] = DatabaseTables();
    }
    rollbackIdx = 0;
    rollbackSize = 0;

    readTable("studentTable");
    readTable("facultyTable");
}
// default destructor
Database::~Database() {
    delete tables;
}
// add student record
void Database::addStudent(Student *student) {
    tables->masterStudent->insert(*student);
}
// remove student record via student id
Student* Database::removeStudent(int studentId) {
    Student *student = new Student(studentId);
    Student *studentRemoved = tables->masterStudent->search(*student);
    tables->masterStudent->remove(*student);
    return studentRemoved;
}
// print student record via student id
void Database::printStudent(ostream& os, int studentId) {
    Student *student = new Student(studentId);
    os << *(tables->masterStudent->search(*student));
}
// print all student records
void Database::printAllStudent(ostream& os) {
    tables->masterStudent->printInorder(os);
}
// print student's advisor via student id
void Database::printStudentAdvisor(ostream& os, int studentId) {
    Student *student = new Student(studentId);
    int advisorId = tables->masterStudent->search(*student)->getAdvisorId();
    printFaculty(os, advisorId);
}
// print student's advisor via student id
int Database::getStudentAdvisorId(int studentId) {
    Student *student = new Student(studentId);
    return tables->masterStudent->search(*student)->getAdvisorId();
}
// change student's advisor via ids
void Database::changeStudentAdvisor(int studentId, int facultyId) {
    Student *student = new Student(studentId);
    tables->masterStudent->search(*student)->setAdvisorId(facultyId);
}
// check if student's advisor exists in the database
bool Database::existStudentAdvisor(int studentId, int facultyId) {
    Student *student = new Student(studentId);
    Student *studentFound = tables->masterStudent->search(*student);
    return (studentFound->getAdvisorId() == facultyId);
}
// add faculty record
void Database::addFaculty(Faculty *faculty) {
    tables->masterFaculty->insert(*faculty);
}
// remove faculty record via faculty id
Faculty* Database::removeFaculty(int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    Faculty *facultyRemoved = tables->masterFaculty->search(*faculty);
    tables->masterFaculty->remove(*faculty);
    return facultyRemoved;
}
// print faculty record via faculty id
void Database::printFaculty(ostream& os, int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    os << *(tables->masterFaculty->search(*faculty));
}
// print all faculty records
void Database::printAllFaculty(ostream& os) {
    tables->masterFaculty->printInorder(os);
}
// print faculty's advisees via faculty id
void Database::printFacultyAdvisees(ostream& os, int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    int *adviseesArray = tables->masterFaculty->search(*faculty)->getAdviseesArray();
    int size = tables->masterFaculty->search(*faculty)->getAdviseesSize();

    for (int i = 0; i < size; ++i) {
        printStudent(os, adviseesArray[i]);
    }
}
// remove faculty's advisee via ids
void Database::removeFacultyAdvisee(int facultyId, int studentId) {
    Faculty *faculty = new Faculty(facultyId);
    tables->masterFaculty->search(*faculty)->removeAdvisee(studentId);
}
// add faculty's advisee via ids
void Database::addFacultyAdvisee(int facultyId, int studentId) {
    Faculty *faculty = new Faculty(facultyId);
    tables->masterFaculty->search(*faculty)->addAdvisee(studentId);
}
// check if faculty's advisee exists in the database
bool Database::existFacultyAdvisee(int facultyId, int studentId) {
    Faculty *faculty = new Faculty(facultyId);
    int *adviseesArray = tables->masterFaculty->search(*faculty)->getAdviseesArray();
    int size = tables->masterFaculty->search(*faculty)->getAdviseesSize();
    bool found = false;
    int i = 0;

    // iterate through the advisee and find the match
    while (!found && i < size) {
        if (studentId == adviseesArray[i++]) {
            found = true;
        }
    }

    return found;
}
// remove all advisees from Faculty via faculty id
void Database::removeFacultyAllAdvisees(int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    int *adviseesArray = tables->masterFaculty->search(*faculty)->getAdviseesArray();
    int size = tables->masterFaculty->search(*faculty)->getAdviseesSize();

    // iterate each advisee and remove from the database
    for (int i = 0; i < size; ++i) {
        removeFacultyAdvisee(facultyId, adviseesArray[i]);
    }
}
void Database::removeAdviseesAdvisor(int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    int *adviseesArray = tables->masterFaculty->search(*faculty)->getAdviseesArray();
    int size = tables->masterFaculty->search(*faculty)->getAdviseesSize();

    // iterate each advisee and remove the advisor ID
    for (int i = 0; i < size; ++i) {
        if (checkValidStudentId(adviseesArray[i])) {
            changeStudentAdvisor(adviseesArray[i], -1);
        }
    }
}
void Database::addAdviseesAdvisor(int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    Faculty *facultySearched = tables->masterFaculty->search(*faculty);
    int *adviseesArray = tables->masterFaculty->search(*faculty)->getAdviseesArray();
    int size = tables->masterFaculty->search(*faculty)->getAdviseesSize();

    // iterate each advisee and remove the advisor ID
    for (int i = 0; i < size; ++i) {
        if (checkValidStudentId(adviseesArray[i])) {
            changeStudentAdvisor(adviseesArray[i], facultyId);
        }
    }
}
// check if faculty exists in the database via faculty id
bool Database::checkValidFacultyId(int facultyId) {
    Faculty *faculty = new Faculty(facultyId);
    Faculty *searchedFaculty = tables->masterFaculty->search(*faculty);
    if (searchedFaculty == NULL) {
        cout << "***** Invalid Faculty ID: " << facultyId << " *****" << endl;
        return false;
    }
    return true;
}
// check if student exists in the database via student id
bool Database::checkValidStudentId(int studentId) {
    Student *student = new Student(studentId);
    Student *searchedStudent = tables->masterStudent->search(*student);
    if (searchedStudent == NULL) {
        cout << "***** Invalid Student ID: " << studentId << " *****" << endl;
        return false;
    }
    return true;
}
// check if faculty's advisees exist in the database via faculty id
bool Database::checkValidAdvisees(int facultyId, string adviseesString) {
    Faculty *faculty = new Faculty(facultyId);
    int size;
    int *adviseesArray = faculty->convertStringToArray(adviseesString, size);
    bool valid = true;

    // check if faculty's advisee exists in the database
    for (int i = 0; i < size; ++i) {
        if (!checkValidStudentId(adviseesArray[i])) {
            valid = false;
        }
    }
    return valid;
}
// main menu
void Database::printMainMenu() {
    cout << "++++++++++++++++++++++++++++++ Main Menu ++++++++++++++++++++++++++++++" << endl;
    cout << "(1) Print all students and their information" << endl;
    cout << "(2) Print all faculty and their information" << endl;
    cout << "(3) Find and display student information given the students id" << endl;
    cout << "(4) Find and display faculty information given the faculty id" << endl;
    cout << "(5) Given a student’s id, print the name and info of their faculty advisor" << endl;
    cout << "(6) Given a faculty id, print ALL the names and info of his/her advisees" << endl;
    cout << "(7) Add a new student" << endl;
    cout << "(8) Delete a student given the id" << endl;
    cout << "(9) Add a new faculty member" << endl;
    cout << "(10) Delete a faculty member given the id" << endl;
    cout << "(11) Change a student’s advisor given the student id and the new faculty id" << endl;
    cout << "(12) Remove an advisee from a faculty member given the ids" << endl;
    cout << "(13) Rollback" << endl;
    cout << "(14) Exit" << endl;
    cout << "Enter your choice? ";
}
// get user choice
int Database::getMainChoice() {
    printMainMenu();
    string userStr;
    int userInt;

    do {
        getline(cin, userStr);
        userInt = stringToInt(userStr);
        if (userInt < 1 || userInt > 14) {
            cout << "***** Invalid choice, try again *****" << endl;
            cout << "Enter your choice? ";
        }
    } while(userInt < 1 || userInt > 14);

    return userInt;
}
// get student record from user input
Student* Database::getStudentRecord() {
    int id;
    string name;
    string level;
    string major;
    double gpa;
    int advisorId;

    id = getUserInt("Enter Student ID: ", 0);
    name = getUserString("Enter Student Name: ");
    level = getUserString("Enter Student Level: ");
    major = getUserString("Enter Student Major: ");
    gpa = getUserDouble("Enter Student GPA: ");
    advisorId = getUserInt("Enter Faculty Advisor ID: ", 1);

    // allow empty advisor but print warning
    if (advisorId == -1) {
        cout << "-----Advisor ID is Empty, Record is Created with Empty Advisor ID -----" << endl;
        pause("  Press Enter to continue ...");
    }
    else if (!checkValidFacultyId(advisorId)) {
        return NULL;
    }

    // instantiate a student object
    Student *student = new Student(id, name, level, major, gpa, advisorId);

    return student;
}
// get faculty record from user input
Faculty* Database::getFacultyRecord() {
    int id;
    string name;
    string level;
    string department;
    string adviseesString;

    id = getUserInt("Enter Faculty ID: ", 0);
    name = getUserString("Enter Faculty Name: ");
    level = getUserString("Enter Faculty Level: ");
    department = getUserString("Enter Faculty Department: ");
    adviseesString = getUserString("Enter Faculty Advisees (IDs separated by comma): ");

    // allow empty advisor but print warning
    if (adviseesString == "") {
        cout << "----- Advisees is Empty, Record is Created with Empty Advisees -----" << endl;
        pause("  Press Enter to continue ...");
    }
    else if (!checkValidAdvisees(id, adviseesString)) {
        return NULL;
    }

    Faculty *faculty = new Faculty(id, name, level, department, adviseesString);

    return faculty;
}
// run the database in a loop till user select to exit
void Database::run() {
    int studentId;
    int facultyId;
    Faculty *faculty;
    Student *student;
    string userStr;
    bool exit = false;

    do {
        int mainChoice = getMainChoice();

        switch(mainChoice) {
            // Print all students and their information
            case 1: {
                printAllStudent(cout);
                pause("  Press Enter to continue ...");
                break;
            }
            // Print all faculty and their information
            case 2: {
                printAllFaculty(cout);
                pause("  Press Enter to continue ...");
                break;
            }
            // Find and display student information given the students id
            case 3: {
                studentId = getUserInt("Enter Student ID: ", 0);
                if (checkValidStudentId(studentId)) {
                    printStudent(cout, studentId);
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Find and display faculty information given the faculty id
            case 4: {
                facultyId = getUserInt("Enter Faculty ID: ", 0);
                if (checkValidFacultyId(facultyId)) {
                    printFaculty(cout, facultyId);
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Given a student’s id, print the name and info of their faculty advisor
            case 5: {
                studentId = getUserInt("Enter Student ID: ", 0);
                if (checkValidStudentId(studentId)) {
                    printStudentAdvisor(cout, studentId);
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Given a faculty id, print ALL the names and info of his/her advisees
            case 6: {
                facultyId = getUserInt("Enter Faculty ID: ", 0);
                if (checkValidFacultyId(facultyId)) {
                    printFacultyAdvisees(cout, facultyId);
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Add a new student
            case 7: {
                student = getStudentRecord();
                if (student != NULL) {
                    // rollback snapshot
                    rollbackSnapshot();
                    // add student record
                    addStudent(student);
                    // execute referential integrity
                    // if advisor id is not empty then validate it and update the faculty's advisee list
                    if (student->getAdvisorId() != -1) {
                        if (!existFacultyAdvisee(student->getAdvisorId(), student->getId())) {
                            addFacultyAdvisee(student->getAdvisorId(), student->getId());
                        }
                    }
                }
                break;
            }
            // Delete a student given the id
            case 8: {
                studentId = getUserInt("Enter Student ID: ", 0);
                if (checkValidStudentId(studentId)) {
                    // rollback snapshot
                    rollbackSnapshot();
                    // execute referential integrity
                    // if advisor id is not empty then validate it and remove from the faculty's advisee list
                    facultyId = getStudentAdvisorId(studentId);
                    if (facultyId != -1) {
                        if (existFacultyAdvisee(facultyId, studentId)) {
                            removeFacultyAdvisee(facultyId, studentId);
                        }
                    }
                    // remove student record
                    student = removeStudent(studentId);
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Add a new faculty member
            case 9: {
                faculty = getFacultyRecord();
                if (faculty != NULL) {
                    // rollback snapshot
                    rollbackSnapshot();
                    // add faculty record
                    addFaculty(faculty);
                    // execute referential integrity
                    // update advisee's advisor ID
                    if (faculty->getAdvisees() != "") {
                        addAdviseesAdvisor(faculty->getId());
                    }
                }
                break;
            }
            // Delete a faculty member given the id
            case 10: {
                facultyId = getUserInt("Enter Faculty ID: ", 0);
                if (checkValidFacultyId(facultyId)) {
                    // rollback snapshot
                    rollbackSnapshot();
                    // execute referential integrity
                    // remove advisor id for each faculty's advisee
                    removeAdviseesAdvisor(facultyId);
                    // execute referential integrity
                    // remove faculty's advisee list
                    removeFacultyAllAdvisees(facultyId);
                    // remove faculty record
                    faculty = removeFaculty(facultyId);
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Change a student’s advisor given the student id and the new faculty id
            case 11: {
                studentId = getUserInt("Enter Student ID: ", 0);
                facultyId = getUserInt("Enter Faculty ID: ", 0);
                if (checkValidStudentId(studentId) && checkValidFacultyId(facultyId)) {
                    // rollback snapshot
                    rollbackSnapshot();
                    int advisorIdRemoved = getStudentAdvisorId(studentId);
                    // change student's advisor ID
                    changeStudentAdvisor(studentId, facultyId);
                    // add student to to new faculty's advisee list
                    if (!existFacultyAdvisee(facultyId, studentId)) {
                        addFacultyAdvisee(facultyId, studentId);
                    }
                    // execute referential integrity
                    // remove student id from old faculty's advisee list
                    if (existFacultyAdvisee(advisorIdRemoved, studentId)) {
                        removeFacultyAdvisee(advisorIdRemoved, studentId);
                    }
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Remove an advisee from a faculty member given the ids
            case 12: {
                facultyId = getUserInt("Enter Faculty ID: ", 0);
                studentId = getUserInt("Enter Student ID: ", 0);
                if (checkValidFacultyId(facultyId)) {
                    if (existFacultyAdvisee(facultyId, studentId)) {
                        // rollback snapshot
                        rollbackSnapshot();
                        // remove from faculty's advisees list
                        removeFacultyAdvisee(facultyId, studentId);
                        // execute referential integrity
                        // remove student's advisor id
                        if (checkValidStudentId(studentId)) {
                            if (existStudentAdvisor(studentId, facultyId)) {
                                changeStudentAdvisor(studentId, -1);
                            }
                        }
                    }
                }
                pause("  Press Enter to continue ...");
                break;
            }
            // Rollback
            case 13: {
                // roll back
                rollback();
                break;
            }
            // exit
            case 14: {
                // exit
                exit = true;
                break;
            }
        }
    } while (!exit);

    // write database to files
    writeTable("studentTable");
    writeTable("facultyTable");
}
// write database to file
int Database::writeTable(string tableSelect) {
    FileIo *files = new FileIo();

    if (!files->openFileForWrite(tableSelect)) {
        return -1;
    }
    if (tableSelect == "studentTable") {
        tables->masterStudent->printInorder(files->writeStream);
    } else if (tableSelect == "facultyTable") {
        tables->masterFaculty->printInorder(files->writeStream);
    }

    files->closeFiles();
    return 0;
}
// read database from file
int Database::readTable(string tableSelect) {
    FileIo *files = new FileIo();

    if (!files->openFileForRead(tableSelect)) {
        return -1;
    }
    initializeFromFile(files->readStream, tableSelect);

    files->closeFiles();
    return 0;
}
// initialize database from file
void Database::initializeFromFile(ifstream &readStream, string tableSelect) {
    string line;
    int lineIdx = 1;
    string record[6];

    // read database record from file and add to database
    while (getline(readStream, line)) {
        record[lineIdx - 1] = line;
        if (tableSelect == "studentTable" && lineIdx % 6 == 0) {
            Student *student = new Student(stringToInt(record[0]), record[1], record[2], record[3], stringToDouble(record[4]), stringToInt(record[5]));
            tables->masterStudent->insert(*student);
            lineIdx = 1;
        } else if (tableSelect == "facultyTable" && lineIdx % 5 == 0) {
            Faculty *faculty = new Faculty(stringToInt(record[0]), record[1], record[2], record[3], record[4]);
            tables->masterFaculty->insert(*faculty);
            lineIdx = 1;
        } else {
            lineIdx++;
        }
    }
}
// add database snapshot to rollback database
void Database::rollbackSnapshot() {
    // copy database to rollback database
    rollbackDatabase[rollbackIdx] = *tables;
    // maximum rollback size is 5
    if (rollbackSize < 5) {
        rollbackSize++;
    } else {
        cout << "----- Maximum Number of Rollback(5) is Reached, Overwriting the Oldest History -----" << endl;
        pause ("  Press Enter to continue ...");
    }
    // rollbackIdx is in range 0 to 4
    rollbackIdx = (rollbackIdx + 1) % 5;
}
// roll back the database by copying from rollback database
void Database::rollback() {
    if (rollbackSize > 0) {
        // wraparound rollbackIdx at boundary
        if (rollbackIdx == 0) {
            rollbackIdx = 4;
        } else {
            rollbackIdx--;
        }
        // copy database from rollback database
        *tables = rollbackDatabase[rollbackIdx];
        rollbackSize--;
    } else {
        cout << "----- Rollback History is Empty -----" << endl;
        pause ("  Press Enter to continue ...");
    }
}
// string to int conversion
int Database::stringToInt(string inStr) {
    try {
        return stoi(inStr);
    } catch(exception &e) {
        cout << "***** Invalid number, try again *****" << endl;
        return -1;
    }
}
// string to double conversion
double Database::stringToDouble(string inStr) {
    try {
        return stod(inStr);
    } catch(exception &e) {
        cout << "***** Invalid number, try again *****" << endl;
        return -1;
    }
}
// get user input and convert to int
int Database::getUserInt(string msg, int emptyAllowed) {
    string userStr;
    int userInt = -1;

    do {
        cout << msg;
        getline(cin, userStr);
        if (userStr == "" && emptyAllowed) {
            userInt = -1;
        } else {
            userInt = stringToInt(userStr);
        }
    } while(userInt < 0 && !(emptyAllowed && userStr == ""));

    return userInt;
}
// get user input and convert to double
double Database::getUserDouble(string msg) {
    string userStr;
    double userDouble = -1;

    do {
        cout << msg;
        getline(cin, userStr);
        userDouble = stringToDouble(userStr);
    } while(userDouble < 0);

    return userDouble;
}
// get user input in string
string Database::getUserString(string msg) {
    string userStr = "";
    cout << msg;
    getline(cin, userStr);

    return userStr;
}
// Pause till user type "Enter"
void Database::pause(string message) {

  cout << message << flush;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
