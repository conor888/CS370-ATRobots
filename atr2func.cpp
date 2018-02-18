//
// Created by conor on 2/18/2018.
//

#include <iostream>
#include <cmath>
#include "atr2func.h"

using namespace std;

atr2func::atr2func() {

}

static double atr2func::distance(double x1, double y1, double x2, double y2) {
    return abs(sqrt(pow(y1-y2, 2)+pow(x1-x2, 2)));
}