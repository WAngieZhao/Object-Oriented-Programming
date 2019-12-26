//
//  Noble.cpp
//
//  The program calculate battles and status among nobles and their protectos.
//  Methods for Noble class

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Protector.h"

using namespace std;

namespace WarriorCraft {
    //Base Noble class methods
    //Constructors and getters
    Noble::Noble (const string& nm, double nStrength): name(nm), strength (nStrength), alive(true) {}
    string Noble::get_name()const {return name;}
    double Noble::get_strength()const {return strength;}
    bool Noble::is_alive()const {return alive;}

    //Set the noble's new strength
    void Noble::set_strength(double newStrength){
        if (newStrength <= 0){
            strength = 0;
            alive = false;
        }else{
            strength = newStrength;
        }
    }
    //reset the noble's alive
    void Noble::set_alive(bool life){
        alive = life;
    }
    
    //Start a battle with another noble
    void Noble::battle(Noble& enemy){
        double enemy_strength = enemy.get_strength();
        cout << name << " battles " << enemy.get_name() << endl;
        
        if (alive && enemy.is_alive()){
            //If both nobles are alive
            if (strength > enemy_strength){
                //The noble is stronger
                change_strength(enemy_strength);
                enemy.change_strength(strength);
                cout << name << " defeats " << enemy.get_name() << endl;
            } else if (strength < enemy_strength){
                //The enemy if stronger
                change_strength(enemy_strength);
                enemy.change_strength(strength);
                cout << enemy.get_name() << " defeats " << name << endl;
            } else {
                //Draw
                change_strength(enemy_strength);
                enemy.change_strength(strength);
                cout << "Mutual Annihilation: " << name << " and "
                << enemy.get_name() << " die at each other's hands" << endl;
            }
        } else {
            //At least one noble is dead
            if (alive) {
                //The noble is alive
                change_strength(0);
                cout << "He's dead, " << name << endl;
            } else if (enemy.is_alive()){
                //The enemy is alive
                enemy.change_strength(0);
                cout << "He's dead, " << enemy.get_name() << endl;
            } else {
                //Both nobles are dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
    }
    



    //Lord class methods
    //Public methods
    //Constructor
    Lord::Lord (const string& nm): Noble(nm,0) {}
    //Hire a Protector
    bool Lord::hires(Protector& protector){
        if (protector.is_hired()==false && is_alive()){
            //Can hired if the protector is not hired & noble is alive
            protector.change_hire(true,this);
            army.push_back(&protector);
            set_strength(get_strength()+protector.get_strength());
            return true;
        }
        return false;
    }

    //Fire a Protector
    bool Lord::fires(Protector& protector){
        if (protector.is_hired() && is_alive()){
            //Can fire if the protector is hired & noble is alive
            //Find protector index & check if protector is hired by this noble
            size_t protector_index = find_protector_ind(protector);
            if (protector_index != army.size()){
                //If protector is found (hired by this noble)
                cout << "You don't work for me anymore "
                    << protector.get_name() << "! -- " << get_name() << "." << endl;
                //Can fire if the protector is hired & noble is alive
                protector.change_hire(false, this);
                remove_protector(protector);
                return true;
            }
        }
        return false;
    }

    //Remove a Protector from its army
    void Lord::remove_protector(const Protector& protector){
        //Set strength
        set_strength(get_strength()-protector.get_strength());
        //Remove protector from the army
        size_t protector_index = find_protector_ind(protector);
        for (size_t i = protector_index; i < army.size()-1; ++i){
            army[protector_index] = army[protector_index + 1];
        }
        army.pop_back();
    }

    //Calculate and change the strength of his army
    void Lord::change_strength(int change){
        double ratio = 0;
        if (change < get_strength()){
            //Find ratio if the noble is still alive
            ratio = 1 - (change/get_strength());
        } else {
            //If the noble died
            set_strength(0);
        }
        //Change the strenght of warriors
        for (Protector* protector: army){
            protector->set_strength(ratio);
        }
    }

    //Private methods
    //Find the index of the Protector if he is in the army
    size_t Lord::find_protector_ind(const Protector& protector){
        size_t protector_index = army.size();
        for (size_t i=0; i < army.size(); ++i){
            if (&protector == army[i]){
                protector_index = i;
                break;
            }
        }
        return protector_index;
    }

    //PersonWithStrengthToFight class methods
    //Public methods
    //Calculate and change the strength of himself
    void PersonWithStrengthToFight::change_strength(int change){
        set_strength(get_strength()-change);
        cout << "Ugh!" << endl;
    }
}


