//
//  Protector.cpp
//
//  The program calculate battles and status among nobles and their warriors.
//  Methods for Warrior class

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"

using namespace std;
namespace WarriorCraft {
    //Base Protector class methods
    //Constructors and getters
    Protector::Protector(const string& nm, int wrStrength):
        name(nm), strength(wrStrength), hired(false), lord(nullptr) {}
    string Protector::get_name()const {return name;}
    double Protector::get_strength()const {return strength;}
    bool Protector::is_hired()const {return hired;}
    bool Protector::is_alive()const {return alive;}
    string Protector::get_lordName() const {return lord->get_name();};
    
    //Change the hire status of warrior
    void Protector::change_hire(const bool change, Lord* noble){
        hired = change;
        if (change){
            lord = noble;
        } else {
            lord = nullptr;
        }
    }
        
    //Warrior runaway from its lord
    bool Protector::runaway(){
        if (is_alive()){
            cout << name << " flees in terror, abandoing his lord, "
                 << lord->get_name() << endl;
            lord->remove_protector(*this);
            lord = nullptr;
            return true;
        }
        return false;
    }

    //Change the warrior's strength by ratio
    void Protector::set_strength(double ratio){
        strength *= ratio;
    }

    //Wizard class methods
    //Public methods
    //State while defend & set_strength
    void Wizard::set_strength(double ratio){
        cout << "POOF!" << endl;
        Protector::set_strength(ratio);
    }

    //Warrior class methods
    //Public methods
    //State while defend & set_strength
    void Warrior::set_strength(double ratio){
        cout << get_name() << " says: Take that in the name of my lord, " << get_lordName() << endl;
        Protector::set_strength(ratio);
    }

    //Archer class methods
    //Public methods
    //State while defend & set_strength
    void Archer::set_strength(double ratio){
        cout << "TWANG! ";
        Warrior::set_strength(ratio);
    }

    //Swordsman class methods
    //Public methods
    //State while defend & set_strength
    void Swordsman::set_strength(double ratio){
        cout << "CLANG! ";
        Warrior::set_strength(ratio);
    }

}
