#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
//
// Created by Влад on 23.04.2016.
//

using namespace std;

int index = 0;
bool varWidth = 0;
bool varPrecision = 0;

enum formatLength {
    lengthNull,
    hh,
    h,
    l,
    ll,
    j,
    z,
    t,
    L,
};

enum formatSpecifier {
    d,
    i,
    u,
    o,
    x,
    X,
    f,
    F,
    e,
    E,
    g,
    G,
    a,
    A,
    c,
    s,
    p,
    n,

};

struct formatType {
    bool negative = 0;
    bool positive = 0;
    bool space = 0;
    bool sharp = 0;
    bool zero = 0;
    int width = 0;
    int precision = 0;
    formatLength length;
    formatSpecifier spec;
};

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

template<typename T>
string intToString(formatType prototype, T number) {
    string stringNumber;
    char *charNumber = new char[20];
    string format = "";
    if (prototype.sharp) {
        format = "#" + format;
    }
    switch (prototype.length) {
        case hh: {
            snprintf(charNumber, 20, ("%" + format + "hhd").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case h: {
            snprintf(charNumber, 20, ("%" + format + "hd").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case l: {
            snprintf(charNumber, 20, ("%" + format + "ld").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case ll: {
            snprintf(charNumber, 20, ("%" + format + "lld").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case j: {
            snprintf(charNumber, 20, ("%" + format + "jd").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case z: {
            snprintf(charNumber, 20, ("%" + format + "zd").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case t: {
            snprintf(charNumber, 20, ("%" + format + "td").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        default: {
            snprintf(charNumber, 20, ("%" + format + "d").c_str(), number);
            stringNumber = charNumber;
        }
    }
    return stringNumber;
}

template<typename T>
string toOctHex(formatType prototype, T newNumber, string oldString) {
    string stringNumber;
    string precision = "";
    if (prototype.sharp) {
        precision = "#" + precision;
    }
    char *charNumber = new char[20];
    if (prototype.spec == o) {
        snprintf(charNumber, 20, ("%" + precision + "o").c_str(), newNumber);
        stringNumber = charNumber;
        return stringNumber;
    }
    if (prototype.spec == x) {
        snprintf(charNumber, 20, ("%" + precision + "x").c_str(), newNumber);
        stringNumber = charNumber;
        return stringNumber;
    }
    if (prototype.spec == X) {
        snprintf(charNumber, 20, ("%" + precision + "X").c_str(), newNumber);
        stringNumber = charNumber;
        for (int j = 0; i < stringNumber.length(); j++) {
            if (!isdigit(stringNumber[j])) {
                stringNumber[j] = toupper(stringNumber[j]);
            }
        }
        return stringNumber;
    }
    return oldString;
}

template<typename T>
string unsignedVar(formatType prototype, T number) {
    string stringNumber;
    switch (prototype.length) {
        case hh: {
            unsigned char newNumber = (unsigned char) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case h: {
            unsigned short int newNumber = (unsigned short int) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case l: {
            unsigned long int newNumber = (unsigned long int) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case ll: {
            unsigned long long int newNumber = (unsigned long long int) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case j: {
            uintmax_t newNumber = (uintmax_t) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case z: {
            size_t newNumber = (size_t) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        case t: {
            ptrdiff_t newNumber = (ptrdiff_t) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
            break;
        }
        default: {
            unsigned int newNumber = (unsigned int) number;
            stringNumber = to_string(newNumber);
            stringNumber = toOctHex(prototype, newNumber, stringNumber);
        }
    }
    return stringNumber;
}

template<typename T>
string floatSpec(formatType prototype, T number) {
    string stringNumber;
    char *charNumber = new char[1024];
    string precision = "";
    if (prototype.precision != -1) {
        precision += ".";
        precision += to_string(prototype.precision);
    }
    if (prototype.sharp) {
        precision = "#" + precision;
    }
    switch (prototype.spec) {
        case E: {
            snprintf(charNumber, 1024, ("%" + precision + "E").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case e: {
            snprintf(charNumber, 1024, ("%" + precision + "e").c_str(), number);
            stringNumber = charNumber;
            break;
        }

        case F: {
            snprintf(charNumber, 1024, ("%" + precision + "F").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case f: {

            snprintf(charNumber, 1024, ("%" + precision + "f").c_str(), number);
            stringNumber = charNumber;
            break;
        }

        case A: {
            snprintf(charNumber, 1024, ("%" + precision + "A").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case a: {
            snprintf(charNumber, 1024, ("%" + precision + "a").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case G: {
            snprintf(charNumber, 1024, ("%" + precision + "G").c_str(), number);
            stringNumber = charNumber;
            break;
        }
        case g: {
            snprintf(charNumber, 1024, ("%" + precision + "g").c_str(), number);
            stringNumber = charNumber;
            break;
        }
    }
    return stringNumber;
}

template<typename T>
string floatNumbers(formatType prototype, T number) {
    string stringNumber;
    switch (prototype.length) {
        case L: {
            long double newNumber = (long double) number;
            stringNumber = floatSpec(prototype, newNumber);
            break;
        }
        default: {
            double newNumber = (double) number;
            stringNumber = floatSpec(prototype, newNumber);
        }
    }
    return stringNumber;
}

string writeVar(formatType prototype, string variable) {
    return levelingOfString(prototype, variable);
}

template<typename T>
typename std::enable_if<(std::is_convertible<T, string>::value), string>::type
writeVar(formatType prototype, T variable) {
    string stringNumber = variable;
    return levelingOfString(prototype, stringNumber);
}

template<typename T>
typename std::enable_if<!(std::is_convertible<T, string>::value), string>::type
writeVar(formatType prototype, T variable) {
    string stringNumber;
    if (prototype.spec == d || prototype.spec == i) {
        stringNumber = intToString(prototype, variable);
        return levelingOfString(prototype, stringNumber);
    }
    if (prototype.spec == u || prototype.spec == o || prototype.spec == x || prototype.spec == X) {
        stringNumber = unsignedVar(prototype, variable);
        return levelingOfString(prototype, stringNumber);
    }
    if (prototype.spec == f || prototype.spec == F || prototype.spec == e || prototype.spec == E ||
        prototype.spec == g || prototype.spec == G || prototype.spec == a || prototype.spec == A) {
        stringNumber = floatNumbers(prototype, variable);
        return levelingOfString(prototype, stringNumber);
    }
    if (prototype.spec == c) {
        stringNumber += variable;
        return levelingOfString(prototype, stringNumber);
    }
    if (prototype.spec == s) {
        stringNumber = variable;
        return levelingOfString(prototype, stringNumber);
    }
    if (prototype.spec == p) {

    }
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

template<typename T, typename... Args>
string toString(string const &format, T first, Args ... args) {
    string answer;
    while (true) { //вывод все что перед процентом
        if (format[index] == '%' && format[index + 1] == '%') {
            answer += "%";
            index += 2;
        }
        if (format[index] == '%' && format[index + 1] != '%') {
            break;
        }
        if (format[index] == '\0') {
            answer += format[index];
            return answer;
        }
        answer += format[index];
        index++;
    }
    varPrecision = 0;
    varWidth = 0;
    formatType prototype = readFormat(format);
    if (varPrecision || varWidth) {
        answer += getPW(prototype, format, first, args...);
        return answer;
    }
    answer += writeVar(prototype, first);
    answer += toString(format, args...);
    return answer;
};

template<typename T, typename... Args>
string toString2(formatType prototype, string const &format, T first, Args ... args) {
    string answer;
    answer = writeVar(prototype, first);
    answer += toString(format, args...);
    return answer;
};

string toString2(formatType prototype, string const &format) {
    throw std::invalid_argument("too many arguments");
}

string getPW(formatType prototype, string const &format) {
    throw std::invalid_argument("too many arguments");
}

template<typename T, typename... Args>
typename std::enable_if<!(std::is_convertible<T, int>::value), string>::type
getPW(formatType prototype, string const &format, T first, Args ... args) {
    throw std::invalid_argument("too many arguments");
};

template<typename T, typename... Args>
typename std::enable_if<(std::is_convertible<T, int>::value), string>::type
getPW(formatType prototype, string const &format, T first, Args ... args) {
    string answer;
    if (varWidth) {
        varWidth = 0;
        prototype.width = first;
        if (varPrecision) {
            answer = getPW(prototype, format, args...);
        } else {
            answer = toString2(prototype, format, args...);
        }
        return answer;
    }
    if (varPrecision) {
        varPrecision = 0;
        prototype.precision = first;
        answer = toString2(prototype, format, args...);
        return answer;
    }
};

template<typename ... Args>
string format(string const &format, Args ... args) {
    string answer = toString(format, args...);
    index = 0;
    return answer;
}


