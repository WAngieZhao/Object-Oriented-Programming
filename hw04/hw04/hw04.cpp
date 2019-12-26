//
//  hw04.cpp
//  Created by Angie Zhao on 2019/10/5.
//
//  The program calculate battles and status among nobles and their warriors.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior{
    //Set Warrior's output operator
    friend ostream& operator<< (ostream& os, const Warrior& warrior){
        os << "\t" << warrior.name << ": " << warrior.strength << endl;
        return os;
    }
    
public:
    Warrior(const string& nm, int wrStrength):
        name(nm), strength(wrStrength), hired(false) {}
    string get_name()const {return name;}
    double get_strength()const {return strength;}
    bool is_hired()const {return hired;}
    
    void change_hire(const bool& change){
        //Change the hire status of warrior
        hired = change;
    }
    
    void set_strength(double ratio){
        //Change the warrior's strength by ratio
        strength *= ratio;
    }
    
private:
    string name;
    double strength;
    bool hired;
};

class Noble{
    //Set Noble's output operator
    friend ostream& operator<< (ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (Warrior* warrior: noble.army){
            os << *warrior;
        }
        return os;
    }
    
public:
    Noble (const string& nm): name(nm), strength (0), alive(true) {}
    string get_name()const {return name;}
    double get_strength()const {return strength;}
    bool is_alive()const {return alive;}
    
    bool hire(Warrior& warrior){
        if (warrior.is_hired()==false && alive){
            //Can hired if the warrior is not hired & noble is alive
            warrior.change_hire(true);
            army.push_back(&warrior);
            strength += warrior.get_strength();
            return true;
        }
        return false;
    }
    
    bool fire(Warrior& warrior){
        if (warrior.is_hired() && alive){
            //Can fire if the warrior is hired & noble is alive
            //Find warrior index & check if warrior is hired by this noble
            size_t warrior_index = army.size();
            for (size_t i=0; i < army.size(); ++i){
                if (&warrior == army[i]){
                    warrior_index = i;
                    break;
                }
            }
            
            if (warrior_index != army.size()){
                //If warrior is found (hired by this noble)
                cout << "You don't work for me anymore " << warrior.get_name() << "! -- " << name << "." << endl;
                //Can fire if the warrior is hired & noble is alive
                warrior.change_hire(false);
                strength -= warrior.get_strength();
                
                //Remove warrior from the army
                for (size_t i = warrior_index; i < army.size()-1; ++i){
                    army[warrior_index] = army[warrior_index + 1];
                }
                army.pop_back();
                return true;
            }
        }
        return false;
    }
    
    void change_strength(int change){
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
    
    void battle(Noble& enemy){
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
        
private:
    string name;
    double strength;
    bool alive;
    vector<Warrior*> army;
};



int main(int argc, const char * argv[]) {
   Noble art("King Arthur");
   Noble lance("Lancelot du Lac");
   Noble jim("Jim");
   Noble linus("Linus Torvalds");
   Noble billie("Bill Gates");
   
   Warrior cheetah("Tarzan", 10);
   Warrior wizard("Merlin", 15);
   Warrior theGovernator("Conan", 12);
   Warrior nimoy("Spock", 15);
   Warrior lawless("Xena", 20);
   Warrior mrGreen("Hulk", 8);
   Warrior dylan("Hercules", 3);
   
   jim.hire(nimoy);
   lance.hire(theGovernator);
   art.hire(wizard);
   lance.hire(dylan);
   linus.hire(lawless);
   billie.hire(mrGreen);
   art.hire(cheetah);
   
   cout << "==========\n"
        << "Status before all battles, etc.\n";
   cout << jim << endl;
   cout << lance << endl;
   cout << art << endl;
   cout << linus << endl;
   cout << billie << endl;
   cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;
    
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
    
    
    return 0;
}
























