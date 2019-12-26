//
//  rec11.cpp
//
//  Created by Angie Zhao on 2019/11/15.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;


// Node to be used a part of linked list
struct Node {
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
    int data;
    Node* next;
};

void listAddHead(Node*& headPtr, int entry);
Node* listBuild(const vector<int>& vals);
void listClear(Node*& headPtr);

ostream& operator<<(ostream& os, Node* node);
void splice(Node* insert, Node* location);
Node* isSublist(Node* sublist, Node* list);
Node* sharedListBruteForce(Node* lst1, Node* lst2);
Node* sharedListUsingSet(Node* n1, Node* n2);
    
int main(){
    //Part 1:
    cout << "Part One:" << endl;
    Node* list = listBuild({ 5,7,9,1 });
    Node* spliceList = listBuild({ 6,3,2 });
    Node* target1 = list->next;
    cout << "L1: " << list;
    cout << "L2: " << spliceList;
    cout << "Target: " << target1;
    cout << "Splicing L2 at target in L1" << endl;
    splice(spliceList,target1);
    cout << "L1: " << list;
    cout << "L2: " << spliceList;
    
    //Part 2:
    cout << "===================== \n" << "Part two:" << endl;
    Node* target2 = listBuild({1,2,3,2,3,2,4,5,6});
    cout << "Target: " << target2;
    
    Node* match1 = new Node{1, nullptr};//listBuild({1});
    cout << "Attempt match: " << match1;
    cout << isSublist(match1, target2);
    
    Node* match2 = listBuild({3,9});
    cout << "Attempt match: " << match2;
    cout << isSublist(match2, target2);
    
    Node* match3 = listBuild({2,3});
    cout << "Attempt match: " << match3;
    cout << isSublist(match3, target2);
    
    Node* match4 = listBuild({2,4,5,6});
    cout << "Attempt match: " << match4;
    cout << isSublist(match4, target2);
    
    Node* match5 = listBuild({2,3,2,4});
    cout << "Attempt match: " << match5;
    cout << isSublist(match5, target2);
    
    Node* match6 = listBuild({5,6,7});
    cout << "Attempt match: " << match6;
    cout << isSublist(match6, target2);
    
    Node* match7 = new Node{6, nullptr};
    cout << "Attempt match: " << match7;
    cout << isSublist(match7, target2);
    
    //Part 3:
    cout << "===================== \n" << "Part three:" << endl;
    Node* lst1 = listBuild({ 2,3 });
    Node* lst2 = listBuild({ 2,3,3 });
    Node* joint = listBuild({4,5});
    lst1->next->next = joint;
    lst2->next->next->next = joint;
    cout << "L1: " << lst1 << endl;
    cout << "L2: " << lst2 << endl;
    cout << "Shared: " << sharedListUsingSet(lst1,lst2) << endl;
    
    
    return 0;
}

    
// listAddHead: adds a data item to the beginning of a [possibly empty] list
void listAddHead(Node*& headPtr, int entry) {
    headPtr = new Node(entry, headPtr);
}

// listClear: frees up all the nodes in a list
void listClear(Node*& headPtr) {
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
}

// Example of using would be:
//    Node* myList = listBuild({1, 4, 9, 16}); // builds a list of: 1 4 9 16
Node* listBuild(const vector<int>& vals) {
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
}

ostream& operator<<(ostream& os, Node* node) {
    while (node){
        os << node->data << ' ';
        node = node->next;
    }
    os << endl;
    return os;
}

void splice(Node* insert, Node* location){
    Node* locationNext = location->next;
    location->next = insert;
    while (insert->next){
        insert = insert->next;
    }
    insert->next = locationNext;
}

Node* isSublist(Node* sublist, Node* list){
    Node* start = nullptr;
    Node* findSublist = sublist;
    //循环条件：sublist & list did not reach to its end.
    while (list && findSublist){
        //the data of two match
        if (findSublist->data == list->data){
            start = list;
            Node* findList = list;
            //start to match the rest of the list & sublist
            //exist the loop if reach the end of one list
            //or does not match
            while (findSublist && findList){
                //match until does not match
                if (findSublist->data != findList->data){
                    break;
                }
                findSublist = findSublist->next;
                findList = findList->next;
            }
            
            if (!findSublist){
                //if reach the end of sublist = find
                return start;
            } else {
                //did not match, reset the sublist pointer
                start = nullptr;
                findSublist = sublist;
            }
        } else {
            //if data does not match
            //reset start to nullptr & sublist pointer to the start of the sublist
            start = nullptr;
            findSublist = sublist;
        }
        //reach to the next pointer in the lst
        list = list->next;
    }
    
    if (!start){
        cout << "Failed to match";
    }
    return start;
}

Node* sharedListBruteForce(Node* lst1, Node* lst2){
    Node* lst2_ptr = lst2;
    while(lst1){
        while(lst2_ptr){
            if (lst1 == lst2_ptr){
                return lst1;
            }
            lst2_ptr = lst2_ptr->next;
        }
        lst1 = lst1->next;
        lst2_ptr = lst2;
    }

    return nullptr;
}

Node* sharedListUsingSet(Node* n1, Node* n2) {
    unordered_set<Node*> stuff;
    while (n1) {
        stuff.insert(n1);
        n1 = n1->next;
    }
    while (n2) {
        if (stuff.find(n2) != stuff.end()){
            return n2;
        }
        n2 = n2->next;
    }
    return nullptr;
}
