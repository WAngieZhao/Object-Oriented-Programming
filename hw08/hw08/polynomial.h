//
//  polynomial.h
//  Created by Angie Zhao on 2019/12/3.
//
//  A class Polynomial for storing and manipulating polynomial expressions.
//  A struct Node used in single linked list for storing the coefficients

#ifndef POLYNOMIAL
#define POLYNOMIAL

#include <iostream>
#include <vector>

//Struct Node, used to build the list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

// Node related methods
// Node's Output Operator<<
std::ostream& operator<<(std::ostream&, Node*);

// Clear/freeup all nodes in the list
void listClear(Node*&);
// Add a node at the front
void add_front(Node*& head, int d);
// Return the last node
Node* last(Node*);
// Add a node at the end
void add_end(Node*&, int);


// Class Polynomial
class Polynomial {
    //Polynomial's output operator
    friend std::ostream& operator<<(std::ostream&, Polynomial);
    //Polynomial's == (equal to) operator
    friend bool operator==(Polynomial, Polynomial);
public:
    // Polynomial constructor
    Polynomial(const std::vector<int>& p = std::vector<int>(1, 0));

    // Delete the last node
    bool del_tail();
    // Takes a x value and evaluates the polynomial
    int evaluate(int);
    // Polynomial's += operator, change polynomial's value
    Polynomial operator+=(Polynomial);
    
    // Polynomial destructor
    ~Polynomial();
    // Polynomial copy constructor
    Polynomial(const Polynomial&);
    // Polynomial assignment operator
    Polynomial& operator=(const Polynomial&);

private:
    Node* p_lst;
    // Store the polynomial in a list
    Node* listBuild(const std::vector<int>&);
    // Copy a node
    Node* duplicate(Node*);
    // Clean up the 0 terms
    void cleanup(Node*&);
};

// Polynomial related methods
// Polynomial's + (add) operator
Polynomial operator+(Polynomial, Polynomial);
// Polynomial's != (not equal to) operator
bool operator!=(Polynomial, Polynomial);

#endif
