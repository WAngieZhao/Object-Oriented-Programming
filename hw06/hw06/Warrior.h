//
//  Warrior.h
//  Created by Angie Zhao on 2019/10/27.
//
//  The program calculate battles and status among nobles and their warriors.
//  Header file for Warrior class

#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Noble;

    //Warriors with initial strength
    //Can runaway/be fired or hired by Noble
    class Warrior{
        friend std::ostream& operator<< (std::ostream& os, const Warrior& warrior);
    public:
        //Constructor and Getters
        Warrior(const std::string& nm, int wrStrength);
        std::string get_name()const;
        double get_strength()const;
        bool is_hired()const;
        
        //Change the hire status of warrior
        void change_hire(const bool& change, Noble* noble);
        //Warrior runaway from its lord
        void runaway();
        
        //Change the warrior's strength by ratio
        void set_strength(double ratio);
    private:
        std::string name;
        double strength;
        bool hired;
        Noble* lord;
    };
}

#endif /* Warrior_h */
