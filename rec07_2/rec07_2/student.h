//
//  student.h
//  rec07_2
//
//  Created by Angie Zhao on 2019/10/18.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#ifndef STUDENT_H
#define STUDENT_H
using namespace std;

namespace BrooklynPoly{
    class Course;
    class Student {
        friend ostream& operator<<(ostream& os, const Student& rhs);
    public:
        // Student methods needed by Registrar
        Student(const string& name);
        const string& getName() const;
        bool addCourse(Course* course);
        bool changeName(const string& newName);

        // Student method needed by Course
        void removedFromCourse(Course* course);

    private:
        string name;
        vector<Course*> courses;
    };
}


#endif /* student_h */
