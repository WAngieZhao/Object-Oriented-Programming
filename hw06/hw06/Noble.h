//
//  Noble.h
//  Created by Angie Zhao on 2019/10/27.
//
//  The program calculate battles and status among nobles and their warriors.
//  Header file for Noble class

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;

    //Noble can build an army by hiring and fireing warriors
    class Noble{
        friend std::ostream& operator<< (std::ostream& os, const Noble& noble);
    public:
        //Constructor and getters
        Noble (const std::string& nm);
        std::string get_name()const;
        double get_strength()const;
        bool is_alive()const;
        
        //Hire a warrior
        bool hire(Warrior& warrior);
        //Fire a warrior
        bool fire(Warrior& warrior);
        //Calculate and change the strength of his army
        void change_strength(int change);
        //Remove a warrior from its army
        void remove_warrior(const Warrior& warrior);
        
        //Start a battle with another noble
        void battle(Noble& enemy);
    private:
        std::string name;
        double strength;
        bool alive;
        std::vector<Warrior*> army;
        
        //Find the index of the warrior if he is in the army
        size_t find_warrior_ind(const Warrior& warrior);
    };
}


#endif /* Noble_h */
