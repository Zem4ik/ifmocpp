#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "format.h"
//
// Created by Влад on 23.04.2016.
//

using namespace std;

namespace Format {
    int indexofFormatString = 0;
    bool varWidth = 0;
    bool varPrecision = 0;

    void getFlag(formatType *prototype, string const &format) {
        while (true) {
            switch (format[indexofFormatString]) {
                case '-': {
                    prototype->negative = 1;
                    indexofFormatString++;
                    break;
                }
                case '+': {
                    prototype->positive = 1;
                    indexofFormatString++;
                    break;
                }
                case ' ': {
                    prototype->space = 1;
                    indexofFormatString++;
                    break;
                }
                case '#': {
                    prototype->sharp = 1;
                    indexofFormatString++;
                    break;
                }
                case '0': {
                    prototype->zero = 1;
                    indexofFormatString++;
                    break;
                }
                default: {
                    return;
                }
            }
        }
    }

    int getNumber(string const &format) {
        int answer = 0; //Октай докапался до этого места!!!!!!!!!!!!!!!!!!!!!!!
        while (isdigit(format[indexofFormatString])) {
            answer = answer * 10 + (format[indexofFormatString] - '0');
            indexofFormatString++;
        }
        return answer;
    }

    int getPrecision(string const &format) {
        if (format[indexofFormatString] != '.') {
            return -1;
        }
        indexofFormatString++;
        if (format[indexofFormatString] == '*') {
            varPrecision = 1;
            return -1;
        }
        return getNumber(format);
    }

    formatLength getLength(string const &format) {
        if (format[indexofFormatString] == 'h' && format[indexofFormatString + 1] == 'h') {
            indexofFormatString += 2;
            return hh;
        }
        if (format[indexofFormatString] == 'l' && format[indexofFormatString + 1] == 'l') {
            indexofFormatString += 2;
            return ll;
        }
        if (format[indexofFormatString] == 'l') {
            indexofFormatString++;
            return l;
        }
        if (format[indexofFormatString] == 'h') {
            indexofFormatString++;
            return h;
        }
        if (format[indexofFormatString] == 'j') {
            indexofFormatString++;
            return j;
        }
        if (format[indexofFormatString] == 'z') {
            indexofFormatString++;
            return z;
        }
        if (format[indexofFormatString] == 't') {
            indexofFormatString++;
            return t;
        }
        if (format[indexofFormatString] == 'L') {
            indexofFormatString++;
            return L;
        }
        return lengthNull;
    }

    formatSpecifier getSpecifier(string const &format) {
        if (format[indexofFormatString] == 'd') {
            indexofFormatString++;
            return d;
        }
        if (format[indexofFormatString] == 'i') {
            indexofFormatString++;
            return i;
        }
        if (format[indexofFormatString] == 'u') {
            indexofFormatString++;
            return u;
        }
        if (format[indexofFormatString] == 'o') {
            indexofFormatString++;
            return o;
        }
        if (format[indexofFormatString] == 'x') {
            indexofFormatString++;
            return x;
        }
        if (format[indexofFormatString] == 'X') {
            indexofFormatString++;
            return X;
        }
        if (format[indexofFormatString] == 'f') {
            indexofFormatString++;
            return f;
        }
        if (format[indexofFormatString] == 'F') {
            indexofFormatString++;
            return F;
        }
        if (format[indexofFormatString] == 'e') {
            indexofFormatString++;
            return e;
        }
        if (format[indexofFormatString] == 'E') {
            indexofFormatString++;
            return E;
        }
        if (format[indexofFormatString] == 'g') {
            indexofFormatString++;
            return g;
        }
        if (format[indexofFormatString] == 'G') {
            indexofFormatString++;
            return G;
        }
        if (format[indexofFormatString] == 'a') {
            indexofFormatString++;
            return a;
        }
        if (format[indexofFormatString] == 'A') {
            indexofFormatString++;
            return A;
        }
        if (format[indexofFormatString] == 'c') {
            indexofFormatString++;
            return c;
        }
        if (format[indexofFormatString] == 's') {
            indexofFormatString++;
            return s;
        }
        if (format[indexofFormatString] == 'p') {
            indexofFormatString++;
            return p;
        }
        if (format[indexofFormatString] == 'n') {
            indexofFormatString++;
            return n;
        }
    }

