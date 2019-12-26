//
//  Rational.cpp
//  rec08_2
//
//  Created by Angie Zhao on 2019/10/25.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#include <iostream>
#include "Rational.h"
using namespace std;

namespace CS2124 {
    //friend methods
    ostream& operator<< (ostream& os, const Rational& rhs){
            os << rhs.numerator << '/' << rhs.denominator;
            return os;
        }
    istream& operator>> (istream& is, Rational& rhs){
        int numerator;
        int denominator;
        char slash;
        is >> numerator >> slash >> denominator;
        
        rhs.numerator = numerator;
        rhs.denominator = denominator;
        rhs.normalize();
        return is;
    }
    
    bool operator== (const Rational& lhs, const Rational& rhs){
        return ((lhs.numerator == rhs.numerator)
                && (lhs.denominator == rhs.denominator));
    }
    
    bool operator< (const Rational& lhs, const Rational& rhs){
        //compare a/b & c/d = compare ad/bd & cb/db;
        // = compare ad & cb
        return (lhs.numerator * rhs.denominator
                < rhs.numerator * lhs.denominator);
    }
    
    //public method
    Rational::Rational(int num, int deno):numerator(num), denominator(deno){
        normalize();
    }
    
    Rational& Rational::operator+= (const Rational& rhs){
        //(a/b) + (c/d) = (ad+cb)/bd
        numerator = numerator*rhs.denominator + rhs.numerator*denominator;
        denominator *= rhs.denominator;
        normalize();
        return(*this);
    }
    
    Rational& Rational::operator++(){
        *this += 1;
        return(*this);
    }
    
    Rational Rational::operator++ (int dummy){
        Rational result(*this);
        *this += 1;
        return result;
    }
    
    Rational::operator bool(){
        return numerator != 0;
    }
    
    //private methods
    void Rational::normalize(){
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
    
    //outside methods
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
}
