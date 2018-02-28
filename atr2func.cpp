//
// Created by conor on 2/18/2018.
//

//#include <iostream>
//#include <fstream>
#include <cmath>
#include <sstream>
//#include <sstream>
#include "atr2func.h"

atr2func::atr2func() {

}

std::string atr2func::hex(int num) {
    std::stringstream ss;
    ss << std::hex << num;
    std::string s(ss.str());
    s = atr2func::ucase(s);
    return s;
}

double atr2func::valuer(std::string i) {
    double s;
    int n;

    s = std::stoi(i);
    return s;
}

long atr2func::value(std::string i) {
    long s;
    int n;

    s = std::stoi(i);
    return s;
}

std::string atr2func::cstrr(double i) {
    std::string s1;

    s1 = std::to_string(i);
    return s1;
}

std::string atr2func::cstr(long i) {
    std::string s1;

    s1 = std::to_string(i);
    return s1;
}

std::string atr2func::zero_pad(long n, long l) {
    std::string s;

    s = atr2func::cstr(n);
    while (s.length() < l) {
        s = "0" + s;
    }

    return s;
}

std::string atr2func::zero_pads(std::string s, long l) {
    std::string s1;

    s1 = s;
    while (s.length() < l) {
        s1 = "0" + s1;
    }

    return s1;
}

std::string atr2func::addfront(std::string b, int l) {
    while (b.length() < l) {
        b = " " + b;
    }
    return b;
}

std::string atr2func::addrear(std::string b, int l) {
    while (b.length() < l) {
        b = b + " ";
    }
    return b;
}

std::string atr2func::ucase(std::string s) {
    int i;
    if((int)s.length() >= 1) {
        for (i = 0; i < s.length(); i++) {
            s[i] = (char)toupper(s[i]);
        }
    }
    return s;
}

std::string atr2func::lcase(std::string s) {
    int i;
    if((int)s.length() >= 1) {
        for (i = 0; i < s.length(); i++) {
            s[i] = (char)tolower(s[i]);
        }
    }
    return s;
}

std::string atr2func::space(uint8_t i) {
    std::string s;
    int k;

    s.clear();
    if (i > 0) {
        for (k = 0; k < i; i++) {
            s = s + " ";
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
        s1.erase((unsigned int)(l + 1), std::string::npos);
        return s1;
    }
}

std::string atr2func::rstr(std::string s1, int l) {
    if ((int)s1.length() <= 1) {
        return s1;
    } else {
        s1.erase(0, (s1.length() - l));
        return s1;
    }
}

void atr2func::make_tables() {
    int i, j, k;

    for (i = 0; i <= 255; i++) {
        atr2func::sint[i] = sin(i / 128 * 3.1415926535897932385);
        atr2func::cost[i] = cos(i / 128 * 3.1415926535897932385);
    }
}

int atr2func::hex2int(std::string s) {
    uint16_t w;
    int i;

    i = 0;
    w = 0;
    while(i < s.length()) {
        i++;
        if (s[i] == '0') {
            w = (uint16_t)((w << 4) | 0);
        } else if (s[i] == '1') {
            w = (uint16_t)((w << 4) | 1);
        } else if (s[i] == '2') {
            w = (uint16_t)((w << 4) | 2);
        } else if (s[i] == '3') {
            w = (uint16_t)((w << 4) | 3);
        } else if (s[i] == '4') {
            w = (uint16_t)((w << 4) | 4);
        } else if (s[i] == '5') {
            w = (uint16_t)((w << 4) | 5);
        } else if (s[i] == '6') {
            w = (uint16_t)((w << 4) | 6);
        } else if (s[i] == '7') {
            w = (uint16_t)((w << 4) | 7);
        } else if (s[i] == '8') {
            w = (uint16_t)((w << 4) | 8);
        } else if (s[i] == '9') {
            w = (uint16_t)((w << 4) | 9);
        } else if (s[i] == 'A') {
            w = (uint16_t)((w << 4) | 10);
        } else if (s[i] == 'B') {
            w = (uint16_t)((w << 4) | 11);
        } else if (s[i] == 'C') {
            w = (uint16_t)((w << 4) | 12);
        } else if (s[i] == 'D') {
            w = (uint16_t)((w << 4) | 13);
        } else if (s[i] == 'E') {
            w = (uint16_t)((w << 4) | 14);
        } else if (s[i] == 'F') {
            w = (uint16_t)((w << 4) | 15);
        } else {
            i = s.length();
        }
    }

    return (int)w;
}

int atr2func::str2int(std::string s) {
    long i, j, k;
    bool neg;

    neg = false;
    s = atr2func::btrim(atr2func::ucase(s));
    if (s.empty()) {
        k = 0;
    } else {
        if (s[0] == '-') {
            neg = true;
            s = atr2func::rstr(s, s.length() - 1);
        }
        k = 0;
        if (atr2func::lstr(s, 2) == "0X") {
            k = atr2func::hex2int(atr2func::rstr(s, s.length() - 2));
        } else if (atr2func::rstr(s, 1) == "H") {
            k = atr2func::hex2int(atr2func::lstr(s, s.length() - 1));
        } else {
            k = atr2func::value(s);
        }
        if (neg) {
            k = 0 - k;
        }
    }
    return k;
}

double atr2func::distance(double x1, double y1, double x2, double y2) {
    return abs(sqrt(pow(y1-y2, 2)+pow(x1-x2, 2)));
}