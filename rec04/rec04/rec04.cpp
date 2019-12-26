//
//  rec04.cpp
//
//  Created by Angie Zhao on 2019/9/27.
//  Copyright © 2019 Angie Zhao. All rights reserved.

#include <iostream>
#include <vector>
using namespace std;

struct Complex {
   double real;
   double img;
};

class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   void setX( int val )  { x = val; }
private:
   int x;
};

class PlainOldClassV2 {
public:
   PlainOldClassV2() : x(-72) {}
   int getX() const { return x; }
   //void setX( int x )  { x = x; } // HMMMM???
    void setX( int x )  { this->x = x; } // No confusion!
private:
   int x;
};

class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers)
         cout << "already have speakers attached!\n";
      else
         attachedSpeakers = &spkrs;
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
      attachedSpeakers = nullptr;
   }
  
   void playMusic( ) const {
      if (attachedSpeakers)
         attachedSpeakers -> vibrateSpeakerCones(440);
      else
         cout << "No speakers attached\n";
   }
private:
   const SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if (roomie) {
            cerr << "Already has a rommate" << endl;
        }
        else if (newRoomate.roomie) {
            cerr << "The new rommate already has a rommate" << endl;
        }
        else if (this == &newRoomate) {
            cerr << "Can't move in with yourself" << endl;
        }
        roomie = &newRoomate;        // now I have a new roomie
        newRoomate.roomie = this;    // and now they do too
    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie;
    string name;
};

int main(int argc, const char * argv[]) {
    //task 1-7
    cout << "===Task 1-8===" << endl;
    int x;
    x = 10;
    cout << "x = " << x << endl;
    
    //task 8
    int* p;
    p = &x;
    //p = 0x7ffeefbff4fc;
    cout << "p = " << p << endl;
    
    //task 10
    cout << endl << "===Task 10===" << endl;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    
    //task 11
    cout << endl << "===Task 11===" << endl;
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;
    
    //task 12
    cout << endl << "===Task 12===" << endl;
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;
    
    //task 13
    cout << endl << "===Task 13===" << endl;
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;
    
    //task 14
    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
    //pD  = p;
    //p   = pD;
    
    //task 15
    int joe = 24;
    const int sal = 19;
    int*  pI;
//      pI = &joe;
//     *pI = 234;
//      pI = &sal; //cannot assign const int to int*
//     *pI = 7623;

//    const int* pcI; //pcI is pointer to const int
//      pcI = &joe;
//     *pcI = 234; //cannot deference becuase 234 is int not const int
//      pcI = &sal;
//     *pcI = 7623;

//    int* const cpI; //pcI is const
    //default value = null, yet it cannot be changed later
//    int* const cpI(&joe); //redefinition of const cpI is not allowed
//    int* const cpI(&sal); //redefinition of const cpI is not allowed
//      cpI = &joe; //cannot assign value to const cpI
//     *cpI = 234;
//      cpI = &sal; //cannot assign value to const cpI
//     *cpI = 7623;

//    const int* const cpcI; //cpcI is const, and it is a pointer to const int*
//    const int* const cpcI(&joe); //redefinition of const cpcI is not allowed
//    const int* const cpcI(&sal); //redefinition of const cpcI is not allowed
//      cpcI = &joe;  // *cpcI = 234; //cannot assign value to const cpcI
//      cpcI = &sal;  //cannot assign value to const cpcI
//     *cpcI = 7623; //const sal is not assignable
    
    //task 16
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
    //pC->real is better than (*pC).real [do not use]
    //cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
    //cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    
    //task 17
    cout << endl << "===Task 17===" << endl;
    PlainOldClassV2 poc;
    PlainOldClassV2* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;
    
    //task 19
    cout << endl << "===Task 19===" << endl;
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
    << " is stored at address " << pDyn
    << " which is in the heap\n";
    
    //task 20
    cout << endl << "===Task 20===" << endl;
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";
    
    //task 21
    pDyn = nullptr;
    double* pDouble = nullptr;
    
    //task 22
    //cout << "Can we dereference nullptr?  " << *pDyn << endl; //do NOT
    //cout << "Can we dereference nullptr?  " << *pDouble << endl; //do NOT
    
    //task 24
    //delete a Null point is not an error
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe
    
    //task 25
    //a programming error to delete a deleted pntr
    //error when running
//    short* pShrt = new short(5);
//    delete pShrt;
//    delete pShrt;
    
    //task 26
    //delete can only be used with heap
//    long jumper = 12238743;
//    delete jumper;
//    long* ptrTolong = &jumper;
//    delete ptrTolong;
//    Complex cmplx;
//    delete cmplx;
    
    //task 27
    cout << endl << "===Task 27===" << endl;
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
       tmpPCmplx = new Complex; // create a new Complex object on the heap
       tmpPCmplx->real = ndx;   // set real and img to be the
       tmpPCmplx->img  = ndx;   // value of the current ndx
       complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx]; //⚠︎important
    }
    // clear the vector
    complV.clear();
    //.clear() does NOT delete on the things inside the vector
    //programmer must delete each object stored on the heap by deleting pointer value stored in the vector

    //task 28
    cout << endl << "===Task 28===" << endl;
    class Colour {
    public:
        Colour(const string& name, unsigned r, unsigned g, unsigned b): name(name), r(r), g(g), b(b) {}
        void display() const {
            cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
        }
    private:
        string name;      // what we call this colour
        unsigned r, g, b; // red/green/blue values for displaying
    };

    vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }
//
//    // display all the Colours in the vector:
//    //free up memeories on heap
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
        delete colours[ndx];
    }
    
    //task 29
    cout << endl << "===Task 29===" << endl;
    SpeakerSystem spk1,spk2;
    Amplifier amp1;
    cout << "Speaker initialize" << endl;
    spk1.vibrateSpeakerCones(01);
    spk2.vibrateSpeakerCones(99);
    cout << endl << "Amplifier attach and play test" << endl;
    amp1.attachSpeakers(spk1);
    amp1.attachSpeakers(spk2); //already have speakers attached
    amp1.playMusic(); //Playing: 440Hz sound...
    cout << endl << "Amplifier deteach and playMusic error test" << endl;
    amp1.detachSpeakers();
    amp1.playMusic(); //No speakers attached
    
    //task 30
    cout << endl << "===Task 30===" << endl;
    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
}
