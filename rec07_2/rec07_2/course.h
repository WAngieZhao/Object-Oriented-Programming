//
//  course.h
//  rec07_2
//
//  Created by Angie Zhao on 2019/10/18.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#ifndef COURSE_H
#define COURSE_H
using namespace std;

namespace BrooklynPoly{
    class Student;

    class Course {
        friend ostream& operator<<(ostream& os, const Course& rhs);
    public:
        // Course methods needed by Registrar
        Course(const string& courseName);
        const string& getName() const;
        bool addStudent(Student* student);
        void removeStudentsFromCourse();

    private:
        string name;
        vector<Student*> students;
    };
}

#endif /* course_h */
