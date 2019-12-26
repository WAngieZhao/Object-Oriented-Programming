//
//  hw02.cpp
//  Created by Angie Zhao (wz1342) on 2019/9/22.
//
//  The program read the input file "warriors.txt" to calculate battles and status among warriors.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Warrior{
    string name;
    int strength;
};

void createWarrior(string& warriorName, int& warriorStrength, vector<Warrior>& warriors);
size_t findWarrior(string& name, vector<Warrior>& warriors);
void battle(Warrior& warrior1, Warrior& warrior2);
void status(vector<Warrior>& warriors);


int main() {
    vector<Warrior> warriors;
    
    //Open the input file
    ifstream history("warriors.txt") ;
    if (!history){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    //Read input file
    string word,name1,name2;
    int strength;
    while (history >> word){
        if (word == "Warrior"){
            //Create warrior
            history >> name1 >> strength;
            createWarrior(name1, strength, warriors);
        } else if (word == "Status"){
            //Check status
            status(warriors);
        } else {
            //Start battle
            history >> name1 >> name2;
            //Find coresponding warriors in the vector
            size_t warrior1 = findWarrior(name1, warriors);
            size_t warrior2 = findWarrior(name2, warriors);
            //Battle
            battle(warriors[warrior1], warriors[warrior2]);
        }
    }
    return 0;
}

//Creates a new warrior with the specified name and strength.
//Put the warrior into the vector
void createWarrior(string& warriorName, int& warriorStrength, vector<Warrior>& warriors){
    Warrior new_warrior{warriorName, warriorStrength};
    warriors.push_back(new_warrior);
}

//Return the index of the warrior based on his name
size_t findWarrior(string& name, vector<Warrior>& warriors){
    size_t warrior_index = 0;
    for(size_t i = 0; i < warriors.size(); ++i){
        if (name == warriors[i].name){
            warrior_index = i;
            break;
        }
    }
    return warrior_index;
}

//Calculate a battle occured between two warriors
void battle(Warrior& warrior1, Warrior& warrior2){
    cout << warrior1.name << " battles " << warrior2.name << endl;

    if (warrior1.strength > 0 && warrior2.strength > 0){
        //If both warriors are alive
        if (warrior1.strength == warrior2.strength){
            //Draw
            warrior1.strength = 0;
            warrior2.strength = 0;
            cout << "Mutual Annihilation: " << warrior1.name << " and " << warrior2.name << " die at each other's hands" << endl;
        } else {
            //If one warrior is stronger than another
            if (warrior1.strength > warrior2.strength){
                //warrior1 is stronger
                warrior1.strength -= warrior2.strength;
                warrior2.strength = 0;
                cout << warrior1.name << " defeats " << warrior2.name << endl;
            } else{
                //warrior2 is stronger
                warrior2.strength -= warrior1.strength;
                warrior1.strength = 0;
                cout << warrior2.name << " defeats " << warrior1.name << endl;
            }
        }
    } else {
        //At least one warrior is dead
        if (warrior1.strength == warrior2.strength) {
            //both warriors are dead and their strength == 0
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        } else {
            //Only one warrior is dead
            if (warrior1.strength == 0){
                //warrior1 is dead
                cout << "He's dead, " << warrior2.name << endl;
            } else {
                //warrior2 is dead
                cout << "He's dead, " << warrior1.name << endl;
            }
        }
    }
}

//lists all warriors and their strengths.
void status(vector<Warrior>& warriors){
    size_t total = warriors.size();
    cout << "There are: " << total << " warriors" << endl;
    for (Warrior warrior : warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}

