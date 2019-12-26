//
//  hw01.cpp
//  Created by Angie Zhao on 2019/9/9.
//
//  Decrypt File
//  The program will read an encrypted file and decrypt it.
//  The number of rotation given at the start of the file.
//  The program will also reverse the lines in the file.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//decrypt each character and return them
//only change lowercase characters
char decrypt_char(char character, int distance){
    char output;
    if (islower(character)){
        output = character - distance;
        if (output<'a'){
            output += 26;
        }
    } else {
        output = character;
    }
    return output;
}

//modify an encrypted string to unencrypted form
void string_modify(string& str, int distance){
    //using decrypt_char to decrypt every characters in the string
    for (int char_index = 0; char_index < str.size(); ++char_index){
        str[char_index] = decrypt_char(str[char_index], distance);
    }
}

//reverse and print the unencrypted string
int main() {
    ifstream enc("encrypted") ;
    if (!enc) {
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    int distance;
    enc >> distance;
    
    string line;
    vector<string> lines;
    getline(enc, line);
    //read the file line by line and use string_modify to modify each string
    //push modified lines into vector lines
    while (getline(enc, line)){
        string_modify(line, distance);
        lines.push_back(line);
    }
    
    //reverse the lines in the file
    //print the vector from the last item to the first item
    for (size_t i = lines.size(); i>0; --i){
        cout << lines[i-1] << endl;
    }
    enc.close();
    return 0;
}
