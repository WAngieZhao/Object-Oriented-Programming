//
//  Noble.cpp
//  Created by Angie Zhao on 2019/10/27.
//
//  The program calculate battles and status among nobles and their warriors.
//  Methods for Noble class

#include <iostream>
#include <string>
#include <vector>
#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft {
    //Noble class ourput operator
    ostream& operator<< (ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (Warrior* warrior: noble.army){
            os << "\t" << *warrior;
        }
        return os;
    }
        
    //Constructors and getters
    Noble::Noble (const string& nm): name(nm), strength (0), alive(true) {}
    string Noble::get_name()const {return name;}
    double Noble::get_strength()const {return strength;}
    bool Noble::is_alive()const {return alive;}
        
    //Hire a warrior
    bool Noble::hire(Warrior& warrior){
        if (warrior.is_hired()==false && alive){
            //Can hired if the warrior is not hired & noble is alive
            warrior.change_hire(true,this);
            army.push_back(&warrior);
            strength += warrior.get_strength();
            return true;
        }
        return false;
    }
    
    //Fire a warrior
    bool Noble::fire(Warrior& warrior){
        if (warrior.is_hired() && alive){
            //Can fire if the warrior is hired & noble is alive
            //Find warrior index & check if warrior is hired by this noble
            size_t warrior_index = find_warrior_ind(warrior);
            if (warrior_index != army.size()){
                //If warrior is found (hired by this noble)
                cout << "You don't work for me anymore "
                    << warrior.get_name() << "! -- " << name << "." << endl;
                //Can fire if the warrior is hired & noble is alive
                warrior.change_hire(false, this);
                remove_warrior(warrior);
                return true;
            }
        }
        return false;
    }
    
    //Remove a warrior from its army
    void Noble::remove_warrior(const Warrior& warrior){
        //Set strength
        strength -= warrior.get_strength();
        
        //Remove warrior from the army
        size_t warrior_index = find_warrior_ind(warrior);
        for (size_t i = warrior_index; i < army.size()-1; ++i){
            army[warrior_index] = army[warrior_index + 1];
        }
        army.pop_back();
    }
        
    //Calculate and change the strength of his army
    void Noble::change_strength(int change){
        double ratio = 0;
        if (change < strength){
            //Find ratio if the noble is still alive
            ratio = 1 - (change/strength);
        } else {
            //If the noble died
            strength = 0;
            alive = false;
        }
        //Change the strenght of warriors
        for (Warrior* warrior: army){
            warrior->set_strength(ratio);
        }
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
                enemy.change_strength(strength);
                change_strength(enemy_strength);
                cout << enemy.get_name() << " defeats " << name << endl;
            } else {
                //Draw
                enemy.change_strength(strength);
                change_strength(enemy_strength);
                cout << "Mutual Annihilation: " << name << " and "
                << enemy.get_name() << " die at each other's hands" << endl;
            }
        } else {
            //At least one noble is dead
            if (alive) {
                //The noble is alive
                cout << "He's dead, " << name << endl;
            } else if (enemy.is_alive()){
                //The enemy is alive
                cout << "He's dead, " << enemy.get_name() << endl;
            } else {
                //Both nobles are dead
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }
        }
    }
    
    //Find the index of the warrior if he is in the army
    size_t Noble::find_warrior_ind(const Warrior& warrior){
        size_t warrior_index = army.size();
        for (size_t i=0; i < army.size(); ++i){
            if (&warrior == army[i]){
                warrior_index = i;
                break;
            }
        }
        return warrior_index;
    }
}

