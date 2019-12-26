　//
//  rec08.cpp
//
//  Created by Angie Zhao on 2019/10/25.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

class Rational {
    friend ostream& operator<< (ostream& os, const Rational& rhs){
        os << rhs.numerator << '/' << rhs.denominator;
        return os;
    }
    friend istream& operator>> (istream& is, Rational& rhs){
        int numerator;
        int denominator;
        char slash;
        is >> numerator >> slash >> denominator;
        
        rhs.numerator = numerator;
        rhs.denominator = denominator;
        rhs.normalize();
        return is;
    }
    
    friend bool operator== (const Rational& lhs, const Rational& rhs){
        return ((lhs.numerator == rhs.numerator)
                && (lhs.denominator == rhs.denominator));
    }
    
    friend bool operator< (const Rational& lhs, const Rational& rhs){
        //compare a/b & c/d = compare ad/bd & cb/db;
        // = compare ad & cb
        return (lhs.numerator * rhs.denominator
                < rhs.numerator * lhs.denominator);
    }
    
public:
    Rational(int num = 0, int deno = 1):numerator(num), denominator(deno){
        normalize();
    }
    
    Rational& operator+= (const Rational& rhs){
        //(a/b) + (c/d) = (ad+cb)/bd
        numerator = numerator*rhs.denominator + rhs.numerator*denominator;
        denominator *= rhs.denominator;
        normalize();
        return(*this);
    }
    
    Rational& operator++(){
        *this += 1;
        return(*this);
    }
    
    Rational operator++ (int dummy){
        Rational result(*this);
        *this += 1;
        return result;
    }
    
    explicit operator bool(){
        return numerator != 0;
    }
    
private:
    int numerator;
    int denominator;
    void normalize(){
        int gcd = greatestCommonDivisor(abs(numerator),abs(denominator));
        if (numerator < 0 && denominator < 0){
            numerator = abs(numerator/gcd);
            denominator = abs(denominator/gcd);
        } else if (denominator < 0){
            numerator = (-1)*(numerator/gcd);
            denominator = abs(denominator/gcd);
        } else {
            numerator = numerator/gcd;
            denominator = denominator/gcd;
        }
    }
};

Rational operator+ (const Rational& lhs, const Rational& rhs){
    Rational result;
    result += rhs;
    result += lhs;
    return result;
}

bool operator!= (const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs);
}

//Pre-Decrement
Rational& operator--(Rational& rhs){
    rhs += -1;
    return(rhs);
}
//Post-Decrement
Rational operator-- (Rational& lhs,int dummy){
    Rational result(lhs);
    lhs += -1;
    return result;
}

bool operator<= (const Rational& lhs, const Rational& rhs){
    return ((lhs < rhs) || (lhs == rhs));
}

bool operator> (const Rational& lhs, const Rational& rhs){
    return !(lhs<=rhs);
}

bool operator>= (const Rational& lhs, const Rational& rhs){
    return !(lhs<rhs);
}


int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

int main() {
    Rational twoThirds(2,3);
    cout << twoThirds << endl;

    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;

    // Implement as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
//    cout << "a-- -- = " << (a-- --) << endl;
//    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

}

