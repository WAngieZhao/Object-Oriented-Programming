//
//  polynomial.cpp
//  Created by Angie Zhao on 2019/12/3.
//
//  A class Polynomial for storing and manipulating polynomial expressions.
//  A struct Node used in single linked list for storing the coefficients

#include <iostream>
#include <string>
using namespace std;

#include "polynomial.h"

// Node related methods
// Node's Output Operator<<
ostream& operator<<(ostream& os, Node* nd) {
    if (!nd)
        os << "NULL";
    else
        os << nd->data;
    return os;
}

// Clear/freeup all nodes in the list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

//Add a node at the front
void add_front(Node*& head, int d) {
    head = new Node(d, head);
}

//Return the last Node
Node* last(Node* head) {
    if (!head) return nullptr;
    Node* np = head;
    while (np->next) np = np->next;
    return np;
}

//At a node at the end
void add_end(Node*& head, int d) {
    Node* end = last(head);
    if (!end)
        add_front(head, d);
    else
        end->next = new Node(d);
}

// Polynomial related methods
// Polynomial public methods
// Polynomial constructor
Polynomial::Polynomial(const vector<int>& p) : p_lst(listBuild(p)) {
    cleanup(p_lst);
}

// Delete the last node
bool Polynomial::del_tail() {
    if (p_lst == nullptr){
        return false;
    }
    Node** prev_next = &p_lst;
    Node* curr = p_lst;
    while (curr->next) {
        prev_next = &(*prev_next)->next;
        curr = curr->next;
    }
    delete curr;
    *(prev_next) = nullptr;
    return true;
}

// Takes a x value and evaluates the polynomial
int Polynomial::evaluate(int x) {
    Node* head = p_lst;
    int value = 0;
    int degree = 0;
    while (head) {
        //calculate x^degree
        int term = 1;
        for (int i = 0; i < degree; i++){
            term *= x;
        }
        //calculate value
        value += head->data*term;
        head = head->next;
        degree++;
    }
    return value;
}

// Polynomial's += operator, change polynomial's value
Polynomial Polynomial::operator+=(Polynomial p2) {
    Node* head = p_lst;
    while (head && p2.p_lst) {
        head->data += p2.p_lst->data;
        head = head->next;
        p2.p_lst = p2.p_lst->next;
    }
    while (p2.p_lst) {
        add_end(p_lst, p2.p_lst->data);
        p2.p_lst = p2.p_lst->next;
    }
    cleanup(p_lst);
    return *this;
}

// Polynomial destructor
Polynomial::~Polynomial() {
    while (p_lst) {
        Node* next = p_lst->next;
        delete p_lst;
        p_lst = next;
    }
}

// Polynomial copy constructor
Polynomial::Polynomial(const Polynomial& p) {
    p_lst = duplicate(p.p_lst);
}

// Polynomial assignment operator
Polynomial& Polynomial::operator=(const Polynomial& p) {
    if (this != &p) {
        while (p_lst) {
            Node* next = p_lst->next;
            delete p_lst;
            p_lst = next;
        }
        p_lst = duplicate(p.p_lst);
    }
    return *this;
}

// Polynomial private methods
// Store the polynominal in a list
Node* Polynomial::listBuild(const vector<int>& p) {
    Node* result = nullptr;
    for (size_t index = 0; index < p.size(); ++index) {
        add_front(result, p[index]);
    }
    return result;
}

// Copy a node
Node* Polynomial::duplicate(Node* head) {
    if (!head){
        return nullptr;
    }

    Node* new_head = nullptr; 
    Node* curr = head;
    while (curr) {
        add_end(new_head, curr->data);
        curr = curr->next;
    }
    return new_head;
}

// Clean up the 0 terms
void Polynomial::cleanup(Node*& head) {
    if(p_lst->next){
        while (last(head)->data == 0) {
            del_tail();
        }
    }
}

// Polynomial related methods
// Polynomial's output operator
ostream& operator<<(ostream& os, Polynomial p) {
    string expression = to_string(p.p_lst->data);
    p.p_lst = p.p_lst->next;
    // print last term and x term
    if (p.p_lst) {
        if (p.p_lst->data != 0) {
            if (p.p_lst->data == 1) {
                expression = "x + " + expression;
            } else {
                expression = to_string(p.p_lst->data) + "x + " + expression;
            }
        }
        p.p_lst = p.p_lst->next;
    }

    // print terms w/ degree >=2
    int degree = 2;
    while (p.p_lst) {
        if (p.p_lst->data != 0) {
            if (p.p_lst->data == 1) {
                expression = "x^" + to_string(degree) + " + " + expression;
            }
            else {
                expression = to_string(p.p_lst->data) + "x^"
                    + to_string(degree) + " + " + expression;
            }
        }
        degree++;
        p.p_lst = p.p_lst->next;
    }
    os << expression;
    return os;
}

// Polynomial's + (add) operator
Polynomial operator+(Polynomial p1, Polynomial p2) {
    return p1 += p2;
}

// Polynomial's == (equal to) operator
bool operator==(Polynomial p1, Polynomial p2) {
    while (p1.p_lst || p2.p_lst) {
        if (p1.p_lst->data != p2.p_lst->data) {
            return false;
        }
        p1.p_lst = p1.p_lst->next;
        p2.p_lst = p2.p_lst->next;
    }
    if (p1.p_lst) {
        return false;
    }
    if (p2.p_lst) {
        return false;
    }
    return true;
}

// Polynomial's != (not equal to) operator
bool operator!=(Polynomial p1, Polynomial p2) {
    return !(p1 == p2);
}
