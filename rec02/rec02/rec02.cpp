//
//  rec02.cpp
//
//  Created by Angie Zhao on 2019/9/13.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Hydrocarbon{
    int c,h;
    vector<string> name;
};

void open_file(ifstream& file);
void get_formula(ifstream& file, vector<Hydrocarbon>& CH_lst);
void sort_formula(vector<Hydrocarbon>& CH_lst);
void display(vector<Hydrocarbon>& CH_lst);

int main() {
    ifstream file;
    vector<Hydrocarbon> CH_lst;
    
    open_file(file);
    get_formula(file,CH_lst);
    sort_formula(CH_lst);
    display(CH_lst);

    return 0;
}

//open the file
void open_file(ifstream& file){
    string file_name;
    do{
        cout << "Please enter the file name: ";
        cin >> file_name;
        file.open(file_name);
        if (!file) {
            cerr << "Could not open the file.\n";
            file.clear();
            file.open(file_name);
        }
    } while (!file);
}

//get formula and push it into vector
void get_formula(ifstream& file, vector<Hydrocarbon>& CH_lst){
    char C, H;
    string formula_name;
    int c_num, h_num;
    //read each line
    while (file >> formula_name >> C >> c_num >> H >> h_num){
        Hydrocarbon formula;
        formula.c = c_num;
        formula.h = h_num;
        //test if the same molecular formula already exist
        bool no_repeat = true;
        //if exist, add name to the corresponding name vector
        for (size_t ind = 0; ind < CH_lst.size(); ++ind){
            if ((c_num == CH_lst[ind].c) && (h_num == CH_lst[ind].h)) {
                CH_lst[ind].name.push_back(formula_name);
                no_repeat = false;
            }
        }
        //if this molecular formula do not exist, push it to CH_lst
        if (no_repeat == true){
            formula.name.push_back(formula_name);
            CH_lst.push_back(formula);
        }
    }
}

//sort the formula in the vector inplace
void sort_formula(vector<Hydrocarbon>& CH_lst){
    Hydrocarbon temp1,temp2;
    //Bubble Sort
    for (size_t ind = 0; ind < CH_lst.size(); ++ind){
        for (size_t curr = 0; curr < CH_lst.size()-1; ++curr){
            //compare #C
            if (CH_lst[curr].c > CH_lst[curr+1].c){
                temp1 = CH_lst[curr];
                temp2 = CH_lst[curr+1];
                CH_lst[curr] = temp2;
                CH_lst[curr+1] = temp1;
            } else if (CH_lst[curr].c == CH_lst[curr+1].c){
                //compare #H
                if (CH_lst[curr].h > CH_lst[curr+1].h){
                    temp1 = CH_lst[curr];
                    temp2 = CH_lst[curr+1];
                    CH_lst[curr] = temp2;
                    CH_lst[curr+1] = temp1;
                }
            }
        }
    }
}

//display the result
void display(vector<Hydrocarbon>& CH_lst){
    //print each term in the CH_lst
    for (Hydrocarbon ch:CH_lst){
        cout << 'C' << ch.c << 'H'<< ch.h;
        //print each term in the name vector
        for (string name: ch.name){
            cout << ' ' << name ;
        }
        cout << endl;
    }
}

