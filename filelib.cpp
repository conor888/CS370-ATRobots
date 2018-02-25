//
// Created by conor on 2/25/2018.
//

#include <fstream>
#include "filelib.h"
#include "atr2func.h"

filelib::filelib() {

}

bool filelib::exist(std::string thisfile) {
    std::ifstream testopen(thisfile);
    return testopen.good();
}

std::string filelib::base_name(std::string name) {
    int k;
    std::string s1, s2;

    s1.clear();
    s2.clear();
    k = 1;
    while ((k <= name.length()) && (name[k] != '.')) {
        s1 = s1 + name[k];
        k++;
    }

    return s1;
}

std::string filelib::no_path(std::string fn) {
    int i, k;

    k = 0;
    for (i = fn.length() - 1; i >= 0; i--) {
        if(((fn[i] == '\\') || (fn[i] == ':')) && (k < i)) {
            k = i;
        }
    }
    if (k != 0) {
        return atr2func::rstr(fn, fn.length() - k);
    } else {
        return fn;
    }
}