//
//  course.cpp
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

namespace BrooklynPoly {
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
    const string& Course::getName() const {return name;};

    bool Course::addStudent(Student* student){
        //find student
        size_t index = students.size();
        for (size_t i = 0; i < students.size(); i++){
            if (students[i] == student){
                index = i;
            }
        }
        
        //check if student is already enrolled in class
        if (index != students.size()){
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
}
