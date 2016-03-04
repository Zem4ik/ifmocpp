#include "rational.h"


int rational::gcd(int a, int b) const{
    int c;
    while (a != 0) {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

rational::rational(int a) {
    num = a;
    denom = 1;
}

rational::rational(int a, int b) {
    int c = gcd(a, b);
    num = a / c;
    denom = b / c;
}

int rational::getNum() const {
    return num;
}

int rational::getDenom() const {
    return denom;
}

rational rational::operator+(rational const & secondRational) const {
    int newNum;
    int newDenom;
    newDenom = denom * secondRational.getDenom() / gcd(denom, secondRational.getDenom());
    newNum = num * newDenom / denom + secondRational.getNum() * newDenom / secondRational.getDenom();
    rational answer(newNum, newDenom);
    return answer;
}

rational rational::operator-(rational const & secondRational) const {
    int newNum;
    int newDenom;
    newDenom = denom * secondRational.getDenom() / gcd(denom, secondRational.getDenom());
    newNum = num * newDenom / denom - secondRational.getNum() * newDenom / secondRational.getDenom();
    rational answer(newNum, newDenom);
    return answer;
}

rational rational::operator*(const rational &secondRational) const {
    int newNum;
    int newDenom;
    newNum = num * secondRational.getNum();
    newDenom = denom * secondRational.getDenom();
    rational answer(newNum, newDenom);
    return answer;
}

rational rational::operator/(const rational &secondRational) const {
    int newNum;
    int newDenom;
    newNum = num * secondRational.getDenom();
    newDenom = denom * secondRational.getNum();
    rational answer(newNum, newDenom);
    return answer;
}