    formatType readFormat(string const &format) {
        formatType answer;
        indexofFormatString++;
        getFlag(&answer, format);
        if (format[indexofFormatString] == '*') {
            varWidth = 1;
            indexofFormatString++;
        } else {
            answer.width = getNumber(format);
        }
        answer.precision = getPrecision(format);
        answer.length = getLength(format);
        answer.spec = getSpecifier(format);
        return answer;
    }

    string levelingOfString(formatType prototype, string stringNumber) {
        string answer;
        bool temp = prototype.spec == d || prototype.spec == i || prototype.spec == f || prototype.spec == F;
        if (prototype.positive && prototype.spec != s && temp) {
            if (stringNumber[0] != '-') {
                stringNumber = "+" + stringNumber;
            }
        }

        int length = stringNumber.length();
        if (stringNumber[0] == '+' || stringNumber[0] == '-') {
            length--;
        }

        if (prototype.precision > length) {
            if (stringNumber[0] == '+' || stringNumber[0] == '-') {
                answer += stringNumber[0];
            }
            for (int j = 0; j < prototype.precision - length; j++) {
                answer = answer + "0";
            }
            for (int j = 0; j < stringNumber.length(); j++) {
                if (stringNumber[j] == '+' || stringNumber[j] == '-') {
                    continue;
                }
                answer += stringNumber[j];
            }
        } else {
            answer = stringNumber;
        }

        if (prototype.width > answer.length()) {
            if (prototype.negative) {
                for (; 0 < prototype.width - answer.length();) {
                    answer = answer + " ";
                }
            }
            if (prototype.zero && prototype.spec != s) {
                temp = prototype.spec == d || prototype.spec == i || prototype.spec == o ||
                            prototype.spec == u || prototype.spec == x || prototype.spec == X;
                if (!temp || prototype.precision == -1) {
                    if (0 < prototype.width - answer.length()) {
                        if (stringNumber[0] == '+' || stringNumber[0] == '-') {
                            answer = stringNumber[0];
                        } else {
                            answer = "";
                        }
                        for (int j = 0; j < prototype.width - stringNumber.length(); j++) {
                            answer = answer + "0";
                        }
                        for (int j = 0; j < stringNumber.length(); j++) {
                            if (stringNumber[j] == '+' || stringNumber[j] == '-') {
                                continue;
                            }
                            answer += stringNumber[j];
                        }
                    }
                }
            }
            while (0 < (int) (prototype.width - answer.length())) {
                answer = " " + answer;
            }
        }

        if (prototype.space) {
            if (stringNumber[0] != '+' && stringNumber[0] != '-' && answer[0] != ' ') {
                answer = " " + answer;
            }
        }
        return answer;
    }

    string writeVar(formatType prototype, string variable) {
        return levelingOfString(prototype, variable);
    }

    string toString(string const &format) {
        string answer;
        while (true) { //вывод все что перед процентом
            if (format[indexofFormatString] == '%' && format[indexofFormatString + 1] == '%') {
                answer += "%";
                indexofFormatString += 2;
            }
            if (format[indexofFormatString] == '%' && format[indexofFormatString + 1] != '%') {
                throw std::invalid_argument("too many arguments");
            }
            if (format[indexofFormatString] == '\0') {
                return answer;
            }
            answer += format[indexofFormatString];
            indexofFormatString++;
        }
    }

    string toString2(formatType prototype, string const &format) {
        throw std::invalid_argument("too many arguments");
    }

    string getPW(formatType prototype, string const &format) {
        throw std::invalid_argument("too many arguments");
    }
}