//
//  Noble.h
//  Created by Angie Zhao on 2019/11/11.
//
//  The program calculate battles and status among nobles and their warriors.
//  Header file for Noble class

#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Protector;

    //Noble can build an army by hiring and fireing warriors
    class Noble{
    public:
        //Constructor and getters
        Noble (const std::string& nm, double nStrength);
        std::string get_name()const;
        double get_strength()const;
        bool is_alive()const;
        
        //Calculate and change the strength of the noble
        virtual void change_strength(int change) = 0;
        //Set the noble's new strength
        void set_strength(double newStrength);
        //reset the noble's alive
        void set_alive(bool life);
        
        //Start a battle with another noble
        void battle(Noble& enemy);
    private:
        std::string name;
        double strength;
        bool alive;
        
    };

    class Lord: public Noble{
    public:
        //Constructor
        Lord (const std::string& nm);
        //Hire a Protector
        bool hires(Protector& protector);
        //Fire a Protector
        bool fires(Protector& protector);
        //Remove a Protector from its army
        void remove_protector(const Protector& protector);
        
        //Calculate and change the strength of his army
        virtual void change_strength(int change);
        
    private:
        //LandLord(const std::string &name);
        std::vector<Protector*> army;
        
        //Find the index of the Protector if he is in the army
        size_t find_protector_ind(const Protector& protector);
    };

    class PersonWithStrengthToFight: public Noble{
    public:
        using Noble::Noble;
        //Calculate and change the strength of himself
        virtual void change_strength(int change);
    };


}


#endif /* Noble_h */
