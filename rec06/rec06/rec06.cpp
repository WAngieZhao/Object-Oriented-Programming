//
//  rec06.cpp
//
//  Created by Angie Zhao on 2019/10/11.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <string>
#include <iostream>
using namespace std;

const int INITIAL_CAPACITY = 1;

class Position {
    friend ostream& operator<<(ostream& os, const Position& rhs) {
        os << '[' << rhs.title << ',' << rhs.salary << ']';
        return os;
    }
public:
    Position(const string& aTitle, double aSalary)
        : title(aTitle), salary(aSalary) {}
    const string& getTitle() const { return title; }
    double getSalary() const { return salary; }
    void changeSalaryTo(double d) { salary = d; }
private:
    string title;
    double salary;
}; // class Position

class Entry {
    friend ostream& operator<<(ostream& os, const Entry& rhs) {
        os << rhs.name << ' ' << rhs.room
           << ' ' << rhs.phone << ", " << *rhs.pos;
        return os;
    }
public:
    Entry(const string& name, unsigned room, unsigned phone, Position& position)
        : name(name), room(room), phone(phone), pos(&position) {
    }
    const string& getName() const { return name; }
    unsigned getPhone() const { return phone; }
private:
    string name;
    unsigned room;
    unsigned phone;
    Position* pos;
}; // class Entry

class Directory {
    // Overload output operator
    friend ostream& operator<<(ostream& os, const Directory& directory) {
        for (size_t i = 0; i < directory.size; ++i){
            os << *(directory.entries[i]) << endl;
        }
        return os;
    }
    
public:
    Directory(){
        entries = new Entry*[INITIAL_CAPACITY];
        size = 0;
        capacity = INITIAL_CAPACITY;
    };
    
    ~Directory(){
        cout << "Directory is being deleted" << endl;
        for (size_t i = 0; i < size; i++) {
            delete entries[i];
        }
        delete[] entries;
    }
    
    Directory& operator= (const Directory& dire2) {
        if (&dire2 != this) {
            cout << "Calling assignment operator" << endl;
            for (size_t i = 0; i < size; i++) {
                delete entries[i];
            }
            delete[] entries;
            
            entries = new Entry*[capacity];
            for (size_t i = 0; i < size; i++) {
                entries[i] = new Entry(*(dire2.entries[i]));
            }
        }
        return *this;
    }
    
    Directory(const Directory& dire2){
        cout << "Directory is being copied" << endl;
        entries = new Entry*[dire2.capacity];
        size = dire2.size;
        capacity = dire2.capacity;
        
        for (size_t i = 0; i < size; ++i){
            entries[i] = new Entry(*(dire2.entries[i]));
        }
    }
    
    unsigned operator[](const string& name) const {
        for (size_t i = 0; i < size; i++) {
            if (entries[i]->getName() == name) {
                return entries[i]->getPhone();
            }
        }
        return 9999;
    }
    
    // We'll get you started with the add method, but obviously you
    // have a lot of work to do here.
    void add(const string& name, unsigned room, unsigned ph, Position& pos) {
        if (size == capacity)    {
            // something is missing!!!  Add it!
            Entry** old_entries = entries;
            entries = new Entry* [2*capacity];
            for (size_t i = 0; i < size; ++i){
                entries[i] = old_entries[i];
            }
            capacity *= 2;
            delete[] old_entries;

        } // if
        entries[size] = new Entry(name, room, ph, pos);
        ++size;
    } // add

private:
    Entry** entries;
    size_t size;
    size_t capacity;
}; // class Directory

void doNothing(Directory dir) { cout << dir << endl; }

int main() {
    
    // Note that the Postion objects are NOT on the heap.
    Position boss("Boss", 3141.59);
    Position pointyHair("Pointy Hair", 271.83);
    Position techie("Techie", 14142.13);
    Position peon("Peonissimo", 34.79);
    
    // Create a Directory
    Directory d;
    d.add("Marilyn", 123, 4567, boss);
    cout << d << endl;

    Directory d2 = d;    // What function is being used??
    d2.add("Gallagher", 111, 2222, techie);
    d2.add("Carmack", 314, 1592, techie);
    cout << d << endl;

    cout << "Calling doNothing\n";
    doNothing(d2);
    cout << "Back from doNothing\n";

    Directory d3;
    d3 = d2;

    // Should display 1592
    cout << d2["Carmack"] << endl;
    
} // main
