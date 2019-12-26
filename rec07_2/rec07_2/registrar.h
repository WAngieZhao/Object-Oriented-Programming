//
//  registrar.h
//  rec07_2
//
//  Created by Angie Zhao on 2019/10/18.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#ifndef REGISTRAR_H
#define REGISTRAR_H
using namespace std;

namespace BrooklynPoly{
    class Student;
    class Course;

    class Registrar {
        friend ostream& operator<<(ostream& os, const Registrar& rhs);
    public:
        Registrar();
        bool addCourse(const string& courseName);
        bool addStudent(const string& name);

        bool enrollStudentInCourse(const string& studentName,
                                   const string& courseName);
        bool cancelCourse(const string& courseName);
        
        bool changeStudentName(const string& oldName,
                               const string& newName);
        bool dropStudentFromCourse(const string& studentName,
                                   const string& courseName);
        void purge();

    private:
        size_t findStudent(const string& studentName) const;
        size_t findCourse(const string& courseName) const;

        vector<Course*> courses;
        vector<Student*> students;
    };
}


#endif /* registrar_h */
