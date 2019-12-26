//
//  rec05.cpp
//
//  Created by Angie Zhao on 2019/10/4.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section{
    friend ostream& operator<< (ostream& os, const Section& section){
        os << "Section: " << section.name << ", Time slot: " << section.time << ", Students: ";
        if (section.studentRecords.size() == 0) {
            os << "None" << endl;
        }
        else {
            os << endl;
            for (size_t i = 0; i < section.studentRecords.size(); ++i){
                os << *(section.studentRecords[i]) << endl;
            }
        }
        return os;
    }
    
    class Time{
        friend ostream& operator<< (ostream& os, const Time& time){
            os << "[Day: " << time.date << ", Start time: " ;
            if (time.hour <= 12){
                os << time.hour << "am]";
            } else {
                os << time.hour - 12 << "pm]";
            }
            return os;
        }
        
    public:
        Time(const string& tDate, int& tHour): date(tDate), hour(tHour) {}
        string get_date() const {return date;}
        int get_hour() const {return hour;}
        
    private:
        string date;
        int hour;
    };
    
    class StudentRecord{
        friend ostream& operator<< (ostream& os, const StudentRecord studentRecord){
            os << "Name: " << studentRecord.name << ", Grades:";
            for (size_t i = 0; i < studentRecord.grade.size(); ++i){
                os << ' ' << studentRecord.grade[i];
            }
            return os;
        }
        
    public:
        StudentRecord(const string& SRName):name(SRName), grade(14,-1) {}
        string get_name() const {return name;}
        void setGrade(int score, int week){
            grade[week-1] = score;
        }
        
    private:
        string name;
        vector<int> grade;
    };
    
public:
    Section(const string& secName, const string& secDate, int secHour):
    name(secName), time(secDate, secHour), studentRecords() {}
    string get_name() const {return name;}
    string get_sectionDate() const {return time.get_date();}
    int get_sectionHour() const {return time.get_hour();}
    
    void addStudent(const string& studentName){
        StudentRecord* student_report = new StudentRecord(studentName);
        studentRecords.push_back(student_report);
    }

    void setStudentGrade(const string& name, int score, int week){
        size_t index = studentRecords.size();
        for (size_t i = 0; i < studentRecords.size(); ++i)
            if (studentRecords[i]->get_name() == name){
                index = i;
            }
        studentRecords[index]->setGrade(score,week);
    }
    
    ~Section() {
        cout << "Section " << name << " is being deleted" << endl;
        for (size_t i = 0; i < studentRecords.size(); ++i){
            cout << "Deleting " << studentRecords[i]->get_name() << endl;
            delete studentRecords[i];
        }
        studentRecords.clear();
    }
    
    Section(Section& section): name(section.name), time(section.time){
        for (size_t i = 0; i < section.studentRecords.size(); ++i){
            StudentRecord* new_record = new StudentRecord(*(section.studentRecords[i]));
            studentRecords.push_back(new_record);
        }
    }
    
private:
    string name;
    Time time;
    vector<StudentRecord*> studentRecords;
};


class LabWorker{
    friend ostream& operator<< (ostream& os, const LabWorker& worker){
        if (worker.section == nullptr){
            os << worker.name << "does not have a section";
        } else {
            os << worker.name << "has " << *worker.section;
        }
        return os;
    }
    
public:
    LabWorker(const string& LWName): name(LWName), section(nullptr) {}
    string get_name() const {return name;}
    void addSection(Section& sec){
        section = &sec;
    }
    void addGrade(const string& name, int score, int week){
        section -> setStudentGrade(name, score, week);
    }
    
private:
    string name;
    Section* section;
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main(int argc, const char * argv[]) {
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;
    
    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;
    
    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;
    
    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;
    
    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;
    
    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;
    
    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;
    
    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
}

