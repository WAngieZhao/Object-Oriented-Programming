//
//  rec09.cpp
//
//  Created by Angie Zhao on 2019/11/1.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

class PrintedMaterial {
//    friend ostream& operator<< (ostream& os, const PrintedMaterial& material){
//        os << "Page Numbers: " << material.numOfPages << endl;
//        return os;
//    }
public:
    PrintedMaterial(unsigned pages): numOfPages(pages){}
    virtual void displayNumPages() const = 0;
protected:
private:
    unsigned numOfPages;
};

class Magazine : public PrintedMaterial {
public:
    Magazine(unsigned pages): PrintedMaterial(pages){}
    void displayNumPages() const {
        cout << "Magazine - ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

void PrintedMaterial::displayNumPages() const {
  cout << "Pages: " << numOfPages << endl;
}


class Book : public PrintedMaterial {
public:
    Book(unsigned pages): PrintedMaterial(pages){}
    void displayNumPages() const {
        cout << "Book - ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

class TextBook : public Book {
public:
    TextBook(unsigned pages, unsigned index): Book(pages), numOfIndexPages(index){}
    void displayNumPages() const {
        cout << "TextBook - Index Pages: "<< numOfIndexPages << endl;
        cout << "TextBook - ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
    unsigned numOfIndexPages;
};

class Novel : public Book {
public:
    Novel(unsigned pages): Book(pages){}
    void displayNumPages() const {
        cout << "Novel -  ";
        PrintedMaterial::displayNumPages();
    }
protected:
private:
};

//Prototypes:
void displayNumberOfPages (const PrintedMaterial& material);

// tester/modeler code
int main()
{
    TextBook t(5430, 23);
    Novel n(213);
    Magazine m(6);
    
    cout << "=== Task 8 Test ===" << endl;
    t.displayNumPages();
    n.displayNumPages();
    m.displayNumPages();
    
//    cout << "=== Task 9 Test ===" << endl;
//    PrintedMaterial pm = t; // like putting a t into a vector of PrintedMaterials
//    pm.displayNumPages();

    cout << "=== Task 10 & 11 Test ===" << endl;
    PrintedMaterial* pmPtr;
    pmPtr = &t;
    // instead of putting an actual PrintedMaterial
    // object into the vector, we put a pointer to
    // a PrintedMaterial object (t) into a vector
    // of pointers-to-PrintedMaterial
    // (that is, pointers to the Base class)
    // we'll be "managing" our objects by using
    // pointers to PrintedMaterial values.

    pmPtr->displayNumPages();

    cout << "=== Task 12 Test ===";
    // print some stuff by calling a generic function
    cout << "\nUse a generic functino for printing\n";
    displayNumberOfPages(m);
    displayNumberOfPages(n);
    displayNumberOfPages(t);

    cout << "=== Task 14 Test ===";
    cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
    cout << "Now with the virtual mechanism involved\n";
//    PrintedMaterial* pmPtr;
//    pmPtr = &t; // like putting t into a vector but
                // we are actually putting the address of t
                // into a vector pointers of pointers to
                // PrintedMaterials. We'll "say" we are putting
                // t into the vector
                // (that is, pointers to the Base class)
    pmPtr->displayNumPages();

    cout << "=== Task 15 Test ===" << endl;
    vector <PrintedMaterial*> printed;
    printed.push_back(&t);
    printed.push_back(&n);
    printed.push_back(&m);
    //Should be same w/ Task 8 Test
    for (PrintedMaterial* print: printed)
    {
        print->displayNumPages();
    }
}

void displayNumberOfPages (const PrintedMaterial& material){
    material.displayNumPages();
}
