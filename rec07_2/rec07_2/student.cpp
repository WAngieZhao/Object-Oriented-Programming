//
//  student.cpp
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

using namespace std;

namespace BrooklynPoly{
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
    Student::Student(const string& name): name(name){};
    const string& Student::getName() const {return name;};
        
    bool Student::changeName(const string& newName){
        name = newName;
        return true;
    }

    bool Student::addCourse(Course* course){
        //find course
        size_t index = courses.size();
        for (size_t i = 0; i < courses.size(); i++){
            if (courses[i] == course){
                index = i;
            }
        }
        
        //check if student is already enrolled in class
        if (index != courses.size()){
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
}
