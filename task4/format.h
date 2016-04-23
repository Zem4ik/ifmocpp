#ifndef FORMAT_H
#define FORMAT_H

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
//
// Created by Влад on 23.04.2016.
//

using namespace std;

namespace Format {
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

    void getFlag(formatType *prototype, string const &format);

    int getNumber(string const &format);

    int getPrecision(string const &format);

    formatLength getLength(string const &format);

    formatSpecifier getSpecifier(string const &format);

    formatType readFormat(string const &format);

    string levelingOfString(formatType prototype, string stringNumber);

    template<typename T>
    string intToString(formatType prototype, T number);

    template<typename T>
    string toOctHex(formatType prototype, T newNumber, string oldString);

    template<typename T>
    string unsignedVar(formatType prototype, T number);

    template<typename T>
    string floatSpec(formatType prototype, T number);

    template<typename T>
    string floatNumbers(formatType prototype, T number);

    string writeVar(formatType prototype, string variable);

    template<typename T>
    typename std::enable_if<(std::is_convertible<T, string>::value), string>::type
            writeVar(formatType prototype, T variable);

    template<typename T>
    typename std::enable_if<!(std::is_convertible<T, string>::value), string>::type
            writeVar(formatType prototype, T variable);

    string toString(string const &format);

    template<typename T, typename... Args>
    string toString(string const &format, T first, Args ... args);

    template<typename T, typename... Args>
    string toString2(formatType prototype, string const &format, T first, Args ... args);

    string toString2(formatType prototype, string const &format);

    string getPW(formatType prototype, string const &format);

    template<typename T, typename... Args>
    typename std::enable_if<!(std::is_convertible<T, int>::value), string>::type
            getPW(formatType prototype, string const &format, T first, Args ... args);

    template<typename T, typename... Args>
    typename std::enable_if<(std::is_convertible<T, int>::value), string>::type
            getPW(formatType prototype, string const &format, T first, Args ... args);

}
using namespace Format;

template<typename ... Args>
string format(string const &format, Args ... args) {
    string answer = toString(format, args...);
    index = 0;
    return answer;
}


#endif