//
//  registrar.cpp
//  rec07_2
//
//  Created by Angie Zhao on 2019/10/18.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

#include "course.h"
#include "student.h"
#include "registrar.h"

using namespace std;

namespace BrooklynPoly {
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
        } else {
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
    
        //extra
        bool Registrar::changeStudentName(const string& oldName,
                                          const string& newName){
            size_t studentInd = findStudent(oldName);
            students[studentInd]->changeName(newName);
            return true;
        }
        
        bool Registrar::dropStudentFromCourse(const string& studentName,
                                   const string& courseName){
            size_t studentInd = findStudent(studentName);
            size_t courseInd = findCourse(courseName);
    
            //check if both student and course are found
            if (studentInd == students.size() || courseInd == courses.size()){
                return false;
            } else {
                students[studentInd]->removedFromCourse(courses[courseInd]);
                //courses[courseInd]->removeStudentsFromCourse(students[studentInd]);
            }
            return true;
        }

            
            //    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
            
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
        
}
