//
//  Protector.h
//  hw07
//
//  Created by Angie Zhao on 2019/11/11.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#ifndef PROTECTOR_H
#define PROTECTOR_H

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Noble;

    //Warriors with initial strength
    //Can runaway/be fired or hired by Noble
    class Protector{
    public:
        //Constructor and Getters
        Protector(const std::string& nm, int pStrength);
        std::string get_name()const;
        double get_strength()const;
        bool is_hired()const;
        bool is_alive()const;
        std::string get_lordName() const;
        
        //Change the hire status of warrior
        void change_hire(const bool change, Lord* noble);
        //Warrior runaway from its lord
        bool runaway();
        
        //Change the warrior's strength by ratio
        virtual void set_strength(double ratio) = 0;
        
        
    private:
        std::string name;
        double strength;
        bool hired;
        bool alive;
        Lord* lord;
    };
    
    //Protector type: Wizard
    class Wizard: public Protector{
    public:
        //Constructor
        using Protector::Protector;
        //State while defend & set_strength
        virtual void set_strength(double ratio);
    };

    //Protector type: Warrior
    class Warrior: public Protector{
    public:
        //Constructor
        using Protector::Protector;
        //State while defend & set_strength
        virtual void set_strength(double ratio) = 0;
    };
    //Warrior type: Archer
    class Archer : public Warrior {
    public:
        //Constructor
        using Warrior::Warrior;
        //State while defend & set_strength
        virtual void set_strength(double ratio);
    };
    //Warrior type: Swordsman
    class Swordsman : public Warrior {
    public:
        //Constructor
        using Warrior::Warrior;
        //State while defend & set_strength
        virtual void set_strength(double ratio);
    };
}

#endif /* Protector_h */
