//
//  rec13.cpp
//
//  Created by Angie Zhao on 2019/12/6.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;


// 9. Calling the function to print the list
void print_list(const list<int>& lst){
//    for (list <int>::iterator iter=lst.begin(); iter!=lst.end (); iter++){
//        cout << *iter << " ";
//    }
    for (list<int>::const_iterator iter=lst.begin(); iter!=lst.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

// 10. Calling the function that prints the list, using ranged-for
void ranged_print_list(const list<int>& lst){
    for (int item: lst){
        cout << item << " ";
    }
    cout << endl;
}

// 11. Calling the function that, using auto, prints alterate
void print_list_alterate(const list<int>& lst){
    for (auto iter=lst.begin(); iter!=lst.end(); iter++,iter++){
        cout << *iter << " ";
    }
    cout << endl;
}

// 12.  Write a function find that takes a list and value to search for.
list<int>::const_iterator find_item(const list<int>& lst, int value){
    for (list<int>::const_iterator iter=lst.begin(); iter!=lst.end(); iter++) {
        if (value == *iter) {
            return iter;
        }
    }
    return lst.end();
}

// 13.  Write a function find that takes a list and value to search for.
auto find_item_auto(const list<int>& lst, int value){
    for (auto iter=lst.begin(); iter!=lst.end(); iter++) {
        if (value == *iter) {
            return iter;
        }
    }
    return lst.end();
}

// 15. Generic algorithms: find_if, is_even
bool is_even(int num) {return num % 2 == 0;}

// 16. Functor
class is_even_fuctor{
public:
    bool operator() (int num) const {
        return num % 2 == 0;
    }
};

// 19. Implement find as a function for lists
list<int>::iterator ourFind(list<int>::iterator begin, list<int>::iterator end, int num){
    cout << "(Running ourFind function) ";
    for (list<int>::iterator iter=begin; iter!=end; iter++) {
        if (*iter == num) {
            return iter;
        }
    }
    return end;
}

// 20. Implement find as a templated function
template <typename T, typename U>
T ourFind(T begin, T end, U num){
    cout << "(Running ourFind template) ";
    for (T iter = begin; iter != end; iter++) {
        if (*iter == num) {
            return iter;
        }
    }
    return end;
}

int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> vec({1,8,3,5,11,23,18,9});
    for (int item: vec) {cout << item << " ";}

    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> lst (vec.begin(), vec.end());
    for (int item : lst) {cout << item << " ";}
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(vec.begin(), vec.end());
    for (int sorted:vec) {cout << sorted << " ";}
    cout << endl;
    for (int sorted:lst) {cout << sorted << " ";}
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for (size_t i=0; i<vec.size(); i+=2){
        cout << vec[i] << " ";
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
//    for (size_t i=0; i<; lst.size(); i+=2){
//        cout << lst[i] << " ";
//    }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for (vector<int>::iterator iter=vec.begin(); iter<vec.end(); iter+=2){
        cout << *iter << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for (list<int>::iterator iter=lst.begin(); iter!=lst.end(); iter++,iter++){
        cout << *iter << " ";
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    lst.sort();
    for (int sorted:lst) {cout << sorted << " ";}
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    print_list(lst);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    ranged_print_list(lst);
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    print_list_alterate(lst);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    cout << "Test find item 1: " << *find_item(lst,1) << endl;
    cout << "Test find item 77: ";
    if (find_item(lst,77) == lst.end()){
        cout << "Not Found" << endl;
    } else {
        cout << *find_item(lst,77) << endl;
    }
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    cout << "Test find item 1: " << *find_item(lst,1) << endl;
    cout << "Test find item 77: ";
    if (find_item_auto(lst,77) == lst.end()){
        cout << "Not Found" << endl;
    } else {
        cout << *find_item_auto(lst,77) << endl;
    }
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    cout << "Test find item 1: " << *find(lst.begin(),lst.end(),1) << endl;
    list<int>::iterator iter_14 = find(lst.begin(),lst.end(),77);
    cout << "Test find item 77: ";
    if (iter_14 == lst.end()){
        cout << "Not Found" << endl;
    } else {
        cout << *iter_14 << endl;
    }
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    list<int>::iterator iter_15 = find_if(lst.begin(),lst.end(),is_even);
    if (iter_15 != lst.end()) {
        cout << "The first even number: " << *iter_15 << endl;
    }
    else {cout << "No even number" << endl;}
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    list<int>::iterator iter_16 = find_if(lst.begin(),lst.end(),is_even_fuctor());
    if (iter_16 != lst.end()) {
        cout << "The first even number: " << *iter_16 << endl;
    }
    else {cout << "No even number" << endl;}
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    list<int>::iterator iter_17 = find_if(lst.begin(),lst.end(),
                                          [](int num)->bool {return num % 2 == 0;});
    if (iter_17 != lst.end()) {
        cout << "The first even number: " << *iter_17 << endl;
    }
    else {cout << "No even number" << endl;}
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int arr[8];
    copy(lst.begin(), lst.end(), arr);
    for (int item : arr) {cout << item << " ";}
    cout << endl;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    cout << "Test ourFind item 1: " << *ourFind(lst.begin(),lst.end(),1) << endl;
    cout << "Test ourFind item 77: ";
    list<int>::iterator iter_19 = ourFind(lst.begin(),lst.end(),77);
    if (iter_19 == lst.end()){
        cout << "Not Found" << endl;
    } else {
        cout << *iter_19 << endl;
    }
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    cout << "Test Template using vector:" << endl;
    cout << "Test ourFind item 1: " << *ourFind(vec.begin(),vec.end(),1) << endl;
    cout << "Test ourFind item 77: ";
    vector<int>::iterator iter_20_1 = ourFind(vec.begin(),vec.end(),77);
    if (iter_20_1 == vec.end()){
        cout << "Not Found" << endl;
    } else {
        cout << *iter_20_1 << endl;
    }
    cout << "Test Template/Func using vector:" << endl;
    cout << "Test ourFind item 1: " << *ourFind(lst.begin(),lst.end(),1) << endl;
    cout << "Test ourFind item 77: ";
    list<int>::iterator iter_20_2 = ourFind(lst.begin(),lst.end(),77);
    if (iter_20_2 == lst.end()){
        cout << "Not Found" << endl;
    } else {
        cout << *iter_20_2 << endl;
    }
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream ifs("pooh-nopunc.txt");
    if (!ifs) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    vector<string> words;
    string word;
    while (ifs >> word) {
        vector<string>::iterator iter = find(words.begin(), words.end(), word);
        if (iter == words.end()) {
            words.push_back(word);
        }
    }
//    cout << "The distinct words:" << endl;
//    for (string word : words) {
//        cout << word << " ";
//    }
    
    cout << "The number of distinct words: " << words.size() << endl;
    cout << "=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifs.clear();
    ifs.seekg(0, ios::beg);
    
    set<string> words_set;
    while (ifs >> word) {
        words_set.insert(word);
    }
    cout << "The number of distinct words: " <<
        words_set.size() << endl;
    //    cout << "The distinct words:" << endl;
    //    for (string word : words_set) {
    //        cout << word << " ";
    //    }
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifs.clear();
    ifs.seekg(0, ios::beg);
    
    map<string, vector<int>> wordMap;
    int index = 1;
    while (ifs >> word) {
        wordMap[word].push_back(index);
        index++;
    }
    
    for (auto pair : wordMap) {
        cout << pair.first << " postion: ";
        for (int i : pair.second) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << "=======\n";
    
    ifs.close();
}

