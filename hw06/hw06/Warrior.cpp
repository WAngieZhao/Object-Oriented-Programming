//
//  Warrior.cpp
//  Created by Angie Zhao on 2019/10/27.
//
//  The program calculate battles and status among nobles and their warriors.
//  Methods for Warrior class

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Warrior.h"

using namespace std;
namespace WarriorCraft {
    //Set Warrior's output operator
    ostream& operator<< (ostream& os, const Warrior& warrior){
        os << warrior.name << ": " << warrior.strength << endl;
        return os;
    }
    
    //Constructors and getters
    Warrior::Warrior(const string& nm, int wrStrength):
        name(nm), strength(wrStrength), hired(false), lord(nullptr) {}
    string Warrior::get_name()const {return name;}
    double Warrior::get_strength()const {return strength;}
    bool Warrior::is_hired()const {return hired;}
    
    //Change the hire status of warrior
    void Warrior::change_hire(const bool& change, Noble* noble){
        hired = change;
        if (change){
            lord = noble;
        } else {
            lord = nullptr;
        }
    }
        
    //Warrior runaway from its lord
    void Warrior::runaway(){
        cout << name << " flees in terror, abandoing his lord, "
             << lord->get_name() << endl;
        lord->remove_warrior(*this);
        lord = nullptr;
    }
    //Change the warrior's strength by ratio
    void Warrior::set_strength(double ratio){
        strength *= ratio;
    }

}
