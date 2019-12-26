//
//  rec01.cpp
//  rec01
//
//  Created by Angie Zhao on 2019/9/6.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream jab("jabberwocky") ;
    if (!jab) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    string line;
    getline(jab, line);
    jab.seekg(0);
    while (getline(jab, line)) {
        cout << line << endl;
    }

    jab.clear();
    jab.seekg(0);
    string word;
    int count = 0;
    while (jab >> word) {
        ++count;
    }
    
    cout << count << endl;
    jab.close();
    return 0;
}
