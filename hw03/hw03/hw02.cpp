//
//  hw02.cpp
//  Created by Angie Zhao on 2019/9/28.
//
//  The program read the input file "warriors.txt" to calculate battles and status among warriors.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Warrior{
public:
    Warrior(const string& name, const string& weapon, int& strength):
        warriorName(name), warriorWeapon(Weapon(weapon,strength)){}
    
    string get_name()const {return warriorName;}
    string get_weaponName()const {return warriorWeapon.get_name();}
    int get_weaponStrength()const {return warriorWeapon.get_strength();}
    
    //Ask weapon to change strength
    void change_weaponStrength(int change){
        warriorWeapon.change_strength(change);
    }
    
    //set Warrior's output operator
    friend ostream& operator<< (ostream& os, const Warrior& warrior){
        os << "Warrior: " << warrior.warriorName << ", " << warrior.warriorWeapon;
        return os;
    }
    
private:
    //class Weapon
    class Weapon{
    public:
        Weapon(const string& weapon, int& strength): wpName(weapon), wpStrength(strength){}
        
        string get_name()const {return wpName;}
        int get_strength()const {return wpStrength;}
        
        //change weapon strength
        void change_strength(int change){
            if(change < get_strength()){
                wpStrength -= change;
            }else{
                wpStrength = 0;
            }
        }
        
        //set Weapon's output operator
        friend ostream& operator<< (ostream& os, const Weapon& weapon){
            os << "weapon: " << weapon.wpName << ", " << weapon.wpStrength;
            return os;
        }

    private:
        string wpName;
        int wpStrength;
        
    };
    
    string warriorName;
    Weapon warriorWeapon;    
};

size_t findWarrior(string& name, vector<Warrior>& warriors);
void battle(Warrior& warrior1, Warrior& warrior2);
void status(vector<Warrior>& warriors);

int main(int argc, const char * argv[]) {
    vector<Warrior> warriors;
    
    //Open the input file
    ifstream history("warriors.txt") ;
    if (!history){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    //Read input file
    string word,name1,name2, weapon;
    int strength;
    while (history >> word){
        if (word == "Warrior"){
            history >> name1 >> weapon >> strength;
            //Create warrior
            //Put the warrior into the vector
            warriors.emplace_back(name1, weapon, strength);
        } else if (word == "Status"){
            //Check status
            status(warriors);
        } else {
            //Start battle
            history >> name1 >> name2;
            //Find coresponding warriors in the vector
            Warrior& warrior1 = warriors[findWarrior(name1, warriors)];
            Warrior& warrior2 = warriors[findWarrior(name2, warriors)];
            //Battle
            battle(warrior1, warrior2);
        }
    }
    return 0;
}

//Return the index of the warrior based on his name
size_t findWarrior(string& name, vector<Warrior>& warriors){
    size_t warrior_index = warriors.size();
    for(size_t i = 0; i < warriors.size(); ++i){
        if (name == warriors[i].get_name()){
            warrior_index = i;
            break;
        }
    }
    return warrior_index;
}

//Calculate a battle occured between two warriors
void battle(Warrior& warrior1, Warrior& warrior2){
    cout << warrior1.get_name() << " battles " << warrior2.get_name() << endl;
    
    int strength1 = warrior1.get_weaponStrength();
    int strength2 = warrior2.get_weaponStrength();
    
    if (strength1 > 0 && strength2 > 0){
        //If both warriors are alive
        if (strength1 == strength2){
            //Draw
            warrior1.change_weaponStrength(strength2);
            warrior2.change_weaponStrength(strength1);
            cout << "Mutual Annihilation: " << warrior1.get_name() << " and "
                << warrior2.get_name() << " die at each other's hands" << endl;
        } else {
            //If one warrior is stronger than another
            if (strength1 > strength2){
                //warrior1 is stronger
                warrior1.change_weaponStrength(strength2);
                warrior2.change_weaponStrength(strength1);
                cout << warrior1.get_name() << " defeats " << warrior2.get_name() << endl;
            } else{
                //warrior2 is stronger
                warrior2.change_weaponStrength(strength1);
                warrior1.change_weaponStrength(strength2);
                cout << warrior2.get_name() << " defeats " << warrior1.get_name() << endl;
            }
        }
    }else {
        //At least one warrior is dead
        if (strength1 == strength2) {
            //both warriors are dead and their strength == 0
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else {
            //Only one warrior is dead
            if (strength1 == 0){
                //warrior1 is dead
                cout << "He's dead, " << warrior2.get_name() << endl;
            } else {
                //warrior2 is dead
                cout << "He's dead, " << warrior1.get_name() << endl;
            }
        }
    }
}

//lists all warriors and their weapon status.
void status(vector<Warrior>& warriors){
    size_t total = warriors.size();
    cout << "There are: " << total << " warriors" << endl;
    for (Warrior warrior : warriors){
        cout << warrior << endl;
    }
}
