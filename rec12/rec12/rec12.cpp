//
//  rec12.cpp
//
//  Created by Angie Zhao on 2019/11/22.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <cstdlib>
#include <iostream>
using namespace std;

class List{
    friend ostream& operator<<(ostream& os, const List& lst) {
        Node* curr = lst.header->next;
        while (curr != lst.trailer) {
            os << curr->data << " ";
            curr = curr->next;
        }
        return os;
    }

public:
    List():header(nullptr), lst_size(0), trailer(nullptr) {
        header = new Node(0);
        trailer = new Node(0);
        header->next = trailer;
        trailer->prev = header;
    }
    
    //Task 1
    const int size() const{
        return lst_size;
    }
    
    int front() const{
        if (lst_size!= 0){
            return header->next->data;
        }else{
            return -1;
        }
    }
    
    int& front(){
        return header->next->data;
    }
    
    int back() const{
        return trailer->prev->data;
    }
    
    int& back() {
        return trailer->prev->data;
    }
    
    void push_back(int data){
        Node* new_node = new Node(data);
        Node* last = trailer->prev;
        new_node->next = trailer;
        new_node->prev = last;
        last->next = new_node;
        trailer->prev = new_node;
        
        lst_size += 1;
    }
    
    int pop_back(){
        Node* delete_node = trailer->prev;
        Node* new_last = delete_node->prev;
        int data = delete_node->data;
        if(lst_size>=1){
            trailer->prev = new_last;
            new_last->next = trailer;
            delete delete_node;
//            delete_node = nullptr;
            lst_size -= 1;
        }
        return data;
    }
    
    //Task 2
    void push_front(int data){
        Node* new_node = new Node(data);
        Node* first = header->next;
        new_node->next = first;
        new_node->prev = header;
        first->prev = new_node;
        header->next = new_node;
        lst_size += 1;
    }
    
    int pop_front(){
        Node* delete_node = header->next;
        Node* new_first = delete_node->next;
        int data = delete_node->data;
        if(lst_size >= 1){
            header->next = new_first;
            new_first->prev = header;
            lst_size -= 1;
            delete delete_node;
//            delete_node = nullptr;
        }
        return data;
    }
    
    //Task 3
    void clear(){
        Node* curr = header->next;
        while (curr != trailer) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
        header->next = trailer;
        trailer->prev = header;
        lst_size = 0;
    }
    
    //Task 4
    int operator[](size_t index) const{
        Node* curr = header->next;
        for (size_t i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }
    
    int& operator[](size_t index){
        Node* curr = header->next;
        for (size_t i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->data;
    }
    

private:
    struct Node {
        Node(int d) : data(d), next(nullptr), prev(nullptr) {}
        int data;
        Node* next;
        Node* prev;
    };
    Node* header;
    Node* trailer;
    int lst_size;
    
public:
    //Task 5
    class iterator {
        friend bool operator!=(const iterator& rhs, const iterator& lhs) {
            return rhs.nptr != lhs.nptr;
        }
        friend bool operator==(const iterator& rhs, const iterator& lhs) {
            return rhs.nptr == lhs.nptr;
        }
        friend List;
    public:
        iterator(Node* head) : nptr(head) {}

        iterator& operator++() {
            nptr = nptr->next;
            return *this;
        }

        iterator& operator--() {
            nptr = nptr->prev;
            return *this;
        }

        int& operator*() { return nptr->data; }
        int operator*() const { return nptr->data; }

    private:
        Node* nptr;
    };
    
    //pointing to the first item
    iterator begin() {return iterator(header->next);}
    //just past the last item
    iterator end() {return iterator(trailer);}
    
    //Task 6
    iterator insert(iterator iter, int data){
        Node* new_node = new Node(data);
//        Node* before = iter.nptr->prev;
//        Node* after = iter.nptr;
        new_node->next = iter.nptr;
        new_node->prev = iter.nptr->prev;
        iter.nptr->prev->next = new_node;
        iter.nptr->prev = new_node;
        lst_size += 1;
        iter.nptr = new_node;
        return iter;
    }
    
    //Task 7
    iterator erase(const iterator& iter){
        Node* erase_node = iter.nptr;
        Node* before = erase_node->prev;
        Node* after = erase_node->next;
        before->next = after;
        after->prev = before;
        
        delete erase_node;
//        erase_node = nullptr;
        lst_size -= 1;
        return iterator(after);
    }
    
};






// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}

// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

//// Task 8
//void doNothing(List aList) {
//    cout << "In doNothing\n";
//    printListInfo(aList);
//    cout << endl;
//    cout << "Leaving doNothing\n";
//}

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);


    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";

    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";
    
    

    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

//    // Task 8
//    cout << "\n------Task Eight------\n";
//    cout << "Copy control\n";
//    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
//    myList.clear();
//    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
//    printListInfo(myList);
//    cout << "Calling doNothing(myList)\n";
//    doNothing(myList);
//    cout << "Back from doNothing(myList)\n";
//    printListInfo(myList);
//
//    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
//    List listTwo;
//    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
//    printListInfo(listTwo);
//    cout << "listTwo = myList\n";
//    listTwo = myList;
//    cout << "myList: ";
//    printListInfo(myList);
//    cout << "listTwo: ";
//    printListInfo(listTwo);
//    cout << "===================\n";
}

//    //Task 8
//    List(const List& rhs){
//        header = new Node(0);
//        trailer = new Node(0);
//
//        if (rhs.size() == 0){
//            header->next = trailer;
//            trailer->prev = header;
//        }else{
//            for (int i = 0; i < lst_size; ++i){
//                push_back(rhs[i]);
//            }
//        }
//    }
//
//    ~List(){
//        this->clear();
//        delete header;
//        delete trailer;
//
//    }
//
//    List& operator=(const List& rhs){
//        if (this != &rhs){
//            this->~List();
//            List curr(rhs);
//        }
//        return *this;
//    }
