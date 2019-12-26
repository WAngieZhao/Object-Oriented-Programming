//
//  rec03.cpp
//
//  Created by Angie Zhao on 2019/9/20.

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

//1. Define a struct
struct Account{
    string name;
    int acc_num;
};


//2. Define a class Account
class Acct{
public:
    Acct(const string& nm = "" , const int number = 0): name(nm), acc_num(number){}
    const string& getName()const {return name;}
    int getNumber()const {return acc_num;}
    int getBalance()const {return balance;}
    friend ostream& operator<< (ostream& os, const Acct& acc);
    
    void deposit(int amt){
        history.emplace_back("Deposit",amt);
        balance += amt;
    }
    
    void withdraw(int amt){
        history.emplace_back("Withdraw",amt);
        if (amt <= balance){
            balance -= amt;
        }
    }
    
private:
    //3. Define a class Transaction
    class Transaction{
    public:
        Transaction(const string& type = "Deposit", const int amt = 0): movement(type), amount(amt){}
        const string& getMovement()const {return movement;}
        int getAmount()const {return amount;}
        friend ostream& operator<< (ostream& os, Transaction transaction) {
            os << "Transaction type: " << transaction.getMovement() << ", Amount: " << transaction.getAmount();
            return os;
        }
    private:
        string movement;
        int amount;
    };
    
    string name;
    int acc_num;
    vector<Transaction> history;
    int balance = 0.0;
};

ostream& operator<< (ostream& os, const Acct& acc){
    //os << "Name: " << acc.getName() << ", Account Number: " << acc.getNumber();
    os << "Name: " << acc.name << ", Account Number: " << acc.acc_num;
    return os;
}


int main() {
    //1.a
    vector<Account> accounts;
    
    ifstream acc_rec("accounts.txt") ;
    if (!acc_rec){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    string nm;
    int number;
    while (acc_rec >> nm >> number){
        Account this_account;
        this_account.name = nm;
        this_account.acc_num = number;
        accounts.push_back(this_account);
    }
    acc_rec.close();
    
    cout << "1.a" << endl;
    for (Account acc:accounts){
        cout << "Name: " << acc.name << ", Account Number: " << acc.acc_num << endl;
    }
    
    //1.b
    accounts.clear();
    acc_rec.open("accounts.txt");
    if (!acc_rec){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    while (acc_rec >> nm >> number){
        Account this_account{nm, number};
        accounts.push_back(this_account);
    }
    
    acc_rec.close();
    
    cout << "1.b" << endl;
    for (Account acc:accounts){
        cout << "Name: " << acc.name << ", Account Number: " << acc.acc_num << endl;
    }
    
    //2.a.1a
    vector<Acct> accts;
    acc_rec.open("accounts.txt");
    if (!acc_rec){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    while (acc_rec >> nm >> number){
        Acct this_account(nm,number);
        accts.push_back(this_account);
    }
    acc_rec.close();
    
    cout << "2.a.1a" << endl;
    for (Acct acc: accts){
        cout << "Name: " << acc.getName() << ", Account Number: " << acc.getNumber() << endl;
    }
    
    //2.1.1b
    accts.clear();
    acc_rec.open("accounts.txt");
    if (!acc_rec){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    while (acc_rec >> nm >> number){
        Acct this_account{nm,number};
        accts.push_back(this_account);
    }
    
    acc_rec.close();
    
    cout << "2.a.1b" << endl;
    for (Acct acc: accts){
        cout << "Name: " << acc.getName() << ", Account Number: " << acc.getNumber() << endl;
    }
    
    //2.b
    cout << "2.b" << endl;
    for (Acct acc: accts){
        cout << acc << endl;
    }
    
    //2.d
    accts.clear();
    acc_rec.open("accounts.txt");
    if (!acc_rec){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    while (acc_rec >> nm >> number){
        accts.push_back(Acct(nm,number));
    }
    
    //2.e
    accts.clear();
    acc_rec.clear();
    acc_rec.seekg(0);
    while (acc_rec >> nm >> number){
        accts.emplace_back(nm,number);
    }
    
    //3.e
    accts.clear();
    cout << "3.e" << endl;
    acc_rec.clear();
    ifstream trans_rec("transactions.txt") ;
    if (!trans_rec){
        cerr << "Could not open the file.\n";
        exit(1);
    }
    
    string word;
    int amount;
    while (trans_rec >> word) {
        //if word is account
        if (word == "Account") {
            trans_rec >> nm >> number;
            accts.emplace_back(nm, number);
            cout << "account name: " << nm << ", account number: " << number << endl;
        }
        //if word is deposit
        else if(word == "Deposit") {
            //identify id number and amount of transaction
            trans_rec >> number >> amount;
            for (int i = 0; i < accts.size(); i++) {
                if (number == accts[i].getNumber()) {
                    accts[i].deposit(amount);
                }
            }
        }
        //if word is withdraw
        else if(word == "Withdraw") {
            //identify id number and amount of transaction
            trans_rec >> number >> amount;
            for (int i = 0; i < accts.size(); i++) {
                if (number == accts[i].getNumber()) {
                    if(amount > accts[i].getBalance()) {
                        cerr << "transaction failed: Insufficient funds" << endl;
                    }
                    else {accts[i].withdraw(amount);}
                }
            }
        }
    }

    trans_rec.close();
}

