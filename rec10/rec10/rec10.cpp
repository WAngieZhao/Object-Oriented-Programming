//
//  rec10.cpp
//
//  Created by Angie Zhao on 2019/11/8.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Instrument {
public:
    virtual void makeSound() const = 0;
    virtual void play() const = 0;
private:
};

void Instrument::makeSound() const {
    cout << "To make a sound... ";
}

//Brass
class Brass: public Instrument {
public:
    Brass(unsigned bSize): size(bSize) {}
    
    virtual void makeSound() const {
      cout << "blow on a mouthpiece of size " << size << endl;
    }
private:
    unsigned size;
};

class Trombone: public Brass{
public:
    Trombone(unsigned size): Brass(size) {}
    virtual void play() const{
        cout << "Blat";
    }
};

class Trumpet: public Brass{
public:
    Trumpet(unsigned size): Brass(size) {}
    virtual void play() const{
        cout << "Toot";
    }
};

//String
class String: public Instrument{
public:
    String(unsigned sPitch): pitch(sPitch) {}
    
    virtual void makeSound() const {
      cout << "bow a string with pitch " << pitch << endl;
    }
private:
    unsigned pitch;
};

class Cello: public String{
public:
    Cello(unsigned pitch): String(pitch) {}
    virtual void play() const{
        cout << "Squawk";
    }
};

class Violin: public String{
public:
    Violin(unsigned pitch): String(pitch) {}
    virtual void play() const{
        cout << "Screech";
    }
};

//Percussion
class Percussion: public Instrument{
public:
    virtual void makeSound() const {
      cout << "hit me!" << endl;
    }
private:
};

class Drum: public Percussion{
public:
    virtual void play() const{
        cout << "Boom";
    }
};

class Cymbal: public Percussion{
public:
    virtual void play() const{
        cout << "Crash";
    }
};

class MILL {
public:
    MILL(): instruments(0) {}
    
    void dailyTestPlay(){
        for (Instrument* instr: instruments){
            if (instr != nullptr){
                instr->makeSound();
            }
        }
    }
    
    void receiveInstr(Instrument& instrument){
        //instrument.makeSound();
        Instrument* instr = &instrument;
        size_t instr_ind = instruments.size();
        for(size_t i = 0; i < instruments.size(); i++){
            if (instruments[i] == nullptr){
                instruments[i] = instr;
                instr_ind = i;
                break;
            }
        }
        //put instrument if there is no empty space
        if (instr_ind == instruments.size()){
            instruments.push_back(instr);
        }
    }
    
    Instrument* loanOut(){
        Instrument* instr = nullptr;
        for (Instrument*& instrument: instruments){
            if (instrument != nullptr){
                instr = instrument;
                instrument = nullptr;
                break;
            }
        }
        return instr;
    }
private:
     vector<Instrument*> instruments;
};


class Musician {
public:
    Musician() : instr(nullptr) {}

    void acceptInstr(Instrument* instPtr) {instr = instPtr;}

    Instrument* giveBackInstr() {
        Instrument* result(instr);
        instr = nullptr;
        return result;
    }

    void testPlay() const {
        if (instr){
            instr->makeSound();
        } else {
            cerr << "have no instr\n";
        }
    }
    
    void play() {
        if (instr){
            instr->play();
        }
    }

private:
    Instrument* instr;
};

class Orch {
public:
    void addPlayer(Musician& musician) {
      musicians.push_back(&musician);
    }
    void play() const {
        for(size_t i = 0; i < musicians.size(); i++){
            musicians[i] -> play();
        }
        cout << endl;
    }
private:
    vector<Musician*> musicians;
};


int main() {
    // The initialization phase

    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12);
    Violin violin(567);

    MILL mill;
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);

    Musician bob;
    Musician sue;
    Musician mary;
    Musician ralph;
    Musician jody;
    Musician morgan;

    Orch orch;
    
    cout << "======THE SCENARIO======" << endl;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();

    //Sue gets an instrument from the MIL2 and joins the orchestra.
    //Sue trumpet
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    //ralph violin
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    //mary trombone
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    //jody violin
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    //morgan drum
    morgan.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

} // main

