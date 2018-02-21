//
// Created by conor on 2/18/2018.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "atr2func.h"

using namespace std;

atr2func::atr2func() {

}

std::string atr2func::ucase(std::string s) {
    int i;
    if((int)s.length() >= 1) {
        for (i = 0; i < s.length(); i++) {
            s[i] = toupper(s[i]);
        }
    }
    return s;
}

std::string atr2func::ltrim(std::string s1) {
    while(((int)s1.length() > 0) && ((s1.compare(0, 1, " ") == 0) ||
            (s1.compare(0, 1, "\b") == 0) || (s1.compare(0, 1, "\t") == 0))) {
        s1.erase(0, 1);
    }
    return s1;
}

std::string atr2func::rtrim(std::string s1) {
    while(((int)s1.length() > 0) && ((s1.compare(s1.length() - 1, 1, " ") == 0) ||
            (s1.compare(s1.length() - 1, 1, "\b") == 0) ||
            (s1.compare(s1.length() - 1, 1, "\t") == 0))) {
        s1.erase(s1.length() - 1, 1);
    }
    return s1;
}

std::string atr2func::btrim(std::string s1) {
    return atr2func::ltrim(atr2func::rtrim(s1));
}

std::string atr2func::lstr(std::string s1, int l) {
    if ((int)s1.length() <= 1) {
        return s1;
    } else {
        s1.erase((unsigned int)(l + 1), (s1.length() - l));
        return s1;
    }
}

std::string atr2func::rstr(std::string s1, int l) {
    if ((int)s1.length() <= 1) {
        return s1;
    } else {
        //s1.erase((s1.length() - l), l);
        return s1;
    }
}

double atr2func::distance(double x1, double y1, double x2, double y2) {
    return abs(sqrt(pow(y1-y2, 2)+pow(x1-x2, 2)));
}



//Our custom functions:
bool atr2func::exists(std::string s) {
    ifstream testopen(s);
    return testopen.good();
}