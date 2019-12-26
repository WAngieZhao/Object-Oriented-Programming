/*
  testNobleWarrior.cpp
  John Sterling
  Association: Noble - Warrior
  Test code for hw04
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.

int main() {
	
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
	
}
