//
//  main.cpp
//  hw02
//
//  Created by Angie Zhao on 2019/9/22.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

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
void battle(Warrior& warrior1, Warrior& warrior2);
void status(vector<Warrior>& warriors);


int main() {
    vector<Warrior> warriors;
    
    //open input file
    ifstream history("warriors.txt") ;
    if (!history){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    //read input file
    string word,name1,name2;
    int strength;
    while (history >> word){
        if (word == "Warrior"){
            //create warrior
            history >> name1 >> strength;
            createWarrior(name1, strength, warriors);
        } else if (word == "Status"){
            //check status
            status(warriors);
        } else {
            //battle
            history >> name1 >> name2;
            
            Warrior warrior1,warrior2;
            bool find1 = false;
            bool find2 = false;
            //assign warriors
            for(size_t i = 0; i < warriors.size(); ++i){
                if (name1 == warriors[i].name){
                    warrior1 = warriors[i];
                    find1 = true;
                } else if (name2 == warriors[i].name){
                    warrior2 = warriors[i];
                    find2 = true;
                }
                if (find1 && find2){
                    battle(warrior1, warrior2);
                    break;
                }
            }
        }
    }
    
    return 0;
}

void createWarrior(string& warriorName, int& warriorStrength, vector<Warrior>& warriors){
    Warrior new_warrior{warriorName, warriorStrength};
    warriors.push_back(new_warrior);
}

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

void status(vector<Warrior>& warriors){
    size_t total = warriors.size();
    cout << "There are: " << total << " warriors" << endl;
    for (Warrior warrior : warriors){
        cout << "Warrior: " << warrior.name << ", strength: " << warrior.strength << endl;
    }
}


//打之前都活着：
//1.平手
//Mutual Annihilation: Arthur and Lancelot die at each other's hands
//2.defeats
//Torvalds defeats Gates
//打之前有人死了
//1.死了一个
//He's dead, Jim
//2.both死的
//Oh, NO! They're both dead! Yuck!;


