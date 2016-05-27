#include <stdio.h>
#include <sstream>
#include <iostream>
#include "format.h"


//
// Created by Влад on 23.04.2016.
//

using namespace std;

int main() {
    /*
    arrint[2] = 1;
    cout << format("Characters: %c %c \n", 'a', 65);
    cout << format("Decimals: %d %ld\n", 1977, 650000L);
    cout << format("Preceding with blanks: %10d \n", 1977);
    cout << format("Preceding with blanks: %010d \n", 1977);
    cout << format("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    cout << format("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    cout << format("Width trick: %*d \n", 5, 10);
    cout << format("%s \n", "A string");
    cout << format("%p\n", arrint);


    printf("%p\n", arrint);
    printf("Characters: %c %c \n", 'a', 65);
    printf("Decimals: %d %ld\n", 1977, 650000L);
    printf("Preceding with blanks: %10d \n", 1977);
    printf("Preceding with zeros: %010d \n", 1977);
    printf("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
    printf("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
    printf("Width trick: %*d \n", 5, 10);
    printf("%s \n", "A string");
    */
    int aa = 5;
    int *dd = &aa;
    int cc[3] = {1, 2, 3};
    int d = 5;
    cout << format("%@", cc);
}

