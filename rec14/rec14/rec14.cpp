//
//  rec14.cpp
//
//  Created by Angie Zhao on 2019/12/13.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

//Task 1
bool hasEven(int num) {
    if (num == 0) {
        return true;
    } else if (num == 1) {
        return false;
    } else {
        int digit = num % 2;
        if (digit == 0) {
            return hasEven((num - digit)/2);
        }
        else {
            return !hasEven((num - digit)/2);
        }
    }
}

//Task 2
struct Node {
    Node(int d, Node* n = nullptr): data(d), next(n) {}
    int data;
    Node* next;
};

Node* sum_list(Node* lst1, Node* lst2) {
    Node* curr = nullptr;
    if (lst1 && lst2) {
        curr = new Node(lst1->data + lst2->data);
        curr->next = sum_list(lst1->next, lst2->next);
        return curr;
    } else if ((!lst1) && lst2) {
        curr = new Node(lst2->data);
        curr->next = sum_list(lst1, lst2->next);
        return curr;
    } else if (lst1 && (!lst2)) {
        curr = new Node(lst1->data);
        curr->next = sum_list(lst1->next, lst2);
        return curr;
    } else {
        return curr;
    }
}

void print_list(ostream& os, Node* head) {
    Node* np = head;
    while (np) {
        os << np->data << " ";
        np = np->next;
    }
    os << endl;
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

//Task 3
struct TNode {
    TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
        : data(data), left(left), right(right) {}
    int data;
    TNode *left, *right;
};


int max(TNode* root){
    if (root == nullptr){
        throw invalid_argument("Root is nullptr");
    }

    int max_val = root->data;
    TNode* left = root->left;
    TNode* right = root->right;
    if (left && right){
        int lmax = max(root->left);
        int rmax = max(root->right);
        if (lmax > rmax && lmax > max_val) {max_val = lmax;}
        if (rmax > lmax && lmax > max_val) {max_val = rmax;}
        return max_val;
    } else if (left && (!right)) {
        int lmax = max(left);
        if (lmax > max_val) {max_val = lmax;}
        return max_val;
    } else if ((!left) && right) {
        int rmax = max(right);
        if (rmax > max_val) {max_val = rmax;}
        return max_val;
    }
    return max_val;
}

//Task 4
bool palindrome(char s[], int length) {
    if (length <= 1) {
        return true;
    } else {
        if (s[0] == s[length-1]) {
            return palindrome(++s, length-2);
        } else {
            return false;
        }
    }
}

//Task 5
int towers(int n, char start, char goal, char spare){
    if (n == 0){
        return 0;
    } else {
        return 1 + towers(n-1, start, spare, goal) + towers(n-1, spare, goal, start);
    }
}

//Task 6
void mystery(int n) {
   if (n > 1) {
      cout << 'a';
      mystery(n/2);
      cout << 'b';
      mystery(n/2);
   }
   cout << 'c';
}



int main() {
    // Task 1
    cout << "======Task 1======" << endl;
    cout << "hasEven(7): ";
    if (hasEven(7)){
        cout << "True" << endl;
    }else{
        cout << "False" << endl;;
    }
    cout << "hasEven(-100): ";
    if (hasEven(-100)){
        cout << "True" << endl;
    }else{
        cout << "False" << endl;
    }
    
    // Task 2
    cout << "======Task 2======" << endl;
    Node* lst1 = nullptr;
    add_end(lst1, 1);
    add_end(lst1, 2);
    add_end(lst1, 3);
    cout << "List 1: ";
    print_list(cout,lst1);
    
    Node* lst2 = nullptr;
    add_end(lst2, 4);
    add_end(lst2, 5);
    add_end(lst2, 6);
    add_end(lst2, 7);
    cout << "List 2: ";
    print_list(cout,lst2);
    
    Node* sum = sum_list(lst1, lst2);
    print_list(cout,sum);
    
    // Task 3
    cout << "======Task 3======" << endl;
    cout << "The max value of the tree is : ";
    TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
    cout << max(&f) << endl;
    TNode* error = nullptr;
    try {
        cout << max(error) << endl;
    } catch (invalid_argument e) {
        cerr << "Caught exception: " << e.what() << endl;
    }
    
    //Task 4
    cout << "======Task 4======" << endl;
    char s[] = "racecar";
    if (palindrome(s, 7)) { cout << "Yes!\n"; }
    
    //Task 5
    cout << "======Task 5======" << endl;
    cout << towers(1, 'a', 'b', 'c') << endl;
    cout << towers(2, 'a', 'b', 'c') << endl;
    cout << towers(3, 'a', 'b', 'c') << endl;
    cout << towers(4, 'a', 'b', 'c') << endl;
    cout << towers(5, 'a', 'b', 'c') << endl;
    cout << towers(6, 'a', 'b', 'c') << endl;
    cout << towers(7, 'a', 'b', 'c') << endl;
    cout << towers(8, 'a', 'b', 'c') << endl;
    cout << towers(9, 'a', 'b', 'c') << endl;
    cout << towers(10, 'a', 'b', 'c') << endl;
    
    //Task 6
    cout << "======Task 6======" << endl;
    cout << "Mystery 0: Guess = 'c'; Actual = ";
    mystery(0);
    cout << "\n Mystery 1: Guess = 'c'; Actual = ";
    mystery(1);
    cout << "\n Mystery 2: Guess = 'acbcc'; Actual = ";
    mystery(2);
    cout << "\n Mystery 3: Guess = 'acbcc'; Actual = ";
    mystery(3);
    cout << "\n Mystery 7: Guess = 'a acbcc b acbcc c'; Actual = ";
    //7: a+ 3 +b+ 3 +c
    //3: a+ 1 +b+ 1 +c
    //1: c
    
    //5: a+2+b+2+c
    //2: a+1+b+1+c
    //1: c
    
    //9:a+4+b+4+c
    //4:a+2+b+2+c
    //2: a+1+b+1+c
    //1: c
    
    
    //4: a+2+b+c
    //2: a+1+b+1+c
//    aacbccbacbccc
    mystery(4);
    cout << endl;

}
