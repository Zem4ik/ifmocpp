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
    void getFlag(formatType *prototype, string const &format) {
        while (true) {
            switch (format[index]) {
                case '-': {
                    prototype->negative = 1;
                    index++;
                    break;
                }
                case '+': {
                    prototype->positive = 1;
                    index++;
                    break;
                }
                case ' ': {
                    prototype->space = 1;
                    index++;
                    break;
                }
                case '#': {
                    prototype->sharp = 1;
                    index++;
                    break;
                }
                case '0': {
                    prototype->zero = 1;
                    index++;
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
        while (isdigit(format[index])) {
            answer = answer * 10 + (format[index] - '0');
            index++;
        }
        return answer;
    }

    int getPrecision(string const &format) {
        if (format[index] != '.') {
            return -1;
        }
        index++;
        if (format[index] == '*') {
            varPrecision = 1;
            return -1;
        }
        return getNumber(format);
    }

    formatLength getLength(string const &format) {
        if (format[index] == 'h' && format[index + 1] == 'h') {
            index += 2;
            return hh;
        }
        if (format[index] == 'l' && format[index + 1] == 'l') {
            index += 2;
            return ll;
        }
        if (format[index] == 'l') {
            index++;
            return l;
        }
        if (format[index] == 'h') {
            index++;
            return h;
        }
        if (format[index] == 'j') {
            index++;
            return j;
        }
        if (format[index] == 'z') {
            index++;
            return z;
        }
        if (format[index] == 't') {
            index++;
            return t;
        }
        if (format[index] == 'L') {
            index++;
            return L;
        }
        return lengthNull;
    }

    formatSpecifier getSpecifier(string const &format) {
        if (format[index] == 'd') {
            index++;
            return d;
        }
        if (format[index] == 'i') {
            index++;
            return i;
        }
        if (format[index] == 'u') {
            index++;
            return u;
        }
        if (format[index] == 'o') {
            index++;
            return o;
        }
        if (format[index] == 'x') {
            index++;
            return x;
        }
        if (format[index] == 'X') {
            index++;
            return X;
        }
        if (format[index] == 'f') {
            index++;
            return f;
        }
        if (format[index] == 'F') {
            index++;
            return F;
        }
        if (format[index] == 'e') {
            index++;
            return e;
        }
        if (format[index] == 'E') {
            index++;
            return E;
        }
        if (format[index] == 'g') {
            index++;
            return g;
        }
        if (format[index] == 'G') {
            index++;
            return G;
        }
        if (format[index] == 'a') {
            index++;
            return a;
        }
        if (format[index] == 'A') {
            index++;
            return A;
        }
        if (format[index] == 'c') {
            index++;
            return c;
        }
        if (format[index] == 's') {
            index++;
            return s;
        }
        if (format[index] == 'p') {
            index++;
            return p;
        }
        if (format[index] == 'n') {
            index++;
            return n;
        }
    }

    formatType readFormat(string const &format) {
        formatType answer;
        index++;
        getFlag(&answer, format);
        if (format[index] == '*') {
            varWidth = 1;
            index++;
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
        if (prototype.positive && prototype.spec != s) {
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
                bool temp = prototype.spec == d || prototype.spec == i || prototype.spec == o ||
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
            if (stringNumber[0] != '+' && stringNumber[0] != '-') {
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
            if (format[index] == '%' && format[index + 1] == '%') {
                answer += "%";
                index += 2;
            }
            if (format[index] == '%' && format[index + 1] != '%') {
                throw std::invalid_argument("too many arguments");
            }
            if (format[index] == '\0') {
                return answer;
            }
            answer += format[index];
            index++;
        }
    }

    string toString2(formatType prototype, string const &format) {
        throw std::invalid_argument("too many arguments");
    }

    string getPW(formatType prototype, string const &format) {
        throw std::invalid_argument("too many arguments");
    }
}