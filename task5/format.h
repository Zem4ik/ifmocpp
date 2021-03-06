#ifndef FORMAT_H
#define FORMAT_H

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <typeinfo>
//
// Created by Влад on 23.04.2016.
//

using namespace std;

template<typename ... Args>
string format(string const &format, const Args&... args);

namespace Format {
    extern int indexofFormatString;
    extern bool varWidth;
    extern bool varPrecision;

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
        at,
        none,
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

    //function which takes format specifier of variable from string
    formatType readFormat(string const &format);

    //takes string presentation of variable and change it in compliance with format specifier
    string levelingOfString(formatType prototype, string stringNumber);

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

    string writeVar(formatType prototype, string variable);

    //takes prototype for variable (which can be converted to string) and returns it's string presentation
    template<typename T>
    typename std::enable_if<(std::is_convertible<T, string>::value), string>::type
    writeVar(formatType prototype, T variable) {
        if (prototype.spec == p) {
            string stringNumber;
            char *charNumber = new char[1024];
            snprintf(charNumber, 1024, "%p", variable);
            stringNumber = charNumber;
            return stringNumber;
        }
        if (prototype.spec == s) {
            string stringNumber = variable;
            return levelingOfString(prototype, stringNumber);
        } else {
            throw std::invalid_argument("Invalid argument: string expected");
        }
    }

    //takes prototype for variable (which type is pointer and which can't bo converted to string) and returns it's string presentation
    template<typename T>
    typename std::enable_if<(!(std::is_convertible<T, string>::value) && (std::is_pointer<T>::value)), string>::type
    writeVar(formatType prototype, T variable) {
        string stringNumber;
        char *charNumber = new char[1024];
        snprintf(charNumber, 1024, "%p", variable);
        stringNumber = charNumber;
        return stringNumber;
    }

    //takes prototype for variable (which can't be converted to string and which type isn't pointer) and returns it's string presentation
    template<typename T>
    typename std::enable_if<!(std::is_convertible<T, string>::value) && !(std::is_pointer<T>::value), string>::type
    writeVar(formatType prototype, T variable) {
        string stringNumber;
        if (!is_convertible<T, int>::value) {
            throw std::invalid_argument("Invalid argument");
        }
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
        throw std::invalid_argument("Invalid argument");
    }

    string write_at(nullptr_t variable);

    template<typename T>
    typename std::enable_if<(std::is_convertible<T, string>::value), string>::type
    write_at(T& variable) {
        return variable;
    };

    template <typename T, int n>
    int sizeOfArray(T(&)[n]) { return n; }

    template<typename T>
    typename std::enable_if<(std::is_array<T>::value && !std::is_convertible<T, string>::value), string>::type
    write_at(T& array) {
        string result;
        int n = sizeOfArray(array);
        result = "[";
        for (int i = 0; i < n - 1; i++) {
            result += to_string(array[i]) + ",";
        }
        result += to_string(array[n - 1]) + "]";
        return result;
    };

    template<typename T>
    typename std::enable_if<(!std::is_convertible<T, string>::value && !std::is_array<T>::value && std::is_pointer<T>::value), string>::type
    write_at(T& variable) {
        string result;
        string type = typeid(*variable).name();
        if (type == "i") {
            type = "int";
        }
        if (type == "Ss") {
            type = "std::string";
        }
        if (variable == 0) {
            result += "nullptr<" + type + ">";
        } else {
            result += "ptr<" + type + ">(" + format("%@", *variable) + ")";
        }
        return result;
    };

    template<typename T>
    typename std::enable_if<!std::is_integral<T>::value && !std::is_convertible<T, std::string>::value && !std::is_pointer<T>::value && !std::is_array<T>::value, std::string>::type
    write_at(T& variable){
        throw std::invalid_argument("Invalid argument for %@");
    }

    template<typename T>
    typename std::enable_if<(std::is_integral<T>::value), std::string>::type
    write_at(T& variable){
        return to_string(variable);
    }

    string toString(string const &format);

    //works with format and arguments which were given in function "format" and returns result string
    template<typename T, typename... Args>
    string toString(string const &format, T& first, Args&... args) {
        string answer;
        while (true) {
            if (format[indexofFormatString] == '%' && format[indexofFormatString + 1] == '%') {
                answer += "%";
                indexofFormatString += 2;
            }
            if (format[indexofFormatString] == '%' && format[indexofFormatString + 1] != '%') {
                break;
            }
            if (format[indexofFormatString] == '\0') {
                if (format.size() == 0 || indexofFormatString == format.size()) {
                    throw std::invalid_argument("too much arguments");
                }
                answer += format[indexofFormatString];
                return answer;
            }
            answer += format[indexofFormatString];
            indexofFormatString++;
        }
        varPrecision = 0;
        varWidth = 0;
        formatType prototype = readFormat(format);
        if (varPrecision || varWidth) {
            answer += getPW(prototype, format, first, args...);
            return answer;
        }
        if (prototype.spec == at) {
            answer += write_at(first);
            answer += toString(format, args...);
        } else {
            answer += writeVar(prototype, first);
            answer += toString(format, args...);
        }
        return answer;
    };

    template<typename T, typename... Args>
    string toString2(formatType prototype, string const &format, T first, Args ... args) {
        string answer;
        answer = writeVar(prototype, first);
        answer += toString(format, args...);
        return answer;
    };

    string toString2(formatType prototype, string const &format);

    string getPW(formatType prototype, string const &format);

    template<typename T, typename... Args>
    typename std::enable_if<!(std::is_convertible<T, int>::value), string>::type
    getPW(formatType prototype, string const &format, T first, Args ... args) {
        throw std::invalid_argument("Invalid argument: not int found instead of *");
    };

    //function which takes width or precision if it's needed
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

}
using namespace Format;

//returns a formatted string using the specified format string and arguments

/**
 * format
 *
 * returns formatted string  in compliance with specified format string
 *
 * @param   args
 *          Arguments declared in format string by special symbols.
 *
 * @throws  std::invalid_argument
 *          This error is thrown in the situation when program get an argument with wrong type
 *
 * @throws  std::out_of_range
 *          This error is thrown in the situation when there are not enough arguments
 */
template<typename ... Args>
string format(string const &format, const Args&... args) {
    varWidth = 0;
    varPrecision = 0;
    indexofFormatString = 0;
    string answer = toString(format, args...);
    return answer;
}


#endif