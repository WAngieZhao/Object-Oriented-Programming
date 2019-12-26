//
//  hw05.cpp
//  Created by Angie Zhao on 2019/10/13.
//
//  The program read the input file "nobleWarriors.txt" to calculate battles and status among nobles and their warriors.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//Warriors with initial strength
//Can be fired or hired by noble
class Warrior{
    //Set Warrior's output operator
    friend ostream& operator<< (ostream& os, const Warrior& warrior){
        os << warrior.name << ": " << warrior.strength << endl;
        return os;
    }
    
public:
    Warrior(const string& nm, int wrStrength):
        name(nm), strength(wrStrength), hired(false) {}
    string get_name()const {return name;}
    double get_strength()const {return strength;}
    bool is_hired()const {return hired;}
    
    //change hire status of a warrior
    void change_hire(const bool& change){
        hired = change;
    }
    
    //Change the warrior's strength by ratio
    void set_strength(double ratio){
        strength *= ratio;
    }
    
private:
    string name;
    double strength;
    bool hired;
};

//Noble can build an army by hiring and fireing warriors
class Noble{
    //Set Noble's output operator
    friend ostream& operator<< (ostream& os, const Noble& noble){
        os << noble.name << " has an army of " << noble.army.size() << endl;
        for (Warrior* warrior: noble.army){
            os << "\t" << *warrior;
        }
        return os;
    }
    
public:
    Noble (const string& nm): name(nm), strength (0), alive(true) {}
    string get_name()const {return name;}
    double get_strength()const {return strength;}
    bool is_alive()const {return alive;}
    
    //Hire a warrior
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
    
    //Fire a warrior
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
                cout << "You don't work for me anymore "
                    << warrior.get_name() << "! -- " << name << "." << endl;
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
    
    //Calculate and change the strength of his army
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
    
    //Start a battle with another noble
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

//function prototypes
size_t find_noble_index(const vector<Noble*>& nobles, const string& name);
size_t find_warrior_index(const vector<Warrior*>& warriors, const string& name);
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors);

int main(int argc, const char * argv[]) {
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    
    //Open the input file
    ifstream history("nobleWarriors.txt") ;
    if (!history){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    //Read input file
    string word,name1,name2;
    int strength;
    while (history >> word){
        if (word == "Noble"){
            history >> name1;
            size_t noble = find_noble_index(nobles, name1);
            
            //check if Noble exist
            if (noble < nobles.size()) {
                cerr << "Error: The noble already exist.";
            }
            else{
                //Create Noble on the heap
                nobles.emplace_back(new Noble(name1));
            }
        } else if (word == "Warrior"){
            history >> name1 >> strength;
            size_t warrior = find_warrior_index(warriors, name1);
            
            //check if Warrior exist
            if (warrior < warriors.size()) {
                cerr << "Error: The warrior already exist.";
            }
            else{
                //Create Warrior on the heap
                warriors.emplace_back(new Warrior(name1,strength));
            }
        } else if (word == "Hire"){
            //name1 = Noble; name2 = Warrior
            history >> name1 >> name2;
            size_t noble = find_noble_index(nobles, name1);
            size_t warrior = find_warrior_index(warriors, name2);
            
            //check if Noble or Warrior exist
            if ((noble == nobles.size()) || warrior == warriors.size()) {
                cerr << "Error: The noble or the warrior does not exist.";
            } else {
                //hire
                nobles[noble] -> hire(*(warriors[warrior]));
            }
            
        } else if (word == "Fire"){
            //name1 = Noble; name2 = Warrior
            history >> name1 >> name2;
            size_t noble = find_noble_index(nobles, name1);
            size_t warrior = find_warrior_index(warriors, name2);
            
            //check if Noble or Warrior exist
            if (noble == nobles.size() || warrior == warriors.size()) {
                cerr << "Error: The noble or the warrior does not exist.";
            } else {
                //hire
                nobles[noble] -> fire(*(warriors[warrior]));
            }
            
        }else if (word == "Status"){
            //Check status
            status(nobles,warriors);
        } else if (word == "Battle"){
            //Start battle
            history >> name1 >> name2;
            //Find coresponding Nobles in the vector
            size_t noble1 = find_noble_index(nobles, name1);
            size_t noble2 = find_noble_index(nobles, name2);
            //Battle
            if (noble1 == nobles.size() || noble2 == nobles.size()) {
                cerr << "Error: At least one of the nobles does not exist.";
            } else {
                nobles[noble1] -> battle(*(nobles[noble2]));
            }
        } else {
            //Word == Clear
            clear(nobles,warriors);
        }
    }
    history.close();
}

//Find the Noble in the noble vector
size_t find_noble_index(const vector<Noble*>& nobles, const string& name){
    size_t index = nobles.size();
    for (size_t i = 0; i < nobles.size(); ++i){
        if (nobles[i] -> get_name() == name){
            index = i;
        }
    }
    return index;
}

//Find the Warrior in the noble vector
size_t find_warrior_index(const vector<Warrior*>& warriors, const string& name){
    size_t index = warriors.size();
    for (size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i] -> get_name() == name){
            index = i;
        }
    }
    return index;
}

//Print the status of all Nobles and all Warriors
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){
    //print Nobles
    cout << "Status\n" << "======\n" << "Nobles:" << endl;
    if (nobles.size() != 0) {
        for (Noble* noble: nobles){
            cout << *noble;
        }
        
    } else {
        cout << "NONE" << endl;
    }
    
    //print Unemployed Warriors
    cout << "Unemployed Warriors:" << endl;
    int unemployed_cntr = 0;
    
    for (Warrior* warrior: warriors){
        if (warrior -> is_hired() == false){
            unemployed_cntr++;
            cout << *warrior;
        }
    }
    if (unemployed_cntr == 0){
        cout << "NONE" << endl;
    }
}

//Clear all the Nobles and Warriors
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
    //clear Nobles
    for (Noble* noble: nobles) {
        delete noble;
    }
    nobles.clear();
    //clear Warriors
    for (Warrior* warrior: warriors) {
        delete warrior;
    }
    warriors.clear();
}
