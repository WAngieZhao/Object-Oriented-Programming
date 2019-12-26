//
//  Rational.h
//  rec08_2
//
//  Created by Angie Zhao on 2019/10/25.
//  Copyright © 2019 Angie Zhao. All rights reserved.
//

#ifndef RATIONAL_H
#define RATIONAL_H

namespace CS2124 {
int greatestCommonDivisor(int x, int y);

class Rational {
    friend std::ostream& operator<< (std::ostream& os, const Rational& rhs);
    friend std::istream& operator>> (std::istream& is, Rational& rhs);
    friend bool operator== (const Rational& lhs, const Rational& rhs);
    friend bool operator< (const Rational& lhs, const Rational& rhs);
public:
    Rational(int num = 0, int deno = 1);
    
    Rational& operator+= (const Rational& rhs);
    Rational& operator++();
    Rational operator++ (int dummy);
    
    explicit operator bool();
    
private:
    int numerator;
    int denominator;
    void normalize();
};

Rational operator+ (const Rational& lhs, const Rational& rhs);
bool operator!= (const Rational& lhs, const Rational& rhs);

Rational& operator--(Rational& rhs);
Rational operator-- (Rational& lhs,int dummy);

bool operator<= (const Rational& lhs, const Rational& rhs);
bool operator> (const Rational& lhs, const Rational& rhs);
bool operator>= (const Rational& lhs, const Rational& rhs);
}
#endif /* Rational_h */
