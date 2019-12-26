//
//  rec07_1.cpp
//
//  Created by Angie Zhao on 2019/10/18.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const {return name;};
    bool addStudent(Student* student);
    void removeStudentsFromCourse();

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const {return name;};
    bool addCourse(Course* course);

    // Student method needed by Course
    void removedFromCourse(Course* course);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string& courseName);
    bool addStudent(const string& name);
    
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    
    void purge();

private:
    size_t findStudent(const string& studentName) const;
    size_t findCourse(const string& courseName) const;

    vector<Course*> courses;
    vector<Student*> students;
};

int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;
     
    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;
   
    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}

//Course class method
//Course operator<<
ostream& operator<<(ostream& os, const Course& rhs){
    //print course name
    os << rhs.name << ": ";
    //check and print course student
    if (rhs.students.size() == 0){
        os << "No Students";
    } else {
        for (Student* student: rhs.students){
            os << student->getName() << " ";
        }
    }
    return os;
}

Course::Course(const string& courseName): name(courseName){};

bool Course::addStudent(Student* student){
    //find student
    size_t index = students.size();
    for (size_t i = 0; i < students.size(); i++){
        if (students[i] == student){
            index = i;
        }
    }
    
    //check if student is already enrolled in class
    if (index == students.size()){
        return false;
    }else{
    students.push_back(student);
    }
    return true;
}

void Course::removeStudentsFromCourse(){
    for (Student* student: students) {
        student->removedFromCourse(this);
    }
    students.clear();
}


//Student class method
//Student operator<<
ostream& operator<<(ostream& os, const Student& rhs){
    //print student name
    os << rhs.name << ": ";
    //check and print student course
    if (rhs.courses.size() == 0){
        os << "No Courses";
    } else {
        for (Course* course: rhs.courses){
            os << course->getName() << " ";
        }
    }
    return os;
}

// Student methods needed by Registrar
Student:: Student(const string& name): name(name){};

bool Student::addCourse(Course* course){
    //find course
    size_t index = courses.size();
    for (size_t i = 0; i < courses.size(); i++){
        if (courses[i] == course){
            index = i;
        }
    }
    
    //check if student is already enrolled in class
    if (index == courses.size()){
        return false;
    }else{
        courses.push_back(course);
    }
    return true;
}

// Student method needed by Course
void Student::removedFromCourse(Course* course){
    size_t courseInd = -1;
    //find course
    for (size_t i = 0; i < courses.size(); i++){
        if (courses[i] == course){
            courseInd = i;
            break;
        }
    }
    
    for (size_t i = courseInd; i < (courses.size()-1); i++) {
        courses[i] = courses[i + 1];
    }
    courses.pop_back();
}


//Register Class method
//Register operator<<
ostream& operator<<(ostream& os, const Registrar& rhs){
    //print courses
    os << "Registrar's Report\n" << "Courses: " << endl;
    //check if there are any courses
    if (rhs.courses.size() != 0) {
        for (Course* course: rhs.courses) {
            os << *(course) << endl;
        }
    }
    //print students
    os << "Students: " << endl;
    //check if there are any students
    if (rhs.students.size () != 0){
        for (Student* student: rhs.students) {
            os << *(student) << endl;
        }
    }
    return os;
}

//public methods
Registrar::Registrar(){};

bool Registrar::addCourse(const string& courseName){
    size_t courseInd = findCourse(courseName);
    if (courseInd != courses.size()){
        return false;
    }else{
        courses.push_back(new Course(courseName));
    }
    return true;
};

bool Registrar::addStudent(const string& name){
    size_t studentInd = findStudent(name);
    if (studentInd != students.size()){
        return false;
    }else{
        students.push_back(new Student(name));
    }
    return true;
}

bool Registrar::enrollStudentInCourse(const string& studentName,
                           const string& courseName){
    size_t studentInd = findStudent(studentName);
    size_t courseInd = findCourse(courseName);
    
    //check if both student and course are found
    if (studentInd == students.size() || courseInd == courses.size()){
        return false;
    } else {456j m
        students[studentInd]->addCourse(courses[courseInd]);
        courses[courseInd]->addStudent(students[studentInd]);
    }
    return true;
}

bool Registrar::cancelCourse(const string& courseName){
    size_t courseInd = findCourse(courseName);
    if (courseInd == courses.size()){
        return false;
    } else {
        courses[courseInd]->removeStudentsFromCourse();
        delete courses[courseInd];
        courses[courseInd] = nullptr;
        for (size_t i = courseInd; i < (courses.size()-1); i++) {
            courses[i] = courses[i + 1];
        }
        courses.pop_back();
    }
    return true;
}

void Registrar::purge(){
    for (Student* student: students) {
        delete student;
        student = nullptr;
    }
    for (Course* course: courses) {
        delete course;
        course = nullptr;
    }
    students.clear();
    courses.clear();
}

//private methods
size_t Registrar::findStudent(const string& studentName) const{
    size_t index = students.size();
    for (size_t i = 0; i < students.size(); i++){
        if (students[i]->getName() == studentName){
            index = i;
        }
    }
    return index;
}

size_t Registrar::findCourse(const string& courseName) const{
    size_t index = courses.size();
    for (size_t i = 0; i < courses.size(); i++){
        if (courses[i]->getName() == courseName){
            index = i;
        }
    }
    return index;
}
